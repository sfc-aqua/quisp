//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/applications/dhcp/DhcpMessage.msg.
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
#include "DhcpMessage_m.h"

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

Register_Enum(inet::DhcpOpcode, (inet::DhcpOpcode::BOOTREQUEST, inet::DhcpOpcode::BOOTREPLY));

Register_Enum(inet::DhcpMessageType, (inet::DhcpMessageType::DHCPDISCOVER, inet::DhcpMessageType::DHCPOFFER, inet::DhcpMessageType::DHCPREQUEST, inet::DhcpMessageType::DHCPDECLINE, inet::DhcpMessageType::DHCPACK, inet::DhcpMessageType::DHCPNAK, inet::DhcpMessageType::DHCPRELEASE, inet::DhcpMessageType::DHCPINFORM));

Register_Enum(inet::DhcpOptionCode, (inet::DhcpOptionCode::DHCP_MSG_TYPE, inet::DhcpOptionCode::CLIENT_ID, inet::DhcpOptionCode::HOSTNAME, inet::DhcpOptionCode::REQUESTED_IP, inet::DhcpOptionCode::PARAM_LIST, inet::DhcpOptionCode::SUBNET_MASK, inet::DhcpOptionCode::ROUTER, inet::DhcpOptionCode::DNS, inet::DhcpOptionCode::NTP_SRV, inet::DhcpOptionCode::RENEWAL_TIME, inet::DhcpOptionCode::REBIND_TIME, inet::DhcpOptionCode::LEASE_TIME, inet::DhcpOptionCode::SERVER_ID));

Register_Enum(inet::DhcpTimerType, (inet::DhcpTimerType::WAIT_OFFER, inet::DhcpTimerType::WAIT_ACK, inet::DhcpTimerType::T1, inet::DhcpTimerType::T2, inet::DhcpTimerType::LEASE_TIMEOUT, inet::DhcpTimerType::START_DHCP));

Register_Class(DhcpOptions)

DhcpOptions::DhcpOptions() : ::omnetpp::cObject()
{
}

DhcpOptions::DhcpOptions(const DhcpOptions& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

DhcpOptions::~DhcpOptions()
{
    delete [] this->parameterRequestList;
    delete [] this->router;
    delete [] this->dns;
    delete [] this->ntp;
}

DhcpOptions& DhcpOptions::operator=(const DhcpOptions& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void DhcpOptions::copy(const DhcpOptions& other)
{
    this->messageType = other.messageType;
    this->hostName = other.hostName;
    delete [] this->parameterRequestList;
    this->parameterRequestList = (other.parameterRequestList_arraysize==0) ? nullptr : new DhcpOptionCode[other.parameterRequestList_arraysize];
    parameterRequestList_arraysize = other.parameterRequestList_arraysize;
    for (size_t i = 0; i < parameterRequestList_arraysize; i++) {
        this->parameterRequestList[i] = other.parameterRequestList[i];
    }
    this->clientIdentifier = other.clientIdentifier;
    this->requestedIp = other.requestedIp;
    this->subnetMask = other.subnetMask;
    delete [] this->router;
    this->router = (other.router_arraysize==0) ? nullptr : new Ipv4Address[other.router_arraysize];
    router_arraysize = other.router_arraysize;
    for (size_t i = 0; i < router_arraysize; i++) {
        this->router[i] = other.router[i];
    }
    delete [] this->dns;
    this->dns = (other.dns_arraysize==0) ? nullptr : new Ipv4Address[other.dns_arraysize];
    dns_arraysize = other.dns_arraysize;
    for (size_t i = 0; i < dns_arraysize; i++) {
        this->dns[i] = other.dns[i];
    }
    delete [] this->ntp;
    this->ntp = (other.ntp_arraysize==0) ? nullptr : new Ipv4Address[other.ntp_arraysize];
    ntp_arraysize = other.ntp_arraysize;
    for (size_t i = 0; i < ntp_arraysize; i++) {
        this->ntp[i] = other.ntp[i];
    }
    this->serverIdentifier = other.serverIdentifier;
    this->renewalTime = other.renewalTime;
    this->rebindingTime = other.rebindingTime;
    this->leaseTime = other.leaseTime;
}

void DhcpOptions::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->hostName);
    b->pack(parameterRequestList_arraysize);
    doParsimArrayPacking(b,this->parameterRequestList,parameterRequestList_arraysize);
    doParsimPacking(b,this->clientIdentifier);
    doParsimPacking(b,this->requestedIp);
    doParsimPacking(b,this->subnetMask);
    b->pack(router_arraysize);
    doParsimArrayPacking(b,this->router,router_arraysize);
    b->pack(dns_arraysize);
    doParsimArrayPacking(b,this->dns,dns_arraysize);
    b->pack(ntp_arraysize);
    doParsimArrayPacking(b,this->ntp,ntp_arraysize);
    doParsimPacking(b,this->serverIdentifier);
    doParsimPacking(b,this->renewalTime);
    doParsimPacking(b,this->rebindingTime);
    doParsimPacking(b,this->leaseTime);
}

