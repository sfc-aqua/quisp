//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/xmipv6/MobilityHeader.msg.
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
#include "MobilityHeader_m.h"

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

Register_Enum(inet::MobilityHeaderType, (inet::MobilityHeaderType::BINDING_REFRESH_REQUEST, inet::MobilityHeaderType::HOME_TEST_INIT, inet::MobilityHeaderType::CARE_OF_TEST_INIT, inet::MobilityHeaderType::HOME_TEST, inet::MobilityHeaderType::CARE_OF_TEST, inet::MobilityHeaderType::BINDING_UPDATE, inet::MobilityHeaderType::BINDING_ACKNOWLEDGEMENT, inet::MobilityHeaderType::BINDING_ERROR));

Register_Class(MobilityHeader)

MobilityHeader::MobilityHeader() : ::inet::FieldsChunk()
{
}

MobilityHeader::MobilityHeader(const MobilityHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

MobilityHeader::~MobilityHeader()
{
}

MobilityHeader& MobilityHeader::operator=(const MobilityHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void MobilityHeader::copy(const MobilityHeader& other)
{
    this->mobilityHeaderType = other.mobilityHeaderType;
}

void MobilityHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->mobilityHeaderType);
}

void MobilityHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->mobilityHeaderType);
}

MobilityHeaderType MobilityHeader::getMobilityHeaderType() const
{
    return this->mobilityHeaderType;
}

void MobilityHeader::setMobilityHeaderType(MobilityHeaderType mobilityHeaderType)
{
    handleChange();
    this->mobilityHeaderType = mobilityHeaderType;
}

class MobilityHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_mobilityHeaderType,
    };
  public:
    MobilityHeaderDescriptor();
    virtual ~MobilityHeaderDescriptor();

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

Register_ClassDescriptor(MobilityHeaderDescriptor)

MobilityHeaderDescriptor::MobilityHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::MobilityHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

MobilityHeaderDescriptor::~MobilityHeaderDescriptor()
{
    delete[] propertyNames;
}

bool MobilityHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MobilityHeader *>(obj)!=nullptr;
}

const char **MobilityHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MobilityHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MobilityHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int MobilityHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_mobilityHeaderType
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *MobilityHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "mobilityHeaderType",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int MobilityHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "mobilityHeaderType") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *MobilityHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MobilityHeaderType",    // FIELD_mobilityHeaderType
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **MobilityHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_mobilityHeaderType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *MobilityHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_mobilityHeaderType:
            if (!strcmp(propertyName, "enum")) return "inet::MobilityHeaderType";
            return nullptr;
        default: return nullptr;
    }
}

int MobilityHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MobilityHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MobilityHeader'", field);
    }
}

const char *MobilityHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MobilityHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        case FIELD_mobilityHeaderType: return enum2string(pp->getMobilityHeaderType(), "inet::MobilityHeaderType");
        default: return "";
    }
}

void MobilityHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MobilityHeader'", field);
    }
}

omnetpp::cValue MobilityHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        case FIELD_mobilityHeaderType: return static_cast<int>(pp->getMobilityHeaderType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MobilityHeader' as cValue -- field index out of range?", field);
    }
}

void MobilityHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MobilityHeader'", field);
    }
}

const char *MobilityHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr MobilityHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MobilityHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MobilityHeader *pp = omnetpp::fromAnyPtr<MobilityHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MobilityHeader'", field);
    }
}

Register_Class(BindingUpdate)

BindingUpdate::BindingUpdate() : ::inet::MobilityHeader()
{
}

BindingUpdate::BindingUpdate(const BindingUpdate& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

BindingUpdate::~BindingUpdate()
{
}

BindingUpdate& BindingUpdate::operator=(const BindingUpdate& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void BindingUpdate::copy(const BindingUpdate& other)
{
    this->lifetime = other.lifetime;
    this->sequence = other.sequence;
    this->ackFlag = other.ackFlag;
    this->homeRegistrationFlag = other.homeRegistrationFlag;
    this->linkLocalAddressCompatibilityFlag = other.linkLocalAddressCompatibilityFlag;
    this->keyManagementFlag = other.keyManagementFlag;
    this->homeAddressMN = other.homeAddressMN;
    this->bindingAuthorizationData = other.bindingAuthorizationData;
}

void BindingUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->lifetime);
    doParsimPacking(b,this->sequence);
    doParsimPacking(b,this->ackFlag);
    doParsimPacking(b,this->homeRegistrationFlag);
    doParsimPacking(b,this->linkLocalAddressCompatibilityFlag);
    doParsimPacking(b,this->keyManagementFlag);
    doParsimPacking(b,this->homeAddressMN);
    doParsimPacking(b,this->bindingAuthorizationData);
}

void BindingUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->lifetime);
    doParsimUnpacking(b,this->sequence);
    doParsimUnpacking(b,this->ackFlag);
    doParsimUnpacking(b,this->homeRegistrationFlag);
    doParsimUnpacking(b,this->linkLocalAddressCompatibilityFlag);
    doParsimUnpacking(b,this->keyManagementFlag);
    doParsimUnpacking(b,this->homeAddressMN);
    doParsimUnpacking(b,this->bindingAuthorizationData);
}

