//
// Generated file, do not edit! Created by nedtool 5.2 from classical_messages.msg.
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
#include "classical_messages_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(header)

header::header(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->srcAddr = 0;
    this->destAddr = 0;
    this->hopCount = 0;
}

header::header(const header& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

header::~header()
{
}

header& header::operator=(const header& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void header::copy(const header& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->hopCount = other.hopCount;
}

void header::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->hopCount);
}

void header::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->hopCount);
}

int header::getSrcAddr() const
{
    return this->srcAddr;
}

void header::setSrcAddr(int srcAddr)
{
    this->srcAddr = srcAddr;
}

int header::getDestAddr() const
{
    return this->destAddr;
}

void header::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int header::getHopCount() const
{
    return this->hopCount;
}

void header::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

class headerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    headerDescriptor();
    virtual ~headerDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(headerDescriptor)

headerDescriptor::headerDescriptor() : omnetpp::cClassDescriptor("header", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

headerDescriptor::~headerDescriptor()
{
    delete[] propertynames;
}

bool headerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<header *>(obj)!=nullptr;
}

const char **headerDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *headerDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int headerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int headerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *headerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "hopCount",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int headerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *headerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **headerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *headerDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int headerDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    header *pp = (header *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *headerDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    header *pp = (header *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string headerDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    header *pp = (header *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcAddr());
        case 1: return long2string(pp->getDestAddr());
        case 2: return long2string(pp->getHopCount());
        default: return "";
    }
}

bool headerDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    header *pp = (header *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddr(string2long(value)); return true;
        case 1: pp->setDestAddr(string2long(value)); return true;
        case 2: pp->setHopCount(string2long(value)); return true;
        default: return false;
    }
}

const char *headerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *headerDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    header *pp = (header *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BSMtimingNotifier)

BSMtimingNotifier::BSMtimingNotifier(const char *name, short kind) : ::header(name,kind)
{
    this->timing_at = 0;
    this->accepted_photons_per_sec = 0;
    this->interval = 0;
    this->number_of_qubits = 0;
    this->internal_qnic = -1;
}

BSMtimingNotifier::BSMtimingNotifier(const BSMtimingNotifier& other) : ::header(other)
{
    copy(other);
}

BSMtimingNotifier::~BSMtimingNotifier()
{
}

BSMtimingNotifier& BSMtimingNotifier::operator=(const BSMtimingNotifier& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void BSMtimingNotifier::copy(const BSMtimingNotifier& other)
{
    this->timing_at = other.timing_at;
    this->accepted_photons_per_sec = other.accepted_photons_per_sec;
    this->interval = other.interval;
    this->number_of_qubits = other.number_of_qubits;
    this->internal_qnic = other.internal_qnic;
}

void BSMtimingNotifier::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->timing_at);
    doParsimPacking(b,this->accepted_photons_per_sec);
    doParsimPacking(b,this->interval);
    doParsimPacking(b,this->number_of_qubits);
    doParsimPacking(b,this->internal_qnic);
}

void BSMtimingNotifier::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->timing_at);
    doParsimUnpacking(b,this->accepted_photons_per_sec);
    doParsimUnpacking(b,this->interval);
    doParsimUnpacking(b,this->number_of_qubits);
    doParsimUnpacking(b,this->internal_qnic);
}

::omnetpp::simtime_t BSMtimingNotifier::getTiming_at() const
{
    return this->timing_at;
}

void BSMtimingNotifier::setTiming_at(::omnetpp::simtime_t timing_at)
{
    this->timing_at = timing_at;
}

int BSMtimingNotifier::getAccepted_photons_per_sec() const
{
    return this->accepted_photons_per_sec;
}

void BSMtimingNotifier::setAccepted_photons_per_sec(int accepted_photons_per_sec)
{
    this->accepted_photons_per_sec = accepted_photons_per_sec;
}

double BSMtimingNotifier::getInterval() const
{
    return this->interval;
}

void BSMtimingNotifier::setInterval(double interval)
{
    this->interval = interval;
}

int BSMtimingNotifier::getNumber_of_qubits() const
{
    return this->number_of_qubits;
}

void BSMtimingNotifier::setNumber_of_qubits(int number_of_qubits)
{
    this->number_of_qubits = number_of_qubits;
}

int BSMtimingNotifier::getInternal_qnic() const
{
    return this->internal_qnic;
}

void BSMtimingNotifier::setInternal_qnic(int internal_qnic)
{
    this->internal_qnic = internal_qnic;
}

class BSMtimingNotifierDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BSMtimingNotifierDescriptor();
    virtual ~BSMtimingNotifierDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BSMtimingNotifierDescriptor)