void DhcpOptions::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->hostName);
    delete [] this->parameterRequestList;
    b->unpack(parameterRequestList_arraysize);
    if (parameterRequestList_arraysize == 0) {
        this->parameterRequestList = nullptr;
    } else {
        this->parameterRequestList = new DhcpOptionCode[parameterRequestList_arraysize];
        doParsimArrayUnpacking(b,this->parameterRequestList,parameterRequestList_arraysize);
    }
    doParsimUnpacking(b,this->clientIdentifier);
    doParsimUnpacking(b,this->requestedIp);
    doParsimUnpacking(b,this->subnetMask);
    delete [] this->router;
    b->unpack(router_arraysize);
    if (router_arraysize == 0) {
        this->router = nullptr;
    } else {
        this->router = new Ipv4Address[router_arraysize];
        doParsimArrayUnpacking(b,this->router,router_arraysize);
    }
    delete [] this->dns;
    b->unpack(dns_arraysize);
    if (dns_arraysize == 0) {
        this->dns = nullptr;
    } else {
        this->dns = new Ipv4Address[dns_arraysize];
        doParsimArrayUnpacking(b,this->dns,dns_arraysize);
    }
    delete [] this->ntp;
    b->unpack(ntp_arraysize);
    if (ntp_arraysize == 0) {
        this->ntp = nullptr;
    } else {
        this->ntp = new Ipv4Address[ntp_arraysize];
        doParsimArrayUnpacking(b,this->ntp,ntp_arraysize);
    }
    doParsimUnpacking(b,this->serverIdentifier);
    doParsimUnpacking(b,this->renewalTime);
    doParsimUnpacking(b,this->rebindingTime);
    doParsimUnpacking(b,this->leaseTime);
}

DhcpMessageType DhcpOptions::getMessageType() const
{
    return this->messageType;
}

void DhcpOptions::setMessageType(DhcpMessageType messageType)
{
    this->messageType = messageType;
}

const char * DhcpOptions::getHostName() const
{
    return this->hostName.c_str();
}

void DhcpOptions::setHostName(const char * hostName)
{
    this->hostName = hostName;
}

size_t DhcpOptions::getParameterRequestListArraySize() const
{
    return parameterRequestList_arraysize;
}

DhcpOptionCode DhcpOptions::getParameterRequestList(size_t k) const
{
    if (k >= parameterRequestList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)parameterRequestList_arraysize, (unsigned long)k);
    return this->parameterRequestList[k];
}

void DhcpOptions::setParameterRequestListArraySize(size_t newSize)
{
    DhcpOptionCode *parameterRequestList2 = (newSize==0) ? nullptr : new DhcpOptionCode[newSize];
    size_t minSize = parameterRequestList_arraysize < newSize ? parameterRequestList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        parameterRequestList2[i] = this->parameterRequestList[i];
    for (size_t i = minSize; i < newSize; i++)
        parameterRequestList2[i] = static_cast<inet::DhcpOptionCode>(-1);
    delete [] this->parameterRequestList;
    this->parameterRequestList = parameterRequestList2;
    parameterRequestList_arraysize = newSize;
}

void DhcpOptions::setParameterRequestList(size_t k, DhcpOptionCode parameterRequestList)
{
    if (k >= parameterRequestList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)parameterRequestList_arraysize, (unsigned long)k);
    this->parameterRequestList[k] = parameterRequestList;
}

void DhcpOptions::insertParameterRequestList(size_t k, DhcpOptionCode parameterRequestList)
{
    if (k > parameterRequestList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)parameterRequestList_arraysize, (unsigned long)k);
    size_t newSize = parameterRequestList_arraysize + 1;
    DhcpOptionCode *parameterRequestList2 = new DhcpOptionCode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        parameterRequestList2[i] = this->parameterRequestList[i];
    parameterRequestList2[k] = parameterRequestList;
    for (i = k + 1; i < newSize; i++)
        parameterRequestList2[i] = this->parameterRequestList[i-1];
    delete [] this->parameterRequestList;
    this->parameterRequestList = parameterRequestList2;
    parameterRequestList_arraysize = newSize;
}