unsigned int BindingUpdate::getLifetime() const
{
    return this->lifetime;
}

void BindingUpdate::setLifetime(unsigned int lifetime)
{
    handleChange();
    this->lifetime = lifetime;
}

unsigned int BindingUpdate::getSequence() const
{
    return this->sequence;
}

void BindingUpdate::setSequence(unsigned int sequence)
{
    handleChange();
    this->sequence = sequence;
}

bool BindingUpdate::getAckFlag() const
{
    return this->ackFlag;
}

void BindingUpdate::setAckFlag(bool ackFlag)
{
    handleChange();
    this->ackFlag = ackFlag;
}

bool BindingUpdate::getHomeRegistrationFlag() const
{
    return this->homeRegistrationFlag;
}

void BindingUpdate::setHomeRegistrationFlag(bool homeRegistrationFlag)
{
    handleChange();
    this->homeRegistrationFlag = homeRegistrationFlag;
}

bool BindingUpdate::getLinkLocalAddressCompatibilityFlag() const
{
    return this->linkLocalAddressCompatibilityFlag;
}

void BindingUpdate::setLinkLocalAddressCompatibilityFlag(bool linkLocalAddressCompatibilityFlag)
{
    handleChange();
    this->linkLocalAddressCompatibilityFlag = linkLocalAddressCompatibilityFlag;
}

bool BindingUpdate::getKeyManagementFlag() const
{
    return this->keyManagementFlag;
}

void BindingUpdate::setKeyManagementFlag(bool keyManagementFlag)
{
    handleChange();
    this->keyManagementFlag = keyManagementFlag;
}

const Ipv6Address& BindingUpdate::getHomeAddressMN() const
{
    return this->homeAddressMN;
}

void BindingUpdate::setHomeAddressMN(const Ipv6Address& homeAddressMN)
{
    handleChange();
    this->homeAddressMN = homeAddressMN;
}

int BindingUpdate::getBindingAuthorizationData() const
{
    return this->bindingAuthorizationData;
}

void BindingUpdate::setBindingAuthorizationData(int bindingAuthorizationData)
{
    handleChange();
    this->bindingAuthorizationData = bindingAuthorizationData;
}

class BindingUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lifetime,
        FIELD_sequence,
        FIELD_ackFlag,
        FIELD_homeRegistrationFlag,
        FIELD_linkLocalAddressCompatibilityFlag,
        FIELD_keyManagementFlag,
        FIELD_homeAddressMN,
        FIELD_bindingAuthorizationData,
    };
  public:
    BindingUpdateDescriptor();
    virtual ~BindingUpdateDescriptor();

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

Register_ClassDescriptor(BindingUpdateDescriptor)

BindingUpdateDescriptor::BindingUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::BindingUpdate)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

BindingUpdateDescriptor::~BindingUpdateDescriptor()
{
    delete[] propertyNames;
}

bool BindingUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BindingUpdate *>(obj)!=nullptr;
}

const char **BindingUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BindingUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BindingUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int BindingUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lifetime
        FD_ISEDITABLE,    // FIELD_sequence
        FD_ISEDITABLE,    // FIELD_ackFlag
        FD_ISEDITABLE,    // FIELD_homeRegistrationFlag
        FD_ISEDITABLE,    // FIELD_linkLocalAddressCompatibilityFlag
        FD_ISEDITABLE,    // FIELD_keyManagementFlag
        0,    // FIELD_homeAddressMN
        FD_ISEDITABLE,    // FIELD_bindingAuthorizationData
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *BindingUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lifetime",
        "sequence",
        "ackFlag",
        "homeRegistrationFlag",
        "linkLocalAddressCompatibilityFlag",
        "keyManagementFlag",
        "homeAddressMN",
        "bindingAuthorizationData",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int BindingUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lifetime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequence") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ackFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "homeRegistrationFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "linkLocalAddressCompatibilityFlag") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "keyManagementFlag") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "homeAddressMN") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "bindingAuthorizationData") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *BindingUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_lifetime
        "unsigned int",    // FIELD_sequence
        "bool",    // FIELD_ackFlag
        "bool",    // FIELD_homeRegistrationFlag
        "bool",    // FIELD_linkLocalAddressCompatibilityFlag
        "bool",    // FIELD_keyManagementFlag
        "inet::Ipv6Address",    // FIELD_homeAddressMN
        "int",    // FIELD_bindingAuthorizationData
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **BindingUpdateDescriptor::getFieldPropertyNames(int field) const
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

const char *BindingUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BindingUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BindingUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BindingUpdate'", field);
    }
}