BSMtimingNotifierDescriptor::BSMtimingNotifierDescriptor() : omnetpp::cClassDescriptor("BSMtimingNotifier", "header")
{
    propertynames = nullptr;
}

BSMtimingNotifierDescriptor::~BSMtimingNotifierDescriptor()
{
    delete[] propertynames;
}

bool BSMtimingNotifierDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BSMtimingNotifier *>(obj)!=nullptr;
}

const char **BSMtimingNotifierDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BSMtimingNotifierDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BSMtimingNotifierDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int BSMtimingNotifierDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *BSMtimingNotifierDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "timing_at",
        "accepted_photons_per_sec",
        "interval",
        "number_of_qubits",
        "internal_qnic",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int BSMtimingNotifierDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timing_at")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "accepted_photons_per_sec")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "interval")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "number_of_qubits")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "internal_qnic")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BSMtimingNotifierDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "int",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **BSMtimingNotifierDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BSMtimingNotifierDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BSMtimingNotifierDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BSMtimingNotifier *pp = (BSMtimingNotifier *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BSMtimingNotifierDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSMtimingNotifier *pp = (BSMtimingNotifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BSMtimingNotifierDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSMtimingNotifier *pp = (BSMtimingNotifier *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getTiming_at());
        case 1: return long2string(pp->getAccepted_photons_per_sec());
        case 2: return double2string(pp->getInterval());
        case 3: return long2string(pp->getNumber_of_qubits());
        case 4: return long2string(pp->getInternal_qnic());
        default: return "";
    }
}

bool BSMtimingNotifierDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BSMtimingNotifier *pp = (BSMtimingNotifier *)object; (void)pp;
    switch (field) {
        case 0: pp->setTiming_at(string2simtime(value)); return true;
        case 1: pp->setAccepted_photons_per_sec(string2long(value)); return true;
        case 2: pp->setInterval(string2double(value)); return true;
        case 3: pp->setNumber_of_qubits(string2long(value)); return true;
        case 4: pp->setInternal_qnic(string2long(value)); return true;
        default: return false;
    }
}

const char *BSMtimingNotifierDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *BSMtimingNotifierDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BSMtimingNotifier *pp = (BSMtimingNotifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EPPStimingNotifier)

EPPStimingNotifier::EPPStimingNotifier(const char *name, short kind) : ::header(name,kind)
{
    this->timing_at = 0;
    this->interval = 0;
    this->number_of_qubits = 0;
    this->internal_qnic = -1;
}

EPPStimingNotifier::EPPStimingNotifier(const EPPStimingNotifier& other) : ::header(other)
{
    copy(other);
}

EPPStimingNotifier::~EPPStimingNotifier()
{
}

EPPStimingNotifier& EPPStimingNotifier::operator=(const EPPStimingNotifier& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void EPPStimingNotifier::copy(const EPPStimingNotifier& other)
{
    this->timing_at = other.timing_at;
    this->interval = other.interval;
    this->number_of_qubits = other.number_of_qubits;
    this->internal_qnic = other.internal_qnic;
}

void EPPStimingNotifier::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->timing_at);
    doParsimPacking(b,this->interval);
    doParsimPacking(b,this->number_of_qubits);
    doParsimPacking(b,this->internal_qnic);
}

void EPPStimingNotifier::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->timing_at);
    doParsimUnpacking(b,this->interval);
    doParsimUnpacking(b,this->number_of_qubits);
    doParsimUnpacking(b,this->internal_qnic);
}

::omnetpp::simtime_t EPPStimingNotifier::getTiming_at() const
{
    return this->timing_at;
}

void EPPStimingNotifier::setTiming_at(::omnetpp::simtime_t timing_at)
{
    this->timing_at = timing_at;
}

double EPPStimingNotifier::getInterval() const
{
    return this->interval;
}

void EPPStimingNotifier::setInterval(double interval)
{
    this->interval = interval;
}

int EPPStimingNotifier::getNumber_of_qubits() const
{
    return this->number_of_qubits;
}

void EPPStimingNotifier::setNumber_of_qubits(int number_of_qubits)
{
    this->number_of_qubits = number_of_qubits;
}

int EPPStimingNotifier::getInternal_qnic() const
{
    return this->internal_qnic;
}

void EPPStimingNotifier::setInternal_qnic(int internal_qnic)
{
    this->internal_qnic = internal_qnic;
}

class EPPStimingNotifierDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EPPStimingNotifierDescriptor();
    virtual ~EPPStimingNotifierDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EPPStimingNotifierDescriptor)