void DhcpOptions::appendParameterRequestList(DhcpOptionCode parameterRequestList)
{
    insertParameterRequestList(parameterRequestList_arraysize, parameterRequestList);
}

void DhcpOptions::eraseParameterRequestList(size_t k)
{
    if (k >= parameterRequestList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)parameterRequestList_arraysize, (unsigned long)k);
    size_t newSize = parameterRequestList_arraysize - 1;
    DhcpOptionCode *parameterRequestList2 = (newSize == 0) ? nullptr : new DhcpOptionCode[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        parameterRequestList2[i] = this->parameterRequestList[i];
    for (i = k; i < newSize; i++)
        parameterRequestList2[i] = this->parameterRequestList[i+1];
    delete [] this->parameterRequestList;
    this->parameterRequestList = parameterRequestList2;
    parameterRequestList_arraysize = newSize;
}

const MacAddress& DhcpOptions::getClientIdentifier() const
{
    return this->clientIdentifier;
}

void DhcpOptions::setClientIdentifier(const MacAddress& clientIdentifier)
{
    this->clientIdentifier = clientIdentifier;
}

const Ipv4Address& DhcpOptions::getRequestedIp() const
{
    return this->requestedIp;
}

void DhcpOptions::setRequestedIp(const Ipv4Address& requestedIp)
{
    this->requestedIp = requestedIp;
}

const Ipv4Address& DhcpOptions::getSubnetMask() const
{
    return this->subnetMask;
}

void DhcpOptions::setSubnetMask(const Ipv4Address& subnetMask)
{
    this->subnetMask = subnetMask;
}

size_t DhcpOptions::getRouterArraySize() const
{
    return router_arraysize;
}

const Ipv4Address& DhcpOptions::getRouter(size_t k) const
{
    if (k >= router_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)router_arraysize, (unsigned long)k);
    return this->router[k];
}

void DhcpOptions::setRouterArraySize(size_t newSize)
{
    Ipv4Address *router2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = router_arraysize < newSize ? router_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        router2[i] = this->router[i];
    delete [] this->router;
    this->router = router2;
    router_arraysize = newSize;
}

void DhcpOptions::setRouter(size_t k, const Ipv4Address& router)
{
    if (k >= router_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)router_arraysize, (unsigned long)k);
    this->router[k] = router;
}

void DhcpOptions::insertRouter(size_t k, const Ipv4Address& router)
{
    if (k > router_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)router_arraysize, (unsigned long)k);
    size_t newSize = router_arraysize + 1;
    Ipv4Address *router2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        router2[i] = this->router[i];
    router2[k] = router;
    for (i = k + 1; i < newSize; i++)
        router2[i] = this->router[i-1];
    delete [] this->router;
    this->router = router2;
    router_arraysize = newSize;
}

void DhcpOptions::appendRouter(const Ipv4Address& router)
{
    insertRouter(router_arraysize, router);
}

void DhcpOptions::eraseRouter(size_t k)
{
    if (k >= router_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)router_arraysize, (unsigned long)k);
    size_t newSize = router_arraysize - 1;
    Ipv4Address *router2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        router2[i] = this->router[i];
    for (i = k; i < newSize; i++)
        router2[i] = this->router[i+1];
    delete [] this->router;
    this->router = router2;
    router_arraysize = newSize;
}

size_t DhcpOptions::getDnsArraySize() const
{
    return dns_arraysize;
}

const Ipv4Address& DhcpOptions::getDns(size_t k) const
{
    if (k >= dns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dns_arraysize, (unsigned long)k);
    return this->dns[k];
}

void DhcpOptions::setDnsArraySize(size_t newSize)
{
    Ipv4Address *dns2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = dns_arraysize < newSize ? dns_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        dns2[i] = this->dns[i];
    delete [] this->dns;
    this->dns = dns2;
    dns_arraysize = newSize;
}

void DhcpOptions::setDns(size_t k, const Ipv4Address& dns)
{
    if (k >= dns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dns_arraysize, (unsigned long)k);
    this->dns[k] = dns;
}

void DhcpOptions::insertDns(size_t k, const Ipv4Address& dns)
{
    if (k > dns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dns_arraysize, (unsigned long)k);
    size_t newSize = dns_arraysize + 1;
    Ipv4Address *dns2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dns2[i] = this->dns[i];
    dns2[k] = dns;
    for (i = k + 1; i < newSize; i++)
        dns2[i] = this->dns[i-1];
    delete [] this->dns;
    this->dns = dns2;
    dns_arraysize = newSize;
}

void DhcpOptions::appendDns(const Ipv4Address& dns)
{
    insertDns(dns_arraysize, dns);
}

