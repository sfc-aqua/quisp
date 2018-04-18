//
// Generated file, do not edit! Created by nedtool 5.2 from PhotonicQubit.msg.
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
#include "PhotonicQubit_m.h"

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

Register_Class(PhotonicQubit)

PhotonicQubit::PhotonicQubit(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->message_type = "qubit";
    this->pauliXerr = false;
    this->pauliZerr = false;
    this->photonLost = false;
    this->nonPaulierr = false;
    this->nonPaulierrTwo = false;
    this->NodeEntangledWith = -1;
    this->QNICEntangledWith = -1;
    this->StationaryQubitEntangledWith = -1;
    this->error_random_for_debug = 0;
    this->first = false;
    this->last = false;
}

PhotonicQubit::PhotonicQubit(const PhotonicQubit& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PhotonicQubit::~PhotonicQubit()
{
}

PhotonicQubit& PhotonicQubit::operator=(const PhotonicQubit& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PhotonicQubit::copy(const PhotonicQubit& other)
{
    this->message_type = other.message_type;
    this->pauliXerr = other.pauliXerr;
    this->pauliZerr = other.pauliZerr;
    this->photonLost = other.photonLost;
    this->nonPaulierr = other.nonPaulierr;
    this->nonPaulierrTwo = other.nonPaulierrTwo;
    this->NodeEntangledWith = other.NodeEntangledWith;
    this->QNICEntangledWith = other.QNICEntangledWith;
    this->StationaryQubitEntangledWith = other.StationaryQubitEntangledWith;
    this->error_random_for_debug = other.error_random_for_debug;
    this->first = other.first;
    this->last = other.last;
}

void PhotonicQubit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->message_type);
    doParsimPacking(b,this->pauliXerr);
    doParsimPacking(b,this->pauliZerr);
    doParsimPacking(b,this->photonLost);
    doParsimPacking(b,this->nonPaulierr);
    doParsimPacking(b,this->nonPaulierrTwo);
    doParsimPacking(b,this->NodeEntangledWith);
    doParsimPacking(b,this->QNICEntangledWith);
    doParsimPacking(b,this->StationaryQubitEntangledWith);
    doParsimPacking(b,this->error_random_for_debug);
    doParsimPacking(b,this->first);
    doParsimPacking(b,this->last);
}

void PhotonicQubit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->message_type);
    doParsimUnpacking(b,this->pauliXerr);
    doParsimUnpacking(b,this->pauliZerr);
    doParsimUnpacking(b,this->photonLost);
    doParsimUnpacking(b,this->nonPaulierr);
    doParsimUnpacking(b,this->nonPaulierrTwo);
    doParsimUnpacking(b,this->NodeEntangledWith);
    doParsimUnpacking(b,this->QNICEntangledWith);
    doParsimUnpacking(b,this->StationaryQubitEntangledWith);
    doParsimUnpacking(b,this->error_random_for_debug);
    doParsimUnpacking(b,this->first);
    doParsimUnpacking(b,this->last);
}

const char * PhotonicQubit::getMessage_type() const
{
    return this->message_type.c_str();
}

void PhotonicQubit::setMessage_type(const char * message_type)
{
    this->message_type = message_type;
}

bool PhotonicQubit::getPauliXerr() const
{
    return this->pauliXerr;
}

void PhotonicQubit::setPauliXerr(bool pauliXerr)
{
    this->pauliXerr = pauliXerr;
}

bool PhotonicQubit::getPauliZerr() const
{
    return this->pauliZerr;
}

void PhotonicQubit::setPauliZerr(bool pauliZerr)
{
    this->pauliZerr = pauliZerr;
}

bool PhotonicQubit::getPhotonLost() const
{
    return this->photonLost;
}

void PhotonicQubit::setPhotonLost(bool photonLost)
{
    this->photonLost = photonLost;
}

bool PhotonicQubit::getNonPaulierr() const
{
    return this->nonPaulierr;
}

void PhotonicQubit::setNonPaulierr(bool nonPaulierr)
{
    this->nonPaulierr = nonPaulierr;
}

bool PhotonicQubit::getNonPaulierrTwo() const
{
    return this->nonPaulierrTwo;
}

void PhotonicQubit::setNonPaulierrTwo(bool nonPaulierrTwo)
{
    this->nonPaulierrTwo = nonPaulierrTwo;
}

int PhotonicQubit::getNodeEntangledWith() const
{
    return this->NodeEntangledWith;
}

void PhotonicQubit::setNodeEntangledWith(int NodeEntangledWith)
{
    this->NodeEntangledWith = NodeEntangledWith;
}

int PhotonicQubit::getQNICEntangledWith() const
{
    return this->QNICEntangledWith;
}

void PhotonicQubit::setQNICEntangledWith(int QNICEntangledWith)
{
    this->QNICEntangledWith = QNICEntangledWith;
}

int PhotonicQubit::getStationaryQubitEntangledWith() const
{
    return this->StationaryQubitEntangledWith;
}

