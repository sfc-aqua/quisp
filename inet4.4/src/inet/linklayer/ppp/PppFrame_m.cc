//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ppp/PppFrame.msg.
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
#include "PppFrame_m.h"

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

Register_Class(PppHeader)

PppHeader::PppHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(PPP_HEADER_LENGTH);

}

PppHeader::PppHeader(const PppHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

PppHeader::~PppHeader()
{
}

PppHeader& PppHeader::operator=(const PppHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void PppHeader::copy(const PppHeader& other)
{
    this->flag = other.flag;
    this->address = other.address;
    this->control = other.control;
    this->protocol = other.protocol;
}

void PppHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->flag);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->control);
    doParsimPacking(b,this->protocol);
}

void PppHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->flag);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->control);
    doParsimUnpacking(b,this->protocol);
}

short PppHeader::getFlag() const
{
    return this->flag;
}

void PppHeader::setFlag(short flag)
{
    handleChange();
    this->flag = flag;
}

short PppHeader::getAddress() const
{
    return this->address;
}

void PppHeader::setAddress(short address)
{
    handleChange();
    this->address = address;
}

short PppHeader::getControl() const
{
    return this->control;
}

void PppHeader::setControl(short control)
{
    handleChange();
    this->control = control;
}

int PppHeader::getProtocol() const
{
    return this->protocol;
}

void PppHeader::setProtocol(int protocol)
{
    handleChange();
    this->protocol = protocol;
}

class PppHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flag,
        FIELD_address,
        FIELD_control,
        FIELD_protocol,
    };
  public:
    PppHeaderDescriptor();
    virtual ~PppHeaderDescriptor();

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

Register_ClassDescriptor(PppHeaderDescriptor)

PppHeaderDescriptor::PppHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PppHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

PppHeaderDescriptor::~PppHeaderDescriptor()
{
    delete[] propertyNames;
}

bool PppHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PppHeader *>(obj)!=nullptr;
}

const char **PppHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PppHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PppHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int PppHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_flag
        FD_ISEDITABLE,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_control
        FD_ISEDITABLE,    // FIELD_protocol
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *PppHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flag",
        "address",
        "control",
        "protocol",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int PppHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "control") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "protocol") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *PppHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_flag
        "short",    // FIELD_address
        "short",    // FIELD_control
        "int",    // FIELD_protocol
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **PppHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *PppHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PppHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PppHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PppHeader'", field);
    }
}

const char *PppHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PppHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        case FIELD_flag: return long2string(pp->getFlag());
        case FIELD_address: return long2string(pp->getAddress());
        case FIELD_control: return long2string(pp->getControl());
        case FIELD_protocol: return long2string(pp->getProtocol());
        default: return "";
    }
}

void PppHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        case FIELD_flag: pp->setFlag(string2long(value)); break;
        case FIELD_address: pp->setAddress(string2long(value)); break;
        case FIELD_control: pp->setControl(string2long(value)); break;
        case FIELD_protocol: pp->setProtocol(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppHeader'", field);
    }
}

omnetpp::cValue PppHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        case FIELD_flag: return pp->getFlag();
        case FIELD_address: return pp->getAddress();
        case FIELD_control: return pp->getControl();
        case FIELD_protocol: return pp->getProtocol();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PppHeader' as cValue -- field index out of range?", field);
    }
}

void PppHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        case FIELD_flag: pp->setFlag(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_address: pp->setAddress(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_control: pp->setControl(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_protocol: pp->setProtocol(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppHeader'", field);
    }
}

const char *PppHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PppHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PppHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PppHeader *pp = omnetpp::fromAnyPtr<PppHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppHeader'", field);
    }
}

Register_Class(PppTrailer)

PppTrailer::PppTrailer() : ::inet::FieldsChunk()
{
    this->setChunkLength(PPP_TRAILER_LENGTH);

}

PppTrailer::PppTrailer(const PppTrailer& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

PppTrailer::~PppTrailer()
{
}

PppTrailer& PppTrailer::operator=(const PppTrailer& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void PppTrailer::copy(const PppTrailer& other)
{
    this->fcs = other.fcs;
    this->flag = other.flag;
}

void PppTrailer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->fcs);
    doParsimPacking(b,this->flag);
}

void PppTrailer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->fcs);
    doParsimUnpacking(b,this->flag);
}

short PppTrailer::getFcs() const
{
    return this->fcs;
}

void PppTrailer::setFcs(short fcs)
{
    handleChange();
    this->fcs = fcs;
}

short PppTrailer::getFlag() const
{
    return this->flag;
}

void PppTrailer::setFlag(short flag)
{
    handleChange();
    this->flag = flag;
}

class PppTrailerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fcs,
        FIELD_flag,
    };
  public:
    PppTrailerDescriptor();
    virtual ~PppTrailerDescriptor();

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

Register_ClassDescriptor(PppTrailerDescriptor)

PppTrailerDescriptor::PppTrailerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PppTrailer)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

PppTrailerDescriptor::~PppTrailerDescriptor()
{
    delete[] propertyNames;
}

bool PppTrailerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PppTrailer *>(obj)!=nullptr;
}

const char **PppTrailerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PppTrailerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PppTrailerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int PppTrailerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fcs
        FD_ISEDITABLE,    // FIELD_flag
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *PppTrailerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fcs",
        "flag",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int PppTrailerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fcs") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "flag") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *PppTrailerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_fcs
        "short",    // FIELD_flag
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **PppTrailerDescriptor::getFieldPropertyNames(int field) const
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

const char *PppTrailerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PppTrailerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PppTrailerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PppTrailer'", field);
    }
}

const char *PppTrailerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PppTrailerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return long2string(pp->getFcs());
        case FIELD_flag: return long2string(pp->getFlag());
        default: return "";
    }
}

void PppTrailerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(string2long(value)); break;
        case FIELD_flag: pp->setFlag(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppTrailer'", field);
    }
}

omnetpp::cValue PppTrailerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return pp->getFcs();
        case FIELD_flag: return pp->getFlag();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PppTrailer' as cValue -- field index out of range?", field);
    }
}

void PppTrailerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_flag: pp->setFlag(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppTrailer'", field);
    }
}

const char *PppTrailerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PppTrailerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PppTrailerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PppTrailer *pp = omnetpp::fromAnyPtr<PppTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PppTrailer'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