void DhcpOptions::eraseDns(size_t k)
{
    if (k >= dns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dns_arraysize, (unsigned long)k);
    size_t newSize = dns_arraysize - 1;
    Ipv4Address *dns2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dns2[i] = this->dns[i];
    for (i = k; i < newSize; i++)
        dns2[i] = this->dns[i+1];
    delete [] this->dns;
    this->dns = dns2;
    dns_arraysize = newSize;
}

size_t DhcpOptions::getNtpArraySize() const
{
    return ntp_arraysize;
}

const Ipv4Address& DhcpOptions::getNtp(size_t k) const
{
    if (k >= ntp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ntp_arraysize, (unsigned long)k);
    return this->ntp[k];
}

void DhcpOptions::setNtpArraySize(size_t newSize)
{
    Ipv4Address *ntp2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = ntp_arraysize < newSize ? ntp_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        ntp2[i] = this->ntp[i];
    delete [] this->ntp;
    this->ntp = ntp2;
    ntp_arraysize = newSize;
}

void DhcpOptions::setNtp(size_t k, const Ipv4Address& ntp)
{
    if (k >= ntp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ntp_arraysize, (unsigned long)k);
    this->ntp[k] = ntp;
}

void DhcpOptions::insertNtp(size_t k, const Ipv4Address& ntp)
{
    if (k > ntp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ntp_arraysize, (unsigned long)k);
    size_t newSize = ntp_arraysize + 1;
    Ipv4Address *ntp2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ntp2[i] = this->ntp[i];
    ntp2[k] = ntp;
    for (i = k + 1; i < newSize; i++)
        ntp2[i] = this->ntp[i-1];
    delete [] this->ntp;
    this->ntp = ntp2;
    ntp_arraysize = newSize;
}

void DhcpOptions::appendNtp(const Ipv4Address& ntp)
{
    insertNtp(ntp_arraysize, ntp);
}

void DhcpOptions::eraseNtp(size_t k)
{
    if (k >= ntp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ntp_arraysize, (unsigned long)k);
    size_t newSize = ntp_arraysize - 1;
    Ipv4Address *ntp2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ntp2[i] = this->ntp[i];
    for (i = k; i < newSize; i++)
        ntp2[i] = this->ntp[i+1];
    delete [] this->ntp;
    this->ntp = ntp2;
    ntp_arraysize = newSize;
}

const Ipv4Address& DhcpOptions::getServerIdentifier() const
{
    return this->serverIdentifier;
}

void DhcpOptions::setServerIdentifier(const Ipv4Address& serverIdentifier)
{
    this->serverIdentifier = serverIdentifier;
}

::omnetpp::simtime_t DhcpOptions::getRenewalTime() const
{
    return this->renewalTime;
}

void DhcpOptions::setRenewalTime(::omnetpp::simtime_t renewalTime)
{
    this->renewalTime = renewalTime;
}

::omnetpp::simtime_t DhcpOptions::getRebindingTime() const
{
    return this->rebindingTime;
}

void DhcpOptions::setRebindingTime(::omnetpp::simtime_t rebindingTime)
{
    this->rebindingTime = rebindingTime;
}

::omnetpp::simtime_t DhcpOptions::getLeaseTime() const
{
    return this->leaseTime;
}

void DhcpOptions::setLeaseTime(::omnetpp::simtime_t leaseTime)
{
    this->leaseTime = leaseTime;
}

class DhcpOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_messageType,
        FIELD_hostName,
        FIELD_parameterRequestList,
        FIELD_clientIdentifier,
        FIELD_requestedIp,
        FIELD_subnetMask,
        FIELD_router,
        FIELD_dns,
        FIELD_ntp,
        FIELD_serverIdentifier,
        FIELD_renewalTime,
        FIELD_rebindingTime,
        FIELD_leaseTime,
    };
  public:
    DhcpOptionsDescriptor();
    virtual ~DhcpOptionsDescriptor();

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

Register_ClassDescriptor(DhcpOptionsDescriptor)

DhcpOptionsDescriptor::DhcpOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::DhcpOptions)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

DhcpOptionsDescriptor::~DhcpOptionsDescriptor()
{
    delete[] propertyNames;
}

bool DhcpOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DhcpOptions *>(obj)!=nullptr;
}

const char **DhcpOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DhcpOptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DhcpOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 13+base->getFieldCount() : 13;
}

unsigned int DhcpOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_messageType
        FD_ISEDITABLE,    // FIELD_hostName
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_parameterRequestList
        0,    // FIELD_clientIdentifier
        0,    // FIELD_requestedIp
        0,    // FIELD_subnetMask
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_router
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_dns
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_ntp
        0,    // FIELD_serverIdentifier
        FD_ISEDITABLE,    // FIELD_renewalTime
        FD_ISEDITABLE,    // FIELD_rebindingTime
        FD_ISEDITABLE,    // FIELD_leaseTime
    };
    return (field >= 0 && field < 13) ? fieldTypeFlags[field] : 0;
}

