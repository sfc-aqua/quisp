//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/aodv/AodvControlPackets.msg.
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
#include "AodvControlPackets_m.h"

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
namespace aodv {

Register_Enum(inet::aodv::AodvControlPacketType, (inet::aodv::AodvControlPacketType::RREQ, inet::aodv::AodvControlPacketType::RREP, inet::aodv::AodvControlPacketType::RERR, inet::aodv::AodvControlPacketType::RREPACK, inet::aodv::AodvControlPacketType::RREQ_IPv6, inet::aodv::AodvControlPacketType::RREP_IPv6, inet::aodv::AodvControlPacketType::RERR_IPv6, inet::aodv::AodvControlPacketType::RREPACK_IPv6));

Register_Class(AodvControlPacket)

AodvControlPacket::AodvControlPacket() : ::inet::FieldsChunk()
{
}

AodvControlPacket::AodvControlPacket(const AodvControlPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

AodvControlPacket::~AodvControlPacket()
{
}

AodvControlPacket& AodvControlPacket::operator=(const AodvControlPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void AodvControlPacket::copy(const AodvControlPacket& other)
{
    this->packetType = other.packetType;
}

void AodvControlPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->packetType);
}

void AodvControlPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->packetType);
}

AodvControlPacketType AodvControlPacket::getPacketType() const
{
    return this->packetType;
}

void AodvControlPacket::setPacketType(AodvControlPacketType packetType)
{
    handleChange();
    this->packetType = packetType;
}

class AodvControlPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_packetType,
    };
  public:
    AodvControlPacketDescriptor();
    virtual ~AodvControlPacketDescriptor();

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

Register_ClassDescriptor(AodvControlPacketDescriptor)

AodvControlPacketDescriptor::AodvControlPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::AodvControlPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

AodvControlPacketDescriptor::~AodvControlPacketDescriptor()
{
    delete[] propertyNames;
}

bool AodvControlPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AodvControlPacket *>(obj)!=nullptr;
}

const char **AodvControlPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AodvControlPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AodvControlPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int AodvControlPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_packetType
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *AodvControlPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetType",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int AodvControlPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "packetType") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *AodvControlPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::aodv::AodvControlPacketType",    // FIELD_packetType
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **AodvControlPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *AodvControlPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType:
            if (!strcmp(propertyName, "enum")) return "inet::aodv::AodvControlPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int AodvControlPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AodvControlPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AodvControlPacket'", field);
    }
}

const char *AodvControlPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AodvControlPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return enum2string(pp->getPacketType(), "inet::aodv::AodvControlPacketType");
        default: return "";
    }
}

void AodvControlPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AodvControlPacket'", field);
    }
}

omnetpp::cValue AodvControlPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return static_cast<int>(pp->getPacketType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AodvControlPacket' as cValue -- field index out of range?", field);
    }
}

void AodvControlPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AodvControlPacket'", field);
    }
}

const char *AodvControlPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr AodvControlPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AodvControlPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AodvControlPacket *pp = omnetpp::fromAnyPtr<AodvControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AodvControlPacket'", field);
    }
}

Register_Class(Rreq)

Rreq::Rreq() : ::inet::aodv::AodvControlPacket()
{
}

Rreq::Rreq(const Rreq& other) : ::inet::aodv::AodvControlPacket(other)
{
    copy(other);
}

Rreq::~Rreq()
{
}

Rreq& Rreq::operator=(const Rreq& other)
{
    if (this == &other) return *this;
    ::inet::aodv::AodvControlPacket::operator=(other);
    copy(other);
    return *this;
}

void Rreq::copy(const Rreq& other)
{
    this->joinFlag = other.joinFlag;
    this->repairFlag = other.repairFlag;
    this->gratuitousRREPFlag = other.gratuitousRREPFlag;
    this->destOnlyFlag = other.destOnlyFlag;
    this->unknownSeqNumFlag = other.unknownSeqNumFlag;
    this->reserved = other.reserved;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->originatorSeqNum = other.originatorSeqNum;
}

void Rreq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::aodv::AodvControlPacket::parsimPack(b);
    doParsimPacking(b,this->joinFlag);
    doParsimPacking(b,this->repairFlag);
    doParsimPacking(b,this->gratuitousRREPFlag);
    doParsimPacking(b,this->destOnlyFlag);
    doParsimPacking(b,this->unknownSeqNumFlag);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->originatorSeqNum);
}

void Rreq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::aodv::AodvControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->joinFlag);
    doParsimUnpacking(b,this->repairFlag);
    doParsimUnpacking(b,this->gratuitousRREPFlag);
    doParsimUnpacking(b,this->destOnlyFlag);
    doParsimUnpacking(b,this->unknownSeqNumFlag);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->originatorSeqNum);
}

