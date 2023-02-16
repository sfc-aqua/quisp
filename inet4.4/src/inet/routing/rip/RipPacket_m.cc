//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/rip/RipPacket.msg.
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
#include "RipPacket_m.h"

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

Register_Enum(inet::RipCommand, (inet::RipCommand::RIP_REQUEST, inet::RipCommand::RIP_RESPONSE));

Register_Enum(inet::RipAf, (inet::RipAf::RIP_AF_NONE, inet::RipAf::RIP_AF_INET));

RipEntry::RipEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RipEntry& a)
{
    doParsimPacking(b,a.addressFamilyId);
    doParsimPacking(b,a.routeTag);
    doParsimPacking(b,a.address);
    doParsimPacking(b,a.prefixLength);
    doParsimPacking(b,a.nextHop);
    doParsimPacking(b,a.metric);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RipEntry& a)
{
    doParsimUnpacking(b,a.addressFamilyId);
    doParsimUnpacking(b,a.routeTag);
    doParsimUnpacking(b,a.address);
    doParsimUnpacking(b,a.prefixLength);
    doParsimUnpacking(b,a.nextHop);
    doParsimUnpacking(b,a.metric);
}

class RipEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_addressFamilyId,
        FIELD_routeTag,
        FIELD_address,
        FIELD_prefixLength,
        FIELD_nextHop,
        FIELD_metric,
    };
  public:
    RipEntryDescriptor();
    virtual ~RipEntryDescriptor();

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

Register_ClassDescriptor(RipEntryDescriptor)

RipEntryDescriptor::RipEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RipEntry)), "")
{
    propertyNames = nullptr;
}

RipEntryDescriptor::~RipEntryDescriptor()
{
    delete[] propertyNames;
}

bool RipEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RipEntry *>(obj)!=nullptr;
}

const char **RipEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RipEntryDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RipEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int RipEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_addressFamilyId
        FD_ISEDITABLE,    // FIELD_routeTag
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_prefixLength
        0,    // FIELD_nextHop
        FD_ISEDITABLE,    // FIELD_metric
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *RipEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "addressFamilyId",
        "routeTag",
        "address",
        "prefixLength",
        "nextHop",
        "metric",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int RipEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "addressFamilyId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "routeTag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "prefixLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "nextHop") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *RipEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RipAf",    // FIELD_addressFamilyId
        "unsigned short",    // FIELD_routeTag
        "inet::L3Address",    // FIELD_address
        "int",    // FIELD_prefixLength
        "inet::L3Address",    // FIELD_nextHop
        "unsigned int",    // FIELD_metric
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **RipEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_addressFamilyId: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RipEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_addressFamilyId:
            if (!strcmp(propertyName, "enum")) return "inet::RipAf";
            return nullptr;
        default: return nullptr;
    }
}

int RipEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RipEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RipEntry'", field);
    }
}

const char *RipEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RipEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addressFamilyId: return enum2string(pp->addressFamilyId, "inet::RipAf");
        case FIELD_routeTag: return ulong2string(pp->routeTag);
        case FIELD_address: return pp->address.str();
        case FIELD_prefixLength: return long2string(pp->prefixLength);
        case FIELD_nextHop: return pp->nextHop.str();
        case FIELD_metric: return ulong2string(pp->metric);
        default: return "";
    }
}

void RipEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        case FIELD_routeTag: pp->routeTag = string2ulong(value); break;
        case FIELD_prefixLength: pp->prefixLength = string2long(value); break;
        case FIELD_metric: pp->metric = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipEntry'", field);
    }
}

omnetpp::cValue RipEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addressFamilyId: return static_cast<int>(pp->addressFamilyId);
        case FIELD_routeTag: return (omnetpp::intval_t)(pp->routeTag);
        case FIELD_address: return omnetpp::toAnyPtr(&pp->address); break;
        case FIELD_prefixLength: return pp->prefixLength;
        case FIELD_nextHop: return omnetpp::toAnyPtr(&pp->nextHop); break;
        case FIELD_metric: return (omnetpp::intval_t)(pp->metric);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RipEntry' as cValue -- field index out of range?", field);
    }
}

void RipEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        case FIELD_routeTag: pp->routeTag = omnetpp::checked_int_cast<unsigned short>(value.intValue()); break;
        case FIELD_prefixLength: pp->prefixLength = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_metric: pp->metric = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipEntry'", field);
    }
}

const char *RipEntryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RipEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->address); break;
        case FIELD_nextHop: return omnetpp::toAnyPtr(&pp->nextHop); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RipEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RipEntry *pp = omnetpp::fromAnyPtr<RipEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipEntry'", field);
    }
}

Register_Class(RipPacket)

RipPacket::RipPacket() : ::inet::FieldsChunk()
{
}