const char *BindingUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BindingUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_lifetime: return ulong2string(pp->getLifetime());
        case FIELD_sequence: return ulong2string(pp->getSequence());
        case FIELD_ackFlag: return bool2string(pp->getAckFlag());
        case FIELD_homeRegistrationFlag: return bool2string(pp->getHomeRegistrationFlag());
        case FIELD_linkLocalAddressCompatibilityFlag: return bool2string(pp->getLinkLocalAddressCompatibilityFlag());
        case FIELD_keyManagementFlag: return bool2string(pp->getKeyManagementFlag());
        case FIELD_homeAddressMN: return pp->getHomeAddressMN().str();
        case FIELD_bindingAuthorizationData: return long2string(pp->getBindingAuthorizationData());
        default: return "";
    }
}

void BindingUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_lifetime: pp->setLifetime(string2ulong(value)); break;
        case FIELD_sequence: pp->setSequence(string2ulong(value)); break;
        case FIELD_ackFlag: pp->setAckFlag(string2bool(value)); break;
        case FIELD_homeRegistrationFlag: pp->setHomeRegistrationFlag(string2bool(value)); break;
        case FIELD_linkLocalAddressCompatibilityFlag: pp->setLinkLocalAddressCompatibilityFlag(string2bool(value)); break;
        case FIELD_keyManagementFlag: pp->setKeyManagementFlag(string2bool(value)); break;
        case FIELD_bindingAuthorizationData: pp->setBindingAuthorizationData(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingUpdate'", field);
    }
}

omnetpp::cValue BindingUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_lifetime: return (omnetpp::intval_t)(pp->getLifetime());
        case FIELD_sequence: return (omnetpp::intval_t)(pp->getSequence());
        case FIELD_ackFlag: return pp->getAckFlag();
        case FIELD_homeRegistrationFlag: return pp->getHomeRegistrationFlag();
        case FIELD_linkLocalAddressCompatibilityFlag: return pp->getLinkLocalAddressCompatibilityFlag();
        case FIELD_keyManagementFlag: return pp->getKeyManagementFlag();
        case FIELD_homeAddressMN: return omnetpp::toAnyPtr(&pp->getHomeAddressMN()); break;
        case FIELD_bindingAuthorizationData: return pp->getBindingAuthorizationData();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BindingUpdate' as cValue -- field index out of range?", field);
    }
}

void BindingUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_lifetime: pp->setLifetime(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_sequence: pp->setSequence(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_ackFlag: pp->setAckFlag(value.boolValue()); break;
        case FIELD_homeRegistrationFlag: pp->setHomeRegistrationFlag(value.boolValue()); break;
        case FIELD_linkLocalAddressCompatibilityFlag: pp->setLinkLocalAddressCompatibilityFlag(value.boolValue()); break;
        case FIELD_keyManagementFlag: pp->setKeyManagementFlag(value.boolValue()); break;
        case FIELD_bindingAuthorizationData: pp->setBindingAuthorizationData(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingUpdate'", field);
    }
}

const char *BindingUpdateDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BindingUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_homeAddressMN: return omnetpp::toAnyPtr(&pp->getHomeAddressMN()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BindingUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingUpdate *pp = omnetpp::fromAnyPtr<BindingUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingUpdate'", field);
    }
}

Register_Enum(inet::BaStatus, (inet::BaStatus::BINDING_UPDATE_ACCEPTED, inet::BaStatus::BU_ACCEPT_BUT_DISCOVER_PREFIX, inet::BaStatus::REASON_UNSPECIFIED, inet::BaStatus::ADMINISTRATIVELY_PROHIBITED, inet::BaStatus::INSUFFICIENT_RESOURCES, inet::BaStatus::HOME_REGISTRATION_NOT_SUPPORTED, inet::BaStatus::NOT_HOME_SUBNET, inet::BaStatus::NOT_HA_FOR_THIS_MN, inet::BaStatus::DAD_FAILED, inet::BaStatus::SEQUENCE_NUMBER_OUT_OF_WINDOW, inet::BaStatus::EXPIRED_HOME_NONCE_INDEX, inet::BaStatus::EXPIRED_CARE_OF_NONCE_INDEX, inet::BaStatus::EXPIRED_NONCES, inet::BaStatus::REGISTRATION_TYPE_CHANGE_DISALLOWED));

Register_Class(BindingAcknowledgement)

BindingAcknowledgement::BindingAcknowledgement() : ::inet::MobilityHeader()
{
}

BindingAcknowledgement::BindingAcknowledgement(const BindingAcknowledgement& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

BindingAcknowledgement::~BindingAcknowledgement()
{
}

BindingAcknowledgement& BindingAcknowledgement::operator=(const BindingAcknowledgement& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void BindingAcknowledgement::copy(const BindingAcknowledgement& other)
{
    this->status = other.status;
    this->sequenceNumber = other.sequenceNumber;
    this->lifetime = other.lifetime;
    this->keyManagementFlag = other.keyManagementFlag;
    this->bindingAuthorizationData = other.bindingAuthorizationData;
}

void BindingAcknowledgement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->lifetime);
    doParsimPacking(b,this->keyManagementFlag);
    doParsimPacking(b,this->bindingAuthorizationData);
}

