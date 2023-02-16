//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/lmac/LMacHeader.msg.
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
#include "LMacHeader_m.h"

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

Register_Enum(inet::LMacType, (inet::LMacType::LMAC_CONTROL, inet::LMacType::LMAC_TIMEOUT, inet::LMacType::LMAC_WAKEUP, inet::LMacType::LMAC_SEND_DATA, inet::LMacType::LMAC_SETUP_PHASE_END, inet::LMacType::LMAC_CHECK_CHANNEL, inet::LMacType::LMAC_SOMEBODY, inet::LMacType::LMAC_DATA, inet::LMacType::LMAC_START_LMAC, inet::LMacType::LMAC_SEND_CONTROL));

Register_Class(LMacHeaderBase)

LMacHeaderBase::LMacHeaderBase() : ::inet::FieldsChunk()
{
}

LMacHeaderBase::LMacHeaderBase(const LMacHeaderBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LMacHeaderBase::~LMacHeaderBase()
{
    delete [] this->occupiedSlots;
}

LMacHeaderBase& LMacHeaderBase::operator=(const LMacHeaderBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LMacHeaderBase::copy(const LMacHeaderBase& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->type = other.type;
    this->mySlot = other.mySlot;
    delete [] this->occupiedSlots;
    this->occupiedSlots = (other.occupiedSlots_arraysize==0) ? nullptr : new MacAddress[other.occupiedSlots_arraysize];
    occupiedSlots_arraysize = other.occupiedSlots_arraysize;
    for (size_t i = 0; i < occupiedSlots_arraysize; i++) {
        this->occupiedSlots[i] = other.occupiedSlots[i];
    }
}

void LMacHeaderBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->mySlot);
    b->pack(occupiedSlots_arraysize);
    doParsimArrayPacking(b,this->occupiedSlots,occupiedSlots_arraysize);
}

void LMacHeaderBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->mySlot);
    delete [] this->occupiedSlots;
    b->unpack(occupiedSlots_arraysize);
    if (occupiedSlots_arraysize == 0) {
        this->occupiedSlots = nullptr;
    } else {
        this->occupiedSlots = new MacAddress[occupiedSlots_arraysize];
        doParsimArrayUnpacking(b,this->occupiedSlots,occupiedSlots_arraysize);
    }
}

const MacAddress& LMacHeaderBase::getSrcAddr() const
{
    return this->srcAddr;
}

void LMacHeaderBase::setSrcAddr(const MacAddress& srcAddr)
{
    handleChange();
    this->srcAddr = srcAddr;
}

const MacAddress& LMacHeaderBase::getDestAddr() const
{
    return this->destAddr;
}

void LMacHeaderBase::setDestAddr(const MacAddress& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

LMacType LMacHeaderBase::getType() const
{
    return this->type;
}

void LMacHeaderBase::setType(LMacType type)
{
    handleChange();
    this->type = type;
}

int LMacHeaderBase::getMySlot() const
{
    return this->mySlot;
}

void LMacHeaderBase::setMySlot(int mySlot)
{
    handleChange();
    this->mySlot = mySlot;
}

size_t LMacHeaderBase::getOccupiedSlotsArraySize() const
{
    return occupiedSlots_arraysize;
}

const MacAddress& LMacHeaderBase::getOccupiedSlots(size_t k) const
{
    if (k >= occupiedSlots_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)occupiedSlots_arraysize, (unsigned long)k);
    return this->occupiedSlots[k];
}

void LMacHeaderBase::setOccupiedSlotsArraySize(size_t newSize)
{
    handleChange();
    MacAddress *occupiedSlots2 = (newSize==0) ? nullptr : new MacAddress[newSize];
    size_t minSize = occupiedSlots_arraysize < newSize ? occupiedSlots_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        occupiedSlots2[i] = this->occupiedSlots[i];
    delete [] this->occupiedSlots;
    this->occupiedSlots = occupiedSlots2;
    occupiedSlots_arraysize = newSize;
}

void LMacHeaderBase::setOccupiedSlots(size_t k, const MacAddress& occupiedSlots)
{
    if (k >= occupiedSlots_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)occupiedSlots_arraysize, (unsigned long)k);
    handleChange();
    this->occupiedSlots[k] = occupiedSlots;
}