EPPStimingNotifierDescriptor::EPPStimingNotifierDescriptor() : omnetpp::cClassDescriptor("EPPStimingNotifier", "header")
{
    propertynames = nullptr;
}

EPPStimingNotifierDescriptor::~EPPStimingNotifierDescriptor()
{
    delete[] propertynames;
}

bool EPPStimingNotifierDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EPPStimingNotifier *>(obj)!=nullptr;
}

const char **EPPStimingNotifierDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EPPStimingNotifierDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EPPStimingNotifierDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int EPPStimingNotifierDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *EPPStimingNotifierDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "timing_at",
        "interval",
        "number_of_qubits",
        "internal_qnic",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int EPPStimingNotifierDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timing_at")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "interval")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "number_of_qubits")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "internal_qnic")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EPPStimingNotifierDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **EPPStimingNotifierDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EPPStimingNotifierDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EPPStimingNotifierDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EPPStimingNotifier *pp = (EPPStimingNotifier *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EPPStimingNotifierDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EPPStimingNotifier *pp = (EPPStimingNotifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EPPStimingNotifierDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EPPStimingNotifier *pp = (EPPStimingNotifier *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getTiming_at());
        case 1: return double2string(pp->getInterval());
        case 2: return long2string(pp->getNumber_of_qubits());
        case 3: return long2string(pp->getInternal_qnic());
        default: return "";
    }
}

bool EPPStimingNotifierDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EPPStimingNotifier *pp = (EPPStimingNotifier *)object; (void)pp;
    switch (field) {
        case 0: pp->setTiming_at(string2simtime(value)); return true;
        case 1: pp->setInterval(string2double(value)); return true;
        case 2: pp->setNumber_of_qubits(string2long(value)); return true;
        case 3: pp->setInternal_qnic(string2long(value)); return true;
        default: return false;
    }
}

const char *EPPStimingNotifierDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EPPStimingNotifierDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EPPStimingNotifier *pp = (EPPStimingNotifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(EmitPhotonRequest)

EmitPhotonRequest::EmitPhotonRequest(const char *name, short kind) : ::header(name,kind)
{
    this->qubit_index = 0;
    this->qnic_index = 0;
    this->qnic_type = 0;
    this->receiver = false;
    this->first = false;
    this->last = false;
    this->trial = 0;
}

EmitPhotonRequest::EmitPhotonRequest(const EmitPhotonRequest& other) : ::header(other)
{
    copy(other);
}

EmitPhotonRequest::~EmitPhotonRequest()
{
}

EmitPhotonRequest& EmitPhotonRequest::operator=(const EmitPhotonRequest& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void EmitPhotonRequest::copy(const EmitPhotonRequest& other)
{
    this->qubit_index = other.qubit_index;
    this->qnic_index = other.qnic_index;
    this->qnic_type = other.qnic_type;
    this->receiver = other.receiver;
    this->first = other.first;
    this->last = other.last;
    this->trial = other.trial;
}

void EmitPhotonRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->qubit_index);
    doParsimPacking(b,this->qnic_index);
    doParsimPacking(b,this->qnic_type);
    doParsimPacking(b,this->receiver);
    doParsimPacking(b,this->first);
    doParsimPacking(b,this->last);
    doParsimPacking(b,this->trial);
}

void EmitPhotonRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->qubit_index);
    doParsimUnpacking(b,this->qnic_index);
    doParsimUnpacking(b,this->qnic_type);
    doParsimUnpacking(b,this->receiver);
    doParsimUnpacking(b,this->first);
    doParsimUnpacking(b,this->last);
    doParsimUnpacking(b,this->trial);
}

int EmitPhotonRequest::getQubit_index() const
{
    return this->qubit_index;
}

void EmitPhotonRequest::setQubit_index(int qubit_index)
{
    this->qubit_index = qubit_index;
}

int EmitPhotonRequest::getQnic_index() const
{
    return this->qnic_index;
}

void EmitPhotonRequest::setQnic_index(int qnic_index)
{
    this->qnic_index = qnic_index;
}

int EmitPhotonRequest::getQnic_type() const
{
    return this->qnic_type;
}

void EmitPhotonRequest::setQnic_type(int qnic_type)
{
    this->qnic_type = qnic_type;
}

bool EmitPhotonRequest::getReceiver() const
{
    return this->receiver;
}

void EmitPhotonRequest::setReceiver(bool receiver)
{
    this->receiver = receiver;
}

bool EmitPhotonRequest::getFirst() const
{
    return this->first;
}

void EmitPhotonRequest::setFirst(bool first)
{
    this->first = first;
}

bool EmitPhotonRequest::getLast() const
{
    return this->last;
}