void BindingAcknowledgement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->lifetime);
    doParsimUnpacking(b,this->keyManagementFlag);
    doParsimUnpacking(b,this->bindingAuthorizationData);
}

BaStatus BindingAcknowledgement::getStatus() const
{
    return this->status;
}

void BindingAcknowledgement::setStatus(BaStatus status)
{
    handleChange();
    this->status = status;
}

unsigned int BindingAcknowledgement::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void BindingAcknowledgement::setSequenceNumber(unsigned int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

unsigned int BindingAcknowledgement::getLifetime() const
{
    return this->lifetime;
}

void BindingAcknowledgement::setLifetime(unsigned int lifetime)
{
    handleChange();
    this->lifetime = lifetime;
}

bool BindingAcknowledgement::getKeyManagementFlag() const
{
    return this->keyManagementFlag;
}

void BindingAcknowledgement::setKeyManagementFlag(bool keyManagementFlag)
{
    handleChange();
    this->keyManagementFlag = keyManagementFlag;
}

int BindingAcknowledgement::getBindingAuthorizationData() const
{
    return this->bindingAuthorizationData;
}

void BindingAcknowledgement::setBindingAuthorizationData(int bindingAuthorizationData)
{
    handleChange();
    this->bindingAuthorizationData = bindingAuthorizationData;
}

class BindingAcknowledgementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_status,
        FIELD_sequenceNumber,
        FIELD_lifetime,
        FIELD_keyManagementFlag,
        FIELD_bindingAuthorizationData,
    };
  public:
    BindingAcknowledgementDescriptor();
    virtual ~BindingAcknowledgementDescriptor();

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

Register_ClassDescriptor(BindingAcknowledgementDescriptor)

BindingAcknowledgementDescriptor::BindingAcknowledgementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::BindingAcknowledgement)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

BindingAcknowledgementDescriptor::~BindingAcknowledgementDescriptor()
{
    delete[] propertyNames;
}

bool BindingAcknowledgementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BindingAcknowledgement *>(obj)!=nullptr;
}

const char **BindingAcknowledgementDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BindingAcknowledgementDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BindingAcknowledgementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int BindingAcknowledgementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_lifetime
        FD_ISEDITABLE,    // FIELD_keyManagementFlag
        FD_ISEDITABLE,    // FIELD_bindingAuthorizationData
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *BindingAcknowledgementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "status",
        "sequenceNumber",
        "lifetime",
        "keyManagementFlag",
        "bindingAuthorizationData",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int BindingAcknowledgementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "lifetime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "keyManagementFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "bindingAuthorizationData") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *BindingAcknowledgementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::BaStatus",    // FIELD_status
        "unsigned int",    // FIELD_sequenceNumber
        "unsigned int",    // FIELD_lifetime
        "bool",    // FIELD_keyManagementFlag
        "int",    // FIELD_bindingAuthorizationData
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **BindingAcknowledgementDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BindingAcknowledgementDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status:
            if (!strcmp(propertyName, "enum")) return "inet::BaStatus";
            return nullptr;
        default: return nullptr;
    }
}

int BindingAcknowledgementDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BindingAcknowledgementDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BindingAcknowledgement'", field);
    }
}

const char *BindingAcknowledgementDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BindingAcknowledgementDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        case FIELD_status: return enum2string(pp->getStatus(), "inet::BaStatus");
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_lifetime: return ulong2string(pp->getLifetime());
        case FIELD_keyManagementFlag: return bool2string(pp->getKeyManagementFlag());
        case FIELD_bindingAuthorizationData: return long2string(pp->getBindingAuthorizationData());
        default: return "";
    }
}

void BindingAcknowledgementDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        case FIELD_lifetime: pp->setLifetime(string2ulong(value)); break;
        case FIELD_keyManagementFlag: pp->setKeyManagementFlag(string2bool(value)); break;
        case FIELD_bindingAuthorizationData: pp->setBindingAuthorizationData(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingAcknowledgement'", field);
    }
}

omnetpp::cValue BindingAcknowledgementDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        case FIELD_status: return static_cast<int>(pp->getStatus());
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_lifetime: return (omnetpp::intval_t)(pp->getLifetime());
        case FIELD_keyManagementFlag: return pp->getKeyManagementFlag();
        case FIELD_bindingAuthorizationData: return pp->getBindingAuthorizationData();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BindingAcknowledgement' as cValue -- field index out of range?", field);
    }
}

void BindingAcknowledgementDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_lifetime: pp->setLifetime(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_keyManagementFlag: pp->setKeyManagementFlag(value.boolValue()); break;
        case FIELD_bindingAuthorizationData: pp->setBindingAuthorizationData(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingAcknowledgement'", field);
    }
}

const char *BindingAcknowledgementDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BindingAcknowledgementDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BindingAcknowledgementDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingAcknowledgement *pp = omnetpp::fromAnyPtr<BindingAcknowledgement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingAcknowledgement'", field);
    }
}

Register_Enum(inet::BeStatus, (inet::BeStatus::UNKNOWN_BINDING_FOR_HOME_ADDRESS_DEST_OPTION, inet::BeStatus::UNKNOWN_MH_TYPE));