bool Rreq::getJoinFlag() const
{
    return this->joinFlag;
}

void Rreq::setJoinFlag(bool joinFlag)
{
    handleChange();
    this->joinFlag = joinFlag;
}

bool Rreq::getRepairFlag() const
{
    return this->repairFlag;
}

void Rreq::setRepairFlag(bool repairFlag)
{
    handleChange();
    this->repairFlag = repairFlag;
}

bool Rreq::getGratuitousRREPFlag() const
{
    return this->gratuitousRREPFlag;
}

void Rreq::setGratuitousRREPFlag(bool gratuitousRREPFlag)
{
    handleChange();
    this->gratuitousRREPFlag = gratuitousRREPFlag;
}

bool Rreq::getDestOnlyFlag() const
{
    return this->destOnlyFlag;
}

void Rreq::setDestOnlyFlag(bool destOnlyFlag)
{
    handleChange();
    this->destOnlyFlag = destOnlyFlag;
}

bool Rreq::getUnknownSeqNumFlag() const
{
    return this->unknownSeqNumFlag;
}

void Rreq::setUnknownSeqNumFlag(bool unknownSeqNumFlag)
{
    handleChange();
    this->unknownSeqNumFlag = unknownSeqNumFlag;
}

uint16_t Rreq::getReserved() const
{
    return this->reserved;
}

void Rreq::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

unsigned int Rreq::getHopCount() const
{
    return this->hopCount;
}

void Rreq::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

uint32_t Rreq::getRreqId() const
{
    return this->rreqId;
}

void Rreq::setRreqId(uint32_t rreqId)
{
    handleChange();
    this->rreqId = rreqId;
}

const ::inet::L3Address& Rreq::getDestAddr() const
{
    return this->destAddr;
}

void Rreq::setDestAddr(const ::inet::L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

uint32_t Rreq::getDestSeqNum() const
{
    return this->destSeqNum;
}

void Rreq::setDestSeqNum(uint32_t destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const ::inet::L3Address& Rreq::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void Rreq::setOriginatorAddr(const ::inet::L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

uint32_t Rreq::getOriginatorSeqNum() const
{
    return this->originatorSeqNum;
}

void Rreq::setOriginatorSeqNum(uint32_t originatorSeqNum)
{
    handleChange();
    this->originatorSeqNum = originatorSeqNum;
}

class RreqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_joinFlag,
        FIELD_repairFlag,
        FIELD_gratuitousRREPFlag,
        FIELD_destOnlyFlag,
        FIELD_unknownSeqNumFlag,
        FIELD_reserved,
        FIELD_hopCount,
        FIELD_rreqId,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_originatorSeqNum,
    };
  public:
    RreqDescriptor();
    virtual ~RreqDescriptor();

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

Register_ClassDescriptor(RreqDescriptor)

RreqDescriptor::RreqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::Rreq)), "inet::aodv::AodvControlPacket")
{
    propertyNames = nullptr;
}

RreqDescriptor::~RreqDescriptor()
{
    delete[] propertyNames;
}

bool RreqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rreq *>(obj)!=nullptr;
}

const char **RreqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int RreqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_joinFlag
        FD_ISEDITABLE,    // FIELD_repairFlag
        FD_ISEDITABLE,    // FIELD_gratuitousRREPFlag
        FD_ISEDITABLE,    // FIELD_destOnlyFlag
        FD_ISEDITABLE,    // FIELD_unknownSeqNumFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_rreqId
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *RreqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "joinFlag",
        "repairFlag",
        "gratuitousRREPFlag",
        "destOnlyFlag",
        "unknownSeqNumFlag",
        "reserved",
        "hopCount",
        "rreqId",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "originatorSeqNum",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int RreqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "joinFlag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "repairFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "gratuitousRREPFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "destOnlyFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "unknownSeqNumFlag") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "rreqId") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "destSeqNum") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "originatorAddr") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "originatorSeqNum") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *RreqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_joinFlag
        "bool",    // FIELD_repairFlag
        "bool",    // FIELD_gratuitousRREPFlag
        "bool",    // FIELD_destOnlyFlag
        "bool",    // FIELD_unknownSeqNumFlag
        "uint16_t",    // FIELD_reserved
        "unsigned int",    // FIELD_hopCount
        "uint32_t",    // FIELD_rreqId
        "inet::L3Address",    // FIELD_destAddr
        "uint32_t",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "uint32_t",    // FIELD_originatorSeqNum
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **RreqDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rreq'", field);
    }
}

