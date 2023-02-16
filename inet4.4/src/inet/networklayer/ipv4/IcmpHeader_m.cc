//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/IcmpHeader.msg.
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
#include "IcmpHeader_m.h"

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

Register_Enum(inet::IcmpType, (inet::IcmpType::ICMP_DESTINATION_UNREACHABLE, inet::IcmpType::ICMP_SOURCEQUENCH, inet::IcmpType::ICMP_REDIRECT, inet::IcmpType::ICMP_ECHO_REQUEST, inet::IcmpType::ICMP_ROUTER_ADVERTISEMENT, inet::IcmpType::ICMP_ROUTER_SOLICITATION, inet::IcmpType::ICMP_TIME_EXCEEDED, inet::IcmpType::ICMP_PARAMETER_PROBLEM, inet::IcmpType::ICMP_ECHO_REPLY, inet::IcmpType::ICMP_TIMESTAMP_REQUEST, inet::IcmpType::ICMP_TIMESTAMP_REPLY, inet::IcmpType::ICMP_INFORMATION_REQUEST, inet::IcmpType::ICMP_INFORMATION_REPLY, inet::IcmpType::ICMP_MASK_REQUEST, inet::IcmpType::ICMP_MASK_REPLY));

Register_Enum(inet::IcmpRedirectSubcodes, (inet::IcmpRedirectSubcodes::ICMP_REDIRECT_NET, inet::IcmpRedirectSubcodes::ICMP_REDIRECT_HOST, inet::IcmpRedirectSubcodes::ICMP_REDIRECT_TOSNET, inet::IcmpRedirectSubcodes::ICMP_REDIRECT_TOSHOST));

Register_Enum(inet::IcmpTimeExceededSubcodes, (inet::IcmpTimeExceededSubcodes::ICMP_TIMXCEED_INTRANS, inet::IcmpTimeExceededSubcodes::ICMP_TIMXCEED_REASS));

Register_Enum(inet::IcmpParameterProblemSubcodes, (inet::IcmpParameterProblemSubcodes::ICMP_PARAMPROB_ERRATPTR, inet::IcmpParameterProblemSubcodes::ICMP_PARAMPROB_OPTABSENT, inet::IcmpParameterProblemSubcodes::ICMP_PARAMPROB_LENGTH));

Register_Enum(inet::IcmpDestinationUnreachableCodes, (inet::IcmpDestinationUnreachableCodes::ICMP_DU_NETWORK_UNREACHABLE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_HOST_UNREACHABLE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_PROTOCOL_UNREACHABLE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_PORT_UNREACHABLE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_FRAGMENTATION_NEEDED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_SOURCE_ROUTE_FAILED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_DESTINATION_NETWORK_UNKNOWN, inet::IcmpDestinationUnreachableCodes::ICMP_DU_DESTINATION_HOST_UNKNOWN, inet::IcmpDestinationUnreachableCodes::ICMP_DU_SOURCE_HOST_ISOLATED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_NETWORK_PROHIBITED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_HOST_PROHIBITED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_NETWORK_UNREACHABLE_FOR_TYPE_OF_SERVICE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_HOST_UNREACHABLE_FOR_TYPE_OF_SERVICE, inet::IcmpDestinationUnreachableCodes::ICMP_DU_COMMUNICATION_PROHIBITED, inet::IcmpDestinationUnreachableCodes::ICMP_DU_HOST_PRECEDENCE_VIOLATION, inet::IcmpDestinationUnreachableCodes::ICMP_DU_PRECEDENCE_CUTOFF_IN_EFFECT, inet::IcmpDestinationUnreachableCodes::ICMP_AODV_QUEUE_FULL));

Register_Class(IcmpHeader)

IcmpHeader::IcmpHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(8));

}

IcmpHeader::IcmpHeader(const IcmpHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

IcmpHeader::~IcmpHeader()
{
}

IcmpHeader& IcmpHeader::operator=(const IcmpHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void IcmpHeader::copy(const IcmpHeader& other)
{
    this->type = other.type;
    this->code = other.code;
    this->chksum = other.chksum;
    this->crcMode = other.crcMode;
}

void IcmpHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->code);
    doParsimPacking(b,this->chksum);
    doParsimPacking(b,this->crcMode);
}

void IcmpHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->code);
    doParsimUnpacking(b,this->chksum);
    doParsimUnpacking(b,this->crcMode);
}

IcmpType IcmpHeader::getType() const
{
    return this->type;
}

void IcmpHeader::setType(IcmpType type)
{
    handleChange();
    this->type = type;
}