const char *DhcpOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageType",
        "hostName",
        "parameterRequestList",
        "clientIdentifier",
        "requestedIp",
        "subnetMask",
        "router",
        "dns",
        "ntp",
        "serverIdentifier",
        "renewalTime",
        "rebindingTime",
        "leaseTime",
    };
    return (field >= 0 && field < 13) ? fieldNames[field] : nullptr;
}

int DhcpOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "messageType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hostName") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "parameterRequestList") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "clientIdentifier") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "requestedIp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "subnetMask") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "router") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "dns") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "ntp") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "serverIdentifier") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "renewalTime") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "rebindingTime") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "leaseTime") == 0) return baseIndex + 12;
    return base ? base->findField(fieldName) : -1;
}

const char *DhcpOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::DhcpMessageType",    // FIELD_messageType
        "string",    // FIELD_hostName
        "inet::DhcpOptionCode",    // FIELD_parameterRequestList
        "inet::MacAddress",    // FIELD_clientIdentifier
        "inet::Ipv4Address",    // FIELD_requestedIp
        "inet::Ipv4Address",    // FIELD_subnetMask
        "inet::Ipv4Address",    // FIELD_router
        "inet::Ipv4Address",    // FIELD_dns
        "inet::Ipv4Address",    // FIELD_ntp
        "inet::Ipv4Address",    // FIELD_serverIdentifier
        "omnetpp::simtime_t",    // FIELD_renewalTime
        "omnetpp::simtime_t",    // FIELD_rebindingTime
        "omnetpp::simtime_t",    // FIELD_leaseTime
    };
    return (field >= 0 && field < 13) ? fieldTypeStrings[field] : nullptr;
}

const char **DhcpOptionsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_messageType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_parameterRequestList: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DhcpOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_messageType:
            if (!strcmp(propertyName, "enum")) return "inet::DhcpMessageType";
            return nullptr;
        case FIELD_parameterRequestList:
            if (!strcmp(propertyName, "enum")) return "inet::DhcpOptionCode";
            return nullptr;
        default: return nullptr;
    }
}

int DhcpOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_parameterRequestList: return pp->getParameterRequestListArraySize();
        case FIELD_router: return pp->getRouterArraySize();
        case FIELD_dns: return pp->getDnsArraySize();
        case FIELD_ntp: return pp->getNtpArraySize();
        default: return 0;
    }
}

void DhcpOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_parameterRequestList: pp->setParameterRequestListArraySize(size); break;
        case FIELD_router: pp->setRouterArraySize(size); break;
        case FIELD_dns: pp->setDnsArraySize(size); break;
        case FIELD_ntp: pp->setNtpArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DhcpOptions'", field);
    }
}

const char *DhcpOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DhcpOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: return enum2string(pp->getMessageType(), "inet::DhcpMessageType");
        case FIELD_hostName: return oppstring2string(pp->getHostName());
        case FIELD_parameterRequestList: return enum2string(pp->getParameterRequestList(i), "inet::DhcpOptionCode");
        case FIELD_clientIdentifier: return pp->getClientIdentifier().str();
        case FIELD_requestedIp: return pp->getRequestedIp().str();
        case FIELD_subnetMask: return pp->getSubnetMask().str();
        case FIELD_router: return pp->getRouter(i).str();
        case FIELD_dns: return pp->getDns(i).str();
        case FIELD_ntp: return pp->getNtp(i).str();
        case FIELD_serverIdentifier: return pp->getServerIdentifier().str();
        case FIELD_renewalTime: return simtime2string(pp->getRenewalTime());
        case FIELD_rebindingTime: return simtime2string(pp->getRebindingTime());
        case FIELD_leaseTime: return simtime2string(pp->getLeaseTime());
        default: return "";
    }
}

void DhcpOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_hostName: pp->setHostName((value)); break;
        case FIELD_renewalTime: pp->setRenewalTime(string2simtime(value)); break;
        case FIELD_rebindingTime: pp->setRebindingTime(string2simtime(value)); break;
        case FIELD_leaseTime: pp->setLeaseTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpOptions'", field);
    }
}