RipPacket::RipPacket(const RipPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

RipPacket::~RipPacket()
{
    delete [] this->entry;
}

RipPacket& RipPacket::operator=(const RipPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void RipPacket::copy(const RipPacket& other)
{
    this->command = other.command;
    delete [] this->entry;
    this->entry = (other.entry_arraysize==0) ? nullptr : new RipEntry[other.entry_arraysize];
    entry_arraysize = other.entry_arraysize;
    for (size_t i = 0; i < entry_arraysize; i++) {
        this->entry[i] = other.entry[i];
    }
}

void RipPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->command);
    b->pack(entry_arraysize);
    doParsimArrayPacking(b,this->entry,entry_arraysize);
}

void RipPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
    delete [] this->entry;
    b->unpack(entry_arraysize);
    if (entry_arraysize == 0) {
        this->entry = nullptr;
    } else {
        this->entry = new RipEntry[entry_arraysize];
        doParsimArrayUnpacking(b,this->entry,entry_arraysize);
    }
}

RipCommand RipPacket::getCommand() const
{
    return this->command;
}

void RipPacket::setCommand(RipCommand command)
{
    handleChange();
    this->command = command;
}

size_t RipPacket::getEntryArraySize() const
{
    return entry_arraysize;
}

const RipEntry& RipPacket::getEntry(size_t k) const
{
    if (k >= entry_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entry_arraysize, (unsigned long)k);
    return this->entry[k];
}

void RipPacket::setEntryArraySize(size_t newSize)
{
    handleChange();
    RipEntry *entry2 = (newSize==0) ? nullptr : new RipEntry[newSize];
    size_t minSize = entry_arraysize < newSize ? entry_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        entry2[i] = this->entry[i];
    delete [] this->entry;
    this->entry = entry2;
    entry_arraysize = newSize;
}

void RipPacket::setEntry(size_t k, const RipEntry& entry)
{
    if (k >= entry_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entry_arraysize, (unsigned long)k);
    handleChange();
    this->entry[k] = entry;
}

void RipPacket::insertEntry(size_t k, const RipEntry& entry)
{
    if (k > entry_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entry_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = entry_arraysize + 1;
    RipEntry *entry2 = new RipEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        entry2[i] = this->entry[i];
    entry2[k] = entry;
    for (i = k + 1; i < newSize; i++)
        entry2[i] = this->entry[i-1];
    delete [] this->entry;
    this->entry = entry2;
    entry_arraysize = newSize;
}

void RipPacket::appendEntry(const RipEntry& entry)
{
    insertEntry(entry_arraysize, entry);
}

void RipPacket::eraseEntry(size_t k)
{
    if (k >= entry_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entry_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = entry_arraysize - 1;
    RipEntry *entry2 = (newSize == 0) ? nullptr : new RipEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        entry2[i] = this->entry[i];
    for (i = k; i < newSize; i++)
        entry2[i] = this->entry[i+1];
    delete [] this->entry;
    this->entry = entry2;
    entry_arraysize = newSize;
}

class RipPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_command,
        FIELD_entry,
    };
  public:
    RipPacketDescriptor();
    virtual ~RipPacketDescriptor();

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

Register_ClassDescriptor(RipPacketDescriptor)

RipPacketDescriptor::RipPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RipPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

RipPacketDescriptor::~RipPacketDescriptor()
{
    delete[] propertyNames;
}

bool RipPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RipPacket *>(obj)!=nullptr;
}

const char **RipPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RipPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RipPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RipPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_command
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_entry
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RipPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "command",
        "entry",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RipPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "command") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "entry") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RipPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RipCommand",    // FIELD_command
        "inet::RipEntry",    // FIELD_entry
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RipPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_command: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RipPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_command:
            if (!strcmp(propertyName, "enum")) return "inet::RipCommand";
            return nullptr;
        default: return nullptr;
    }
}

int RipPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        case FIELD_entry: return pp->getEntryArraySize();
        default: return 0;
    }
}

void RipPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        case FIELD_entry: pp->setEntryArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RipPacket'", field);
    }
}

const char *RipPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RipPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        case FIELD_command: return enum2string(pp->getCommand(), "inet::RipCommand");
        case FIELD_entry: return "";
        default: return "";
    }
}

void RipPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipPacket'", field);
    }
}

omnetpp::cValue RipPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        case FIELD_command: return static_cast<int>(pp->getCommand());
        case FIELD_entry: return omnetpp::toAnyPtr(&pp->getEntry(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RipPacket' as cValue -- field index out of range?", field);
    }
}

void RipPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipPacket'", field);
    }
}

const char *RipPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_entry: return omnetpp::opp_typename(typeid(RipEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr RipPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        case FIELD_entry: return omnetpp::toAnyPtr(&pp->getEntry(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RipPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RipPacket *pp = omnetpp::fromAnyPtr<RipPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RipPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

