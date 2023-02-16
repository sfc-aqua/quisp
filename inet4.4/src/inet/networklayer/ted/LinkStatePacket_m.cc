//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ted/LinkStatePacket.msg.
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
#include "LinkStatePacket_m.h"

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

Register_Class(LinkStateMsg)

LinkStateMsg::LinkStateMsg() : ::inet::FieldsChunk()
{
}

LinkStateMsg::LinkStateMsg(const LinkStateMsg& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LinkStateMsg::~LinkStateMsg()
{
    delete [] this->linkInfo;
}

LinkStateMsg& LinkStateMsg::operator=(const LinkStateMsg& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LinkStateMsg::copy(const LinkStateMsg& other)
{
    delete [] this->linkInfo;
    this->linkInfo = (other.linkInfo_arraysize==0) ? nullptr : new TeLinkStateInfo[other.linkInfo_arraysize];
    linkInfo_arraysize = other.linkInfo_arraysize;
    for (size_t i = 0; i < linkInfo_arraysize; i++) {
        this->linkInfo[i] = other.linkInfo[i];
    }
    this->request = other.request;
    this->command = other.command;
}

void LinkStateMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    b->pack(linkInfo_arraysize);
    doParsimArrayPacking(b,this->linkInfo,linkInfo_arraysize);
    doParsimPacking(b,this->request);
    doParsimPacking(b,this->command);
}

void LinkStateMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    delete [] this->linkInfo;
    b->unpack(linkInfo_arraysize);
    if (linkInfo_arraysize == 0) {
        this->linkInfo = nullptr;
    } else {
        this->linkInfo = new TeLinkStateInfo[linkInfo_arraysize];
        doParsimArrayUnpacking(b,this->linkInfo,linkInfo_arraysize);
    }
    doParsimUnpacking(b,this->request);
    doParsimUnpacking(b,this->command);
}

size_t LinkStateMsg::getLinkInfoArraySize() const
{
    return linkInfo_arraysize;
}

const TeLinkStateInfo& LinkStateMsg::getLinkInfo(size_t k) const
{
    if (k >= linkInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)linkInfo_arraysize, (unsigned long)k);
    return this->linkInfo[k];
}

void LinkStateMsg::setLinkInfoArraySize(size_t newSize)
{
    handleChange();
    TeLinkStateInfo *linkInfo2 = (newSize==0) ? nullptr : new TeLinkStateInfo[newSize];
    size_t minSize = linkInfo_arraysize < newSize ? linkInfo_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        linkInfo2[i] = this->linkInfo[i];
    delete [] this->linkInfo;
    this->linkInfo = linkInfo2;
    linkInfo_arraysize = newSize;
}

void LinkStateMsg::setLinkInfo(size_t k, const TeLinkStateInfo& linkInfo)
{
    if (k >= linkInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)linkInfo_arraysize, (unsigned long)k);
    handleChange();
    this->linkInfo[k] = linkInfo;
}

void LinkStateMsg::insertLinkInfo(size_t k, const TeLinkStateInfo& linkInfo)
{
    if (k > linkInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)linkInfo_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = linkInfo_arraysize + 1;
    TeLinkStateInfo *linkInfo2 = new TeLinkStateInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        linkInfo2[i] = this->linkInfo[i];
    linkInfo2[k] = linkInfo;
    for (i = k + 1; i < newSize; i++)
        linkInfo2[i] = this->linkInfo[i-1];
    delete [] this->linkInfo;
    this->linkInfo = linkInfo2;
    linkInfo_arraysize = newSize;
}

void LinkStateMsg::appendLinkInfo(const TeLinkStateInfo& linkInfo)
{
    insertLinkInfo(linkInfo_arraysize, linkInfo);
}

void LinkStateMsg::eraseLinkInfo(size_t k)
{
    if (k >= linkInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)linkInfo_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = linkInfo_arraysize - 1;
    TeLinkStateInfo *linkInfo2 = (newSize == 0) ? nullptr : new TeLinkStateInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        linkInfo2[i] = this->linkInfo[i];
    for (i = k; i < newSize; i++)
        linkInfo2[i] = this->linkInfo[i+1];
    delete [] this->linkInfo;
    this->linkInfo = linkInfo2;
    linkInfo_arraysize = newSize;
}

bool LinkStateMsg::getRequest() const
{
    return this->request;
}

void LinkStateMsg::setRequest(bool request)
{
    handleChange();
    this->request = request;
}

int LinkStateMsg::getCommand() const
{
    return this->command;
}

void LinkStateMsg::setCommand(int command)
{
    handleChange();
    this->command = command;
}

class LinkStateMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_linkInfo,
        FIELD_request,
        FIELD_command,
    };
  public:
    LinkStateMsgDescriptor();
    virtual ~LinkStateMsgDescriptor();

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

Register_ClassDescriptor(LinkStateMsgDescriptor)

LinkStateMsgDescriptor::LinkStateMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LinkStateMsg)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LinkStateMsgDescriptor::~LinkStateMsgDescriptor()
{
    delete[] propertyNames;
}

bool LinkStateMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkStateMsg *>(obj)!=nullptr;
}

const char **LinkStateMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinkStateMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinkStateMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LinkStateMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_linkInfo
        FD_ISEDITABLE,    // FIELD_request
        FD_ISEDITABLE,    // FIELD_command
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LinkStateMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "linkInfo",
        "request",
        "command",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LinkStateMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "linkInfo") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "request") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "command") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LinkStateMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TeLinkStateInfo",    // FIELD_linkInfo
        "bool",    // FIELD_request
        "int",    // FIELD_command
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkStateMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *LinkStateMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LinkStateMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_linkInfo: return pp->getLinkInfoArraySize();
        default: return 0;
    }
}

void LinkStateMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_linkInfo: pp->setLinkInfoArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinkStateMsg'", field);
    }
}

const char *LinkStateMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkStateMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_linkInfo: return "";
        case FIELD_request: return bool2string(pp->getRequest());
        case FIELD_command: return long2string(pp->getCommand());
        default: return "";
    }
}

void LinkStateMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->setRequest(string2bool(value)); break;
        case FIELD_command: pp->setCommand(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateMsg'", field);
    }
}

omnetpp::cValue LinkStateMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_linkInfo: return omnetpp::toAnyPtr(&pp->getLinkInfo(i)); break;
        case FIELD_request: return pp->getRequest();
        case FIELD_command: return pp->getCommand();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinkStateMsg' as cValue -- field index out of range?", field);
    }
}

void LinkStateMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->setRequest(value.boolValue()); break;
        case FIELD_command: pp->setCommand(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateMsg'", field);
    }
}

const char *LinkStateMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_linkInfo: return omnetpp::opp_typename(typeid(TeLinkStateInfo));
        default: return nullptr;
    };
}

omnetpp::any_ptr LinkStateMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_linkInfo: return omnetpp::toAnyPtr(&pp->getLinkInfo(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinkStateMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateMsg *pp = omnetpp::fromAnyPtr<LinkStateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateMsg'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