void EmitPhotonRequest::setLast(bool last)
{
    this->last = last;
}

int EmitPhotonRequest::getTrial() const
{
    return this->trial;
}

void EmitPhotonRequest::setTrial(int trial)
{
    this->trial = trial;
}

class EmitPhotonRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EmitPhotonRequestDescriptor();
    virtual ~EmitPhotonRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EmitPhotonRequestDescriptor)

EmitPhotonRequestDescriptor::EmitPhotonRequestDescriptor() : omnetpp::cClassDescriptor("EmitPhotonRequest", "header")
{
    propertynames = nullptr;
}

EmitPhotonRequestDescriptor::~EmitPhotonRequestDescriptor()
{
    delete[] propertynames;
}

bool EmitPhotonRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EmitPhotonRequest *>(obj)!=nullptr;
}

const char **EmitPhotonRequestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EmitPhotonRequestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EmitPhotonRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int EmitPhotonRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *EmitPhotonRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "qubit_index",
        "qnic_index",
        "qnic_type",
        "receiver",
        "first",
        "last",
        "trial",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int EmitPhotonRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qubit_index")==0) return base+0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qnic_index")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "qnic_type")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiver")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "first")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "last")==0) return base+5;
    if (fieldName[0]=='t' && strcmp(fieldName, "trial")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EmitPhotonRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "bool",
        "bool",
        "bool",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **EmitPhotonRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EmitPhotonRequestDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EmitPhotonRequestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EmitPhotonRequest *pp = (EmitPhotonRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EmitPhotonRequestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmitPhotonRequest *pp = (EmitPhotonRequest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EmitPhotonRequestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmitPhotonRequest *pp = (EmitPhotonRequest *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getQubit_index());
        case 1: return long2string(pp->getQnic_index());
        case 2: return long2string(pp->getQnic_type());
        case 3: return bool2string(pp->getReceiver());
        case 4: return bool2string(pp->getFirst());
        case 5: return bool2string(pp->getLast());
        case 6: return long2string(pp->getTrial());
        default: return "";
    }
}

bool EmitPhotonRequestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EmitPhotonRequest *pp = (EmitPhotonRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setQubit_index(string2long(value)); return true;
        case 1: pp->setQnic_index(string2long(value)); return true;
        case 2: pp->setQnic_type(string2long(value)); return true;
        case 3: pp->setReceiver(string2bool(value)); return true;
        case 4: pp->setFirst(string2bool(value)); return true;
        case 5: pp->setLast(string2bool(value)); return true;
        case 6: pp->setTrial(string2long(value)); return true;
        default: return false;
    }
}

const char *EmitPhotonRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EmitPhotonRequestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EmitPhotonRequest *pp = (EmitPhotonRequest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(SchedulePhotonTransmissionsOnebyOne)

SchedulePhotonTransmissionsOnebyOne::SchedulePhotonTransmissionsOnebyOne(const char *name, short kind) : ::header(name,kind)
{
    this->qnic_index = 0;
    this->num_sent = 0;
    this->number_of_qubits_to_send = 0;
    this->trial = 0;
    this->interval = 0;
    this->timing = 0;
    this->internal_hom = 0;
}

SchedulePhotonTransmissionsOnebyOne::SchedulePhotonTransmissionsOnebyOne(const SchedulePhotonTransmissionsOnebyOne& other) : ::header(other)
{
    copy(other);
}

SchedulePhotonTransmissionsOnebyOne::~SchedulePhotonTransmissionsOnebyOne()
{
}

SchedulePhotonTransmissionsOnebyOne& SchedulePhotonTransmissionsOnebyOne::operator=(const SchedulePhotonTransmissionsOnebyOne& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void SchedulePhotonTransmissionsOnebyOne::copy(const SchedulePhotonTransmissionsOnebyOne& other)
{
    this->qnic_index = other.qnic_index;
    this->num_sent = other.num_sent;
    this->number_of_qubits_to_send = other.number_of_qubits_to_send;
    this->trial = other.trial;
    this->interval = other.interval;
    this->timing = other.timing;
    this->internal_hom = other.internal_hom;
}

void SchedulePhotonTransmissionsOnebyOne::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->qnic_index);
    doParsimPacking(b,this->num_sent);
    doParsimPacking(b,this->number_of_qubits_to_send);
    doParsimPacking(b,this->trial);
    doParsimPacking(b,this->interval);
    doParsimPacking(b,this->timing);
    doParsimPacking(b,this->internal_hom);
}