Register_Class(BindingError)

BindingError::BindingError() : ::inet::MobilityHeader()
{
}

BindingError::BindingError(const BindingError& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

BindingError::~BindingError()
{
}

BindingError& BindingError::operator=(const BindingError& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void BindingError::copy(const BindingError& other)
{
    this->status = other.status;
    this->homeAddress = other.homeAddress;
}

void BindingError::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->homeAddress);
}

void BindingError::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->homeAddress);
}

BeStatus BindingError::getStatus() const
{
    return this->status;
}

void BindingError::setStatus(BeStatus status)
{
    handleChange();
    this->status = status;
}

const Ipv6Address& BindingError::getHomeAddress() const
{
    return this->homeAddress;
}

void BindingError::setHomeAddress(const Ipv6Address& homeAddress)
{
    handleChange();
    this->homeAddress = homeAddress;
}

class BindingErrorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_status,
        FIELD_homeAddress,
    };
  public:
    BindingErrorDescriptor();
    virtual ~BindingErrorDescriptor();

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

Register_ClassDescriptor(BindingErrorDescriptor)

BindingErrorDescriptor::BindingErrorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::BindingError)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

BindingErrorDescriptor::~BindingErrorDescriptor()
{
    delete[] propertyNames;
}

bool BindingErrorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BindingError *>(obj)!=nullptr;
}

const char **BindingErrorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BindingErrorDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BindingErrorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int BindingErrorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_status
        0,    // FIELD_homeAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *BindingErrorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "status",
        "homeAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int BindingErrorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "homeAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *BindingErrorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::BeStatus",    // FIELD_status
        "inet::Ipv6Address",    // FIELD_homeAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **BindingErrorDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BindingErrorDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status:
            if (!strcmp(propertyName, "enum")) return "inet::BeStatus";
            return nullptr;
        default: return nullptr;
    }
}

int BindingErrorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BindingErrorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BindingError'", field);
    }
}

const char *BindingErrorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BindingErrorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        case FIELD_status: return enum2string(pp->getStatus(), "inet::BeStatus");
        case FIELD_homeAddress: return pp->getHomeAddress().str();
        default: return "";
    }
}

void BindingErrorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingError'", field);
    }
}

omnetpp::cValue BindingErrorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        case FIELD_status: return static_cast<int>(pp->getStatus());
        case FIELD_homeAddress: return omnetpp::toAnyPtr(&pp->getHomeAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BindingError' as cValue -- field index out of range?", field);
    }
}

void BindingErrorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingError'", field);
    }
}

const char *BindingErrorDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BindingErrorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        case FIELD_homeAddress: return omnetpp::toAnyPtr(&pp->getHomeAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BindingErrorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingError *pp = omnetpp::fromAnyPtr<BindingError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingError'", field);
    }
}

Register_Class(HomeTestInit)

HomeTestInit::HomeTestInit() : ::inet::MobilityHeader()
{
}

HomeTestInit::HomeTestInit(const HomeTestInit& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

HomeTestInit::~HomeTestInit()
{
}

HomeTestInit& HomeTestInit::operator=(const HomeTestInit& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void HomeTestInit::copy(const HomeTestInit& other)
{
    this->homeInitCookie = other.homeInitCookie;
}

void HomeTestInit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->homeInitCookie);
}

void HomeTestInit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->homeInitCookie);
}

unsigned int HomeTestInit::getHomeInitCookie() const
{
    return this->homeInitCookie;
}

void HomeTestInit::setHomeInitCookie(unsigned int homeInitCookie)
{
    handleChange();
    this->homeInitCookie = homeInitCookie;
}

class HomeTestInitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_homeInitCookie,
    };
  public:
    HomeTestInitDescriptor();
    virtual ~HomeTestInitDescriptor();

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

Register_ClassDescriptor(HomeTestInitDescriptor)

HomeTestInitDescriptor::HomeTestInitDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HomeTestInit)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

HomeTestInitDescriptor::~HomeTestInitDescriptor()
{
    delete[] propertyNames;
}

bool HomeTestInitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HomeTestInit *>(obj)!=nullptr;
}

const char **HomeTestInitDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HomeTestInitDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HomeTestInitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HomeTestInitDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_homeInitCookie
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HomeTestInitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "homeInitCookie",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HomeTestInitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "homeInitCookie") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HomeTestInitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_homeInitCookie
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HomeTestInitDescriptor::getFieldPropertyNames(int field) const
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

const char *HomeTestInitDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HomeTestInitDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HomeTestInitDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HomeTestInit'", field);
    }
}

const char *HomeTestInitDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HomeTestInitDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: return ulong2string(pp->getHomeInitCookie());
        default: return "";
    }
}

void HomeTestInitDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: pp->setHomeInitCookie(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTestInit'", field);
    }
}

omnetpp::cValue HomeTestInitDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: return (omnetpp::intval_t)(pp->getHomeInitCookie());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HomeTestInit' as cValue -- field index out of range?", field);
    }
}

void HomeTestInitDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: pp->setHomeInitCookie(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTestInit'", field);
    }
}

const char *HomeTestInitDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HomeTestInitDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HomeTestInitDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTestInit *pp = omnetpp::fromAnyPtr<HomeTestInit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTestInit'", field);
    }
}

Register_Class(HomeTest)

HomeTest::HomeTest() : ::inet::MobilityHeader()
{
}

HomeTest::HomeTest(const HomeTest& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

HomeTest::~HomeTest()
{
}

HomeTest& HomeTest::operator=(const HomeTest& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void HomeTest::copy(const HomeTest& other)
{
    this->homeInitCookie = other.homeInitCookie;
    this->homeKeyGenToken = other.homeKeyGenToken;
}

void HomeTest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->homeInitCookie);
    doParsimPacking(b,this->homeKeyGenToken);
}

void HomeTest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->homeInitCookie);
    doParsimUnpacking(b,this->homeKeyGenToken);
}

unsigned int HomeTest::getHomeInitCookie() const
{
    return this->homeInitCookie;
}

void HomeTest::setHomeInitCookie(unsigned int homeInitCookie)
{
    handleChange();
    this->homeInitCookie = homeInitCookie;
}

unsigned int HomeTest::getHomeKeyGenToken() const
{
    return this->homeKeyGenToken;
}

void HomeTest::setHomeKeyGenToken(unsigned int homeKeyGenToken)
{
    handleChange();
    this->homeKeyGenToken = homeKeyGenToken;
}

class HomeTestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_homeInitCookie,
        FIELD_homeKeyGenToken,
    };
  public:
    HomeTestDescriptor();
    virtual ~HomeTestDescriptor();

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

Register_ClassDescriptor(HomeTestDescriptor)

HomeTestDescriptor::HomeTestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HomeTest)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

HomeTestDescriptor::~HomeTestDescriptor()
{
    delete[] propertyNames;
}

bool HomeTestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HomeTest *>(obj)!=nullptr;
}

const char **HomeTestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HomeTestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HomeTestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int HomeTestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_homeInitCookie
        FD_ISEDITABLE,    // FIELD_homeKeyGenToken
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *HomeTestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "homeInitCookie",
        "homeKeyGenToken",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int HomeTestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "homeInitCookie") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "homeKeyGenToken") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *HomeTestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_homeInitCookie
        "unsigned int",    // FIELD_homeKeyGenToken
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **HomeTestDescriptor::getFieldPropertyNames(int field) const
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

const char *HomeTestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HomeTestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HomeTestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HomeTest'", field);
    }
}

const char *HomeTestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HomeTestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: return ulong2string(pp->getHomeInitCookie());
        case FIELD_homeKeyGenToken: return ulong2string(pp->getHomeKeyGenToken());
        default: return "";
    }
}

void HomeTestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: pp->setHomeInitCookie(string2ulong(value)); break;
        case FIELD_homeKeyGenToken: pp->setHomeKeyGenToken(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTest'", field);
    }
}

omnetpp::cValue HomeTestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: return (omnetpp::intval_t)(pp->getHomeInitCookie());
        case FIELD_homeKeyGenToken: return (omnetpp::intval_t)(pp->getHomeKeyGenToken());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HomeTest' as cValue -- field index out of range?", field);
    }
}

void HomeTestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        case FIELD_homeInitCookie: pp->setHomeInitCookie(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_homeKeyGenToken: pp->setHomeKeyGenToken(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTest'", field);
    }
}

const char *HomeTestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HomeTestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HomeTestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeTest *pp = omnetpp::fromAnyPtr<HomeTest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeTest'", field);
    }
}

Register_Class(CareOfTestInit)

CareOfTestInit::CareOfTestInit() : ::inet::MobilityHeader()
{
}

CareOfTestInit::CareOfTestInit(const CareOfTestInit& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

CareOfTestInit::~CareOfTestInit()
{
}

CareOfTestInit& CareOfTestInit::operator=(const CareOfTestInit& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void CareOfTestInit::copy(const CareOfTestInit& other)
{
    this->careOfInitCookie = other.careOfInitCookie;
}

void CareOfTestInit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->careOfInitCookie);
}

void CareOfTestInit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->careOfInitCookie);
}

unsigned int CareOfTestInit::getCareOfInitCookie() const
{
    return this->careOfInitCookie;
}

void CareOfTestInit::setCareOfInitCookie(unsigned int careOfInitCookie)
{
    handleChange();
    this->careOfInitCookie = careOfInitCookie;
}

class CareOfTestInitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_careOfInitCookie,
    };
  public:
    CareOfTestInitDescriptor();
    virtual ~CareOfTestInitDescriptor();

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

Register_ClassDescriptor(CareOfTestInitDescriptor)

CareOfTestInitDescriptor::CareOfTestInitDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CareOfTestInit)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

CareOfTestInitDescriptor::~CareOfTestInitDescriptor()
{
    delete[] propertyNames;
}

bool CareOfTestInitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CareOfTestInit *>(obj)!=nullptr;
}

