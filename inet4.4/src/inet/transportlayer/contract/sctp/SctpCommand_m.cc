//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/contract/sctp/SctpCommand.msg.
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
#include "SctpCommand_m.h"

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

class AddressVectorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    AddressVectorDescriptor();
    virtual ~AddressVectorDescriptor();

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

Register_ClassDescriptor(AddressVectorDescriptor)

AddressVectorDescriptor::AddressVectorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::AddressVector)), "")
{
    propertyNames = nullptr;
}

AddressVectorDescriptor::~AddressVectorDescriptor()
{
    delete[] propertyNames;
}

bool AddressVectorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AddressVector *>(obj)!=nullptr;
}

const char **AddressVectorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AddressVectorDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AddressVectorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int AddressVectorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *AddressVectorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int AddressVectorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *AddressVectorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **AddressVectorDescriptor::getFieldPropertyNames(int field) const
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

const char *AddressVectorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int AddressVectorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AddressVectorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AddressVector'", field);
    }
}

const char *AddressVectorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AddressVectorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void AddressVectorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressVector'", field);
    }
}

omnetpp::cValue AddressVectorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AddressVector' as cValue -- field index out of range?", field);
    }
}

void AddressVectorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressVector'", field);
    }
}

const char *AddressVectorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr AddressVectorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AddressVectorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressVector *pp = omnetpp::fromAnyPtr<AddressVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressVector'", field);
    }
}

Register_Enum(inet::SctpErrorCode, ());

Register_Enum(inet::SctpCommandCode, (inet::SctpCommandCode::SCTP_C_ASSOCIATE, inet::SctpCommandCode::SCTP_C_OPEN_PASSIVE, inet::SctpCommandCode::SCTP_C_SEND, inet::SctpCommandCode::SCTP_C_CLOSE, inet::SctpCommandCode::SCTP_C_ABORT, inet::SctpCommandCode::SCTP_C_STATUS, inet::SctpCommandCode::SCTP_C_RECEIVE, inet::SctpCommandCode::SCTP_C_SEND_ORDERED, inet::SctpCommandCode::SCTP_C_SEND_UNORDERED, inet::SctpCommandCode::SCTP_C_PRIMARY, inet::SctpCommandCode::SCTP_C_QUEUE_BYTES_LIMIT, inet::SctpCommandCode::SCTP_C_QUEUE_MSGS_LIMIT, inet::SctpCommandCode::SCTP_C_SHUTDOWN, inet::SctpCommandCode::SCTP_C_NO_OUTSTANDING, inet::SctpCommandCode::SCTP_C_STREAM_RESET, inet::SctpCommandCode::SCTP_C_RESET_ASSOC, inet::SctpCommandCode::SCTP_C_ADD_STREAMS, inet::SctpCommandCode::SCTP_C_NAT_INFO, inet::SctpCommandCode::SCTP_C_SEND_ASCONF, inet::SctpCommandCode::SCTP_C_SET_STREAM_PRIO, inet::SctpCommandCode::SCTP_C_GETSOCKETOPTIONS, inet::SctpCommandCode::SCTP_C_ACCEPT, inet::SctpCommandCode::SCTP_C_SET_RTO_INFO, inet::SctpCommandCode::SCTP_C_ACCEPT_SOCKET_ID, inet::SctpCommandCode::SCTP_C_DESTROY));

Register_Enum(inet::SctpStatusInd, (inet::SctpStatusInd::SCTP_I_DATA, inet::SctpStatusInd::SCTP_I_DATA_NOTIFICATION, inet::SctpStatusInd::SCTP_I_ESTABLISHED, inet::SctpStatusInd::SCTP_I_PEER_CLOSED, inet::SctpStatusInd::SCTP_I_CLOSED, inet::SctpStatusInd::SCTP_I_CONNECTION_REFUSED, inet::SctpStatusInd::SCTP_I_CONNECTION_RESET, inet::SctpStatusInd::SCTP_I_TIMED_OUT, inet::SctpStatusInd::SCTP_I_STATUS, inet::SctpStatusInd::SCTP_I_ABORT, inet::SctpStatusInd::SCTP_I_CONN_LOST, inet::SctpStatusInd::SCTP_I_SEND_MSG, inet::SctpStatusInd::SCTP_I_SHUTDOWN_RECEIVED, inet::SctpStatusInd::SCTP_I_SENDQUEUE_FULL, inet::SctpStatusInd::SCTP_I_SENDQUEUE_ABATED, inet::SctpStatusInd::SCTP_I_ABANDONED, inet::SctpStatusInd::SCTP_I_SEND_STREAMS_RESETTED, inet::SctpStatusInd::SCTP_I_RCV_STREAMS_RESETTED, inet::SctpStatusInd::SCTP_I_RESET_REQUEST_FAILED, inet::SctpStatusInd::SCTP_I_ADDRESS_ADDED, inet::SctpStatusInd::SCTP_I_SENDSOCKETOPTIONS, inet::SctpStatusInd::SCTP_I_AVAILABLE));

Register_Enum(inet::SctpFlags, (inet::SctpFlags::COMPLETE_MESG_UNORDERED, inet::SctpFlags::COMPLETE_MESG_ORDERED));

Register_Class(SctpSimpleMessage)

SctpSimpleMessage::SctpSimpleMessage(const char *name) : ::omnetpp::cPacket(name)
{
}

SctpSimpleMessage::SctpSimpleMessage(const SctpSimpleMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SctpSimpleMessage::~SctpSimpleMessage()
{
    delete [] this->data;
}

SctpSimpleMessage& SctpSimpleMessage::operator=(const SctpSimpleMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SctpSimpleMessage::copy(const SctpSimpleMessage& other)
{
    this->dataLen = other.dataLen;
    delete [] this->data;
    this->data = (other.data_arraysize==0) ? nullptr : new uint8_t[other.data_arraysize];
    data_arraysize = other.data_arraysize;
    for (size_t i = 0; i < data_arraysize; i++) {
        this->data[i] = other.data[i];
    }
    this->creationTime = other.creationTime;
    this->encaps = other.encaps;
}

void SctpSimpleMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->dataLen);
    b->pack(data_arraysize);
    doParsimArrayPacking(b,this->data,data_arraysize);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->encaps);
}

void SctpSimpleMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->dataLen);
    delete [] this->data;
    b->unpack(data_arraysize);
    if (data_arraysize == 0) {
        this->data = nullptr;
    } else {
        this->data = new uint8_t[data_arraysize];
        doParsimArrayUnpacking(b,this->data,data_arraysize);
    }
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->encaps);
}

uint32_t SctpSimpleMessage::getDataLen() const
{
    return this->dataLen;
}

void SctpSimpleMessage::setDataLen(uint32_t dataLen)
{
    this->dataLen = dataLen;
}

size_t SctpSimpleMessage::getDataArraySize() const
{
    return data_arraysize;
}

uint8_t SctpSimpleMessage::getData(size_t k) const
{
    if (k >= data_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)data_arraysize, (unsigned long)k);
    return this->data[k];
}

void SctpSimpleMessage::setDataArraySize(size_t newSize)
{
    uint8_t *data2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = data_arraysize < newSize ? data_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        data2[i] = this->data[i];
    for (size_t i = minSize; i < newSize; i++)
        data2[i] = 0;
    delete [] this->data;
    this->data = data2;
    data_arraysize = newSize;
}

void SctpSimpleMessage::setData(size_t k, uint8_t data)
{
    if (k >= data_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)data_arraysize, (unsigned long)k);
    this->data[k] = data;
}

void SctpSimpleMessage::insertData(size_t k, uint8_t data)
{
    if (k > data_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)data_arraysize, (unsigned long)k);
    size_t newSize = data_arraysize + 1;
    uint8_t *data2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        data2[i] = this->data[i];
    data2[k] = data;
    for (i = k + 1; i < newSize; i++)
        data2[i] = this->data[i-1];
    delete [] this->data;
    this->data = data2;
    data_arraysize = newSize;
}

void SctpSimpleMessage::appendData(uint8_t data)
{
    insertData(data_arraysize, data);
}

void SctpSimpleMessage::eraseData(size_t k)
{
    if (k >= data_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)data_arraysize, (unsigned long)k);
    size_t newSize = data_arraysize - 1;
    uint8_t *data2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        data2[i] = this->data[i];
    for (i = k; i < newSize; i++)
        data2[i] = this->data[i+1];
    delete [] this->data;
    this->data = data2;
    data_arraysize = newSize;
}

::omnetpp::simtime_t SctpSimpleMessage::getCreationTime() const
{
    return this->creationTime;
}

void SctpSimpleMessage::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

bool SctpSimpleMessage::getEncaps() const
{
    return this->encaps;
}

void SctpSimpleMessage::setEncaps(bool encaps)
{
    this->encaps = encaps;
}

class SctpSimpleMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dataLen,
        FIELD_data,
        FIELD_creationTime,
        FIELD_encaps,
    };
  public:
    SctpSimpleMessageDescriptor();
    virtual ~SctpSimpleMessageDescriptor();

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

Register_ClassDescriptor(SctpSimpleMessageDescriptor)

SctpSimpleMessageDescriptor::SctpSimpleMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpSimpleMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SctpSimpleMessageDescriptor::~SctpSimpleMessageDescriptor()
{
    delete[] propertyNames;
}

bool SctpSimpleMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSimpleMessage *>(obj)!=nullptr;
}