const char *RreqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        case FIELD_joinFlag: return bool2string(pp->getJoinFlag());
        case FIELD_repairFlag: return bool2string(pp->getRepairFlag());
        case FIELD_gratuitousRREPFlag: return bool2string(pp->getGratuitousRREPFlag());
        case FIELD_destOnlyFlag: return bool2string(pp->getDestOnlyFlag());
        case FIELD_unknownSeqNumFlag: return bool2string(pp->getUnknownSeqNumFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_rreqId: return ulong2string(pp->getRreqId());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_originatorSeqNum: return ulong2string(pp->getOriginatorSeqNum());
        default: return "";
    }
}

void RreqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        case FIELD_joinFlag: pp->setJoinFlag(string2bool(value)); break;
        case FIELD_repairFlag: pp->setRepairFlag(string2bool(value)); break;
        case FIELD_gratuitousRREPFlag: pp->setGratuitousRREPFlag(string2bool(value)); break;
        case FIELD_destOnlyFlag: pp->setDestOnlyFlag(string2bool(value)); break;
        case FIELD_unknownSeqNumFlag: pp->setUnknownSeqNumFlag(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); break;
        case FIELD_rreqId: pp->setRreqId(string2ulong(value)); break;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); break;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

omnetpp::cValue RreqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        case FIELD_joinFlag: return pp->getJoinFlag();
        case FIELD_repairFlag: return pp->getRepairFlag();
        case FIELD_gratuitousRREPFlag: return pp->getGratuitousRREPFlag();
        case FIELD_destOnlyFlag: return pp->getDestOnlyFlag();
        case FIELD_unknownSeqNumFlag: return pp->getUnknownSeqNumFlag();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_hopCount: return (omnetpp::intval_t)(pp->getHopCount());
        case FIELD_rreqId: return (omnetpp::intval_t)(pp->getRreqId());
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_destSeqNum: return (omnetpp::intval_t)(pp->getDestSeqNum());
        case FIELD_originatorAddr: return omnetpp::toAnyPtr(&pp->getOriginatorAddr()); break;
        case FIELD_originatorSeqNum: return (omnetpp::intval_t)(pp->getOriginatorSeqNum());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rreq' as cValue -- field index out of range?", field);
    }
}

void RreqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        case FIELD_joinFlag: pp->setJoinFlag(value.boolValue()); break;
        case FIELD_repairFlag: pp->setRepairFlag(value.boolValue()); break;
        case FIELD_gratuitousRREPFlag: pp->setGratuitousRREPFlag(value.boolValue()); break;
        case FIELD_destOnlyFlag: pp->setDestOnlyFlag(value.boolValue()); break;
        case FIELD_unknownSeqNumFlag: pp->setUnknownSeqNumFlag(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_rreqId: pp->setRreqId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_destSeqNum: pp->setDestSeqNum(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_originatorSeqNum: pp->setOriginatorSeqNum(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

const char *RreqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RreqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return omnetpp::toAnyPtr(&pp->getOriginatorAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

Register_Class(Rrep)

Rrep::Rrep() : ::inet::aodv::AodvControlPacket()
{
}

Rrep::Rrep(const Rrep& other) : ::inet::aodv::AodvControlPacket(other)
{
    copy(other);
}

Rrep::~Rrep()
{
}

Rrep& Rrep::operator=(const Rrep& other)
{
    if (this == &other) return *this;
    ::inet::aodv::AodvControlPacket::operator=(other);
    copy(other);
    return *this;
}

void Rrep::copy(const Rrep& other)
{
    this->repairFlag = other.repairFlag;
    this->ackRequiredFlag = other.ackRequiredFlag;
    this->reserved = other.reserved;
    this->prefixSize = other.prefixSize;
    this->hopCount = other.hopCount;
    this->destAddr = other.destAddr;
    this->destSeqNum = other.destSeqNum;
    this->originatorAddr = other.originatorAddr;
    this->lifeTime = other.lifeTime;
}

void Rrep::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::aodv::AodvControlPacket::parsimPack(b);
    doParsimPacking(b,this->repairFlag);
    doParsimPacking(b,this->ackRequiredFlag);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->prefixSize);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->destSeqNum);
    doParsimPacking(b,this->originatorAddr);
    doParsimPacking(b,this->lifeTime);
}

void Rrep::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::aodv::AodvControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->repairFlag);
    doParsimUnpacking(b,this->ackRequiredFlag);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->prefixSize);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->destSeqNum);
    doParsimUnpacking(b,this->originatorAddr);
    doParsimUnpacking(b,this->lifeTime);
}

bool Rrep::getRepairFlag() const
{
    return this->repairFlag;
}

void Rrep::setRepairFlag(bool repairFlag)
{
    handleChange();
    this->repairFlag = repairFlag;
}

bool Rrep::getAckRequiredFlag() const
{
    return this->ackRequiredFlag;
}

void Rrep::setAckRequiredFlag(bool ackRequiredFlag)
{
    handleChange();
    this->ackRequiredFlag = ackRequiredFlag;
}