void SchedulePhotonTransmissionsOnebyOne::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->qnic_index);
    doParsimUnpacking(b,this->num_sent);
    doParsimUnpacking(b,this->number_of_qubits_to_send);
    doParsimUnpacking(b,this->trial);
    doParsimUnpacking(b,this->interval);
    doParsimUnpacking(b,this->timing);
    doParsimUnpacking(b,this->internal_hom);
}

int SchedulePhotonTransmissionsOnebyOne::getQnic_index() const
{
    return this->qnic_index;
}

void SchedulePhotonTransmissionsOnebyOne::setQnic_index(int qnic_index)
{
    this->qnic_index = qnic_index;
}

int SchedulePhotonTransmissionsOnebyOne::getNum_sent() const
{
    return this->num_sent;
}

void SchedulePhotonTransmissionsOnebyOne::setNum_sent(int num_sent)
{
    this->num_sent = num_sent;
}

int SchedulePhotonTransmissionsOnebyOne::getNumber_of_qubits_to_send() const
{
    return this->number_of_qubits_to_send;
}

void SchedulePhotonTransmissionsOnebyOne::setNumber_of_qubits_to_send(int number_of_qubits_to_send)
{
    this->number_of_qubits_to_send = number_of_qubits_to_send;
}

int SchedulePhotonTransmissionsOnebyOne::getTrial() const
{
    return this->trial;
}

void SchedulePhotonTransmissionsOnebyOne::setTrial(int trial)
{
    this->trial = trial;
}

double SchedulePhotonTransmissionsOnebyOne::getInterval() const
{
    return this->interval;
}

void SchedulePhotonTransmissionsOnebyOne::setInterval(double interval)
{
    this->interval = interval;
}

::omnetpp::simtime_t SchedulePhotonTransmissionsOnebyOne::getTiming() const
{
    return this->timing;
}

void SchedulePhotonTransmissionsOnebyOne::setTiming(::omnetpp::simtime_t timing)
{
    this->timing = timing;
}

int SchedulePhotonTransmissionsOnebyOne::getInternal_hom() const
{
    return this->internal_hom;
}

void SchedulePhotonTransmissionsOnebyOne::setInternal_hom(int internal_hom)
{
    this->internal_hom = internal_hom;
}

class SchedulePhotonTransmissionsOnebyOneDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SchedulePhotonTransmissionsOnebyOneDescriptor();
    virtual ~SchedulePhotonTransmissionsOnebyOneDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SchedulePhotonTransmissionsOnebyOneDescriptor)

SchedulePhotonTransmissionsOnebyOneDescriptor::SchedulePhotonTransmissionsOnebyOneDescriptor() : omnetpp::cClassDescriptor("SchedulePhotonTransmissionsOnebyOne", "header")
{
    propertynames = nullptr;
}

SchedulePhotonTransmissionsOnebyOneDescriptor::~SchedulePhotonTransmissionsOnebyOneDescriptor()
{
    delete[] propertynames;
}

bool SchedulePhotonTransmissionsOnebyOneDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(obj)!=nullptr;
}

const char **SchedulePhotonTransmissionsOnebyOneDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "qnic_index",
        "num_sent",
        "number_of_qubits_to_send",
        "trial",
        "interval",
        "timing",
        "internal_hom",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int SchedulePhotonTransmissionsOnebyOneDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qnic_index")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "num_sent")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "number_of_qubits_to_send")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "trial")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "interval")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "timing")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "internal_hom")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "double",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SchedulePhotonTransmissionsOnebyOne *pp = (SchedulePhotonTransmissionsOnebyOne *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SchedulePhotonTransmissionsOnebyOne *pp = (SchedulePhotonTransmissionsOnebyOne *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SchedulePhotonTransmissionsOnebyOne *pp = (SchedulePhotonTransmissionsOnebyOne *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getQnic_index());
        case 1: return long2string(pp->getNum_sent());
        case 2: return long2string(pp->getNumber_of_qubits_to_send());
        case 3: return long2string(pp->getTrial());
        case 4: return double2string(pp->getInterval());
        case 5: return simtime2string(pp->getTiming());
        case 6: return long2string(pp->getInternal_hom());
        default: return "";
    }
}

bool SchedulePhotonTransmissionsOnebyOneDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SchedulePhotonTransmissionsOnebyOne *pp = (SchedulePhotonTransmissionsOnebyOne *)object; (void)pp;
    switch (field) {
        case 0: pp->setQnic_index(string2long(value)); return true;
        case 1: pp->setNum_sent(string2long(value)); return true;
        case 2: pp->setNumber_of_qubits_to_send(string2long(value)); return true;
        case 3: pp->setTrial(string2long(value)); return true;
        case 4: pp->setInterval(string2double(value)); return true;
        case 5: pp->setTiming(string2simtime(value)); return true;
        case 6: pp->setInternal_hom(string2long(value)); return true;
        default: return false;
    }
}