const char **SctpSimpleMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSimpleMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSimpleMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpSimpleMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dataLen
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_data
        FD_ISEDITABLE,    // FIELD_creationTime
        FD_ISEDITABLE,    // FIELD_encaps
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpSimpleMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dataLen",
        "data",
        "creationTime",
        "encaps",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpSimpleMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dataLen") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "creationTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "encaps") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSimpleMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_dataLen
        "uint8_t",    // FIELD_data
        "omnetpp::simtime_t",    // FIELD_creationTime
        "bool",    // FIELD_encaps
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSimpleMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSimpleMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSimpleMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_data: return pp->getDataArraySize();
        default: return 0;
    }
}

void SctpSimpleMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_data: pp->setDataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSimpleMessage'", field);
    }
}

const char *SctpSimpleMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSimpleMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dataLen: return ulong2string(pp->getDataLen());
        case FIELD_data: return ulong2string(pp->getData(i));
        case FIELD_creationTime: return simtime2string(pp->getCreationTime());
        case FIELD_encaps: return bool2string(pp->getEncaps());
        default: return "";
    }
}

void SctpSimpleMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dataLen: pp->setDataLen(string2ulong(value)); break;
        case FIELD_data: pp->setData(i,string2ulong(value)); break;
        case FIELD_creationTime: pp->setCreationTime(string2simtime(value)); break;
        case FIELD_encaps: pp->setEncaps(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleMessage'", field);
    }
}

omnetpp::cValue SctpSimpleMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dataLen: return (omnetpp::intval_t)(pp->getDataLen());
        case FIELD_data: return (omnetpp::intval_t)(pp->getData(i));
        case FIELD_creationTime: return pp->getCreationTime().dbl();
        case FIELD_encaps: return pp->getEncaps();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSimpleMessage' as cValue -- field index out of range?", field);
    }
}

void SctpSimpleMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dataLen: pp->setDataLen(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_data: pp->setData(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_creationTime: pp->setCreationTime(value.doubleValue()); break;
        case FIELD_encaps: pp->setEncaps(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleMessage'", field);
    }
}

const char *SctpSimpleMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSimpleMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSimpleMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleMessage *pp = omnetpp::fromAnyPtr<SctpSimpleMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleMessage'", field);
    }
}

Register_Class(SctpCommandReq)

SctpCommandReq::SctpCommandReq() : ::inet::TagBase()
{
}

SctpCommandReq::SctpCommandReq(const SctpCommandReq& other) : ::inet::TagBase(other)
{
    copy(other);
}

SctpCommandReq::~SctpCommandReq()
{
}

SctpCommandReq& SctpCommandReq::operator=(const SctpCommandReq& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void SctpCommandReq::copy(const SctpCommandReq& other)
{
    this->socketId = other.socketId;
    this->sid = other.sid;
    this->numMsgs = other.numMsgs;
    this->ssn = other.ssn;
    this->sendUnordered = other.sendUnordered;
    this->prValue = other.prValue;
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->gate = other.gate;
    this->fd = other.fd;
}

void SctpCommandReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->socketId);
    doParsimPacking(b,this->sid);
    doParsimPacking(b,this->numMsgs);
    doParsimPacking(b,this->ssn);
    doParsimPacking(b,this->sendUnordered);
    doParsimPacking(b,this->prValue);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->gate);
    doParsimPacking(b,this->fd);
}

void SctpCommandReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->socketId);
    doParsimUnpacking(b,this->sid);
    doParsimUnpacking(b,this->numMsgs);
    doParsimUnpacking(b,this->ssn);
    doParsimUnpacking(b,this->sendUnordered);
    doParsimUnpacking(b,this->prValue);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->gate);
    doParsimUnpacking(b,this->fd);
}

int SctpCommandReq::getSocketId() const
{
    return this->socketId;
}

void SctpCommandReq::setSocketId(int socketId)
{
    this->socketId = socketId;
}

int SctpCommandReq::getSid() const
{
    return this->sid;
}

void SctpCommandReq::setSid(int sid)
{
    this->sid = sid;
}

int SctpCommandReq::getNumMsgs() const
{
    return this->numMsgs;
}

void SctpCommandReq::setNumMsgs(int numMsgs)
{
    this->numMsgs = numMsgs;
}

int SctpCommandReq::getSsn() const
{
    return this->ssn;
}

void SctpCommandReq::setSsn(int ssn)
{
    this->ssn = ssn;
}

unsigned short SctpCommandReq::getSendUnordered() const
{
    return this->sendUnordered;
}

void SctpCommandReq::setSendUnordered(unsigned short sendUnordered)
{
    this->sendUnordered = sendUnordered;
}

double SctpCommandReq::getPrValue() const
{
    return this->prValue;
}

void SctpCommandReq::setPrValue(double prValue)
{
    this->prValue = prValue;
}

const L3Address& SctpCommandReq::getLocalAddr() const
{
    return this->localAddr;
}

void SctpCommandReq::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& SctpCommandReq::getRemoteAddr() const
{
    return this->remoteAddr;
}

void SctpCommandReq::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int SctpCommandReq::getLocalPort() const
{
    return this->localPort;
}

void SctpCommandReq::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int SctpCommandReq::getRemotePort() const
{
    return this->remotePort;
}

void SctpCommandReq::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

int SctpCommandReq::getGate() const
{
    return this->gate;
}

void SctpCommandReq::setGate(int gate)
{
    this->gate = gate;
}

int SctpCommandReq::getFd() const
{
    return this->fd;
}

void SctpCommandReq::setFd(int fd)
{
    this->fd = fd;
}

class SctpCommandReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_socketId,
        FIELD_sid,
        FIELD_numMsgs,
        FIELD_ssn,
        FIELD_sendUnordered,
        FIELD_prValue,
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_gate,
        FIELD_fd,
    };
  public:
    SctpCommandReqDescriptor();
    virtual ~SctpCommandReqDescriptor();

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

Register_ClassDescriptor(SctpCommandReqDescriptor)

SctpCommandReqDescriptor::SctpCommandReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpCommandReq)), "inet::TagBase")
{
    propertyNames = nullptr;
}

SctpCommandReqDescriptor::~SctpCommandReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpCommandReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpCommandReq *>(obj)!=nullptr;
}

const char **SctpCommandReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpCommandReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpCommandReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int SctpCommandReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_socketId
        FD_ISEDITABLE,    // FIELD_sid
        FD_ISEDITABLE,    // FIELD_numMsgs
        FD_ISEDITABLE,    // FIELD_ssn
        FD_ISEDITABLE,    // FIELD_sendUnordered
        FD_ISEDITABLE,    // FIELD_prValue
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_gate
        FD_ISEDITABLE,    // FIELD_fd
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *SctpCommandReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "socketId",
        "sid",
        "numMsgs",
        "ssn",
        "sendUnordered",
        "prValue",
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "gate",
        "fd",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int SctpCommandReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "socketId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "numMsgs") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ssn") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sendUnordered") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "prValue") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "gate") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "fd") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpCommandReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_socketId
        "int",    // FIELD_sid
        "int",    // FIELD_numMsgs
        "int",    // FIELD_ssn
        "unsigned short",    // FIELD_sendUnordered
        "double",    // FIELD_prValue
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "int",    // FIELD_gate
        "int",    // FIELD_fd
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpCommandReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpCommandReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpCommandReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpCommandReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpCommandReq'", field);
    }
}

const char *SctpCommandReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpCommandReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: return long2string(pp->getSocketId());
        case FIELD_sid: return long2string(pp->getSid());
        case FIELD_numMsgs: return long2string(pp->getNumMsgs());
        case FIELD_ssn: return long2string(pp->getSsn());
        case FIELD_sendUnordered: return ulong2string(pp->getSendUnordered());
        case FIELD_prValue: return double2string(pp->getPrValue());
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_gate: return long2string(pp->getGate());
        case FIELD_fd: return long2string(pp->getFd());
        default: return "";
    }
}

void SctpCommandReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: pp->setSocketId(string2long(value)); break;
        case FIELD_sid: pp->setSid(string2long(value)); break;
        case FIELD_numMsgs: pp->setNumMsgs(string2long(value)); break;
        case FIELD_ssn: pp->setSsn(string2long(value)); break;
        case FIELD_sendUnordered: pp->setSendUnordered(string2ulong(value)); break;
        case FIELD_prValue: pp->setPrValue(string2double(value)); break;
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        case FIELD_gate: pp->setGate(string2long(value)); break;
        case FIELD_fd: pp->setFd(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCommandReq'", field);
    }
}

omnetpp::cValue SctpCommandReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: return pp->getSocketId();
        case FIELD_sid: return pp->getSid();
        case FIELD_numMsgs: return pp->getNumMsgs();
        case FIELD_ssn: return pp->getSsn();
        case FIELD_sendUnordered: return (omnetpp::intval_t)(pp->getSendUnordered());
        case FIELD_prValue: return pp->getPrValue();
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        case FIELD_gate: return pp->getGate();
        case FIELD_fd: return pp->getFd();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpCommandReq' as cValue -- field index out of range?", field);
    }
}

void SctpCommandReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: pp->setSocketId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sid: pp->setSid(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_numMsgs: pp->setNumMsgs(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ssn: pp->setSsn(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sendUnordered: pp->setSendUnordered(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_prValue: pp->setPrValue(value.doubleValue()); break;
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_gate: pp->setGate(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fd: pp->setFd(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCommandReq'", field);
    }
}

const char *SctpCommandReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpCommandReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpCommandReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCommandReq *pp = omnetpp::fromAnyPtr<SctpCommandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCommandReq'", field);
    }
}

Register_Class(SctpSendReq)

SctpSendReq::SctpSendReq() : ::inet::SctpCommandReq()
{
}

SctpSendReq::SctpSendReq(const SctpSendReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpSendReq::~SctpSendReq()
{
}

SctpSendReq& SctpSendReq::operator=(const SctpSendReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpSendReq::copy(const SctpSendReq& other)
{
    this->prMethod = other.prMethod;
    this->last = other.last;
    this->ppid = other.ppid;
    this->primary = other.primary;
    this->sackNow = other.sackNow;
}

void SctpSendReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->prMethod);
    doParsimPacking(b,this->last);
    doParsimPacking(b,this->ppid);
    doParsimPacking(b,this->primary);
    doParsimPacking(b,this->sackNow);
}

void SctpSendReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->prMethod);
    doParsimUnpacking(b,this->last);
    doParsimUnpacking(b,this->ppid);
    doParsimUnpacking(b,this->primary);
    doParsimUnpacking(b,this->sackNow);
}

