//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/visualizer/base/PacketDrop.msg.
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
#include "PacketDrop_m.h"

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
namespace visualizer {

class PacketDropDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_packet_,
        FIELD_module,
        FIELD_networkNode,
        FIELD_networkInterface,
        FIELD_position,
    };
  public:
    PacketDropDescriptor();
    virtual ~PacketDropDescriptor();

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

Register_ClassDescriptor(PacketDropDescriptor)

PacketDropDescriptor::PacketDropDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::visualizer::PacketDrop)), "inet::PacketDropDetails")
{
    propertyNames = nullptr;
}

PacketDropDescriptor::~PacketDropDescriptor()
{
    delete[] propertyNames;
}

bool PacketDropDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PacketDrop *>(obj)!=nullptr;
}

const char **PacketDropDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PacketDropDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PacketDropDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int PacketDropDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_packet_
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_module
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_networkNode
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_networkInterface
        FD_ISCOMPOUND,    // FIELD_position
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *PacketDropDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packet_",
        "module",
        "networkNode",
        "networkInterface",
        "position",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int PacketDropDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "packet_") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "module") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "networkNode") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "networkInterface") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "position") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *PacketDropDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::cPacket",    // FIELD_packet_
        "omnetpp::cModule",    // FIELD_module
        "omnetpp::cModule",    // FIELD_networkNode
        "inet::NetworkInterface",    // FIELD_networkInterface
        "inet::Coord",    // FIELD_position
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketDropDescriptor::getFieldPropertyNames(int field) const
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

const char *PacketDropDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PacketDropDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PacketDropDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PacketDrop'", field);
    }
}

const char *PacketDropDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        case FIELD_packet_: { const ::omnetpp::cPacket * value = pp->getPacket_(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_module: { const ::omnetpp::cModule * value = pp->getModule(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_networkNode: { const ::omnetpp::cModule * value = pp->getNetworkNode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_networkInterface: { const ::inet::NetworkInterface * value = pp->getNetworkInterface(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PacketDropDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        case FIELD_packet_: { auto obj = pp->getPacket_(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_module: { auto obj = pp->getModule(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_networkNode: { auto obj = pp->getNetworkNode(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_networkInterface: { auto obj = pp->getNetworkInterface(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_position: return "";
        default: return "";
    }
}

void PacketDropDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDrop'", field);
    }
}

omnetpp::cValue PacketDropDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        case FIELD_packet_: return omnetpp::toAnyPtr(pp->getPacket_()); break;
        case FIELD_module: return omnetpp::toAnyPtr(pp->getModule()); break;
        case FIELD_networkNode: return omnetpp::toAnyPtr(pp->getNetworkNode()); break;
        case FIELD_networkInterface: return omnetpp::toAnyPtr(pp->getNetworkInterface()); break;
        case FIELD_position: return omnetpp::toAnyPtr(&pp->getPosition()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PacketDrop' as cValue -- field index out of range?", field);
    }
}

void PacketDropDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDrop'", field);
    }
}

const char *PacketDropDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packet_: return omnetpp::opp_typename(typeid(::omnetpp::cPacket));
        case FIELD_module: return omnetpp::opp_typename(typeid(::omnetpp::cModule));
        case FIELD_networkNode: return omnetpp::opp_typename(typeid(::omnetpp::cModule));
        case FIELD_networkInterface: return omnetpp::opp_typename(typeid(::inet::NetworkInterface));
        case FIELD_position: return omnetpp::opp_typename(typeid(::inet::Coord));
        default: return nullptr;
    };
}

omnetpp::any_ptr PacketDropDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        case FIELD_packet_: return omnetpp::toAnyPtr(pp->getPacket_()); break;
        case FIELD_module: return omnetpp::toAnyPtr(pp->getModule()); break;
        case FIELD_networkNode: return omnetpp::toAnyPtr(pp->getNetworkNode()); break;
        case FIELD_networkInterface: return omnetpp::toAnyPtr(pp->getNetworkInterface()); break;
        case FIELD_position: return omnetpp::toAnyPtr(&pp->getPosition()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PacketDropDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDrop *pp = omnetpp::fromAnyPtr<PacketDrop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDrop'", field);
    }
}

}  // namespace visualizer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