const char **CareOfTestInitDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CareOfTestInitDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CareOfTestInitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int CareOfTestInitDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_careOfInitCookie
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *CareOfTestInitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "careOfInitCookie",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int CareOfTestInitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "careOfInitCookie") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *CareOfTestInitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_careOfInitCookie
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **CareOfTestInitDescriptor::getFieldPropertyNames(int field) const
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

const char *CareOfTestInitDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CareOfTestInitDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CareOfTestInitDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CareOfTestInit'", field);
    }
}

const char *CareOfTestInitDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CareOfTestInitDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: return ulong2string(pp->getCareOfInitCookie());
        default: return "";
    }
}

void CareOfTestInitDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: pp->setCareOfInitCookie(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTestInit'", field);
    }
}

omnetpp::cValue CareOfTestInitDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: return (omnetpp::intval_t)(pp->getCareOfInitCookie());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CareOfTestInit' as cValue -- field index out of range?", field);
    }
}

void CareOfTestInitDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: pp->setCareOfInitCookie(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTestInit'", field);
    }
}

const char *CareOfTestInitDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CareOfTestInitDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CareOfTestInitDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTestInit *pp = omnetpp::fromAnyPtr<CareOfTestInit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTestInit'", field);
    }
}

Register_Class(CareOfTest)

CareOfTest::CareOfTest() : ::inet::MobilityHeader()
{
}

CareOfTest::CareOfTest(const CareOfTest& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

CareOfTest::~CareOfTest()
{
}

CareOfTest& CareOfTest::operator=(const CareOfTest& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void CareOfTest::copy(const CareOfTest& other)
{
    this->careOfInitCookie = other.careOfInitCookie;
    this->careOfKeyGenToken = other.careOfKeyGenToken;
}

void CareOfTest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
    doParsimPacking(b,this->careOfInitCookie);
    doParsimPacking(b,this->careOfKeyGenToken);
}

void CareOfTest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->careOfInitCookie);
    doParsimUnpacking(b,this->careOfKeyGenToken);
}

unsigned int CareOfTest::getCareOfInitCookie() const
{
    return this->careOfInitCookie;
}

void CareOfTest::setCareOfInitCookie(unsigned int careOfInitCookie)
{
    handleChange();
    this->careOfInitCookie = careOfInitCookie;
}

unsigned int CareOfTest::getCareOfKeyGenToken() const
{
    return this->careOfKeyGenToken;
}

void CareOfTest::setCareOfKeyGenToken(unsigned int careOfKeyGenToken)
{
    handleChange();
    this->careOfKeyGenToken = careOfKeyGenToken;
}

class CareOfTestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_careOfInitCookie,
        FIELD_careOfKeyGenToken,
    };
  public:
    CareOfTestDescriptor();
    virtual ~CareOfTestDescriptor();

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

Register_ClassDescriptor(CareOfTestDescriptor)

CareOfTestDescriptor::CareOfTestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CareOfTest)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

CareOfTestDescriptor::~CareOfTestDescriptor()
{
    delete[] propertyNames;
}

bool CareOfTestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CareOfTest *>(obj)!=nullptr;
}

const char **CareOfTestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CareOfTestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CareOfTestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int CareOfTestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_careOfInitCookie
        FD_ISEDITABLE,    // FIELD_careOfKeyGenToken
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *CareOfTestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "careOfInitCookie",
        "careOfKeyGenToken",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int CareOfTestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "careOfInitCookie") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "careOfKeyGenToken") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *CareOfTestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_careOfInitCookie
        "unsigned int",    // FIELD_careOfKeyGenToken
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **CareOfTestDescriptor::getFieldPropertyNames(int field) const
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

const char *CareOfTestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CareOfTestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CareOfTestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CareOfTest'", field);
    }
}

const char *CareOfTestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CareOfTestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: return ulong2string(pp->getCareOfInitCookie());
        case FIELD_careOfKeyGenToken: return ulong2string(pp->getCareOfKeyGenToken());
        default: return "";
    }
}

void CareOfTestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: pp->setCareOfInitCookie(string2ulong(value)); break;
        case FIELD_careOfKeyGenToken: pp->setCareOfKeyGenToken(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTest'", field);
    }
}

omnetpp::cValue CareOfTestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: return (omnetpp::intval_t)(pp->getCareOfInitCookie());
        case FIELD_careOfKeyGenToken: return (omnetpp::intval_t)(pp->getCareOfKeyGenToken());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CareOfTest' as cValue -- field index out of range?", field);
    }
}

void CareOfTestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        case FIELD_careOfInitCookie: pp->setCareOfInitCookie(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_careOfKeyGenToken: pp->setCareOfKeyGenToken(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTest'", field);
    }
}

const char *CareOfTestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CareOfTestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CareOfTestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CareOfTest *pp = omnetpp::fromAnyPtr<CareOfTest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CareOfTest'", field);
    }
}

Register_Class(BindingRefreshRequest)

BindingRefreshRequest::BindingRefreshRequest() : ::inet::MobilityHeader()
{
}