unsigned int SctpSendReq::getPrMethod() const
{
    return this->prMethod;
}

void SctpSendReq::setPrMethod(unsigned int prMethod)
{
    this->prMethod = prMethod;
}

bool SctpSendReq::getLast() const
{
    return this->last;
}

void SctpSendReq::setLast(bool last)
{
    this->last = last;
}

unsigned int SctpSendReq::getPpid() const
{
    return this->ppid;
}

void SctpSendReq::setPpid(unsigned int ppid)
{
    this->ppid = ppid;
}

bool SctpSendReq::getPrimary() const
{
    return this->primary;
}

void SctpSendReq::setPrimary(bool primary)
{
    this->primary = primary;
}

bool SctpSendReq::getSackNow() const
{
    return this->sackNow;
}

void SctpSendReq::setSackNow(bool sackNow)
{
    this->sackNow = sackNow;
}

class SctpSendReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_prMethod,
        FIELD_last,
        FIELD_ppid,
        FIELD_primary,
        FIELD_sackNow,
    };
  public:
    SctpSendReqDescriptor();
    virtual ~SctpSendReqDescriptor();

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

Register_ClassDescriptor(SctpSendReqDescriptor)

SctpSendReqDescriptor::SctpSendReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpSendReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpSendReqDescriptor::~SctpSendReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpSendReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSendReq *>(obj)!=nullptr;
}

const char **SctpSendReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSendReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSendReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int SctpSendReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_prMethod
        FD_ISEDITABLE,    // FIELD_last
        FD_ISEDITABLE,    // FIELD_ppid
        FD_ISEDITABLE,    // FIELD_primary
        FD_ISEDITABLE,    // FIELD_sackNow
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *SctpSendReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "prMethod",
        "last",
        "ppid",
        "primary",
        "sackNow",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int SctpSendReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "prMethod") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "last") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ppid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "primary") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sackNow") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSendReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_prMethod
        "bool",    // FIELD_last
        "unsigned int",    // FIELD_ppid
        "bool",    // FIELD_primary
        "bool",    // FIELD_sackNow
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSendReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSendReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSendReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpSendReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSendReq'", field);
    }
}

const char *SctpSendReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSendReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        case FIELD_prMethod: return ulong2string(pp->getPrMethod());
        case FIELD_last: return bool2string(pp->getLast());
        case FIELD_ppid: return ulong2string(pp->getPpid());
        case FIELD_primary: return bool2string(pp->getPrimary());
        case FIELD_sackNow: return bool2string(pp->getSackNow());
        default: return "";
    }
}

void SctpSendReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        case FIELD_prMethod: pp->setPrMethod(string2ulong(value)); break;
        case FIELD_last: pp->setLast(string2bool(value)); break;
        case FIELD_ppid: pp->setPpid(string2ulong(value)); break;
        case FIELD_primary: pp->setPrimary(string2bool(value)); break;
        case FIELD_sackNow: pp->setSackNow(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendReq'", field);
    }
}

omnetpp::cValue SctpSendReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        case FIELD_prMethod: return (omnetpp::intval_t)(pp->getPrMethod());
        case FIELD_last: return pp->getLast();
        case FIELD_ppid: return (omnetpp::intval_t)(pp->getPpid());
        case FIELD_primary: return pp->getPrimary();
        case FIELD_sackNow: return pp->getSackNow();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSendReq' as cValue -- field index out of range?", field);
    }
}

void SctpSendReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        case FIELD_prMethod: pp->setPrMethod(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_last: pp->setLast(value.boolValue()); break;
        case FIELD_ppid: pp->setPpid(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_primary: pp->setPrimary(value.boolValue()); break;
        case FIELD_sackNow: pp->setSackNow(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendReq'", field);
    }
}

const char *SctpSendReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSendReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSendReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendReq *pp = omnetpp::fromAnyPtr<SctpSendReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendReq'", field);
    }
}

Register_Class(SctpOpenReq)

SctpOpenReq::SctpOpenReq() : ::inet::SctpCommandReq()
{
}

SctpOpenReq::SctpOpenReq(const SctpOpenReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpOpenReq::~SctpOpenReq()
{
}

SctpOpenReq& SctpOpenReq::operator=(const SctpOpenReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpOpenReq::copy(const SctpOpenReq& other)
{
    this->localAddresses = other.localAddresses;
    this->remoteAddresses = other.remoteAddresses;
    this->fork = other.fork;
    this->queueClass = other.queueClass;
    this->sctpAlgorithmClass = other.sctpAlgorithmClass;
    this->inboundStreams = other.inboundStreams;
    this->outboundStreams = other.outboundStreams;
    this->streamReset = other.streamReset;
    this->appLimited = other.appLimited;
    this->prMethod = other.prMethod;
    this->numRequests = other.numRequests;
    this->messagesToPush = other.messagesToPush;
}

void SctpOpenReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->localAddresses);
    doParsimPacking(b,this->remoteAddresses);
    doParsimPacking(b,this->fork);
    doParsimPacking(b,this->queueClass);
    doParsimPacking(b,this->sctpAlgorithmClass);
    doParsimPacking(b,this->inboundStreams);
    doParsimPacking(b,this->outboundStreams);
    doParsimPacking(b,this->streamReset);
    doParsimPacking(b,this->appLimited);
    doParsimPacking(b,this->prMethod);
    doParsimPacking(b,this->numRequests);
    doParsimPacking(b,this->messagesToPush);
}

void SctpOpenReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddresses);
    doParsimUnpacking(b,this->remoteAddresses);
    doParsimUnpacking(b,this->fork);
    doParsimUnpacking(b,this->queueClass);
    doParsimUnpacking(b,this->sctpAlgorithmClass);
    doParsimUnpacking(b,this->inboundStreams);
    doParsimUnpacking(b,this->outboundStreams);
    doParsimUnpacking(b,this->streamReset);
    doParsimUnpacking(b,this->appLimited);
    doParsimUnpacking(b,this->prMethod);
    doParsimUnpacking(b,this->numRequests);
    doParsimUnpacking(b,this->messagesToPush);
}

const AddressVector& SctpOpenReq::getLocalAddresses() const
{
    return this->localAddresses;
}

void SctpOpenReq::setLocalAddresses(const AddressVector& localAddresses)
{
    this->localAddresses = localAddresses;
}

const AddressVector& SctpOpenReq::getRemoteAddresses() const
{
    return this->remoteAddresses;
}

void SctpOpenReq::setRemoteAddresses(const AddressVector& remoteAddresses)
{
    this->remoteAddresses = remoteAddresses;
}

bool SctpOpenReq::getFork() const
{
    return this->fork;
}

void SctpOpenReq::setFork(bool fork)
{
    this->fork = fork;
}

const char * SctpOpenReq::getQueueClass() const
{
    return this->queueClass.c_str();
}

void SctpOpenReq::setQueueClass(const char * queueClass)
{
    this->queueClass = queueClass;
}

const char * SctpOpenReq::getSctpAlgorithmClass() const
{
    return this->sctpAlgorithmClass.c_str();
}

void SctpOpenReq::setSctpAlgorithmClass(const char * sctpAlgorithmClass)
{
    this->sctpAlgorithmClass = sctpAlgorithmClass;
}

uint32_t SctpOpenReq::getInboundStreams() const
{
    return this->inboundStreams;
}

void SctpOpenReq::setInboundStreams(uint32_t inboundStreams)
{
    this->inboundStreams = inboundStreams;
}

uint32_t SctpOpenReq::getOutboundStreams() const
{
    return this->outboundStreams;
}

void SctpOpenReq::setOutboundStreams(uint32_t outboundStreams)
{
    this->outboundStreams = outboundStreams;
}

bool SctpOpenReq::getStreamReset() const
{
    return this->streamReset;
}

void SctpOpenReq::setStreamReset(bool streamReset)
{
    this->streamReset = streamReset;
}

bool SctpOpenReq::getAppLimited() const
{
    return this->appLimited;
}

void SctpOpenReq::setAppLimited(bool appLimited)
{
    this->appLimited = appLimited;
}

int SctpOpenReq::getPrMethod() const
{
    return this->prMethod;
}

void SctpOpenReq::setPrMethod(int prMethod)
{
    this->prMethod = prMethod;
}

uint32_t SctpOpenReq::getNumRequests() const
{
    return this->numRequests;
}

void SctpOpenReq::setNumRequests(uint32_t numRequests)
{
    this->numRequests = numRequests;
}

uint32_t SctpOpenReq::getMessagesToPush() const
{
    return this->messagesToPush;
}

void SctpOpenReq::setMessagesToPush(uint32_t messagesToPush)
{
    this->messagesToPush = messagesToPush;
}

class SctpOpenReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_localAddresses,
        FIELD_remoteAddresses,
        FIELD_fork,
        FIELD_queueClass,
        FIELD_sctpAlgorithmClass,
        FIELD_inboundStreams,
        FIELD_outboundStreams,
        FIELD_streamReset,
        FIELD_appLimited,
        FIELD_prMethod,
        FIELD_numRequests,
        FIELD_messagesToPush,
    };
  public:
    SctpOpenReqDescriptor();
    virtual ~SctpOpenReqDescriptor();

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

Register_ClassDescriptor(SctpOpenReqDescriptor)

SctpOpenReqDescriptor::SctpOpenReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpOpenReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpOpenReqDescriptor::~SctpOpenReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpOpenReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpOpenReq *>(obj)!=nullptr;
}

const char **SctpOpenReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpOpenReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpOpenReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int SctpOpenReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_localAddresses
        FD_ISCOMPOUND,    // FIELD_remoteAddresses
        FD_ISEDITABLE,    // FIELD_fork
        FD_ISEDITABLE,    // FIELD_queueClass
        FD_ISEDITABLE,    // FIELD_sctpAlgorithmClass
        FD_ISEDITABLE,    // FIELD_inboundStreams
        FD_ISEDITABLE,    // FIELD_outboundStreams
        FD_ISEDITABLE,    // FIELD_streamReset
        FD_ISEDITABLE,    // FIELD_appLimited
        FD_ISEDITABLE,    // FIELD_prMethod
        FD_ISEDITABLE,    // FIELD_numRequests
        FD_ISEDITABLE,    // FIELD_messagesToPush
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *SctpOpenReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddresses",
        "remoteAddresses",
        "fork",
        "queueClass",
        "sctpAlgorithmClass",
        "inboundStreams",
        "outboundStreams",
        "streamReset",
        "appLimited",
        "prMethod",
        "numRequests",
        "messagesToPush",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int SctpOpenReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "localAddresses") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remoteAddresses") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fork") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "queueClass") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sctpAlgorithmClass") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "inboundStreams") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "outboundStreams") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "streamReset") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "appLimited") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "prMethod") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "numRequests") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "messagesToPush") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpOpenReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::AddressVector",    // FIELD_localAddresses
        "inet::AddressVector",    // FIELD_remoteAddresses
        "bool",    // FIELD_fork
        "string",    // FIELD_queueClass
        "string",    // FIELD_sctpAlgorithmClass
        "uint32_t",    // FIELD_inboundStreams
        "uint32_t",    // FIELD_outboundStreams
        "bool",    // FIELD_streamReset
        "bool",    // FIELD_appLimited
        "int",    // FIELD_prMethod
        "uint32_t",    // FIELD_numRequests
        "uint32_t",    // FIELD_messagesToPush
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpOpenReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpOpenReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpOpenReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpOpenReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpOpenReq'", field);
    }
}

const char *SctpOpenReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpOpenReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        case FIELD_localAddresses: return "";
        case FIELD_remoteAddresses: return "";
        case FIELD_fork: return bool2string(pp->getFork());
        case FIELD_queueClass: return oppstring2string(pp->getQueueClass());
        case FIELD_sctpAlgorithmClass: return oppstring2string(pp->getSctpAlgorithmClass());
        case FIELD_inboundStreams: return ulong2string(pp->getInboundStreams());
        case FIELD_outboundStreams: return ulong2string(pp->getOutboundStreams());
        case FIELD_streamReset: return bool2string(pp->getStreamReset());
        case FIELD_appLimited: return bool2string(pp->getAppLimited());
        case FIELD_prMethod: return long2string(pp->getPrMethod());
        case FIELD_numRequests: return ulong2string(pp->getNumRequests());
        case FIELD_messagesToPush: return ulong2string(pp->getMessagesToPush());
        default: return "";
    }
}

void SctpOpenReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        case FIELD_fork: pp->setFork(string2bool(value)); break;
        case FIELD_queueClass: pp->setQueueClass((value)); break;
        case FIELD_sctpAlgorithmClass: pp->setSctpAlgorithmClass((value)); break;
        case FIELD_inboundStreams: pp->setInboundStreams(string2ulong(value)); break;
        case FIELD_outboundStreams: pp->setOutboundStreams(string2ulong(value)); break;
        case FIELD_streamReset: pp->setStreamReset(string2bool(value)); break;
        case FIELD_appLimited: pp->setAppLimited(string2bool(value)); break;
        case FIELD_prMethod: pp->setPrMethod(string2long(value)); break;
        case FIELD_numRequests: pp->setNumRequests(string2ulong(value)); break;
        case FIELD_messagesToPush: pp->setMessagesToPush(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOpenReq'", field);
    }
}

omnetpp::cValue SctpOpenReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        case FIELD_localAddresses: return omnetpp::toAnyPtr(&pp->getLocalAddresses()); break;
        case FIELD_remoteAddresses: return omnetpp::toAnyPtr(&pp->getRemoteAddresses()); break;
        case FIELD_fork: return pp->getFork();
        case FIELD_queueClass: return pp->getQueueClass();
        case FIELD_sctpAlgorithmClass: return pp->getSctpAlgorithmClass();
        case FIELD_inboundStreams: return (omnetpp::intval_t)(pp->getInboundStreams());
        case FIELD_outboundStreams: return (omnetpp::intval_t)(pp->getOutboundStreams());
        case FIELD_streamReset: return pp->getStreamReset();
        case FIELD_appLimited: return pp->getAppLimited();
        case FIELD_prMethod: return pp->getPrMethod();
        case FIELD_numRequests: return (omnetpp::intval_t)(pp->getNumRequests());
        case FIELD_messagesToPush: return (omnetpp::intval_t)(pp->getMessagesToPush());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpOpenReq' as cValue -- field index out of range?", field);
    }
}

void SctpOpenReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        case FIELD_fork: pp->setFork(value.boolValue()); break;
        case FIELD_queueClass: pp->setQueueClass(value.stringValue()); break;
        case FIELD_sctpAlgorithmClass: pp->setSctpAlgorithmClass(value.stringValue()); break;
        case FIELD_inboundStreams: pp->setInboundStreams(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_outboundStreams: pp->setOutboundStreams(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_streamReset: pp->setStreamReset(value.boolValue()); break;
        case FIELD_appLimited: pp->setAppLimited(value.boolValue()); break;
        case FIELD_prMethod: pp->setPrMethod(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_numRequests: pp->setNumRequests(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_messagesToPush: pp->setMessagesToPush(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOpenReq'", field);
    }
}

const char *SctpOpenReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_localAddresses: return omnetpp::opp_typename(typeid(AddressVector));
        case FIELD_remoteAddresses: return omnetpp::opp_typename(typeid(AddressVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpOpenReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        case FIELD_localAddresses: return omnetpp::toAnyPtr(&pp->getLocalAddresses()); break;
        case FIELD_remoteAddresses: return omnetpp::toAnyPtr(&pp->getRemoteAddresses()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpOpenReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOpenReq *pp = omnetpp::fromAnyPtr<SctpOpenReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOpenReq'", field);
    }
}

Register_Class(SctpAvailableReq)

SctpAvailableReq::SctpAvailableReq() : ::inet::SctpCommandReq()
{
}

SctpAvailableReq::SctpAvailableReq(const SctpAvailableReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpAvailableReq::~SctpAvailableReq()
{
}

SctpAvailableReq& SctpAvailableReq::operator=(const SctpAvailableReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpAvailableReq::copy(const SctpAvailableReq& other)
{
    this->newSocketId = other.newSocketId;
}

void SctpAvailableReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->newSocketId);
}

void SctpAvailableReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->newSocketId);
}

int SctpAvailableReq::getNewSocketId() const
{
    return this->newSocketId;
}

void SctpAvailableReq::setNewSocketId(int newSocketId)
{
    this->newSocketId = newSocketId;
}

class SctpAvailableReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_newSocketId,
    };
  public:
    SctpAvailableReqDescriptor();
    virtual ~SctpAvailableReqDescriptor();

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

Register_ClassDescriptor(SctpAvailableReqDescriptor)

SctpAvailableReqDescriptor::SctpAvailableReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpAvailableReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpAvailableReqDescriptor::~SctpAvailableReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpAvailableReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAvailableReq *>(obj)!=nullptr;
}

const char **SctpAvailableReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAvailableReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAvailableReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpAvailableReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_newSocketId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpAvailableReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "newSocketId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpAvailableReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "newSocketId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAvailableReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_newSocketId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAvailableReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAvailableReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAvailableReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpAvailableReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAvailableReq'", field);
    }
}

const char *SctpAvailableReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpAvailableReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        case FIELD_newSocketId: return long2string(pp->getNewSocketId());
        default: return "";
    }
}

void SctpAvailableReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        case FIELD_newSocketId: pp->setNewSocketId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAvailableReq'", field);
    }
}

omnetpp::cValue SctpAvailableReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        case FIELD_newSocketId: return pp->getNewSocketId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAvailableReq' as cValue -- field index out of range?", field);
    }
}

void SctpAvailableReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        case FIELD_newSocketId: pp->setNewSocketId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAvailableReq'", field);
    }
}

const char *SctpAvailableReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpAvailableReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAvailableReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAvailableReq *pp = omnetpp::fromAnyPtr<SctpAvailableReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAvailableReq'", field);
    }
}

Register_Class(SctpConnectReq)

SctpConnectReq::SctpConnectReq() : ::inet::SctpCommandReq()
{
}

