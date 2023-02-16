//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee8021q/Ieee8021qTagHeader.msg.
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
#include "Ieee8021qTagHeader_m.h"

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

Register_Class(Ieee8021qTagTpidHeader)

Ieee8021qTagTpidHeader::Ieee8021qTagTpidHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

Ieee8021qTagTpidHeader::Ieee8021qTagTpidHeader(const Ieee8021qTagTpidHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee8021qTagTpidHeader::~Ieee8021qTagTpidHeader()
{
}

Ieee8021qTagTpidHeader& Ieee8021qTagTpidHeader::operator=(const Ieee8021qTagTpidHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee8021qTagTpidHeader::copy(const Ieee8021qTagTpidHeader& other)
{
    this->tpid = other.tpid;
    this->pcp = other.pcp;
    this->dei = other.dei;
    this->vid = other.vid;
}

void Ieee8021qTagTpidHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->tpid);
    doParsimPacking(b,this->pcp);
    doParsimPacking(b,this->dei);
    doParsimPacking(b,this->vid);
}

void Ieee8021qTagTpidHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->tpid);
    doParsimUnpacking(b,this->pcp);
    doParsimUnpacking(b,this->dei);
    doParsimUnpacking(b,this->vid);
}

uint16_t Ieee8021qTagTpidHeader::getTpid() const
{
    return this->tpid;
}

void Ieee8021qTagTpidHeader::setTpid(uint16_t tpid)
{
    handleChange();
    this->tpid = tpid;
}

uint8_t Ieee8021qTagTpidHeader::getPcp() const
{
    return this->pcp;
}

void Ieee8021qTagTpidHeader::setPcp(uint8_t pcp)
{
    handleChange();
    this->pcp = pcp;
}

bool Ieee8021qTagTpidHeader::getDei() const
{
    return this->dei;
}

void Ieee8021qTagTpidHeader::setDei(bool dei)
{
    handleChange();
    this->dei = dei;
}

uint16_t Ieee8021qTagTpidHeader::getVid() const
{
    return this->vid;
}

void Ieee8021qTagTpidHeader::setVid(uint16_t vid)
{
    handleChange();
    this->vid = vid;
}

class Ieee8021qTagTpidHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tpid,
        FIELD_pcp,
        FIELD_dei,
        FIELD_vid,
    };
  public:
    Ieee8021qTagTpidHeaderDescriptor();
    virtual ~Ieee8021qTagTpidHeaderDescriptor();

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

Register_ClassDescriptor(Ieee8021qTagTpidHeaderDescriptor)

Ieee8021qTagTpidHeaderDescriptor::Ieee8021qTagTpidHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee8021qTagTpidHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee8021qTagTpidHeaderDescriptor::~Ieee8021qTagTpidHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee8021qTagTpidHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee8021qTagTpidHeader *>(obj)!=nullptr;
}

const char **Ieee8021qTagTpidHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee8021qTagTpidHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee8021qTagTpidHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee8021qTagTpidHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tpid
        FD_ISEDITABLE,    // FIELD_pcp
        FD_ISEDITABLE,    // FIELD_dei
        FD_ISEDITABLE,    // FIELD_vid
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee8021qTagTpidHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tpid",
        "pcp",
        "dei",
        "vid",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee8021qTagTpidHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tpid") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "pcp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dei") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "vid") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee8021qTagTpidHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_tpid
        "uint8_t",    // FIELD_pcp
        "bool",    // FIELD_dei
        "uint16_t",    // FIELD_vid
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee8021qTagTpidHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee8021qTagTpidHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee8021qTagTpidHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee8021qTagTpidHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee8021qTagTpidHeader'", field);
    }
}

const char *Ieee8021qTagTpidHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee8021qTagTpidHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tpid: return ulong2string(pp->getTpid());
        case FIELD_pcp: return ulong2string(pp->getPcp());
        case FIELD_dei: return bool2string(pp->getDei());
        case FIELD_vid: return ulong2string(pp->getVid());
        default: return "";
    }
}

void Ieee8021qTagTpidHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tpid: pp->setTpid(string2ulong(value)); break;
        case FIELD_pcp: pp->setPcp(string2ulong(value)); break;
        case FIELD_dei: pp->setDei(string2bool(value)); break;
        case FIELD_vid: pp->setVid(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagTpidHeader'", field);
    }
}

omnetpp::cValue Ieee8021qTagTpidHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tpid: return (omnetpp::intval_t)(pp->getTpid());
        case FIELD_pcp: return (omnetpp::intval_t)(pp->getPcp());
        case FIELD_dei: return pp->getDei();
        case FIELD_vid: return (omnetpp::intval_t)(pp->getVid());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee8021qTagTpidHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee8021qTagTpidHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tpid: pp->setTpid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_pcp: pp->setPcp(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_dei: pp->setDei(value.boolValue()); break;
        case FIELD_vid: pp->setVid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagTpidHeader'", field);
    }
}

const char *Ieee8021qTagTpidHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee8021qTagTpidHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee8021qTagTpidHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagTpidHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagTpidHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagTpidHeader'", field);
    }
}

Register_Class(Ieee8021qTagEpdHeader)