const char *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *SchedulePhotonTransmissionsOnebyOneDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SchedulePhotonTransmissionsOnebyOne *pp = (SchedulePhotonTransmissionsOnebyOne *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BSAresult)

BSAresult::BSAresult(const char *name, short kind) : ::header(name,kind)
{
    this->entangled = false;
}

BSAresult::BSAresult(const BSAresult& other) : ::header(other)
{
    copy(other);
}

BSAresult::~BSAresult()
{
}

BSAresult& BSAresult::operator=(const BSAresult& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void BSAresult::copy(const BSAresult& other)
{
    this->entangled = other.entangled;
}

void BSAresult::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->entangled);
}

void BSAresult::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->entangled);
}

bool BSAresult::getEntangled() const
{
    return this->entangled;
}

void BSAresult::setEntangled(bool entangled)
{
    this->entangled = entangled;
}

class BSAresultDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BSAresultDescriptor();
    virtual ~BSAresultDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BSAresultDescriptor)

BSAresultDescriptor::BSAresultDescriptor() : omnetpp::cClassDescriptor("BSAresult", "header")
{
    propertynames = nullptr;
}

BSAresultDescriptor::~BSAresultDescriptor()
{
    delete[] propertynames;
}

bool BSAresultDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BSAresult *>(obj)!=nullptr;
}

const char **BSAresultDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BSAresultDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BSAresultDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int BSAresultDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BSAresultDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "entangled",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int BSAresultDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "entangled")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BSAresultDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **BSAresultDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BSAresultDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BSAresultDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BSAresult *pp = (BSAresult *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BSAresultDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSAresult *pp = (BSAresult *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BSAresultDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSAresult *pp = (BSAresult *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getEntangled());
        default: return "";
    }
}

bool BSAresultDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BSAresult *pp = (BSAresult *)object; (void)pp;
    switch (field) {
        case 0: pp->setEntangled(string2bool(value)); return true;
        default: return false;
    }
}

const char *BSAresultDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *BSAresultDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BSAresult *pp = (BSAresult *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BSAfinish)

BSAfinish::BSAfinish(const char *name, short kind) : ::header(name,kind)
{
    this->entangled = false;
}

BSAfinish::BSAfinish(const BSAfinish& other) : ::header(other)
{
    copy(other);
}

BSAfinish::~BSAfinish()
{
}

BSAfinish& BSAfinish::operator=(const BSAfinish& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void BSAfinish::copy(const BSAfinish& other)
{
    this->entangled = other.entangled;
}

void BSAfinish::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    doParsimPacking(b,this->entangled);
}

void BSAfinish::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    doParsimUnpacking(b,this->entangled);
}

bool BSAfinish::getEntangled() const
{
    return this->entangled;
}

void BSAfinish::setEntangled(bool entangled)
{
    this->entangled = entangled;
}

class BSAfinishDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BSAfinishDescriptor();
    virtual ~BSAfinishDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BSAfinishDescriptor)

BSAfinishDescriptor::BSAfinishDescriptor() : omnetpp::cClassDescriptor("BSAfinish", "header")
{
    propertynames = nullptr;
}

BSAfinishDescriptor::~BSAfinishDescriptor()
{
    delete[] propertynames;
}

bool BSAfinishDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BSAfinish *>(obj)!=nullptr;
}

const char **BSAfinishDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BSAfinishDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BSAfinishDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int BSAfinishDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BSAfinishDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "entangled",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int BSAfinishDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "entangled")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BSAfinishDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **BSAfinishDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BSAfinishDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BSAfinishDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BSAfinish *pp = (BSAfinish *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BSAfinishDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSAfinish *pp = (BSAfinish *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BSAfinishDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BSAfinish *pp = (BSAfinish *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getEntangled());
        default: return "";
    }
}

bool BSAfinishDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BSAfinish *pp = (BSAfinish *)object; (void)pp;
    switch (field) {
        case 0: pp->setEntangled(string2bool(value)); return true;
        default: return false;
    }
}

const char *BSAfinishDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *BSAfinishDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BSAfinish *pp = (BSAfinish *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CombinedBSAresults)

CombinedBSAresults::CombinedBSAresults(const char *name, short kind) : ::BSMtimingNotifier(name,kind)
{
    list_of_failed_arraysize = 0;
    this->list_of_failed = 0;
}

CombinedBSAresults::CombinedBSAresults(const CombinedBSAresults& other) : ::BSMtimingNotifier(other)
{
    list_of_failed_arraysize = 0;
    this->list_of_failed = 0;
    copy(other);
}