int IcmpHeader::getCode() const
{
    return this->code;
}

void IcmpHeader::setCode(int code)
{
    handleChange();
    this->code = code;
}

int IcmpHeader::getChksum() const
{
    return this->chksum;
}

void IcmpHeader::setChksum(int chksum)
{
    handleChange();
    this->chksum = chksum;
}

CrcMode IcmpHeader::getCrcMode() const
{
    return this->crcMode;
}

void IcmpHeader::setCrcMode(CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class IcmpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_code,
        FIELD_chksum,
        FIELD_crcMode,
    };
  public:
    IcmpHeaderDescriptor();
    virtual ~IcmpHeaderDescriptor();

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

Register_ClassDescriptor(IcmpHeaderDescriptor)

IcmpHeaderDescriptor::IcmpHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IcmpHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

IcmpHeaderDescriptor::~IcmpHeaderDescriptor()
{
    delete[] propertyNames;
}

bool IcmpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IcmpHeader *>(obj)!=nullptr;
}

const char **IcmpHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IcmpHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IcmpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int IcmpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_code
        FD_ISEDITABLE,    // FIELD_chksum
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *IcmpHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "code",
        "chksum",
        "crcMode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int IcmpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "code") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "chksum") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *IcmpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::IcmpType",    // FIELD_type
        "int",    // FIELD_code
        "int",    // FIELD_chksum
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **IcmpHeaderDescriptor::getFieldPropertyNames(int field) const
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
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *IcmpHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::IcmpType";
            return nullptr;
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int IcmpHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IcmpHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IcmpHeader'", field);
    }
}

const char *IcmpHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IcmpHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::IcmpType");
        case FIELD_code: return long2string(pp->getCode());
        case FIELD_chksum: return long2string(pp->getChksum());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void IcmpHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_code: pp->setCode(string2long(value)); break;
        case FIELD_chksum: pp->setChksum(string2long(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpHeader'", field);
    }
}

omnetpp::cValue IcmpHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_code: return pp->getCode();
        case FIELD_chksum: return pp->getChksum();
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IcmpHeader' as cValue -- field index out of range?", field);
    }
}

void IcmpHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_code: pp->setCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_chksum: pp->setChksum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpHeader'", field);
    }
}

const char *IcmpHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IcmpHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IcmpHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpHeader *pp = omnetpp::fromAnyPtr<IcmpHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpHeader'", field);
    }
}

Register_Class(IcmpEchoRequest)

IcmpEchoRequest::IcmpEchoRequest() : ::inet::IcmpHeader()
{
    this->setType(ICMP_ECHO_REQUEST);
    this->setCode(0);

}

IcmpEchoRequest::IcmpEchoRequest(const IcmpEchoRequest& other) : ::inet::IcmpHeader(other)
{
    copy(other);
}

IcmpEchoRequest::~IcmpEchoRequest()
{
}

IcmpEchoRequest& IcmpEchoRequest::operator=(const IcmpEchoRequest& other)
{
    if (this == &other) return *this;
    ::inet::IcmpHeader::operator=(other);
    copy(other);
    return *this;
}

void IcmpEchoRequest::copy(const IcmpEchoRequest& other)
{
    this->identifier = other.identifier;
    this->seqNumber = other.seqNumber;
}

void IcmpEchoRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IcmpHeader::parsimPack(b);
    doParsimPacking(b,this->identifier);
    doParsimPacking(b,this->seqNumber);
}

void IcmpEchoRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IcmpHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->identifier);
    doParsimUnpacking(b,this->seqNumber);
}

int IcmpEchoRequest::getIdentifier() const
{
    return this->identifier;
}

void IcmpEchoRequest::setIdentifier(int identifier)
{
    handleChange();
    this->identifier = identifier;
}

int IcmpEchoRequest::getSeqNumber() const
{
    return this->seqNumber;
}

void IcmpEchoRequest::setSeqNumber(int seqNumber)
{
    handleChange();
    this->seqNumber = seqNumber;
}

class IcmpEchoRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_identifier,
        FIELD_seqNumber,
    };
  public:
    IcmpEchoRequestDescriptor();
    virtual ~IcmpEchoRequestDescriptor();

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

Register_ClassDescriptor(IcmpEchoRequestDescriptor)

IcmpEchoRequestDescriptor::IcmpEchoRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IcmpEchoRequest)), "inet::IcmpHeader")
{
    propertyNames = nullptr;
}

