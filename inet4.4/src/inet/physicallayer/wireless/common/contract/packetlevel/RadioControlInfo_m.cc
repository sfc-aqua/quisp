//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/common/contract/packetlevel/RadioControlInfo.msg.
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
#include "RadioControlInfo_m.h"

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
namespace physicallayer {

Register_Enum(inet::physicallayer::RadioCommandCode, (inet::physicallayer::RadioCommandCode::RADIO_C_CONFIGURE));

Register_Class(ConfigureRadioCommand)

ConfigureRadioCommand::ConfigureRadioCommand() : ::omnetpp::cObject()
{
}

ConfigureRadioCommand::ConfigureRadioCommand(const ConfigureRadioCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

ConfigureRadioCommand::~ConfigureRadioCommand()
{
}

ConfigureRadioCommand& ConfigureRadioCommand::operator=(const ConfigureRadioCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void ConfigureRadioCommand::copy(const ConfigureRadioCommand& other)
{
    this->radioMode = other.radioMode;
    this->power = other.power;
    this->bitrate = other.bitrate;
    this->modulation = other.modulation;
    this->centerFrequency = other.centerFrequency;
    this->bandwidth = other.bandwidth;
}

void ConfigureRadioCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->radioMode);
    doParsimPacking(b,this->power);
    doParsimPacking(b,this->bitrate);
    doParsimPacking(b,this->modulation);
    doParsimPacking(b,this->centerFrequency);
    doParsimPacking(b,this->bandwidth);
}

void ConfigureRadioCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->radioMode);
    doParsimUnpacking(b,this->power);
    doParsimUnpacking(b,this->bitrate);
    doParsimUnpacking(b,this->modulation);
    doParsimUnpacking(b,this->centerFrequency);
    doParsimUnpacking(b,this->bandwidth);
}

int ConfigureRadioCommand::getRadioMode() const
{
    return this->radioMode;
}

void ConfigureRadioCommand::setRadioMode(int radioMode)
{
    this->radioMode = radioMode;
}

::inet::W ConfigureRadioCommand::getPower() const
{
    return this->power;
}

void ConfigureRadioCommand::setPower(::inet::W power)
{
    this->power = power;
}

::inet::bps ConfigureRadioCommand::getBitrate() const
{
    return this->bitrate;
}

void ConfigureRadioCommand::setBitrate(::inet::bps bitrate)
{
    this->bitrate = bitrate;
}

const IModulation * ConfigureRadioCommand::getModulation() const
{
    return this->modulation;
}

void ConfigureRadioCommand::setModulation(IModulation * modulation)
{
    this->modulation = modulation;
}

::inet::Hz ConfigureRadioCommand::getCenterFrequency() const
{
    return this->centerFrequency;
}

void ConfigureRadioCommand::setCenterFrequency(::inet::Hz centerFrequency)
{
    this->centerFrequency = centerFrequency;
}

::inet::Hz ConfigureRadioCommand::getBandwidth() const
{
    return this->bandwidth;
}

void ConfigureRadioCommand::setBandwidth(::inet::Hz bandwidth)
{
    this->bandwidth = bandwidth;
}

class ConfigureRadioCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_radioMode,
        FIELD_power,
        FIELD_bitrate,
        FIELD_modulation,
        FIELD_centerFrequency,
        FIELD_bandwidth,
    };
  public:
    ConfigureRadioCommandDescriptor();
    virtual ~ConfigureRadioCommandDescriptor();

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

Register_ClassDescriptor(ConfigureRadioCommandDescriptor)

ConfigureRadioCommandDescriptor::ConfigureRadioCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::ConfigureRadioCommand)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

ConfigureRadioCommandDescriptor::~ConfigureRadioCommandDescriptor()
{
    delete[] propertyNames;
}

bool ConfigureRadioCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ConfigureRadioCommand *>(obj)!=nullptr;
}

const char **ConfigureRadioCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ConfigureRadioCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ConfigureRadioCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int ConfigureRadioCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_radioMode
        FD_ISEDITABLE,    // FIELD_power
        FD_ISEDITABLE,    // FIELD_bitrate
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_modulation
        FD_ISEDITABLE,    // FIELD_centerFrequency
        FD_ISEDITABLE,    // FIELD_bandwidth
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *ConfigureRadioCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "radioMode",
        "power",
        "bitrate",
        "modulation",
        "centerFrequency",
        "bandwidth",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int ConfigureRadioCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "radioMode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "power") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "bitrate") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "modulation") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "centerFrequency") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *ConfigureRadioCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_radioMode
        "inet::W",    // FIELD_power
        "inet::bps",    // FIELD_bitrate
        "inet::physicallayer::IModulation",    // FIELD_modulation
        "inet::Hz",    // FIELD_centerFrequency
        "inet::Hz",    // FIELD_bandwidth
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **ConfigureRadioCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ConfigureRadioCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ConfigureRadioCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ConfigureRadioCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ConfigureRadioCommand'", field);
    }
}

const char *ConfigureRadioCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: { const IModulation * value = pp->getModulation(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string ConfigureRadioCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: return long2string(pp->getRadioMode());
        case FIELD_power: return unit2string(pp->getPower());
        case FIELD_bitrate: return unit2string(pp->getBitrate());
        case FIELD_modulation: return "";
        case FIELD_centerFrequency: return unit2string(pp->getCenterFrequency());
        case FIELD_bandwidth: return unit2string(pp->getBandwidth());
        default: return "";
    }
}

void ConfigureRadioCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: pp->setRadioMode(string2long(value)); break;
        case FIELD_power: pp->setPower(W(string2double(value))); break;
        case FIELD_bitrate: pp->setBitrate(bps(string2double(value))); break;
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(string2double(value))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ConfigureRadioCommand'", field);
    }
}

omnetpp::cValue ConfigureRadioCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: return pp->getRadioMode();
        case FIELD_power: return cValue(pp->getPower().get(),"W");
        case FIELD_bitrate: return cValue(pp->getBitrate().get(),"bps");
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        case FIELD_centerFrequency: return cValue(pp->getCenterFrequency().get(),"Hz");
        case FIELD_bandwidth: return cValue(pp->getBandwidth().get(),"Hz");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ConfigureRadioCommand' as cValue -- field index out of range?", field);
    }
}

void ConfigureRadioCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: pp->setRadioMode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_power: pp->setPower(W(value.doubleValueInUnit("W"))); break;
        case FIELD_bitrate: pp->setBitrate(bps(value.doubleValueInUnit("bps"))); break;
        case FIELD_modulation: pp->setModulation(omnetpp::fromAnyPtr<IModulation>(value.pointerValue())); break;
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(value.doubleValueInUnit("Hz"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ConfigureRadioCommand'", field);
    }
}

const char *ConfigureRadioCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_modulation: return omnetpp::opp_typename(typeid(IModulation));
        default: return nullptr;
    };
}

omnetpp::any_ptr ConfigureRadioCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ConfigureRadioCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ConfigureRadioCommand *pp = omnetpp::fromAnyPtr<ConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: pp->setModulation(omnetpp::fromAnyPtr<IModulation>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ConfigureRadioCommand'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