omnetpp::cValue DhcpOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: return static_cast<int>(pp->getMessageType());
        case FIELD_hostName: return pp->getHostName();
        case FIELD_parameterRequestList: return static_cast<int>(pp->getParameterRequestList(i));
        case FIELD_clientIdentifier: return omnetpp::toAnyPtr(&pp->getClientIdentifier()); break;
        case FIELD_requestedIp: return omnetpp::toAnyPtr(&pp->getRequestedIp()); break;
        case FIELD_subnetMask: return omnetpp::toAnyPtr(&pp->getSubnetMask()); break;
        case FIELD_router: return omnetpp::toAnyPtr(&pp->getRouter(i)); break;
        case FIELD_dns: return omnetpp::toAnyPtr(&pp->getDns(i)); break;
        case FIELD_ntp: return omnetpp::toAnyPtr(&pp->getNtp(i)); break;
        case FIELD_serverIdentifier: return omnetpp::toAnyPtr(&pp->getServerIdentifier()); break;
        case FIELD_renewalTime: return pp->getRenewalTime().dbl();
        case FIELD_rebindingTime: return pp->getRebindingTime().dbl();
        case FIELD_leaseTime: return pp->getLeaseTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DhcpOptions' as cValue -- field index out of range?", field);
    }
}

void DhcpOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_hostName: pp->setHostName(value.stringValue()); break;
        case FIELD_renewalTime: pp->setRenewalTime(value.doubleValue()); break;
        case FIELD_rebindingTime: pp->setRebindingTime(value.doubleValue()); break;
        case FIELD_leaseTime: pp->setLeaseTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpOptions'", field);
    }
}

const char *DhcpOptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr DhcpOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        case FIELD_clientIdentifier: return omnetpp::toAnyPtr(&pp->getClientIdentifier()); break;
        case FIELD_requestedIp: return omnetpp::toAnyPtr(&pp->getRequestedIp()); break;
        case FIELD_subnetMask: return omnetpp::toAnyPtr(&pp->getSubnetMask()); break;
        case FIELD_router: return omnetpp::toAnyPtr(&pp->getRouter(i)); break;
        case FIELD_dns: return omnetpp::toAnyPtr(&pp->getDns(i)); break;
        case FIELD_ntp: return omnetpp::toAnyPtr(&pp->getNtp(i)); break;
        case FIELD_serverIdentifier: return omnetpp::toAnyPtr(&pp->getServerIdentifier()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DhcpOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpOptions *pp = omnetpp::fromAnyPtr<DhcpOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpOptions'", field);
    }
}

Register_Class(DhcpMessage)

DhcpMessage::DhcpMessage() : ::inet::FieldsChunk()
{
}

DhcpMessage::DhcpMessage(const DhcpMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

DhcpMessage::~DhcpMessage()
{
}

DhcpMessage& DhcpMessage::operator=(const DhcpMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void DhcpMessage::copy(const DhcpMessage& other)
{
    this->op = other.op;
    this->htype = other.htype;
    this->hlen = other.hlen;
    this->hops = other.hops;
    this->xid = other.xid;
    this->secs = other.secs;
    this->broadcast = other.broadcast;
    this->reserved = other.reserved;
    this->ciaddr = other.ciaddr;
    this->yiaddr = other.yiaddr;
    this->giaddr = other.giaddr;
    this->chaddr = other.chaddr;
    this->sname = other.sname;
    this->file = other.file;
    this->options = other.options;
}

void DhcpMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->op);
    doParsimPacking(b,this->htype);
    doParsimPacking(b,this->hlen);
    doParsimPacking(b,this->hops);
    doParsimPacking(b,this->xid);
    doParsimPacking(b,this->secs);
    doParsimPacking(b,this->broadcast);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->ciaddr);
    doParsimPacking(b,this->yiaddr);
    doParsimPacking(b,this->giaddr);
    doParsimPacking(b,this->chaddr);
    doParsimPacking(b,this->sname);
    doParsimPacking(b,this->file);
    doParsimPacking(b,this->options);
}

void DhcpMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->op);
    doParsimUnpacking(b,this->htype);
    doParsimUnpacking(b,this->hlen);
    doParsimUnpacking(b,this->hops);
    doParsimUnpacking(b,this->xid);
    doParsimUnpacking(b,this->secs);
    doParsimUnpacking(b,this->broadcast);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->ciaddr);
    doParsimUnpacking(b,this->yiaddr);
    doParsimUnpacking(b,this->giaddr);
    doParsimUnpacking(b,this->chaddr);
    doParsimUnpacking(b,this->sname);
    doParsimUnpacking(b,this->file);
    doParsimUnpacking(b,this->options);
}

DhcpOpcode DhcpMessage::getOp() const
{
    return this->op;
}

void DhcpMessage::setOp(DhcpOpcode op)
{
    handleChange();
    this->op = op;
}