IcmpEchoRequestDescriptor::~IcmpEchoRequestDescriptor()
{
    delete[] propertyNames;
}

bool IcmpEchoRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IcmpEchoRequest *>(obj)!=nullptr;
}

const char **IcmpEchoRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IcmpEchoRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IcmpEchoRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int IcmpEchoRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_identifier
        FD_ISEDITABLE,    // FIELD_seqNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *IcmpEchoRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "identifier",
        "seqNumber",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int IcmpEchoRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "identifier") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "seqNumber") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *IcmpEchoRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_identifier
        "int",    // FIELD_seqNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **IcmpEchoRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *IcmpEchoRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IcmpEchoRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IcmpEchoRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IcmpEchoRequest'", field);
    }
}

const char *IcmpEchoRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IcmpEchoRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: return long2string(pp->getIdentifier());
        case FIELD_seqNumber: return long2string(pp->getSeqNumber());
        default: return "";
    }
}

void IcmpEchoRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: pp->setIdentifier(string2long(value)); break;
        case FIELD_seqNumber: pp->setSeqNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoRequest'", field);
    }
}

omnetpp::cValue IcmpEchoRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: return pp->getIdentifier();
        case FIELD_seqNumber: return pp->getSeqNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IcmpEchoRequest' as cValue -- field index out of range?", field);
    }
}

void IcmpEchoRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: pp->setIdentifier(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_seqNumber: pp->setSeqNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoRequest'", field);
    }
}

const char *IcmpEchoRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IcmpEchoRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IcmpEchoRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoRequest *pp = omnetpp::fromAnyPtr<IcmpEchoRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoRequest'", field);
    }
}

Register_Class(IcmpEchoReply)

IcmpEchoReply::IcmpEchoReply() : ::inet::IcmpHeader()
{
    this->setType(ICMP_ECHO_REPLY);
    this->setCode(0);

}

IcmpEchoReply::IcmpEchoReply(const IcmpEchoReply& other) : ::inet::IcmpHeader(other)
{
    copy(other);
}

IcmpEchoReply::~IcmpEchoReply()
{
}

IcmpEchoReply& IcmpEchoReply::operator=(const IcmpEchoReply& other)
{
    if (this == &other) return *this;
    ::inet::IcmpHeader::operator=(other);
    copy(other);
    return *this;
}

void IcmpEchoReply::copy(const IcmpEchoReply& other)
{
    this->identifier = other.identifier;
    this->seqNumber = other.seqNumber;
}

void IcmpEchoReply::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IcmpHeader::parsimPack(b);
    doParsimPacking(b,this->identifier);
    doParsimPacking(b,this->seqNumber);
}

void IcmpEchoReply::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IcmpHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->identifier);
    doParsimUnpacking(b,this->seqNumber);
}

int IcmpEchoReply::getIdentifier() const
{
    return this->identifier;
}

void IcmpEchoReply::setIdentifier(int identifier)
{
    handleChange();
    this->identifier = identifier;
}

int IcmpEchoReply::getSeqNumber() const
{
    return this->seqNumber;
}

void IcmpEchoReply::setSeqNumber(int seqNumber)
{
    handleChange();
    this->seqNumber = seqNumber;
}

class IcmpEchoReplyDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_identifier,
        FIELD_seqNumber,
    };
  public:
    IcmpEchoReplyDescriptor();
    virtual ~IcmpEchoReplyDescriptor();

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

Register_ClassDescriptor(IcmpEchoReplyDescriptor)

IcmpEchoReplyDescriptor::IcmpEchoReplyDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IcmpEchoReply)), "inet::IcmpHeader")
{
    propertyNames = nullptr;
}

IcmpEchoReplyDescriptor::~IcmpEchoReplyDescriptor()
{
    delete[] propertyNames;
}

bool IcmpEchoReplyDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IcmpEchoReply *>(obj)!=nullptr;
}

const char **IcmpEchoReplyDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IcmpEchoReplyDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IcmpEchoReplyDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int IcmpEchoReplyDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_identifier
        FD_ISEDITABLE,    // FIELD_seqNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *IcmpEchoReplyDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "identifier",
        "seqNumber",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int IcmpEchoReplyDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "identifier") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "seqNumber") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *IcmpEchoReplyDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_identifier
        "int",    // FIELD_seqNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **IcmpEchoReplyDescriptor::getFieldPropertyNames(int field) const
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

const char *IcmpEchoReplyDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IcmpEchoReplyDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IcmpEchoReplyDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IcmpEchoReply'", field);
    }
}