CombinedBSAresults::~CombinedBSAresults()
{
    delete [] this->list_of_failed;
}

CombinedBSAresults& CombinedBSAresults::operator=(const CombinedBSAresults& other)
{
    if (this==&other) return *this;
    ::BSMtimingNotifier::operator=(other);
    copy(other);
    return *this;
}

void CombinedBSAresults::copy(const CombinedBSAresults& other)
{
    delete [] this->list_of_failed;
    this->list_of_failed = (other.list_of_failed_arraysize==0) ? nullptr : new bool[other.list_of_failed_arraysize];
    list_of_failed_arraysize = other.list_of_failed_arraysize;
    for (unsigned int i=0; i<list_of_failed_arraysize; i++)
        this->list_of_failed[i] = other.list_of_failed[i];
}

void CombinedBSAresults::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BSMtimingNotifier::parsimPack(b);
    b->pack(list_of_failed_arraysize);
    doParsimArrayPacking(b,this->list_of_failed,list_of_failed_arraysize);
}

void CombinedBSAresults::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BSMtimingNotifier::parsimUnpack(b);
    delete [] this->list_of_failed;
    b->unpack(list_of_failed_arraysize);
    if (list_of_failed_arraysize==0) {
        this->list_of_failed = 0;
    } else {
        this->list_of_failed = new bool[list_of_failed_arraysize];
        doParsimArrayUnpacking(b,this->list_of_failed,list_of_failed_arraysize);
    }
}

void CombinedBSAresults::setList_of_failedArraySize(unsigned int size)
{
    bool *list_of_failed2 = (size==0) ? nullptr : new bool[size];
    unsigned int sz = list_of_failed_arraysize < size ? list_of_failed_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        list_of_failed2[i] = this->list_of_failed[i];
    for (unsigned int i=sz; i<size; i++)
        list_of_failed2[i] = 0;
    list_of_failed_arraysize = size;
    delete [] this->list_of_failed;
    this->list_of_failed = list_of_failed2;
}

unsigned int CombinedBSAresults::getList_of_failedArraySize() const
{
    return list_of_failed_arraysize;
}

bool CombinedBSAresults::getList_of_failed(unsigned int k) const
{
    if (k>=list_of_failed_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", list_of_failed_arraysize, k);
    return this->list_of_failed[k];
}

void CombinedBSAresults::setList_of_failed(unsigned int k, bool list_of_failed)
{
    if (k>=list_of_failed_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", list_of_failed_arraysize, k);
    this->list_of_failed[k] = list_of_failed;
}

class CombinedBSAresultsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CombinedBSAresultsDescriptor();
    virtual ~CombinedBSAresultsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CombinedBSAresultsDescriptor)

CombinedBSAresultsDescriptor::CombinedBSAresultsDescriptor() : omnetpp::cClassDescriptor("CombinedBSAresults", "BSMtimingNotifier")
{
    propertynames = nullptr;
}

CombinedBSAresultsDescriptor::~CombinedBSAresultsDescriptor()
{
    delete[] propertynames;
}

bool CombinedBSAresultsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CombinedBSAresults *>(obj)!=nullptr;
}

const char **CombinedBSAresultsDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CombinedBSAresultsDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CombinedBSAresultsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int CombinedBSAresultsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CombinedBSAresultsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "list_of_failed",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int CombinedBSAresultsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "list_of_failed")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CombinedBSAresultsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **CombinedBSAresultsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CombinedBSAresultsDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CombinedBSAresultsDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults *pp = (CombinedBSAresults *)object; (void)pp;
    switch (field) {
        case 0: return pp->getList_of_failedArraySize();
        default: return 0;
    }
}

const char *CombinedBSAresultsDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults *pp = (CombinedBSAresults *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CombinedBSAresultsDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults *pp = (CombinedBSAresults *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getList_of_failed(i));
        default: return "";
    }
}

bool CombinedBSAresultsDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults *pp = (CombinedBSAresults *)object; (void)pp;
    switch (field) {
        case 0: pp->setList_of_failed(i,string2bool(value)); return true;
        default: return false;
    }
}

const char *CombinedBSAresultsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *CombinedBSAresultsDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults *pp = (CombinedBSAresults *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CombinedBSAresults_epps)

CombinedBSAresults_epps::CombinedBSAresults_epps(const char *name, short kind) : ::header(name,kind)
{
    list_of_failed_arraysize = 0;
    this->list_of_failed = 0;
}