SctpConnectReq::SctpConnectReq(const SctpConnectReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpConnectReq::~SctpConnectReq()
{
}

SctpConnectReq& SctpConnectReq::operator=(const SctpConnectReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpConnectReq::copy(const SctpConnectReq& other)
{
    this->remoteAddresses = other.remoteAddresses;
    this->status = other.status;
    this->inboundStreams = other.inboundStreams;
    this->outboundStreams = other.outboundStreams;
}

void SctpConnectReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->remoteAddresses);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->inboundStreams);
    doParsimPacking(b,this->outboundStreams);
}

void SctpConnectReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddresses);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->inboundStreams);
    doParsimUnpacking(b,this->outboundStreams);
}

const AddressVector& SctpConnectReq::getRemoteAddresses() const
{
    return this->remoteAddresses;
}

void SctpConnectReq::setRemoteAddresses(const AddressVector& remoteAddresses)
{
    this->remoteAddresses = remoteAddresses;
}

int SctpConnectReq::getStatus() const
{
    return this->status;
}

void SctpConnectReq::setStatus(int status)
{
    this->status = status;
}

int SctpConnectReq::getInboundStreams() const
{
    return this->inboundStreams;
}

void SctpConnectReq::setInboundStreams(int inboundStreams)
{
    this->inboundStreams = inboundStreams;
}

int SctpConnectReq::getOutboundStreams() const
{
    return this->outboundStreams;
}

void SctpConnectReq::setOutboundStreams(int outboundStreams)
{
    this->outboundStreams = outboundStreams;
}

class SctpConnectReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddresses,
        FIELD_status,
        FIELD_inboundStreams,
        FIELD_outboundStreams,
    };
  public:
    SctpConnectReqDescriptor();
    virtual ~SctpConnectReqDescriptor();

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

Register_ClassDescriptor(SctpConnectReqDescriptor)

SctpConnectReqDescriptor::SctpConnectReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpConnectReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpConnectReqDescriptor::~SctpConnectReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpConnectReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpConnectReq *>(obj)!=nullptr;
}

const char **SctpConnectReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpConnectReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpConnectReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpConnectReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_remoteAddresses
        FD_ISEDITABLE,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_inboundStreams
        FD_ISEDITABLE,    // FIELD_outboundStreams
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpConnectReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddresses",
        "status",
        "inboundStreams",
        "outboundStreams",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpConnectReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddresses") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "inboundStreams") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "outboundStreams") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpConnectReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::AddressVector",    // FIELD_remoteAddresses
        "int",    // FIELD_status
        "int",    // FIELD_inboundStreams
        "int",    // FIELD_outboundStreams
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpConnectReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpConnectReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpConnectReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpConnectReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpConnectReq'", field);
    }
}

const char *SctpConnectReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpConnectReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddresses: return "";
        case FIELD_status: return long2string(pp->getStatus());
        case FIELD_inboundStreams: return long2string(pp->getInboundStreams());
        case FIELD_outboundStreams: return long2string(pp->getOutboundStreams());
        default: return "";
    }
}

void SctpConnectReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(string2long(value)); break;
        case FIELD_inboundStreams: pp->setInboundStreams(string2long(value)); break;
        case FIELD_outboundStreams: pp->setOutboundStreams(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpConnectReq'", field);
    }
}

omnetpp::cValue SctpConnectReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddresses: return omnetpp::toAnyPtr(&pp->getRemoteAddresses()); break;
        case FIELD_status: return pp->getStatus();
        case FIELD_inboundStreams: return pp->getInboundStreams();
        case FIELD_outboundStreams: return pp->getOutboundStreams();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpConnectReq' as cValue -- field index out of range?", field);
    }
}

void SctpConnectReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_inboundStreams: pp->setInboundStreams(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_outboundStreams: pp->setOutboundStreams(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpConnectReq'", field);
    }
}

const char *SctpConnectReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_remoteAddresses: return omnetpp::opp_typename(typeid(AddressVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpConnectReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddresses: return omnetpp::toAnyPtr(&pp->getRemoteAddresses()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpConnectReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpConnectReq *pp = omnetpp::fromAnyPtr<SctpConnectReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpConnectReq'", field);
    }
}

Register_Class(SctpRcvReq)

SctpRcvReq::SctpRcvReq() : ::inet::SctpCommandReq()
{
}

SctpRcvReq::SctpRcvReq(const SctpRcvReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpRcvReq::~SctpRcvReq()
{
}

SctpRcvReq& SctpRcvReq::operator=(const SctpRcvReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpRcvReq::copy(const SctpRcvReq& other)
{
    this->ppid = other.ppid;
    this->tsn = other.tsn;
    this->cumTsn = other.cumTsn;
}

void SctpRcvReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->ppid);
    doParsimPacking(b,this->tsn);
    doParsimPacking(b,this->cumTsn);
}

void SctpRcvReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->ppid);
    doParsimUnpacking(b,this->tsn);
    doParsimUnpacking(b,this->cumTsn);
}

uint32_t SctpRcvReq::getPpid() const
{
    return this->ppid;
}

void SctpRcvReq::setPpid(uint32_t ppid)
{
    this->ppid = ppid;
}

uint32_t SctpRcvReq::getTsn() const
{
    return this->tsn;
}

void SctpRcvReq::setTsn(uint32_t tsn)
{
    this->tsn = tsn;
}

uint32_t SctpRcvReq::getCumTsn() const
{
    return this->cumTsn;
}

void SctpRcvReq::setCumTsn(uint32_t cumTsn)
{
    this->cumTsn = cumTsn;
}

class SctpRcvReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ppid,
        FIELD_tsn,
        FIELD_cumTsn,
    };
  public:
    SctpRcvReqDescriptor();
    virtual ~SctpRcvReqDescriptor();

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

Register_ClassDescriptor(SctpRcvReqDescriptor)

SctpRcvReqDescriptor::SctpRcvReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpRcvReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpRcvReqDescriptor::~SctpRcvReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpRcvReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpRcvReq *>(obj)!=nullptr;
}

const char **SctpRcvReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpRcvReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpRcvReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpRcvReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ppid
        FD_ISEDITABLE,    // FIELD_tsn
        FD_ISEDITABLE,    // FIELD_cumTsn
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpRcvReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ppid",
        "tsn",
        "cumTsn",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpRcvReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ppid") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tsn") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "cumTsn") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpRcvReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ppid
        "uint32_t",    // FIELD_tsn
        "uint32_t",    // FIELD_cumTsn
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpRcvReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpRcvReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpRcvReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpRcvReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpRcvReq'", field);
    }
}

const char *SctpRcvReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpRcvReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        case FIELD_ppid: return ulong2string(pp->getPpid());
        case FIELD_tsn: return ulong2string(pp->getTsn());
        case FIELD_cumTsn: return ulong2string(pp->getCumTsn());
        default: return "";
    }
}

void SctpRcvReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        case FIELD_ppid: pp->setPpid(string2ulong(value)); break;
        case FIELD_tsn: pp->setTsn(string2ulong(value)); break;
        case FIELD_cumTsn: pp->setCumTsn(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRcvReq'", field);
    }
}

omnetpp::cValue SctpRcvReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        case FIELD_ppid: return (omnetpp::intval_t)(pp->getPpid());
        case FIELD_tsn: return (omnetpp::intval_t)(pp->getTsn());
        case FIELD_cumTsn: return (omnetpp::intval_t)(pp->getCumTsn());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpRcvReq' as cValue -- field index out of range?", field);
    }
}

void SctpRcvReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        case FIELD_ppid: pp->setPpid(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_tsn: pp->setTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_cumTsn: pp->setCumTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRcvReq'", field);
    }
}

const char *SctpRcvReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpRcvReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpRcvReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRcvReq *pp = omnetpp::fromAnyPtr<SctpRcvReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRcvReq'", field);
    }
}

Register_Class(SctpStatusReq)

SctpStatusReq::SctpStatusReq() : ::inet::SctpCommandReq()
{
}

SctpStatusReq::SctpStatusReq(const SctpStatusReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpStatusReq::~SctpStatusReq()
{
}

SctpStatusReq& SctpStatusReq::operator=(const SctpStatusReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpStatusReq::copy(const SctpStatusReq& other)
{
    this->state = other.state;
    this->stateName = other.stateName;
    this->pathId = other.pathId;
    this->active = other.active;
}

void SctpStatusReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->stateName);
    doParsimPacking(b,this->pathId);
    doParsimPacking(b,this->active);
}

void SctpStatusReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->stateName);
    doParsimUnpacking(b,this->pathId);
    doParsimUnpacking(b,this->active);
}

int SctpStatusReq::getState() const
{
    return this->state;
}

void SctpStatusReq::setState(int state)
{
    this->state = state;
}

const char * SctpStatusReq::getStateName() const
{
    return this->stateName.c_str();
}

void SctpStatusReq::setStateName(const char * stateName)
{
    this->stateName = stateName;
}

const L3Address& SctpStatusReq::getPathId() const
{
    return this->pathId;
}

void SctpStatusReq::setPathId(const L3Address& pathId)
{
    this->pathId = pathId;
}

bool SctpStatusReq::getActive() const
{
    return this->active;
}

void SctpStatusReq::setActive(bool active)
{
    this->active = active;
}

class SctpStatusReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_state,
        FIELD_stateName,
        FIELD_pathId,
        FIELD_active,
    };
  public:
    SctpStatusReqDescriptor();
    virtual ~SctpStatusReqDescriptor();

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

Register_ClassDescriptor(SctpStatusReqDescriptor)

SctpStatusReqDescriptor::SctpStatusReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpStatusReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpStatusReqDescriptor::~SctpStatusReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpStatusReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpStatusReq *>(obj)!=nullptr;
}