const char *IcmpEchoReplyDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IcmpEchoReplyDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: return long2string(pp->getIdentifier());
        case FIELD_seqNumber: return long2string(pp->getSeqNumber());
        default: return "";
    }
}

void IcmpEchoReplyDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: pp->setIdentifier(string2long(value)); break;
        case FIELD_seqNumber: pp->setSeqNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoReply'", field);
    }
}

omnetpp::cValue IcmpEchoReplyDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: return pp->getIdentifier();
        case FIELD_seqNumber: return pp->getSeqNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IcmpEchoReply' as cValue -- field index out of range?", field);
    }
}

void IcmpEchoReplyDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        case FIELD_identifier: pp->setIdentifier(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_seqNumber: pp->setSeqNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoReply'", field);
    }
}

const char *IcmpEchoReplyDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IcmpEchoReplyDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IcmpEchoReplyDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpEchoReply *pp = omnetpp::fromAnyPtr<IcmpEchoReply>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpEchoReply'", field);
    }
}

Register_Class(IcmpPtb)

IcmpPtb::IcmpPtb() : ::inet::IcmpHeader()
{
    this->setType(ICMP_DESTINATION_UNREACHABLE);
    this->setCode(ICMP_DU_FRAGMENTATION_NEEDED);

}

IcmpPtb::IcmpPtb(const IcmpPtb& other) : ::inet::IcmpHeader(other)
{
    copy(other);
}

IcmpPtb::~IcmpPtb()
{
}

IcmpPtb& IcmpPtb::operator=(const IcmpPtb& other)
{
    if (this == &other) return *this;
    ::inet::IcmpHeader::operator=(other);
    copy(other);
    return *this;
}

void IcmpPtb::copy(const IcmpPtb& other)
{
    this->unused = other.unused;
    this->mtu = other.mtu;
}

void IcmpPtb::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IcmpHeader::parsimPack(b);
    doParsimPacking(b,this->unused);
    doParsimPacking(b,this->mtu);
}

void IcmpPtb::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IcmpHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->unused);
    doParsimUnpacking(b,this->mtu);
}

uint16_t IcmpPtb::getUnused() const
{
    return this->unused;
}

void IcmpPtb::setUnused(uint16_t unused)
{
    handleChange();
    this->unused = unused;
}

uint16_t IcmpPtb::getMtu() const
{
    return this->mtu;
}

void IcmpPtb::setMtu(uint16_t mtu)
{
    handleChange();
    this->mtu = mtu;
}

class IcmpPtbDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unused,
        FIELD_mtu,
    };
  public:
    IcmpPtbDescriptor();
    virtual ~IcmpPtbDescriptor();

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

Register_ClassDescriptor(IcmpPtbDescriptor)

IcmpPtbDescriptor::IcmpPtbDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IcmpPtb)), "inet::IcmpHeader")
{
    propertyNames = nullptr;
}

IcmpPtbDescriptor::~IcmpPtbDescriptor()
{
    delete[] propertyNames;
}

bool IcmpPtbDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IcmpPtb *>(obj)!=nullptr;
}

const char **IcmpPtbDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IcmpPtbDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IcmpPtbDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int IcmpPtbDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_unused
        FD_ISEDITABLE,    // FIELD_mtu
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *IcmpPtbDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unused",
        "mtu",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int IcmpPtbDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unused") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "mtu") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *IcmpPtbDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_unused
        "uint16_t",    // FIELD_mtu
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **IcmpPtbDescriptor::getFieldPropertyNames(int field) const
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

const char *IcmpPtbDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IcmpPtbDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IcmpPtbDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IcmpPtb'", field);
    }
}

const char *IcmpPtbDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IcmpPtbDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return ulong2string(pp->getUnused());
        case FIELD_mtu: return ulong2string(pp->getMtu());
        default: return "";
    }
}

void IcmpPtbDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(string2ulong(value)); break;
        case FIELD_mtu: pp->setMtu(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpPtb'", field);
    }
}

omnetpp::cValue IcmpPtbDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return (omnetpp::intval_t)(pp->getUnused());
        case FIELD_mtu: return (omnetpp::intval_t)(pp->getMtu());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IcmpPtb' as cValue -- field index out of range?", field);
    }
}

void IcmpPtbDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_mtu: pp->setMtu(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpPtb'", field);
    }
}

const char *IcmpPtbDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IcmpPtbDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IcmpPtbDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IcmpPtb *pp = omnetpp::fromAnyPtr<IcmpPtb>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IcmpPtb'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