uint16_t Rrep::getReserved() const
{
    return this->reserved;
}

void Rrep::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

unsigned int Rrep::getPrefixSize() const
{
    return this->prefixSize;
}

void Rrep::setPrefixSize(unsigned int prefixSize)
{
    handleChange();
    this->prefixSize = prefixSize;
}

unsigned int Rrep::getHopCount() const
{
    return this->hopCount;
}

void Rrep::setHopCount(unsigned int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const ::inet::L3Address& Rrep::getDestAddr() const
{
    return this->destAddr;
}

void Rrep::setDestAddr(const ::inet::L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

uint32_t Rrep::getDestSeqNum() const
{
    return this->destSeqNum;
}

void Rrep::setDestSeqNum(uint32_t destSeqNum)
{
    handleChange();
    this->destSeqNum = destSeqNum;
}

const ::inet::L3Address& Rrep::getOriginatorAddr() const
{
    return this->originatorAddr;
}

void Rrep::setOriginatorAddr(const ::inet::L3Address& originatorAddr)
{
    handleChange();
    this->originatorAddr = originatorAddr;
}

::omnetpp::simtime_t Rrep::getLifeTime() const
{
    return this->lifeTime;
}

void Rrep::setLifeTime(::omnetpp::simtime_t lifeTime)
{
    handleChange();
    this->lifeTime = lifeTime;
}

class RrepDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_repairFlag,
        FIELD_ackRequiredFlag,
        FIELD_reserved,
        FIELD_prefixSize,
        FIELD_hopCount,
        FIELD_destAddr,
        FIELD_destSeqNum,
        FIELD_originatorAddr,
        FIELD_lifeTime,
    };
  public:
    RrepDescriptor();
    virtual ~RrepDescriptor();

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

Register_ClassDescriptor(RrepDescriptor)

RrepDescriptor::RrepDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::Rrep)), "inet::aodv::AodvControlPacket")
{
    propertyNames = nullptr;
}

RrepDescriptor::~RrepDescriptor()
{
    delete[] propertyNames;
}

bool RrepDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rrep *>(obj)!=nullptr;
}

const char **RrepDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RrepDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RrepDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int RrepDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_repairFlag
        FD_ISEDITABLE,    // FIELD_ackRequiredFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_prefixSize
        FD_ISEDITABLE,    // FIELD_hopCount
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_destSeqNum
        0,    // FIELD_originatorAddr
        FD_ISEDITABLE,    // FIELD_lifeTime
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *RrepDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "repairFlag",
        "ackRequiredFlag",
        "reserved",
        "prefixSize",
        "hopCount",
        "destAddr",
        "destSeqNum",
        "originatorAddr",
        "lifeTime",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int RrepDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "repairFlag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ackRequiredFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "prefixSize") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "destSeqNum") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "originatorAddr") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "lifeTime") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *RrepDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_repairFlag
        "bool",    // FIELD_ackRequiredFlag
        "uint16_t",    // FIELD_reserved
        "unsigned int",    // FIELD_prefixSize
        "unsigned int",    // FIELD_hopCount
        "inet::L3Address",    // FIELD_destAddr
        "uint32_t",    // FIELD_destSeqNum
        "inet::L3Address",    // FIELD_originatorAddr
        "omnetpp::simtime_t",    // FIELD_lifeTime
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **RrepDescriptor::getFieldPropertyNames(int field) const
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

const char *RrepDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RrepDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RrepDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rrep'", field);
    }
}

const char *RrepDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        case FIELD_repairFlag: return bool2string(pp->getRepairFlag());
        case FIELD_ackRequiredFlag: return bool2string(pp->getAckRequiredFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_prefixSize: return ulong2string(pp->getPrefixSize());
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_destSeqNum: return ulong2string(pp->getDestSeqNum());
        case FIELD_originatorAddr: return pp->getOriginatorAddr().str();
        case FIELD_lifeTime: return simtime2string(pp->getLifeTime());
        default: return "";
    }
}

void RrepDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        case FIELD_repairFlag: pp->setRepairFlag(string2bool(value)); break;
        case FIELD_ackRequiredFlag: pp->setAckRequiredFlag(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_prefixSize: pp->setPrefixSize(string2ulong(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); break;
        case FIELD_destSeqNum: pp->setDestSeqNum(string2ulong(value)); break;
        case FIELD_lifeTime: pp->setLifeTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

omnetpp::cValue RrepDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        case FIELD_repairFlag: return pp->getRepairFlag();
        case FIELD_ackRequiredFlag: return pp->getAckRequiredFlag();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_prefixSize: return (omnetpp::intval_t)(pp->getPrefixSize());
        case FIELD_hopCount: return (omnetpp::intval_t)(pp->getHopCount());
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_destSeqNum: return (omnetpp::intval_t)(pp->getDestSeqNum());
        case FIELD_originatorAddr: return omnetpp::toAnyPtr(&pp->getOriginatorAddr()); break;
        case FIELD_lifeTime: return pp->getLifeTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rrep' as cValue -- field index out of range?", field);
    }
}

void RrepDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        case FIELD_repairFlag: pp->setRepairFlag(value.boolValue()); break;
        case FIELD_ackRequiredFlag: pp->setAckRequiredFlag(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_prefixSize: pp->setPrefixSize(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_destSeqNum: pp->setDestSeqNum(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_lifeTime: pp->setLifeTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

const char *RrepDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RrepDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_originatorAddr: return omnetpp::toAnyPtr(&pp->getOriginatorAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RrepDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

UnreachableNode::UnreachableNode()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const UnreachableNode& a)
{
    doParsimPacking(b,a.addr);
    doParsimPacking(b,a.seqNum);
}

void __doUnpacking(omnetpp::cCommBuffer *b, UnreachableNode& a)
{
    doParsimUnpacking(b,a.addr);
    doParsimUnpacking(b,a.seqNum);
}

class UnreachableNodeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_addr,
        FIELD_seqNum,
    };
  public:
    UnreachableNodeDescriptor();
    virtual ~UnreachableNodeDescriptor();

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

Register_ClassDescriptor(UnreachableNodeDescriptor)

UnreachableNodeDescriptor::UnreachableNodeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::UnreachableNode)), "")
{
    propertyNames = nullptr;
}

UnreachableNodeDescriptor::~UnreachableNodeDescriptor()
{
    delete[] propertyNames;
}

bool UnreachableNodeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UnreachableNode *>(obj)!=nullptr;
}

const char **UnreachableNodeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UnreachableNodeDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UnreachableNodeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int UnreachableNodeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_addr
        FD_ISEDITABLE,    // FIELD_seqNum
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *UnreachableNodeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "addr",
        "seqNum",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int UnreachableNodeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "addr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "seqNum") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *UnreachableNodeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_addr
        "uint32_t",    // FIELD_seqNum
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **UnreachableNodeDescriptor::getFieldPropertyNames(int field) const
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

const char *UnreachableNodeDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UnreachableNodeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UnreachableNodeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UnreachableNode'", field);
    }
}

const char *UnreachableNodeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UnreachableNodeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return pp->addr.str();
        case FIELD_seqNum: return ulong2string(pp->seqNum);
        default: return "";
    }
}

void UnreachableNodeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        case FIELD_seqNum: pp->seqNum = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UnreachableNode'", field);
    }
}

omnetpp::cValue UnreachableNodeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return omnetpp::toAnyPtr(&pp->addr); break;
        case FIELD_seqNum: return (omnetpp::intval_t)(pp->seqNum);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UnreachableNode' as cValue -- field index out of range?", field);
    }
}

void UnreachableNodeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        case FIELD_seqNum: pp->seqNum = omnetpp::checked_int_cast<uint32_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UnreachableNode'", field);
    }
}

const char *UnreachableNodeDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr UnreachableNodeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return omnetpp::toAnyPtr(&pp->addr); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UnreachableNodeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UnreachableNode *pp = omnetpp::fromAnyPtr<UnreachableNode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UnreachableNode'", field);
    }
}

Register_Class(Rerr)

Rerr::Rerr() : ::inet::aodv::AodvControlPacket()
{
}

Rerr::Rerr(const Rerr& other) : ::inet::aodv::AodvControlPacket(other)
{
    copy(other);
}

Rerr::~Rerr()
{
    delete [] this->unreachableNodes;
}

Rerr& Rerr::operator=(const Rerr& other)
{
    if (this == &other) return *this;
    ::inet::aodv::AodvControlPacket::operator=(other);
    copy(other);
    return *this;
}

void Rerr::copy(const Rerr& other)
{
    this->noDeleteFlag = other.noDeleteFlag;
    this->reserved = other.reserved;
    delete [] this->unreachableNodes;
    this->unreachableNodes = (other.unreachableNodes_arraysize==0) ? nullptr : new UnreachableNode[other.unreachableNodes_arraysize];
    unreachableNodes_arraysize = other.unreachableNodes_arraysize;
    for (size_t i = 0; i < unreachableNodes_arraysize; i++) {
        this->unreachableNodes[i] = other.unreachableNodes[i];
    }
}

void Rerr::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::aodv::AodvControlPacket::parsimPack(b);
    doParsimPacking(b,this->noDeleteFlag);
    doParsimPacking(b,this->reserved);
    b->pack(unreachableNodes_arraysize);
    doParsimArrayPacking(b,this->unreachableNodes,unreachableNodes_arraysize);
}