const char **SctpStatusReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpStatusReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpStatusReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpStatusReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_state
        FD_ISEDITABLE,    // FIELD_stateName
        0,    // FIELD_pathId
        FD_ISEDITABLE,    // FIELD_active
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpStatusReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "state",
        "stateName",
        "pathId",
        "active",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpStatusReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "state") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "stateName") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "pathId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "active") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpStatusReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_state
        "string",    // FIELD_stateName
        "inet::L3Address",    // FIELD_pathId
        "bool",    // FIELD_active
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpStatusReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpStatusReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpStatusReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpStatusReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpStatusReq'", field);
    }
}

const char *SctpStatusReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpStatusReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        case FIELD_state: return long2string(pp->getState());
        case FIELD_stateName: return oppstring2string(pp->getStateName());
        case FIELD_pathId: return pp->getPathId().str();
        case FIELD_active: return bool2string(pp->getActive());
        default: return "";
    }
}

void SctpStatusReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        case FIELD_state: pp->setState(string2long(value)); break;
        case FIELD_stateName: pp->setStateName((value)); break;
        case FIELD_active: pp->setActive(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStatusReq'", field);
    }
}

omnetpp::cValue SctpStatusReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        case FIELD_state: return pp->getState();
        case FIELD_stateName: return pp->getStateName();
        case FIELD_pathId: return omnetpp::toAnyPtr(&pp->getPathId()); break;
        case FIELD_active: return pp->getActive();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpStatusReq' as cValue -- field index out of range?", field);
    }
}

void SctpStatusReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        case FIELD_state: pp->setState(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_stateName: pp->setStateName(value.stringValue()); break;
        case FIELD_active: pp->setActive(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStatusReq'", field);
    }
}

const char *SctpStatusReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpStatusReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        case FIELD_pathId: return omnetpp::toAnyPtr(&pp->getPathId()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpStatusReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStatusReq *pp = omnetpp::fromAnyPtr<SctpStatusReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStatusReq'", field);
    }
}

Register_Class(SctpResetReq)

SctpResetReq::SctpResetReq() : ::inet::SctpCommandReq()
{
}

SctpResetReq::SctpResetReq(const SctpResetReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpResetReq::~SctpResetReq()
{
    delete [] this->streams;
}

SctpResetReq& SctpResetReq::operator=(const SctpResetReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpResetReq::copy(const SctpResetReq& other)
{
    this->requestType = other.requestType;
    this->instreams = other.instreams;
    this->outstreams = other.outstreams;
    delete [] this->streams;
    this->streams = (other.streams_arraysize==0) ? nullptr : new uint16_t[other.streams_arraysize];
    streams_arraysize = other.streams_arraysize;
    for (size_t i = 0; i < streams_arraysize; i++) {
        this->streams[i] = other.streams[i];
    }
}

void SctpResetReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->requestType);
    doParsimPacking(b,this->instreams);
    doParsimPacking(b,this->outstreams);
    b->pack(streams_arraysize);
    doParsimArrayPacking(b,this->streams,streams_arraysize);
}

void SctpResetReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->requestType);
    doParsimUnpacking(b,this->instreams);
    doParsimUnpacking(b,this->outstreams);
    delete [] this->streams;
    b->unpack(streams_arraysize);
    if (streams_arraysize == 0) {
        this->streams = nullptr;
    } else {
        this->streams = new uint16_t[streams_arraysize];
        doParsimArrayUnpacking(b,this->streams,streams_arraysize);
    }
}

unsigned short SctpResetReq::getRequestType() const
{
    return this->requestType;
}

void SctpResetReq::setRequestType(unsigned short requestType)
{
    this->requestType = requestType;
}

uint16_t SctpResetReq::getInstreams() const
{
    return this->instreams;
}

void SctpResetReq::setInstreams(uint16_t instreams)
{
    this->instreams = instreams;
}

uint16_t SctpResetReq::getOutstreams() const
{
    return this->outstreams;
}

void SctpResetReq::setOutstreams(uint16_t outstreams)
{
    this->outstreams = outstreams;
}

size_t SctpResetReq::getStreamsArraySize() const
{
    return streams_arraysize;
}

uint16_t SctpResetReq::getStreams(size_t k) const
{
    if (k >= streams_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streams_arraysize, (unsigned long)k);
    return this->streams[k];
}

void SctpResetReq::setStreamsArraySize(size_t newSize)
{
    uint16_t *streams2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = streams_arraysize < newSize ? streams_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        streams2[i] = this->streams[i];
    for (size_t i = minSize; i < newSize; i++)
        streams2[i] = 0;
    delete [] this->streams;
    this->streams = streams2;
    streams_arraysize = newSize;
}

void SctpResetReq::setStreams(size_t k, uint16_t streams)
{
    if (k >= streams_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streams_arraysize, (unsigned long)k);
    this->streams[k] = streams;
}

void SctpResetReq::insertStreams(size_t k, uint16_t streams)
{
    if (k > streams_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streams_arraysize, (unsigned long)k);
    size_t newSize = streams_arraysize + 1;
    uint16_t *streams2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streams2[i] = this->streams[i];
    streams2[k] = streams;
    for (i = k + 1; i < newSize; i++)
        streams2[i] = this->streams[i-1];
    delete [] this->streams;
    this->streams = streams2;
    streams_arraysize = newSize;
}

void SctpResetReq::appendStreams(uint16_t streams)
{
    insertStreams(streams_arraysize, streams);
}

void SctpResetReq::eraseStreams(size_t k)
{
    if (k >= streams_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streams_arraysize, (unsigned long)k);
    size_t newSize = streams_arraysize - 1;
    uint16_t *streams2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streams2[i] = this->streams[i];
    for (i = k; i < newSize; i++)
        streams2[i] = this->streams[i+1];
    delete [] this->streams;
    this->streams = streams2;
    streams_arraysize = newSize;
}

class SctpResetReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestType,
        FIELD_instreams,
        FIELD_outstreams,
        FIELD_streams,
    };
  public:
    SctpResetReqDescriptor();
    virtual ~SctpResetReqDescriptor();

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

Register_ClassDescriptor(SctpResetReqDescriptor)

SctpResetReqDescriptor::SctpResetReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpResetReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpResetReqDescriptor::~SctpResetReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpResetReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpResetReq *>(obj)!=nullptr;
}

const char **SctpResetReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpResetReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpResetReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpResetReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestType
        FD_ISEDITABLE,    // FIELD_instreams
        FD_ISEDITABLE,    // FIELD_outstreams
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_streams
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpResetReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestType",
        "instreams",
        "outstreams",
        "streams",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpResetReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "instreams") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "outstreams") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "streams") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpResetReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_requestType
        "uint16_t",    // FIELD_instreams
        "uint16_t",    // FIELD_outstreams
        "uint16_t",    // FIELD_streams
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpResetReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpResetReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpResetReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_streams: return pp->getStreamsArraySize();
        default: return 0;
    }
}

void SctpResetReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_streams: pp->setStreamsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpResetReq'", field);
    }
}

const char *SctpResetReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpResetReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_requestType: return ulong2string(pp->getRequestType());
        case FIELD_instreams: return ulong2string(pp->getInstreams());
        case FIELD_outstreams: return ulong2string(pp->getOutstreams());
        case FIELD_streams: return ulong2string(pp->getStreams(i));
        default: return "";
    }
}

void SctpResetReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_requestType: pp->setRequestType(string2ulong(value)); break;
        case FIELD_instreams: pp->setInstreams(string2ulong(value)); break;
        case FIELD_outstreams: pp->setOutstreams(string2ulong(value)); break;
        case FIELD_streams: pp->setStreams(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetReq'", field);
    }
}

omnetpp::cValue SctpResetReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_requestType: return (omnetpp::intval_t)(pp->getRequestType());
        case FIELD_instreams: return (omnetpp::intval_t)(pp->getInstreams());
        case FIELD_outstreams: return (omnetpp::intval_t)(pp->getOutstreams());
        case FIELD_streams: return (omnetpp::intval_t)(pp->getStreams(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpResetReq' as cValue -- field index out of range?", field);
    }
}

void SctpResetReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        case FIELD_requestType: pp->setRequestType(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_instreams: pp->setInstreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_outstreams: pp->setOutstreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_streams: pp->setStreams(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetReq'", field);
    }
}

const char *SctpResetReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpResetReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpResetReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetReq *pp = omnetpp::fromAnyPtr<SctpResetReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetReq'", field);
    }
}

Register_Class(SctpInfoReq)

SctpInfoReq::SctpInfoReq() : ::inet::SctpCommandReq()
{
}

SctpInfoReq::SctpInfoReq(const SctpInfoReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpInfoReq::~SctpInfoReq()
{
}

SctpInfoReq& SctpInfoReq::operator=(const SctpInfoReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpInfoReq::copy(const SctpInfoReq& other)
{
    this->text = other.text;
}

void SctpInfoReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->text);
}

void SctpInfoReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->text);
}

int SctpInfoReq::getText() const
{
    return this->text;
}

void SctpInfoReq::setText(int text)
{
    this->text = text;
}

class SctpInfoReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_text,
    };
  public:
    SctpInfoReqDescriptor();
    virtual ~SctpInfoReqDescriptor();

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

Register_ClassDescriptor(SctpInfoReqDescriptor)

SctpInfoReqDescriptor::SctpInfoReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpInfoReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpInfoReqDescriptor::~SctpInfoReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpInfoReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpInfoReq *>(obj)!=nullptr;
}