CombinedBSAresults_epps::CombinedBSAresults_epps(const CombinedBSAresults_epps& other) : ::header(other)
{
    list_of_failed_arraysize = 0;
    this->list_of_failed = 0;
    copy(other);
}

CombinedBSAresults_epps::~CombinedBSAresults_epps()
{
    delete [] this->list_of_failed;
}

CombinedBSAresults_epps& CombinedBSAresults_epps::operator=(const CombinedBSAresults_epps& other)
{
    if (this==&other) return *this;
    ::header::operator=(other);
    copy(other);
    return *this;
}

void CombinedBSAresults_epps::copy(const CombinedBSAresults_epps& other)
{
    delete [] this->list_of_failed;
    this->list_of_failed = (other.list_of_failed_arraysize==0) ? nullptr : new bool[other.list_of_failed_arraysize];
    list_of_failed_arraysize = other.list_of_failed_arraysize;
    for (unsigned int i=0; i<list_of_failed_arraysize; i++)
        this->list_of_failed[i] = other.list_of_failed[i];
}

void CombinedBSAresults_epps::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::header::parsimPack(b);
    b->pack(list_of_failed_arraysize);
    doParsimArrayPacking(b,this->list_of_failed,list_of_failed_arraysize);
}

void CombinedBSAresults_epps::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::header::parsimUnpack(b);
    delete [] this->list_of_failed;
    b->unpack(list_of_failed_arraysize);
    if (list_of_failed_arraysize==0) {
        this->list_of_failed = 0;
    } else {
        this->list_of_failed = new bool[list_of_failed_arraysize];
        doParsimArrayUnpacking(b,this->list_of_failed,list_of_failed_arraysize);
    }
}

void CombinedBSAresults_epps::setList_of_failedArraySize(unsigned int size)
{
    bool *list_of_failed2 = (size==0) ? nullptr : new bool[size];
    unsigned int sz = list_of_failed_arraysize < size ? list_of_failed_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        list_of_failed2[i] = this->list_of_failed[i];
    for (unsigned int i=sz; i<size; i++)
        list_of_failed2[i] = 0;
    list_of_failed_arraysize = size;
    delete [] this->list_of_failed;
    this->list_of_failed = list_of_failed2;
}

unsigned int CombinedBSAresults_epps::getList_of_failedArraySize() const
{
    return list_of_failed_arraysize;
}

bool CombinedBSAresults_epps::getList_of_failed(unsigned int k) const
{
    if (k>=list_of_failed_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", list_of_failed_arraysize, k);
    return this->list_of_failed[k];
}

void CombinedBSAresults_epps::setList_of_failed(unsigned int k, bool list_of_failed)
{
    if (k>=list_of_failed_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", list_of_failed_arraysize, k);
    this->list_of_failed[k] = list_of_failed;
}

class CombinedBSAresults_eppsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CombinedBSAresults_eppsDescriptor();
    virtual ~CombinedBSAresults_eppsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CombinedBSAresults_eppsDescriptor)

CombinedBSAresults_eppsDescriptor::CombinedBSAresults_eppsDescriptor() : omnetpp::cClassDescriptor("CombinedBSAresults_epps", "header")
{
    propertynames = nullptr;
}

CombinedBSAresults_eppsDescriptor::~CombinedBSAresults_eppsDescriptor()
{
    delete[] propertynames;
}

bool CombinedBSAresults_eppsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CombinedBSAresults_epps *>(obj)!=nullptr;
}

const char **CombinedBSAresults_eppsDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CombinedBSAresults_eppsDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CombinedBSAresults_eppsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int CombinedBSAresults_eppsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CombinedBSAresults_eppsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "list_of_failed",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int CombinedBSAresults_eppsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "list_of_failed")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CombinedBSAresults_eppsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **CombinedBSAresults_eppsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CombinedBSAresults_eppsDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CombinedBSAresults_eppsDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults_epps *pp = (CombinedBSAresults_epps *)object; (void)pp;
    switch (field) {
        case 0: return pp->getList_of_failedArraySize();
        default: return 0;
    }
}

const char *CombinedBSAresults_eppsDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults_epps *pp = (CombinedBSAresults_epps *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CombinedBSAresults_eppsDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults_epps *pp = (CombinedBSAresults_epps *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getList_of_failed(i));
        default: return "";
    }
}

bool CombinedBSAresults_eppsDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults_epps *pp = (CombinedBSAresults_epps *)object; (void)pp;
    switch (field) {
        case 0: pp->setList_of_failed(i,string2bool(value)); return true;
        default: return false;
    }
}

const char *CombinedBSAresults_eppsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *CombinedBSAresults_eppsDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CombinedBSAresults_epps *pp = (CombinedBSAresults_epps *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