int DhcpMessage::getHtype() const
{
    return this->htype;
}

void DhcpMessage::setHtype(int htype)
{
    handleChange();
    this->htype = htype;
}

int DhcpMessage::getHlen() const
{
    return this->hlen;
}

void DhcpMessage::setHlen(int hlen)
{
    handleChange();
    this->hlen = hlen;
}

int DhcpMessage::getHops() const
{
    return this->hops;
}

void DhcpMessage::setHops(int hops)
{
    handleChange();
    this->hops = hops;
}

unsigned int DhcpMessage::getXid() const
{
    return this->xid;
}

void DhcpMessage::setXid(unsigned int xid)
{
    handleChange();
    this->xid = xid;
}

int DhcpMessage::getSecs() const
{
    return this->secs;
}

void DhcpMessage::setSecs(int secs)
{
    handleChange();
    this->secs = secs;
}

bool DhcpMessage::getBroadcast() const
{
    return this->broadcast;
}

void DhcpMessage::setBroadcast(bool broadcast)
{
    handleChange();
    this->broadcast = broadcast;
}

uint16_t DhcpMessage::getReserved() const
{
    return this->reserved;
}

void DhcpMessage::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

const Ipv4Address& DhcpMessage::getCiaddr() const
{
    return this->ciaddr;
}

void DhcpMessage::setCiaddr(const Ipv4Address& ciaddr)
{
    handleChange();
    this->ciaddr = ciaddr;
}

const Ipv4Address& DhcpMessage::getYiaddr() const
{
    return this->yiaddr;
}

void DhcpMessage::setYiaddr(const Ipv4Address& yiaddr)
{
    handleChange();
    this->yiaddr = yiaddr;
}

const Ipv4Address& DhcpMessage::getGiaddr() const
{
    return this->giaddr;
}

void DhcpMessage::setGiaddr(const Ipv4Address& giaddr)
{
    handleChange();
    this->giaddr = giaddr;
}

const MacAddress& DhcpMessage::getChaddr() const
{
    return this->chaddr;
}

void DhcpMessage::setChaddr(const MacAddress& chaddr)
{
    handleChange();
    this->chaddr = chaddr;
}

const char * DhcpMessage::getSname() const
{
    return this->sname.c_str();
}

void DhcpMessage::setSname(const char * sname)
{
    handleChange();
    this->sname = sname;
}

const char * DhcpMessage::getFile() const
{
    return this->file.c_str();
}

void DhcpMessage::setFile(const char * file)
{
    handleChange();
    this->file = file;
}

const DhcpOptions& DhcpMessage::getOptions() const
{
    return this->options;
}

void DhcpMessage::setOptions(const DhcpOptions& options)
{
    handleChange();
    this->options = options;
}

class DhcpMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_op,
        FIELD_htype,
        FIELD_hlen,
        FIELD_hops,
        FIELD_xid,
        FIELD_secs,
        FIELD_broadcast,
        FIELD_reserved,
        FIELD_ciaddr,
        FIELD_yiaddr,
        FIELD_giaddr,
        FIELD_chaddr,
        FIELD_sname,
        FIELD_file,
        FIELD_options,
    };
  public:
    DhcpMessageDescriptor();
    virtual ~DhcpMessageDescriptor();

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

Register_ClassDescriptor(DhcpMessageDescriptor)

DhcpMessageDescriptor::DhcpMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::DhcpMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

DhcpMessageDescriptor::~DhcpMessageDescriptor()
{
    delete[] propertyNames;
}

bool DhcpMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DhcpMessage *>(obj)!=nullptr;
}

const char **DhcpMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DhcpMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DhcpMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 15+base->getFieldCount() : 15;
}

unsigned int DhcpMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_op
        FD_ISEDITABLE,    // FIELD_htype
        FD_ISEDITABLE,    // FIELD_hlen
        FD_ISEDITABLE,    // FIELD_hops
        FD_ISEDITABLE,    // FIELD_xid
        FD_ISEDITABLE,    // FIELD_secs
        FD_ISEDITABLE,    // FIELD_broadcast
        FD_ISEDITABLE,    // FIELD_reserved
        0,    // FIELD_ciaddr
        0,    // FIELD_yiaddr
        0,    // FIELD_giaddr
        0,    // FIELD_chaddr
        FD_ISEDITABLE,    // FIELD_sname
        FD_ISEDITABLE,    // FIELD_file
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
}

