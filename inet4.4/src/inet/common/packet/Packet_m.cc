//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/packet/Packet.msg.
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
#include "Packet_m.h"

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

class PacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dataLength,
        FIELD_totalLength,
        FIELD_data,
        FIELD_dissection,
        FIELD_content,
        FIELD_tags,
        FIELD_regionTags,
        FIELD_frontOffset,
        FIELD_backOffset,
        FIELD_front,
        FIELD_back,
    };
  public:
    PacketDescriptor();
    virtual ~PacketDescriptor();

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

Register_ClassDescriptor(PacketDescriptor)

PacketDescriptor::PacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Packet)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

PacketDescriptor::~PacketDescriptor()
{
    delete[] propertyNames;
}

bool PacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Packet *>(obj)!=nullptr;
}

const char **PacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PacketDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int PacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_dataLength
        0,    // FIELD_totalLength
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_data
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_dissection
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_content
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_tags
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_regionTags
        0,    // FIELD_frontOffset
        0,    // FIELD_backOffset
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_front
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_back
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *PacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dataLength",
        "totalLength",
        "data",
        "dissection",
        "content",
        "tags",
        "regionTags",
        "frontOffset",
        "backOffset",
        "front",
        "back",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int PacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dataLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "totalLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dissection") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "content") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "tags") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "regionTags") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "frontOffset") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "backOffset") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "front") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "back") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *PacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::b",    // FIELD_dataLength
        "inet::b",    // FIELD_totalLength
        "inet::ChunkTemporarySharedPtr",    // FIELD_data
        "inet::ChunkTemporarySharedPtr",    // FIELD_dissection
        "inet::Chunk",    // FIELD_content
        "omnetpp::cObject",    // FIELD_tags
        "inet::SharingRegionTagSet::TagBaseRegionTag",    // FIELD_regionTags
        "inet::b",    // FIELD_frontOffset
        "inet::b",    // FIELD_backOffset
        "inet::ChunkTemporarySharedPtr",    // FIELD_front
        "inet::ChunkTemporarySharedPtr",    // FIELD_back
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_data: {
            static const char *names[] = { "packetData", "getter",  nullptr };
            return names;
        }
        case FIELD_dissection: {
            static const char *names[] = { "packetData", "getter",  nullptr };
            return names;
        }
        case FIELD_content: {
            static const char *names[] = { "packetData", "getter",  nullptr };
            return names;
        }
        case FIELD_tags: {
            static const char *names[] = { "getter", "sizeGetter",  nullptr };
            return names;
        }
        case FIELD_regionTags: {
            static const char *names[] = { "getter", "sizeGetter",  nullptr };
            return names;
        }
        case FIELD_front: {
            static const char *names[] = { "packetData", "getter",  nullptr };
            return names;
        }
        case FIELD_back: {
            static const char *names[] = { "packetData", "getter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_data:
            if (!strcmp(propertyName, "packetData")) return "";
            if (!strcmp(propertyName, "getter")) return "getData";
            return nullptr;
        case FIELD_dissection:
            if (!strcmp(propertyName, "packetData")) return "";
            if (!strcmp(propertyName, "getter")) return "getDissection";
            return nullptr;
        case FIELD_content:
            if (!strcmp(propertyName, "packetData")) return "";
            if (!strcmp(propertyName, "getter")) return "getContent";
            return nullptr;
        case FIELD_tags:
            if (!strcmp(propertyName, "getter")) return "_getTag";
            if (!strcmp(propertyName, "sizeGetter")) return "getNumTags";
            return nullptr;
        case FIELD_regionTags:
            if (!strcmp(propertyName, "getter")) return "_getRegionTag";
            if (!strcmp(propertyName, "sizeGetter")) return "getNumRegionTags";
            return nullptr;
        case FIELD_front:
            if (!strcmp(propertyName, "packetData")) return "";
            if (!strcmp(propertyName, "getter")) return "getFront";
            return nullptr;
        case FIELD_back:
            if (!strcmp(propertyName, "packetData")) return "";
            if (!strcmp(propertyName, "getter")) return "getBack";
            return nullptr;
        default: return nullptr;
    }
}

int PacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        case FIELD_tags: return pp->getNumTags();
        case FIELD_regionTags: return pp->getNumRegionTags();
        default: return 0;
    }
}

void PacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Packet'", field);
    }
}

const char *PacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        case FIELD_data: { const ChunkTemporarySharedPtr * value = pp->getData(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_dissection: { const ChunkTemporarySharedPtr * value = pp->getDissection(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_content: { const Chunk * value = pp->getContent(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_tags: { const ::omnetpp::cObject * value = pp->_getTag(i); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_front: { const ChunkTemporarySharedPtr * value = pp->getFront(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_back: { const ChunkTemporarySharedPtr * value = pp->getBack(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        case FIELD_dataLength: return unit2string(pp->getDataLength());
        case FIELD_totalLength: return unit2string(pp->getTotalLength());
        case FIELD_data: { auto obj = pp->getData(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_dissection: { auto obj = pp->getDissection(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_content: { auto obj = pp->getContent(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_tags: { auto obj = pp->_getTag(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_regionTags: return pp->_getRegionTag(i).str();
        case FIELD_frontOffset: return unit2string(pp->getFrontOffset());
        case FIELD_backOffset: return unit2string(pp->getBackOffset());
        case FIELD_front: { auto obj = pp->getFront(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_back: { auto obj = pp->getBack(); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void PacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Packet'", field);
    }
}

omnetpp::cValue PacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        case FIELD_dataLength: return cValue(pp->getDataLength().get(),"b");
        case FIELD_totalLength: return cValue(pp->getTotalLength().get(),"b");
        case FIELD_data: return omnetpp::toAnyPtr(pp->getData()); break;
        case FIELD_dissection: return omnetpp::toAnyPtr(pp->getDissection()); break;
        case FIELD_content: return omnetpp::toAnyPtr(pp->getContent()); break;
        case FIELD_tags: return omnetpp::toAnyPtr(pp->_getTag(i)); break;
        case FIELD_regionTags: return omnetpp::toAnyPtr(&pp->_getRegionTag(i)); break;
        case FIELD_frontOffset: return cValue(pp->getFrontOffset().get(),"b");
        case FIELD_backOffset: return cValue(pp->getBackOffset().get(),"b");
        case FIELD_front: return omnetpp::toAnyPtr(pp->getFront()); break;
        case FIELD_back: return omnetpp::toAnyPtr(pp->getBack()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Packet' as cValue -- field index out of range?", field);
    }
}

void PacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Packet'", field);
    }
}

const char *PacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_data: return omnetpp::opp_typename(typeid(ChunkTemporarySharedPtr));
        case FIELD_dissection: return omnetpp::opp_typename(typeid(ChunkTemporarySharedPtr));
        case FIELD_content: return omnetpp::opp_typename(typeid(Chunk));
        case FIELD_tags: return omnetpp::opp_typename(typeid(::omnetpp::cObject));
        case FIELD_regionTags: return omnetpp::opp_typename(typeid(SharingRegionTagSet::TagBaseRegionTag));
        case FIELD_front: return omnetpp::opp_typename(typeid(ChunkTemporarySharedPtr));
        case FIELD_back: return omnetpp::opp_typename(typeid(ChunkTemporarySharedPtr));
        default: return nullptr;
    };
}

omnetpp::any_ptr PacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        case FIELD_data: return omnetpp::toAnyPtr(pp->getData()); break;
        case FIELD_dissection: return omnetpp::toAnyPtr(pp->getDissection()); break;
        case FIELD_content: return omnetpp::toAnyPtr(pp->getContent()); break;
        case FIELD_tags: return omnetpp::toAnyPtr(pp->_getTag(i)); break;
        case FIELD_regionTags: return omnetpp::toAnyPtr(&pp->_getRegionTag(i)); break;
        case FIELD_front: return omnetpp::toAnyPtr(pp->getFront()); break;
        case FIELD_back: return omnetpp::toAnyPtr(pp->getBack()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Packet *pp = omnetpp::fromAnyPtr<Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Packet'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