void Rerr::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::aodv::AodvControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->noDeleteFlag);
    doParsimUnpacking(b,this->reserved);
    delete [] this->unreachableNodes;
    b->unpack(unreachableNodes_arraysize);
    if (unreachableNodes_arraysize == 0) {
        this->unreachableNodes = nullptr;
    } else {
        this->unreachableNodes = new UnreachableNode[unreachableNodes_arraysize];
        doParsimArrayUnpacking(b,this->unreachableNodes,unreachableNodes_arraysize);
    }
}

bool Rerr::getNoDeleteFlag() const
{
    return this->noDeleteFlag;
}

void Rerr::setNoDeleteFlag(bool noDeleteFlag)
{
    handleChange();
    this->noDeleteFlag = noDeleteFlag;
}

uint16_t Rerr::getReserved() const
{
    return this->reserved;
}

void Rerr::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

size_t Rerr::getUnreachableNodesArraySize() const
{
    return unreachableNodes_arraysize;
}

const UnreachableNode& Rerr::getUnreachableNodes(size_t k) const
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNodes_arraysize, (unsigned long)k);
    return this->unreachableNodes[k];
}

void Rerr::setUnreachableNodesArraySize(size_t newSize)
{
    handleChange();
    UnreachableNode *unreachableNodes2 = (newSize==0) ? nullptr : new UnreachableNode[newSize];
    size_t minSize = unreachableNodes_arraysize < newSize ? unreachableNodes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

void Rerr::setUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes)
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNodes_arraysize, (unsigned long)k);
    handleChange();
    this->unreachableNodes[k] = unreachableNodes;
}

void Rerr::insertUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes)
{
    if (k > unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNodes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = unreachableNodes_arraysize + 1;
    UnreachableNode *unreachableNodes2 = new UnreachableNode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    unreachableNodes2[k] = unreachableNodes;
    for (i = k + 1; i < newSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i-1];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

void Rerr::appendUnreachableNodes(const UnreachableNode& unreachableNodes)
{
    insertUnreachableNodes(unreachableNodes_arraysize, unreachableNodes);
}

void Rerr::eraseUnreachableNodes(size_t k)
{
    if (k >= unreachableNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNodes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = unreachableNodes_arraysize - 1;
    UnreachableNode *unreachableNodes2 = (newSize == 0) ? nullptr : new UnreachableNode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNodes2[i] = this->unreachableNodes[i];
    for (i = k; i < newSize; i++)
        unreachableNodes2[i] = this->unreachableNodes[i+1];
    delete [] this->unreachableNodes;
    this->unreachableNodes = unreachableNodes2;
    unreachableNodes_arraysize = newSize;
}

class RerrDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_noDeleteFlag,
        FIELD_reserved,
        FIELD_unreachableNodes,
    };
  public:
    RerrDescriptor();
    virtual ~RerrDescriptor();

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

Register_ClassDescriptor(RerrDescriptor)

RerrDescriptor::RerrDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::Rerr)), "inet::aodv::AodvControlPacket")
{
    propertyNames = nullptr;
}

RerrDescriptor::~RerrDescriptor()
{
    delete[] propertyNames;
}

bool RerrDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rerr *>(obj)!=nullptr;
}

const char **RerrDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RerrDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RerrDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RerrDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_noDeleteFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_unreachableNodes
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RerrDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "noDeleteFlag",
        "reserved",
        "unreachableNodes",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RerrDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "noDeleteFlag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "unreachableNodes") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RerrDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_noDeleteFlag
        "uint16_t",    // FIELD_reserved
        "inet::aodv::UnreachableNode",    // FIELD_unreachableNodes
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RerrDescriptor::getFieldPropertyNames(int field) const
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

const char *RerrDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RerrDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNodes: return pp->getUnreachableNodesArraySize();
        default: return 0;
    }
}

void RerrDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNodes: pp->setUnreachableNodesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rerr'", field);
    }
}

const char *RerrDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RerrDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: return bool2string(pp->getNoDeleteFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_unreachableNodes: return "";
        default: return "";
    }
}

void RerrDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: pp->setNoDeleteFlag(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

omnetpp::cValue RerrDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: return pp->getNoDeleteFlag();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_unreachableNodes: return omnetpp::toAnyPtr(&pp->getUnreachableNodes(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rerr' as cValue -- field index out of range?", field);
    }
}

void RerrDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_noDeleteFlag: pp->setNoDeleteFlag(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

const char *RerrDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_unreachableNodes: return omnetpp::opp_typename(typeid(UnreachableNode));
        default: return nullptr;
    };
}