BindingRefreshRequest::BindingRefreshRequest(const BindingRefreshRequest& other) : ::inet::MobilityHeader(other)
{
    copy(other);
}

BindingRefreshRequest::~BindingRefreshRequest()
{
}

BindingRefreshRequest& BindingRefreshRequest::operator=(const BindingRefreshRequest& other)
{
    if (this == &other) return *this;
    ::inet::MobilityHeader::operator=(other);
    copy(other);
    return *this;
}

void BindingRefreshRequest::copy(const BindingRefreshRequest& other)
{
}

void BindingRefreshRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::MobilityHeader::parsimPack(b);
}

void BindingRefreshRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::MobilityHeader::parsimUnpack(b);
}

class BindingRefreshRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    BindingRefreshRequestDescriptor();
    virtual ~BindingRefreshRequestDescriptor();

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

Register_ClassDescriptor(BindingRefreshRequestDescriptor)

BindingRefreshRequestDescriptor::BindingRefreshRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::BindingRefreshRequest)), "inet::MobilityHeader")
{
    propertyNames = nullptr;
}

BindingRefreshRequestDescriptor::~BindingRefreshRequestDescriptor()
{
    delete[] propertyNames;
}

bool BindingRefreshRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BindingRefreshRequest *>(obj)!=nullptr;
}

const char **BindingRefreshRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BindingRefreshRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BindingRefreshRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int BindingRefreshRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *BindingRefreshRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int BindingRefreshRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *BindingRefreshRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **BindingRefreshRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *BindingRefreshRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BindingRefreshRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BindingRefreshRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BindingRefreshRequest'", field);
    }
}

const char *BindingRefreshRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BindingRefreshRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void BindingRefreshRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingRefreshRequest'", field);
    }
}

omnetpp::cValue BindingRefreshRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BindingRefreshRequest' as cValue -- field index out of range?", field);
    }
}

void BindingRefreshRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingRefreshRequest'", field);
    }
}

const char *BindingRefreshRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr BindingRefreshRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BindingRefreshRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BindingRefreshRequest *pp = omnetpp::fromAnyPtr<BindingRefreshRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BindingRefreshRequest'", field);
    }
}

Register_Class(HomeAddressOption)

HomeAddressOption::HomeAddressOption() : ::inet::Ipv6DestinationOptionsHeader()
{
}

HomeAddressOption::HomeAddressOption(const HomeAddressOption& other) : ::inet::Ipv6DestinationOptionsHeader(other)
{
    copy(other);
}

HomeAddressOption::~HomeAddressOption()
{
}

HomeAddressOption& HomeAddressOption::operator=(const HomeAddressOption& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6DestinationOptionsHeader::operator=(other);
    copy(other);
    return *this;
}

void HomeAddressOption::copy(const HomeAddressOption& other)
{
    this->homeAddress = other.homeAddress;
}

void HomeAddressOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6DestinationOptionsHeader::parsimPack(b);
    doParsimPacking(b,this->homeAddress);
}

void HomeAddressOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6DestinationOptionsHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->homeAddress);
}

const Ipv6Address& HomeAddressOption::getHomeAddress() const
{
    return this->homeAddress;
}

void HomeAddressOption::setHomeAddress(const Ipv6Address& homeAddress)
{
    this->homeAddress = homeAddress;
}

class HomeAddressOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_homeAddress,
    };
  public:
    HomeAddressOptionDescriptor();
    virtual ~HomeAddressOptionDescriptor();

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

Register_ClassDescriptor(HomeAddressOptionDescriptor)

HomeAddressOptionDescriptor::HomeAddressOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HomeAddressOption)), "inet::Ipv6DestinationOptionsHeader")
{
    propertyNames = nullptr;
}

HomeAddressOptionDescriptor::~HomeAddressOptionDescriptor()
{
    delete[] propertyNames;
}

bool HomeAddressOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HomeAddressOption *>(obj)!=nullptr;
}

const char **HomeAddressOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HomeAddressOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HomeAddressOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HomeAddressOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_homeAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HomeAddressOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "homeAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HomeAddressOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "homeAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HomeAddressOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_homeAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HomeAddressOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *HomeAddressOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HomeAddressOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HomeAddressOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HomeAddressOption'", field);
    }
}

const char *HomeAddressOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HomeAddressOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        case FIELD_homeAddress: return pp->getHomeAddress().str();
        default: return "";
    }
}

void HomeAddressOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeAddressOption'", field);
    }
}

omnetpp::cValue HomeAddressOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        case FIELD_homeAddress: return omnetpp::toAnyPtr(&pp->getHomeAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HomeAddressOption' as cValue -- field index out of range?", field);
    }
}

void HomeAddressOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeAddressOption'", field);
    }
}

const char *HomeAddressOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HomeAddressOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        case FIELD_homeAddress: return omnetpp::toAnyPtr(&pp->getHomeAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HomeAddressOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HomeAddressOption *pp = omnetpp::fromAnyPtr<HomeAddressOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HomeAddressOption'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