void LMacHeaderBase::insertOccupiedSlots(size_t k, const MacAddress& occupiedSlots)
{
    if (k > occupiedSlots_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)occupiedSlots_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = occupiedSlots_arraysize + 1;
    MacAddress *occupiedSlots2 = new MacAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        occupiedSlots2[i] = this->occupiedSlots[i];
    occupiedSlots2[k] = occupiedSlots;
    for (i = k + 1; i < newSize; i++)
        occupiedSlots2[i] = this->occupiedSlots[i-1];
    delete [] this->occupiedSlots;
    this->occupiedSlots = occupiedSlots2;
    occupiedSlots_arraysize = newSize;
}

void LMacHeaderBase::appendOccupiedSlots(const MacAddress& occupiedSlots)
{
    insertOccupiedSlots(occupiedSlots_arraysize, occupiedSlots);
}

void LMacHeaderBase::eraseOccupiedSlots(size_t k)
{
    if (k >= occupiedSlots_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)occupiedSlots_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = occupiedSlots_arraysize - 1;
    MacAddress *occupiedSlots2 = (newSize == 0) ? nullptr : new MacAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        occupiedSlots2[i] = this->occupiedSlots[i];
    for (i = k; i < newSize; i++)
        occupiedSlots2[i] = this->occupiedSlots[i+1];
    delete [] this->occupiedSlots;
    this->occupiedSlots = occupiedSlots2;
    occupiedSlots_arraysize = newSize;
}

class LMacHeaderBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_type,
        FIELD_mySlot,
        FIELD_occupiedSlots,
    };
  public:
    LMacHeaderBaseDescriptor();
    virtual ~LMacHeaderBaseDescriptor();

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

Register_ClassDescriptor(LMacHeaderBaseDescriptor)

LMacHeaderBaseDescriptor::LMacHeaderBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LMacHeaderBase)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LMacHeaderBaseDescriptor::~LMacHeaderBaseDescriptor()
{
    delete[] propertyNames;
}

bool LMacHeaderBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LMacHeaderBase *>(obj)!=nullptr;
}

const char **LMacHeaderBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LMacHeaderBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LMacHeaderBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LMacHeaderBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddr
        0,    // FIELD_destAddr
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_mySlot
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_occupiedSlots
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LMacHeaderBaseDescriptor::getFieldName(int field) const
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
        "type",
        "mySlot",
        "occupiedSlots",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LMacHeaderBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "mySlot") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "occupiedSlots") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LMacHeaderBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_srcAddr
        "inet::MacAddress",    // FIELD_destAddr
        "inet::LMacType",    // FIELD_type
        "int",    // FIELD_mySlot
        "inet::MacAddress",    // FIELD_occupiedSlots
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LMacHeaderBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LMacHeaderBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::LMacType";
            return nullptr;
        default: return nullptr;
    }
}

int LMacHeaderBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_occupiedSlots: return pp->getOccupiedSlotsArraySize();
        default: return 0;
    }
}

void LMacHeaderBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_occupiedSlots: pp->setOccupiedSlotsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LMacHeaderBase'", field);
    }
}

const char *LMacHeaderBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LMacHeaderBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr().str();
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_type: return enum2string(pp->getType(), "inet::LMacType");
        case FIELD_mySlot: return long2string(pp->getMySlot());
        case FIELD_occupiedSlots: return pp->getOccupiedSlots(i).str();
        default: return "";
    }
}

void LMacHeaderBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_mySlot: pp->setMySlot(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacHeaderBase'", field);
    }
}

omnetpp::cValue LMacHeaderBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_mySlot: return pp->getMySlot();
        case FIELD_occupiedSlots: return omnetpp::toAnyPtr(&pp->getOccupiedSlots(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LMacHeaderBase' as cValue -- field index out of range?", field);
    }
}

void LMacHeaderBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_mySlot: pp->setMySlot(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacHeaderBase'", field);
    }
}

const char *LMacHeaderBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LMacHeaderBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_occupiedSlots: return omnetpp::toAnyPtr(&pp->getOccupiedSlots(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LMacHeaderBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacHeaderBase *pp = omnetpp::fromAnyPtr<LMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacHeaderBase'", field);
    }
}

Register_Class(LMacControlFrame)

LMacControlFrame::LMacControlFrame() : ::inet::LMacHeaderBase()
{
}

LMacControlFrame::LMacControlFrame(const LMacControlFrame& other) : ::inet::LMacHeaderBase(other)
{
    copy(other);
}

LMacControlFrame::~LMacControlFrame()
{
}

LMacControlFrame& LMacControlFrame::operator=(const LMacControlFrame& other)
{
    if (this == &other) return *this;
    ::inet::LMacHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void LMacControlFrame::copy(const LMacControlFrame& other)
{
}

void LMacControlFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LMacHeaderBase::parsimPack(b);
}

void LMacControlFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LMacHeaderBase::parsimUnpack(b);
}

class LMacControlFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    LMacControlFrameDescriptor();
    virtual ~LMacControlFrameDescriptor();

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

Register_ClassDescriptor(LMacControlFrameDescriptor)

LMacControlFrameDescriptor::LMacControlFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LMacControlFrame)), "inet::LMacHeaderBase")
{
    propertyNames = nullptr;
}

LMacControlFrameDescriptor::~LMacControlFrameDescriptor()
{
    delete[] propertyNames;
}

bool LMacControlFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LMacControlFrame *>(obj)!=nullptr;
}

const char **LMacControlFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LMacControlFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LMacControlFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int LMacControlFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *LMacControlFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int LMacControlFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *LMacControlFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **LMacControlFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *LMacControlFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LMacControlFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LMacControlFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LMacControlFrame'", field);
    }
}

const char *LMacControlFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LMacControlFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void LMacControlFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacControlFrame'", field);
    }
}

omnetpp::cValue LMacControlFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LMacControlFrame' as cValue -- field index out of range?", field);
    }
}

void LMacControlFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacControlFrame'", field);
    }
}

const char *LMacControlFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr LMacControlFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LMacControlFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacControlFrame *pp = omnetpp::fromAnyPtr<LMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacControlFrame'", field);
    }
}

Register_Class(LMacDataFrameHeader)

LMacDataFrameHeader::LMacDataFrameHeader() : ::inet::LMacHeaderBase()
{
}

LMacDataFrameHeader::LMacDataFrameHeader(const LMacDataFrameHeader& other) : ::inet::LMacHeaderBase(other)
{
    copy(other);
}

LMacDataFrameHeader::~LMacDataFrameHeader()
{
}

LMacDataFrameHeader& LMacDataFrameHeader::operator=(const LMacDataFrameHeader& other)
{
    if (this == &other) return *this;
    ::inet::LMacHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void LMacDataFrameHeader::copy(const LMacDataFrameHeader& other)
{
    this->networkProtocol = other.networkProtocol;
}

void LMacDataFrameHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LMacHeaderBase::parsimPack(b);
    doParsimPacking(b,this->networkProtocol);
}

void LMacDataFrameHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LMacHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->networkProtocol);
}

int LMacDataFrameHeader::getNetworkProtocol() const
{
    return this->networkProtocol;
}

void LMacDataFrameHeader::setNetworkProtocol(int networkProtocol)
{
    handleChange();
    this->networkProtocol = networkProtocol;
}

class LMacDataFrameHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkProtocol,
    };
  public:
    LMacDataFrameHeaderDescriptor();
    virtual ~LMacDataFrameHeaderDescriptor();

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

Register_ClassDescriptor(LMacDataFrameHeaderDescriptor)

LMacDataFrameHeaderDescriptor::LMacDataFrameHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LMacDataFrameHeader)), "inet::LMacHeaderBase")
{
    propertyNames = nullptr;
}

LMacDataFrameHeaderDescriptor::~LMacDataFrameHeaderDescriptor()
{
    delete[] propertyNames;
}

bool LMacDataFrameHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LMacDataFrameHeader *>(obj)!=nullptr;
}

const char **LMacDataFrameHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LMacDataFrameHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LMacDataFrameHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LMacDataFrameHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_networkProtocol
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LMacDataFrameHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkProtocol",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LMacDataFrameHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkProtocol") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LMacDataFrameHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_networkProtocol
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LMacDataFrameHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *LMacDataFrameHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LMacDataFrameHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LMacDataFrameHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LMacDataFrameHeader'", field);
    }
}

const char *LMacDataFrameHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LMacDataFrameHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: return long2string(pp->getNetworkProtocol());
        default: return "";
    }
}

void LMacDataFrameHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: pp->setNetworkProtocol(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacDataFrameHeader'", field);
    }
}

omnetpp::cValue LMacDataFrameHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: return pp->getNetworkProtocol();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LMacDataFrameHeader' as cValue -- field index out of range?", field);
    }
}

void LMacDataFrameHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: pp->setNetworkProtocol(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacDataFrameHeader'", field);
    }
}

const char *LMacDataFrameHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LMacDataFrameHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LMacDataFrameHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LMacDataFrameHeader *pp = omnetpp::fromAnyPtr<LMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LMacDataFrameHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