void PhotonicQubit::setStationaryQubitEntangledWith(int StationaryQubitEntangledWith)
{
    this->StationaryQubitEntangledWith = StationaryQubitEntangledWith;
}

double PhotonicQubit::getError_random_for_debug() const
{
    return this->error_random_for_debug;
}

void PhotonicQubit::setError_random_for_debug(double error_random_for_debug)
{
    this->error_random_for_debug = error_random_for_debug;
}

bool PhotonicQubit::getFirst() const
{
    return this->first;
}

void PhotonicQubit::setFirst(bool first)
{
    this->first = first;
}

bool PhotonicQubit::getLast() const
{
    return this->last;
}

void PhotonicQubit::setLast(bool last)
{
    this->last = last;
}

class PhotonicQubitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PhotonicQubitDescriptor();
    virtual ~PhotonicQubitDescriptor();

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

Register_ClassDescriptor(PhotonicQubitDescriptor)

PhotonicQubitDescriptor::PhotonicQubitDescriptor() : omnetpp::cClassDescriptor("PhotonicQubit", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

PhotonicQubitDescriptor::~PhotonicQubitDescriptor()
{
    delete[] propertynames;
}

bool PhotonicQubitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PhotonicQubit *>(obj)!=nullptr;
}

const char **PhotonicQubitDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PhotonicQubitDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PhotonicQubitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount() : 12;
}

unsigned int PhotonicQubitDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *PhotonicQubitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "message_type",
        "pauliXerr",
        "pauliZerr",
        "photonLost",
        "nonPaulierr",
        "nonPaulierrTwo",
        "NodeEntangledWith",
        "QNICEntangledWith",
        "StationaryQubitEntangledWith",
        "error_random_for_debug",
        "first",
        "last",
    };
    return (field>=0 && field<12) ? fieldNames[field] : nullptr;
}

int PhotonicQubitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "message_type")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pauliXerr")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "pauliZerr")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "photonLost")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nonPaulierr")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "nonPaulierrTwo")==0) return base+5;
    if (fieldName[0]=='N' && strcmp(fieldName, "NodeEntangledWith")==0) return base+6;
    if (fieldName[0]=='Q' && strcmp(fieldName, "QNICEntangledWith")==0) return base+7;
    if (fieldName[0]=='S' && strcmp(fieldName, "StationaryQubitEntangledWith")==0) return base+8;
    if (fieldName[0]=='e' && strcmp(fieldName, "error_random_for_debug")==0) return base+9;
    if (fieldName[0]=='f' && strcmp(fieldName, "first")==0) return base+10;
    if (fieldName[0]=='l' && strcmp(fieldName, "last")==0) return base+11;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PhotonicQubitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "int",
        "int",
        "int",
        "double",
        "bool",
        "bool",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : nullptr;
}

const char **PhotonicQubitDescriptor::getFieldPropertyNames(int field) const
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

const char *PhotonicQubitDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int PhotonicQubitDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PhotonicQubit *pp = (PhotonicQubit *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PhotonicQubitDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PhotonicQubit *pp = (PhotonicQubit *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PhotonicQubitDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PhotonicQubit *pp = (PhotonicQubit *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getMessage_type());
        case 1: return bool2string(pp->getPauliXerr());
        case 2: return bool2string(pp->getPauliZerr());
        case 3: return bool2string(pp->getPhotonLost());
        case 4: return bool2string(pp->getNonPaulierr());
        case 5: return bool2string(pp->getNonPaulierrTwo());
        case 6: return long2string(pp->getNodeEntangledWith());
        case 7: return long2string(pp->getQNICEntangledWith());
        case 8: return long2string(pp->getStationaryQubitEntangledWith());
        case 9: return double2string(pp->getError_random_for_debug());
        case 10: return bool2string(pp->getFirst());
        case 11: return bool2string(pp->getLast());
        default: return "";
    }
}

bool PhotonicQubitDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PhotonicQubit *pp = (PhotonicQubit *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessage_type((value)); return true;
        case 1: pp->setPauliXerr(string2bool(value)); return true;
        case 2: pp->setPauliZerr(string2bool(value)); return true;
        case 3: pp->setPhotonLost(string2bool(value)); return true;
        case 4: pp->setNonPaulierr(string2bool(value)); return true;
        case 5: pp->setNonPaulierrTwo(string2bool(value)); return true;
        case 6: pp->setNodeEntangledWith(string2long(value)); return true;
        case 7: pp->setQNICEntangledWith(string2long(value)); return true;
        case 8: pp->setStationaryQubitEntangledWith(string2long(value)); return true;
        case 9: pp->setError_random_for_debug(string2double(value)); return true;
        case 10: pp->setFirst(string2bool(value)); return true;
        case 11: pp->setLast(string2bool(value)); return true;
        default: return false;
    }
}

const char *PhotonicQubitDescriptor::getFieldStructName(int field) const
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

void *PhotonicQubitDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PhotonicQubit *pp = (PhotonicQubit *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