omnetpp::any_ptr RerrDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNodes: return omnetpp::toAnyPtr(&pp->getUnreachableNodes(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RerrDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

Register_Class(RrepAck)

RrepAck::RrepAck() : ::inet::aodv::AodvControlPacket()
{
    this->setChunkLength(B(2));

}

RrepAck::RrepAck(const RrepAck& other) : ::inet::aodv::AodvControlPacket(other)
{
    copy(other);
}

RrepAck::~RrepAck()
{
}

RrepAck& RrepAck::operator=(const RrepAck& other)
{
    if (this == &other) return *this;
    ::inet::aodv::AodvControlPacket::operator=(other);
    copy(other);
    return *this;
}

void RrepAck::copy(const RrepAck& other)
{
    this->reserved = other.reserved;
}

void RrepAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::aodv::AodvControlPacket::parsimPack(b);
    doParsimPacking(b,this->reserved);
}

void RrepAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::aodv::AodvControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
}

uint8_t RrepAck::getReserved() const
{
    return this->reserved;
}

void RrepAck::setReserved(uint8_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

class RrepAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
    };
  public:
    RrepAckDescriptor();
    virtual ~RrepAckDescriptor();

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

Register_ClassDescriptor(RrepAckDescriptor)

RrepAckDescriptor::RrepAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::RrepAck)), "inet::aodv::AodvControlPacket")
{
    propertyNames = nullptr;
}

RrepAckDescriptor::~RrepAckDescriptor()
{
    delete[] propertyNames;
}

bool RrepAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RrepAck *>(obj)!=nullptr;
}

const char **RrepAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RrepAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RrepAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RrepAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RrepAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RrepAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RrepAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_reserved
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RrepAckDescriptor::getFieldPropertyNames(int field) const
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

const char *RrepAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RrepAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RrepAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RrepAck'", field);
    }
}

const char *RrepAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        default: return "";
    }
}

void RrepAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

omnetpp::cValue RrepAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RrepAck' as cValue -- field index out of range?", field);
    }
}

void RrepAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

const char *RrepAckDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RrepAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RrepAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

Register_Class(WaitForRrep)

WaitForRrep::WaitForRrep(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

WaitForRrep::WaitForRrep(const WaitForRrep& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

WaitForRrep::~WaitForRrep()
{
}

WaitForRrep& WaitForRrep::operator=(const WaitForRrep& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WaitForRrep::copy(const WaitForRrep& other)
{
    this->destAddr = other.destAddr;
    this->lastTTL = other.lastTTL;
    this->fromInvalidEntry = other.fromInvalidEntry;
}

void WaitForRrep::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->lastTTL);
    doParsimPacking(b,this->fromInvalidEntry);
}

void WaitForRrep::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->lastTTL);
    doParsimUnpacking(b,this->fromInvalidEntry);
}

const ::inet::L3Address& WaitForRrep::getDestAddr() const
{
    return this->destAddr;
}

void WaitForRrep::setDestAddr(const ::inet::L3Address& destAddr)
{
    this->destAddr = destAddr;
}

unsigned int WaitForRrep::getLastTTL() const
{
    return this->lastTTL;
}

void WaitForRrep::setLastTTL(unsigned int lastTTL)
{
    this->lastTTL = lastTTL;
}

bool WaitForRrep::getFromInvalidEntry() const
{
    return this->fromInvalidEntry;
}

void WaitForRrep::setFromInvalidEntry(bool fromInvalidEntry)
{
    this->fromInvalidEntry = fromInvalidEntry;
}

class WaitForRrepDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destAddr,
        FIELD_lastTTL,
        FIELD_fromInvalidEntry,
    };
  public:
    WaitForRrepDescriptor();
    virtual ~WaitForRrepDescriptor();

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

Register_ClassDescriptor(WaitForRrepDescriptor)

WaitForRrepDescriptor::WaitForRrepDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::WaitForRrep)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

WaitForRrepDescriptor::~WaitForRrepDescriptor()
{
    delete[] propertyNames;
}

bool WaitForRrepDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WaitForRrep *>(obj)!=nullptr;
}

const char **WaitForRrepDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *WaitForRrepDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int WaitForRrepDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int WaitForRrepDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_lastTTL
        FD_ISEDITABLE,    // FIELD_fromInvalidEntry
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *WaitForRrepDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddr",
        "lastTTL",
        "fromInvalidEntry",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int WaitForRrepDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lastTTL") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fromInvalidEntry") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *WaitForRrepDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_destAddr
        "unsigned int",    // FIELD_lastTTL
        "bool",    // FIELD_fromInvalidEntry
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **WaitForRrepDescriptor::getFieldPropertyNames(int field) const
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

const char *WaitForRrepDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int WaitForRrepDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void WaitForRrepDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'WaitForRrep'", field);
    }
}

const char *WaitForRrepDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WaitForRrepDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_lastTTL: return ulong2string(pp->getLastTTL());
        case FIELD_fromInvalidEntry: return bool2string(pp->getFromInvalidEntry());
        default: return "";
    }
}

void WaitForRrepDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        case FIELD_lastTTL: pp->setLastTTL(string2ulong(value)); break;
        case FIELD_fromInvalidEntry: pp->setFromInvalidEntry(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WaitForRrep'", field);
    }
}

omnetpp::cValue WaitForRrepDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_lastTTL: return (omnetpp::intval_t)(pp->getLastTTL());
        case FIELD_fromInvalidEntry: return pp->getFromInvalidEntry();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'WaitForRrep' as cValue -- field index out of range?", field);
    }
}

void WaitForRrepDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        case FIELD_lastTTL: pp->setLastTTL(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_fromInvalidEntry: pp->setFromInvalidEntry(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WaitForRrep'", field);
    }
}

const char *WaitForRrepDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr WaitForRrepDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void WaitForRrepDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    WaitForRrep *pp = omnetpp::fromAnyPtr<WaitForRrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WaitForRrep'", field);
    }
}

Register_Class(PacketHolderMessage)

PacketHolderMessage::PacketHolderMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
    if (this->ownedPacket != nullptr) take(this->ownedPacket);
}

PacketHolderMessage::PacketHolderMessage(const PacketHolderMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PacketHolderMessage::~PacketHolderMessage()
{
    dropAndDelete(this->ownedPacket);
}

PacketHolderMessage& PacketHolderMessage::operator=(const PacketHolderMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PacketHolderMessage::copy(const PacketHolderMessage& other)
{
    dropAndDelete(this->ownedPacket);
    this->ownedPacket = other.ownedPacket;
    if (this->ownedPacket != nullptr) {
        this->ownedPacket = this->ownedPacket->dup();
        take(this->ownedPacket);
        this->ownedPacket->setName(other.ownedPacket->getName());
    }
}

void PacketHolderMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->ownedPacket);
}

void PacketHolderMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->ownedPacket);
}

const ::inet::Packet * PacketHolderMessage::getOwnedPacket() const
{
    return this->ownedPacket;
}

void PacketHolderMessage::setOwnedPacket(::inet::Packet * ownedPacket)
{
    if (this->ownedPacket != nullptr) throw omnetpp::cRuntimeError("setOwnedPacket(): a value is already set, remove it first with removeOwnedPacket()");
    this->ownedPacket = ownedPacket;
    if (this->ownedPacket != nullptr) take(this->ownedPacket);
}

::inet::Packet * PacketHolderMessage::removeOwnedPacket()
{
    ::inet::Packet * retval = this->ownedPacket;
    if (retval != nullptr) drop(retval);
    this->ownedPacket = nullptr;
    return retval;
}

class PacketHolderMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ownedPacket,
    };
  public:
    PacketHolderMessageDescriptor();
    virtual ~PacketHolderMessageDescriptor();

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

Register_ClassDescriptor(PacketHolderMessageDescriptor)

PacketHolderMessageDescriptor::PacketHolderMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::aodv::PacketHolderMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

PacketHolderMessageDescriptor::~PacketHolderMessageDescriptor()
{
    delete[] propertyNames;
}

bool PacketHolderMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PacketHolderMessage *>(obj)!=nullptr;
}

const char **PacketHolderMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PacketHolderMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PacketHolderMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int PacketHolderMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE,    // FIELD_ownedPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PacketHolderMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ownedPacket",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PacketHolderMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ownedPacket") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *PacketHolderMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Packet",    // FIELD_ownedPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketHolderMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PacketHolderMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int PacketHolderMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PacketHolderMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PacketHolderMessage'", field);
    }
}

const char *PacketHolderMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: { const ::inet::Packet * value = pp->getOwnedPacket(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PacketHolderMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: { auto obj = pp->getOwnedPacket(); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void PacketHolderMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketHolderMessage'", field);
    }
}

omnetpp::cValue PacketHolderMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: return omnetpp::toAnyPtr(pp->getOwnedPacket()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PacketHolderMessage' as cValue -- field index out of range?", field);
    }
}

void PacketHolderMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: pp->setOwnedPacket(omnetpp::fromAnyPtr<::inet::Packet>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketHolderMessage'", field);
    }
}

const char *PacketHolderMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ownedPacket: return omnetpp::opp_typename(typeid(::inet::Packet));
        default: return nullptr;
    };
}

omnetpp::any_ptr PacketHolderMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: return omnetpp::toAnyPtr(pp->getOwnedPacket()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PacketHolderMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketHolderMessage *pp = omnetpp::fromAnyPtr<PacketHolderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ownedPacket: pp->setOwnedPacket(omnetpp::fromAnyPtr<::inet::Packet>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketHolderMessage'", field);
    }
}

}  // namespace aodv
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