Ieee8021qTagEpdHeader::Ieee8021qTagEpdHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

Ieee8021qTagEpdHeader::Ieee8021qTagEpdHeader(const Ieee8021qTagEpdHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee8021qTagEpdHeader::~Ieee8021qTagEpdHeader()
{
}

Ieee8021qTagEpdHeader& Ieee8021qTagEpdHeader::operator=(const Ieee8021qTagEpdHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee8021qTagEpdHeader::copy(const Ieee8021qTagEpdHeader& other)
{
    this->pcp = other.pcp;
    this->dei = other.dei;
    this->vid = other.vid;
    this->typeOrLength = other.typeOrLength;
}

void Ieee8021qTagEpdHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->pcp);
    doParsimPacking(b,this->dei);
    doParsimPacking(b,this->vid);
    doParsimPacking(b,this->typeOrLength);
}

void Ieee8021qTagEpdHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->pcp);
    doParsimUnpacking(b,this->dei);
    doParsimUnpacking(b,this->vid);
    doParsimUnpacking(b,this->typeOrLength);
}

uint8_t Ieee8021qTagEpdHeader::getPcp() const
{
    return this->pcp;
}

void Ieee8021qTagEpdHeader::setPcp(uint8_t pcp)
{
    handleChange();
    this->pcp = pcp;
}

bool Ieee8021qTagEpdHeader::getDei() const
{
    return this->dei;
}

void Ieee8021qTagEpdHeader::setDei(bool dei)
{
    handleChange();
    this->dei = dei;
}

uint16_t Ieee8021qTagEpdHeader::getVid() const
{
    return this->vid;
}

void Ieee8021qTagEpdHeader::setVid(uint16_t vid)
{
    handleChange();
    this->vid = vid;
}

uint16_t Ieee8021qTagEpdHeader::getTypeOrLength() const
{
    return this->typeOrLength;
}

void Ieee8021qTagEpdHeader::setTypeOrLength(uint16_t typeOrLength)
{
    handleChange();
    this->typeOrLength = typeOrLength;
}

class Ieee8021qTagEpdHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_pcp,
        FIELD_dei,
        FIELD_vid,
        FIELD_typeOrLength,
    };
  public:
    Ieee8021qTagEpdHeaderDescriptor();
    virtual ~Ieee8021qTagEpdHeaderDescriptor();

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

Register_ClassDescriptor(Ieee8021qTagEpdHeaderDescriptor)

Ieee8021qTagEpdHeaderDescriptor::Ieee8021qTagEpdHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee8021qTagEpdHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee8021qTagEpdHeaderDescriptor::~Ieee8021qTagEpdHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee8021qTagEpdHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee8021qTagEpdHeader *>(obj)!=nullptr;
}

const char **Ieee8021qTagEpdHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee8021qTagEpdHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee8021qTagEpdHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee8021qTagEpdHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_pcp
        FD_ISEDITABLE,    // FIELD_dei
        FD_ISEDITABLE,    // FIELD_vid
        FD_ISEDITABLE,    // FIELD_typeOrLength
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee8021qTagEpdHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pcp",
        "dei",
        "vid",
        "typeOrLength",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee8021qTagEpdHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "pcp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "dei") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "vid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "typeOrLength") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee8021qTagEpdHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_pcp
        "bool",    // FIELD_dei
        "uint16_t",    // FIELD_vid
        "uint16_t",    // FIELD_typeOrLength
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee8021qTagEpdHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee8021qTagEpdHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee8021qTagEpdHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee8021qTagEpdHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee8021qTagEpdHeader'", field);
    }
}

const char *Ieee8021qTagEpdHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee8021qTagEpdHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        case FIELD_pcp: return ulong2string(pp->getPcp());
        case FIELD_dei: return bool2string(pp->getDei());
        case FIELD_vid: return ulong2string(pp->getVid());
        case FIELD_typeOrLength: return ulong2string(pp->getTypeOrLength());
        default: return "";
    }
}

void Ieee8021qTagEpdHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        case FIELD_pcp: pp->setPcp(string2ulong(value)); break;
        case FIELD_dei: pp->setDei(string2bool(value)); break;
        case FIELD_vid: pp->setVid(string2ulong(value)); break;
        case FIELD_typeOrLength: pp->setTypeOrLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagEpdHeader'", field);
    }
}

omnetpp::cValue Ieee8021qTagEpdHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        case FIELD_pcp: return (omnetpp::intval_t)(pp->getPcp());
        case FIELD_dei: return pp->getDei();
        case FIELD_vid: return (omnetpp::intval_t)(pp->getVid());
        case FIELD_typeOrLength: return (omnetpp::intval_t)(pp->getTypeOrLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee8021qTagEpdHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee8021qTagEpdHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        case FIELD_pcp: pp->setPcp(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_dei: pp->setDei(value.boolValue()); break;
        case FIELD_vid: pp->setVid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_typeOrLength: pp->setTypeOrLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagEpdHeader'", field);
    }
}

const char *Ieee8021qTagEpdHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee8021qTagEpdHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee8021qTagEpdHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8021qTagEpdHeader *pp = omnetpp::fromAnyPtr<Ieee8021qTagEpdHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8021qTagEpdHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