const char **SctpInfoReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpInfoReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpInfoReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpInfoReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_text
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpInfoReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "text",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpInfoReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "text") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpInfoReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_text
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpInfoReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpInfoReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpInfoReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpInfoReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpInfoReq'", field);
    }
}

const char *SctpInfoReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpInfoReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_text: return long2string(pp->getText());
        default: return "";
    }
}

void SctpInfoReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_text: pp->setText(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInfoReq'", field);
    }
}

omnetpp::cValue SctpInfoReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_text: return pp->getText();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpInfoReq' as cValue -- field index out of range?", field);
    }
}

void SctpInfoReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_text: pp->setText(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInfoReq'", field);
    }
}

const char *SctpInfoReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpInfoReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpInfoReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInfoReq *pp = omnetpp::fromAnyPtr<SctpInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInfoReq'", field);
    }
}

Register_Class(SctpPathInfoReq)

SctpPathInfoReq::SctpPathInfoReq() : ::inet::SctpCommandReq()
{
}

SctpPathInfoReq::SctpPathInfoReq(const SctpPathInfoReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpPathInfoReq::~SctpPathInfoReq()
{
}

SctpPathInfoReq& SctpPathInfoReq::operator=(const SctpPathInfoReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpPathInfoReq::copy(const SctpPathInfoReq& other)
{
    this->remoteAddress = other.remoteAddress;
}

void SctpPathInfoReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->remoteAddress);
}

void SctpPathInfoReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddress);
}

const L3Address& SctpPathInfoReq::getRemoteAddress() const
{
    return this->remoteAddress;
}

void SctpPathInfoReq::setRemoteAddress(const L3Address& remoteAddress)
{
    this->remoteAddress = remoteAddress;
}

class SctpPathInfoReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddress,
    };
  public:
    SctpPathInfoReqDescriptor();
    virtual ~SctpPathInfoReqDescriptor();

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

Register_ClassDescriptor(SctpPathInfoReqDescriptor)

SctpPathInfoReqDescriptor::SctpPathInfoReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpPathInfoReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpPathInfoReqDescriptor::~SctpPathInfoReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpPathInfoReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpPathInfoReq *>(obj)!=nullptr;
}

const char **SctpPathInfoReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpPathInfoReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpPathInfoReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpPathInfoReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpPathInfoReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpPathInfoReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpPathInfoReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpPathInfoReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpPathInfoReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpPathInfoReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpPathInfoReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpPathInfoReq'", field);
    }
}

const char *SctpPathInfoReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpPathInfoReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return pp->getRemoteAddress().str();
        default: return "";
    }
}

void SctpPathInfoReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfoReq'", field);
    }
}

omnetpp::cValue SctpPathInfoReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpPathInfoReq' as cValue -- field index out of range?", field);
    }
}

void SctpPathInfoReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfoReq'", field);
    }
}

const char *SctpPathInfoReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpPathInfoReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpPathInfoReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfoReq *pp = omnetpp::fromAnyPtr<SctpPathInfoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfoReq'", field);
    }
}

Register_Class(SctpRtoReq)

SctpRtoReq::SctpRtoReq() : ::inet::SctpCommandReq()
{
}

SctpRtoReq::SctpRtoReq(const SctpRtoReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpRtoReq::~SctpRtoReq()
{
}

SctpRtoReq& SctpRtoReq::operator=(const SctpRtoReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpRtoReq::copy(const SctpRtoReq& other)
{
    this->rtoInitial = other.rtoInitial;
    this->rtoMin = other.rtoMin;
    this->rtoMax = other.rtoMax;
}

void SctpRtoReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->rtoInitial);
    doParsimPacking(b,this->rtoMin);
    doParsimPacking(b,this->rtoMax);
}

void SctpRtoReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->rtoInitial);
    doParsimUnpacking(b,this->rtoMin);
    doParsimUnpacking(b,this->rtoMax);
}

double SctpRtoReq::getRtoInitial() const
{
    return this->rtoInitial;
}

void SctpRtoReq::setRtoInitial(double rtoInitial)
{
    this->rtoInitial = rtoInitial;
}

double SctpRtoReq::getRtoMin() const
{
    return this->rtoMin;
}

void SctpRtoReq::setRtoMin(double rtoMin)
{
    this->rtoMin = rtoMin;
}

double SctpRtoReq::getRtoMax() const
{
    return this->rtoMax;
}

void SctpRtoReq::setRtoMax(double rtoMax)
{
    this->rtoMax = rtoMax;
}

class SctpRtoReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rtoInitial,
        FIELD_rtoMin,
        FIELD_rtoMax,
    };
  public:
    SctpRtoReqDescriptor();
    virtual ~SctpRtoReqDescriptor();

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

Register_ClassDescriptor(SctpRtoReqDescriptor)

SctpRtoReqDescriptor::SctpRtoReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpRtoReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpRtoReqDescriptor::~SctpRtoReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpRtoReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpRtoReq *>(obj)!=nullptr;
}

const char **SctpRtoReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpRtoReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpRtoReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpRtoReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_rtoInitial
        FD_ISEDITABLE,    // FIELD_rtoMin
        FD_ISEDITABLE,    // FIELD_rtoMax
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpRtoReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rtoInitial",
        "rtoMin",
        "rtoMax",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpRtoReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rtoInitial") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "rtoMin") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "rtoMax") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpRtoReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_rtoInitial
        "double",    // FIELD_rtoMin
        "double",    // FIELD_rtoMax
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpRtoReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpRtoReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpRtoReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpRtoReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpRtoReq'", field);
    }
}

const char *SctpRtoReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpRtoReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        case FIELD_rtoInitial: return double2string(pp->getRtoInitial());
        case FIELD_rtoMin: return double2string(pp->getRtoMin());
        case FIELD_rtoMax: return double2string(pp->getRtoMax());
        default: return "";
    }
}

void SctpRtoReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        case FIELD_rtoInitial: pp->setRtoInitial(string2double(value)); break;
        case FIELD_rtoMin: pp->setRtoMin(string2double(value)); break;
        case FIELD_rtoMax: pp->setRtoMax(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRtoReq'", field);
    }
}

omnetpp::cValue SctpRtoReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        case FIELD_rtoInitial: return pp->getRtoInitial();
        case FIELD_rtoMin: return pp->getRtoMin();
        case FIELD_rtoMax: return pp->getRtoMax();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpRtoReq' as cValue -- field index out of range?", field);
    }
}

void SctpRtoReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        case FIELD_rtoInitial: pp->setRtoInitial(value.doubleValue()); break;
        case FIELD_rtoMin: pp->setRtoMin(value.doubleValue()); break;
        case FIELD_rtoMax: pp->setRtoMax(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRtoReq'", field);
    }
}

const char *SctpRtoReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpRtoReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpRtoReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpRtoReq *pp = omnetpp::fromAnyPtr<SctpRtoReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpRtoReq'", field);
    }
}

Register_Class(SctpSendQueueAbatedReq)

SctpSendQueueAbatedReq::SctpSendQueueAbatedReq() : ::inet::SctpCommandReq()
{
}

SctpSendQueueAbatedReq::SctpSendQueueAbatedReq(const SctpSendQueueAbatedReq& other) : ::inet::SctpCommandReq(other)
{
    copy(other);
}

SctpSendQueueAbatedReq::~SctpSendQueueAbatedReq()
{
    delete [] this->queuedForStream;
}

SctpSendQueueAbatedReq& SctpSendQueueAbatedReq::operator=(const SctpSendQueueAbatedReq& other)
{
    if (this == &other) return *this;
    ::inet::SctpCommandReq::operator=(other);
    copy(other);
    return *this;
}

void SctpSendQueueAbatedReq::copy(const SctpSendQueueAbatedReq& other)
{
    this->bytesAvailable = other.bytesAvailable;
    this->bytesQueued = other.bytesQueued;
    this->bytesLimit = other.bytesLimit;
    delete [] this->queuedForStream;
    this->queuedForStream = (other.queuedForStream_arraysize==0) ? nullptr : new uint64_t[other.queuedForStream_arraysize];
    queuedForStream_arraysize = other.queuedForStream_arraysize;
    for (size_t i = 0; i < queuedForStream_arraysize; i++) {
        this->queuedForStream[i] = other.queuedForStream[i];
    }
}

void SctpSendQueueAbatedReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SctpCommandReq::parsimPack(b);
    doParsimPacking(b,this->bytesAvailable);
    doParsimPacking(b,this->bytesQueued);
    doParsimPacking(b,this->bytesLimit);
    b->pack(queuedForStream_arraysize);
    doParsimArrayPacking(b,this->queuedForStream,queuedForStream_arraysize);
}

void SctpSendQueueAbatedReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SctpCommandReq::parsimUnpack(b);
    doParsimUnpacking(b,this->bytesAvailable);
    doParsimUnpacking(b,this->bytesQueued);
    doParsimUnpacking(b,this->bytesLimit);
    delete [] this->queuedForStream;
    b->unpack(queuedForStream_arraysize);
    if (queuedForStream_arraysize == 0) {
        this->queuedForStream = nullptr;
    } else {
        this->queuedForStream = new uint64_t[queuedForStream_arraysize];
        doParsimArrayUnpacking(b,this->queuedForStream,queuedForStream_arraysize);
    }
}

uint64_t SctpSendQueueAbatedReq::getBytesAvailable() const
{
    return this->bytesAvailable;
}