const char *DhcpMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "op",
        "htype",
        "hlen",
        "hops",
        "xid",
        "secs",
        "broadcast",
        "reserved",
        "ciaddr",
        "yiaddr",
        "giaddr",
        "chaddr",
        "sname",
        "file",
        "options",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int DhcpMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "op") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "htype") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hlen") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hops") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "xid") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "secs") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "broadcast") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "ciaddr") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "yiaddr") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "giaddr") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "chaddr") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "sname") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "file") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 14;
    return base ? base->findField(fieldName) : -1;
}

const char *DhcpMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::DhcpOpcode",    // FIELD_op
        "int",    // FIELD_htype
        "int",    // FIELD_hlen
        "int",    // FIELD_hops
        "unsigned int",    // FIELD_xid
        "int",    // FIELD_secs
        "bool",    // FIELD_broadcast
        "uint16_t",    // FIELD_reserved
        "inet::Ipv4Address",    // FIELD_ciaddr
        "inet::Ipv4Address",    // FIELD_yiaddr
        "inet::Ipv4Address",    // FIELD_giaddr
        "inet::MacAddress",    // FIELD_chaddr
        "string",    // FIELD_sname
        "string",    // FIELD_file
        "inet::DhcpOptions",    // FIELD_options
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
}

const char **DhcpMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_op: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DhcpMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_op:
            if (!strcmp(propertyName, "enum")) return "inet::DhcpOpcode";
            return nullptr;
        default: return nullptr;
    }
}

int DhcpMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DhcpMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DhcpMessage'", field);
    }
}

const char *DhcpMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DhcpMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_op: return enum2string(pp->getOp(), "inet::DhcpOpcode");
        case FIELD_htype: return long2string(pp->getHtype());
        case FIELD_hlen: return long2string(pp->getHlen());
        case FIELD_hops: return long2string(pp->getHops());
        case FIELD_xid: return ulong2string(pp->getXid());
        case FIELD_secs: return long2string(pp->getSecs());
        case FIELD_broadcast: return bool2string(pp->getBroadcast());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_ciaddr: return pp->getCiaddr().str();
        case FIELD_yiaddr: return pp->getYiaddr().str();
        case FIELD_giaddr: return pp->getGiaddr().str();
        case FIELD_chaddr: return pp->getChaddr().str();
        case FIELD_sname: return oppstring2string(pp->getSname());
        case FIELD_file: return oppstring2string(pp->getFile());
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void DhcpMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_htype: pp->setHtype(string2long(value)); break;
        case FIELD_hlen: pp->setHlen(string2long(value)); break;
        case FIELD_hops: pp->setHops(string2long(value)); break;
        case FIELD_xid: pp->setXid(string2ulong(value)); break;
        case FIELD_secs: pp->setSecs(string2long(value)); break;
        case FIELD_broadcast: pp->setBroadcast(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_sname: pp->setSname((value)); break;
        case FIELD_file: pp->setFile((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpMessage'", field);
    }
}

omnetpp::cValue DhcpMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_op: return static_cast<int>(pp->getOp());
        case FIELD_htype: return pp->getHtype();
        case FIELD_hlen: return pp->getHlen();
        case FIELD_hops: return pp->getHops();
        case FIELD_xid: return (omnetpp::intval_t)(pp->getXid());
        case FIELD_secs: return pp->getSecs();
        case FIELD_broadcast: return pp->getBroadcast();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_ciaddr: return omnetpp::toAnyPtr(&pp->getCiaddr()); break;
        case FIELD_yiaddr: return omnetpp::toAnyPtr(&pp->getYiaddr()); break;
        case FIELD_giaddr: return omnetpp::toAnyPtr(&pp->getGiaddr()); break;
        case FIELD_chaddr: return omnetpp::toAnyPtr(&pp->getChaddr()); break;
        case FIELD_sname: return pp->getSname();
        case FIELD_file: return pp->getFile();
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DhcpMessage' as cValue -- field index out of range?", field);
    }
}

void DhcpMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_htype: pp->setHtype(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hlen: pp->setHlen(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hops: pp->setHops(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_xid: pp->setXid(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_secs: pp->setSecs(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_broadcast: pp->setBroadcast(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_sname: pp->setSname(value.stringValue()); break;
        case FIELD_file: pp->setFile(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpMessage'", field);
    }
}

const char *DhcpMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(DhcpOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr DhcpMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ciaddr: return omnetpp::toAnyPtr(&pp->getCiaddr()); break;
        case FIELD_yiaddr: return omnetpp::toAnyPtr(&pp->getYiaddr()); break;
        case FIELD_giaddr: return omnetpp::toAnyPtr(&pp->getGiaddr()); break;
        case FIELD_chaddr: return omnetpp::toAnyPtr(&pp->getChaddr()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DhcpMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DhcpMessage *pp = omnetpp::fromAnyPtr<DhcpMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DhcpMessage'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