void SctpSendQueueAbatedReq::setBytesAvailable(uint64_t bytesAvailable)
{
    this->bytesAvailable = bytesAvailable;
}

uint64_t SctpSendQueueAbatedReq::getBytesQueued() const
{
    return this->bytesQueued;
}

void SctpSendQueueAbatedReq::setBytesQueued(uint64_t bytesQueued)
{
    this->bytesQueued = bytesQueued;
}

uint64_t SctpSendQueueAbatedReq::getBytesLimit() const
{
    return this->bytesLimit;
}

void SctpSendQueueAbatedReq::setBytesLimit(uint64_t bytesLimit)
{
    this->bytesLimit = bytesLimit;
}

size_t SctpSendQueueAbatedReq::getQueuedForStreamArraySize() const
{
    return queuedForStream_arraysize;
}

uint64_t SctpSendQueueAbatedReq::getQueuedForStream(size_t k) const
{
    if (k >= queuedForStream_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)queuedForStream_arraysize, (unsigned long)k);
    return this->queuedForStream[k];
}

void SctpSendQueueAbatedReq::setQueuedForStreamArraySize(size_t newSize)
{
    uint64_t *queuedForStream2 = (newSize==0) ? nullptr : new uint64_t[newSize];
    size_t minSize = queuedForStream_arraysize < newSize ? queuedForStream_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        queuedForStream2[i] = this->queuedForStream[i];
    for (size_t i = minSize; i < newSize; i++)
        queuedForStream2[i] = 0;
    delete [] this->queuedForStream;
    this->queuedForStream = queuedForStream2;
    queuedForStream_arraysize = newSize;
}

void SctpSendQueueAbatedReq::setQueuedForStream(size_t k, uint64_t queuedForStream)
{
    if (k >= queuedForStream_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)queuedForStream_arraysize, (unsigned long)k);
    this->queuedForStream[k] = queuedForStream;
}

void SctpSendQueueAbatedReq::insertQueuedForStream(size_t k, uint64_t queuedForStream)
{
    if (k > queuedForStream_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)queuedForStream_arraysize, (unsigned long)k);
    size_t newSize = queuedForStream_arraysize + 1;
    uint64_t *queuedForStream2 = new uint64_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        queuedForStream2[i] = this->queuedForStream[i];
    queuedForStream2[k] = queuedForStream;
    for (i = k + 1; i < newSize; i++)
        queuedForStream2[i] = this->queuedForStream[i-1];
    delete [] this->queuedForStream;
    this->queuedForStream = queuedForStream2;
    queuedForStream_arraysize = newSize;
}

void SctpSendQueueAbatedReq::appendQueuedForStream(uint64_t queuedForStream)
{
    insertQueuedForStream(queuedForStream_arraysize, queuedForStream);
}

void SctpSendQueueAbatedReq::eraseQueuedForStream(size_t k)
{
    if (k >= queuedForStream_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)queuedForStream_arraysize, (unsigned long)k);
    size_t newSize = queuedForStream_arraysize - 1;
    uint64_t *queuedForStream2 = (newSize == 0) ? nullptr : new uint64_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        queuedForStream2[i] = this->queuedForStream[i];
    for (i = k; i < newSize; i++)
        queuedForStream2[i] = this->queuedForStream[i+1];
    delete [] this->queuedForStream;
    this->queuedForStream = queuedForStream2;
    queuedForStream_arraysize = newSize;
}

class SctpSendQueueAbatedReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_bytesAvailable,
        FIELD_bytesQueued,
        FIELD_bytesLimit,
        FIELD_queuedForStream,
    };
  public:
    SctpSendQueueAbatedReqDescriptor();
    virtual ~SctpSendQueueAbatedReqDescriptor();

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

Register_ClassDescriptor(SctpSendQueueAbatedReqDescriptor)

SctpSendQueueAbatedReqDescriptor::SctpSendQueueAbatedReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpSendQueueAbatedReq)), "inet::SctpCommandReq")
{
    propertyNames = nullptr;
}

SctpSendQueueAbatedReqDescriptor::~SctpSendQueueAbatedReqDescriptor()
{
    delete[] propertyNames;
}

bool SctpSendQueueAbatedReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSendQueueAbatedReq *>(obj)!=nullptr;
}

const char **SctpSendQueueAbatedReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSendQueueAbatedReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSendQueueAbatedReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpSendQueueAbatedReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_bytesAvailable
        FD_ISEDITABLE,    // FIELD_bytesQueued
        FD_ISEDITABLE,    // FIELD_bytesLimit
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_queuedForStream
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpSendQueueAbatedReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "bytesAvailable",
        "bytesQueued",
        "bytesLimit",
        "queuedForStream",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpSendQueueAbatedReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "bytesAvailable") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bytesQueued") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "bytesLimit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "queuedForStream") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSendQueueAbatedReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_bytesAvailable
        "uint64_t",    // FIELD_bytesQueued
        "uint64_t",    // FIELD_bytesLimit
        "uint64_t",    // FIELD_queuedForStream
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSendQueueAbatedReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSendQueueAbatedReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSendQueueAbatedReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_queuedForStream: return pp->getQueuedForStreamArraySize();
        default: return 0;
    }
}

void SctpSendQueueAbatedReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_queuedForStream: pp->setQueuedForStreamArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSendQueueAbatedReq'", field);
    }
}

const char *SctpSendQueueAbatedReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSendQueueAbatedReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_bytesAvailable: return uint642string(pp->getBytesAvailable());
        case FIELD_bytesQueued: return uint642string(pp->getBytesQueued());
        case FIELD_bytesLimit: return uint642string(pp->getBytesLimit());
        case FIELD_queuedForStream: return uint642string(pp->getQueuedForStream(i));
        default: return "";
    }
}

void SctpSendQueueAbatedReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_bytesAvailable: pp->setBytesAvailable(string2uint64(value)); break;
        case FIELD_bytesQueued: pp->setBytesQueued(string2uint64(value)); break;
        case FIELD_bytesLimit: pp->setBytesLimit(string2uint64(value)); break;
        case FIELD_queuedForStream: pp->setQueuedForStream(i,string2uint64(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendQueueAbatedReq'", field);
    }
}

omnetpp::cValue SctpSendQueueAbatedReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_bytesAvailable: return (omnetpp::intval_t)(pp->getBytesAvailable());
        case FIELD_bytesQueued: return (omnetpp::intval_t)(pp->getBytesQueued());
        case FIELD_bytesLimit: return (omnetpp::intval_t)(pp->getBytesLimit());
        case FIELD_queuedForStream: return (omnetpp::intval_t)(pp->getQueuedForStream(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSendQueueAbatedReq' as cValue -- field index out of range?", field);
    }
}

void SctpSendQueueAbatedReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        case FIELD_bytesAvailable: pp->setBytesAvailable(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_bytesQueued: pp->setBytesQueued(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_bytesLimit: pp->setBytesLimit(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_queuedForStream: pp->setQueuedForStream(i,omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendQueueAbatedReq'", field);
    }
}

const char *SctpSendQueueAbatedReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSendQueueAbatedReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSendQueueAbatedReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSendQueueAbatedReq *pp = omnetpp::fromAnyPtr<SctpSendQueueAbatedReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSendQueueAbatedReq'", field);
    }
}

Register_Class(SctpPathInfo)

SctpPathInfo::SctpPathInfo(const char *name) : ::omnetpp::cNamedObject(name)
{
}

SctpPathInfo::SctpPathInfo(const SctpPathInfo& other) : ::omnetpp::cNamedObject(other)
{
    copy(other);
}

SctpPathInfo::~SctpPathInfo()
{
}

SctpPathInfo& SctpPathInfo::operator=(const SctpPathInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cNamedObject::operator=(other);
    copy(other);
    return *this;
}

void SctpPathInfo::copy(const SctpPathInfo& other)
{
    this->remoteAddress = other.remoteAddress;
}

void SctpPathInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cNamedObject::parsimPack(b);
    doParsimPacking(b,this->remoteAddress);
}

void SctpPathInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cNamedObject::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddress);
}

const L3Address& SctpPathInfo::getRemoteAddress() const
{
    return this->remoteAddress;
}

void SctpPathInfo::setRemoteAddress(const L3Address& remoteAddress)
{
    this->remoteAddress = remoteAddress;
}

class SctpPathInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddress,
    };
  public:
    SctpPathInfoDescriptor();
    virtual ~SctpPathInfoDescriptor();

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

Register_ClassDescriptor(SctpPathInfoDescriptor)

SctpPathInfoDescriptor::SctpPathInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SctpPathInfo)), "omnetpp::cNamedObject")
{
    propertyNames = nullptr;
}

SctpPathInfoDescriptor::~SctpPathInfoDescriptor()
{
    delete[] propertyNames;
}

bool SctpPathInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpPathInfo *>(obj)!=nullptr;
}

const char **SctpPathInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpPathInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpPathInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpPathInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpPathInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpPathInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpPathInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpPathInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpPathInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpPathInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpPathInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpPathInfo'", field);
    }
}

const char *SctpPathInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpPathInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return pp->getRemoteAddress().str();
        default: return "";
    }
}

void SctpPathInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfo'", field);
    }
}

omnetpp::cValue SctpPathInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpPathInfo' as cValue -- field index out of range?", field);
    }
}

void SctpPathInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfo'", field);
    }
}

const char *SctpPathInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpPathInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpPathInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPathInfo *pp = omnetpp::fromAnyPtr<SctpPathInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPathInfo'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

