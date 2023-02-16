//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/TcpConnectionState.msg.
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
#include "TcpConnectionState_m.h"

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
namespace tcp {

class SackListDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SackListDescriptor();
    virtual ~SackListDescriptor();

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

Register_ClassDescriptor(SackListDescriptor)

SackListDescriptor::SackListDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::SackList)), "")
{
    propertyNames = nullptr;
}

SackListDescriptor::~SackListDescriptor()
{
    delete[] propertyNames;
}

bool SackListDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SackList *>(obj)!=nullptr;
}

const char **SackListDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SackListDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SackListDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SackListDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SackListDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SackListDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SackListDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SackListDescriptor::getFieldPropertyNames(int field) const
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

const char *SackListDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SackListDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SackListDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SackList'", field);
    }
}

const char *SackListDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SackListDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SackListDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackList'", field);
    }
}

omnetpp::cValue SackListDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SackList' as cValue -- field index out of range?", field);
    }
}

void SackListDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackList'", field);
    }
}

const char *SackListDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SackListDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SackListDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SackList *pp = omnetpp::fromAnyPtr<SackList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackList'", field);
    }
}

Register_Enum(inet::tcp::TcpState, (inet::tcp::TcpState::TCP_S_INIT, inet::tcp::TcpState::TCP_S_CLOSED, inet::tcp::TcpState::TCP_S_LISTEN, inet::tcp::TcpState::TCP_S_SYN_SENT, inet::tcp::TcpState::TCP_S_SYN_RCVD, inet::tcp::TcpState::TCP_S_ESTABLISHED, inet::tcp::TcpState::TCP_S_CLOSE_WAIT, inet::tcp::TcpState::TCP_S_LAST_ACK, inet::tcp::TcpState::TCP_S_FIN_WAIT_1, inet::tcp::TcpState::TCP_S_FIN_WAIT_2, inet::tcp::TcpState::TCP_S_CLOSING, inet::tcp::TcpState::TCP_S_TIME_WAIT));

Register_Enum(inet::tcp::TcpEventCode, (inet::tcp::TcpEventCode::TCP_E_IGNORE, inet::tcp::TcpEventCode::TCP_E_OPEN_ACTIVE, inet::tcp::TcpEventCode::TCP_E_OPEN_PASSIVE, inet::tcp::TcpEventCode::TCP_E_ACCEPT, inet::tcp::TcpEventCode::TCP_E_SEND, inet::tcp::TcpEventCode::TCP_E_CLOSE, inet::tcp::TcpEventCode::TCP_E_ABORT, inet::tcp::TcpEventCode::TCP_E_DESTROY, inet::tcp::TcpEventCode::TCP_E_STATUS, inet::tcp::TcpEventCode::TCP_E_QUEUE_BYTES_LIMIT, inet::tcp::TcpEventCode::TCP_E_READ, inet::tcp::TcpEventCode::TCP_E_SETOPTION, inet::tcp::TcpEventCode::TCP_E_RCV_DATA, inet::tcp::TcpEventCode::TCP_E_RCV_ACK, inet::tcp::TcpEventCode::TCP_E_RCV_SYN, inet::tcp::TcpEventCode::TCP_E_RCV_SYN_ACK, inet::tcp::TcpEventCode::TCP_E_RCV_FIN, inet::tcp::TcpEventCode::TCP_E_RCV_FIN_ACK, inet::tcp::TcpEventCode::TCP_E_RCV_RST, inet::tcp::TcpEventCode::TCP_E_RCV_UNEXP_SYN, inet::tcp::TcpEventCode::TCP_E_TIMEOUT_2MSL, inet::tcp::TcpEventCode::TCP_E_TIMEOUT_CONN_ESTAB, inet::tcp::TcpEventCode::TCP_E_TIMEOUT_FIN_WAIT_2));

TcpStateVariables::TcpStateVariables()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const TcpStateVariables& a)
{
    doParsimPacking(b,a.active);
    doParsimPacking(b,a.fork);
    doParsimPacking(b,a.snd_mss);
    doParsimPacking(b,a.snd_una);
    doParsimPacking(b,a.snd_nxt);
    doParsimPacking(b,a.snd_max);
    doParsimPacking(b,a.snd_wnd);
    doParsimPacking(b,a.snd_up);
    doParsimPacking(b,a.snd_wl1);
    doParsimPacking(b,a.snd_wl2);
    doParsimPacking(b,a.iss);
    doParsimPacking(b,a.rcv_nxt);
    doParsimPacking(b,a.rcv_wnd);
    doParsimPacking(b,a.rcv_up);
    doParsimPacking(b,a.irs);
    doParsimPacking(b,a.rcv_adv);
    doParsimPacking(b,a.syn_rexmit_count);
    doParsimPacking(b,a.syn_rexmit_timeout);
    doParsimPacking(b,a.fin_ack_rcvd);
    doParsimPacking(b,a.send_fin);
    doParsimPacking(b,a.snd_fin_seq);
    doParsimPacking(b,a.fin_rcvd);
    doParsimPacking(b,a.rcv_fin_seq);
    doParsimPacking(b,a.nagle_enabled);
    doParsimPacking(b,a.delayed_acks_enabled);
    doParsimPacking(b,a.limited_transmit_enabled);
    doParsimPacking(b,a.increased_IW_enabled);
    doParsimPacking(b,a.full_sized_segment_counter);
    doParsimPacking(b,a.ack_now);
    doParsimPacking(b,a.afterRto);
    doParsimPacking(b,a.ws_support);
    doParsimPacking(b,a.ws_enabled);
    doParsimPacking(b,a.ws_manual_scale);
    doParsimPacking(b,a.snd_ws);
    doParsimPacking(b,a.rcv_ws);
    doParsimPacking(b,a.rcv_wnd_scale);
    doParsimPacking(b,a.snd_wnd_scale);
    doParsimPacking(b,a.ts_support);
    doParsimPacking(b,a.ts_enabled);
    doParsimPacking(b,a.snd_initial_ts);
    doParsimPacking(b,a.rcv_initial_ts);
    doParsimPacking(b,a.ts_recent);
    doParsimPacking(b,a.last_ack_sent);
    doParsimPacking(b,a.time_last_data_sent);
    doParsimPacking(b,a.sack_support);
    doParsimPacking(b,a.sack_enabled);
    doParsimPacking(b,a.snd_sack_perm);
    doParsimPacking(b,a.rcv_sack_perm);
    doParsimPacking(b,a.start_seqno);
    doParsimPacking(b,a.end_seqno);
    doParsimPacking(b,a.snd_sack);
    doParsimPacking(b,a.snd_dsack);
    doParsimPacking(b,a.sacks_array);
    doParsimPacking(b,a.highRxt);
    doParsimPacking(b,a.pipe);
    doParsimPacking(b,a.recoveryPoint);
    doParsimPacking(b,a.sackedBytes);
    doParsimPacking(b,a.sackedBytes_old);
    doParsimPacking(b,a.lossRecovery);
    doParsimPacking(b,a.sendQueueLimit);
    doParsimPacking(b,a.queueUpdate);
    doParsimPacking(b,a.dupacks);
    doParsimPacking(b,a.snd_sacks);
    doParsimPacking(b,a.rcv_sacks);
    doParsimPacking(b,a.rcv_oooseg);
    doParsimPacking(b,a.rcv_naseg);
    doParsimPacking(b,a.maxRcvBuffer);
    doParsimPacking(b,a.usedRcvBuffer);
    doParsimPacking(b,a.freeRcvBuffer);
    doParsimPacking(b,a.tcpRcvQueueDrops);
    doParsimPacking(b,a.ecnEchoState);
    doParsimPacking(b,a.sndCwr);
    doParsimPacking(b,a.gotEce);
    doParsimPacking(b,a.gotCeIndication);
    doParsimPacking(b,a.ect);
    doParsimPacking(b,a.endPointIsWillingECN);
    doParsimPacking(b,a.ecnSynSent);
    doParsimPacking(b,a.ecnWillingness);
    doParsimPacking(b,a.sndAck);
    doParsimPacking(b,a.rexmit);
    doParsimPacking(b,a.eceReactionTime);
    doParsimPacking(b,a.dupthresh);
}

void __doUnpacking(omnetpp::cCommBuffer *b, TcpStateVariables& a)
{
    doParsimUnpacking(b,a.active);
    doParsimUnpacking(b,a.fork);
    doParsimUnpacking(b,a.snd_mss);
    doParsimUnpacking(b,a.snd_una);
    doParsimUnpacking(b,a.snd_nxt);
    doParsimUnpacking(b,a.snd_max);
    doParsimUnpacking(b,a.snd_wnd);
    doParsimUnpacking(b,a.snd_up);
    doParsimUnpacking(b,a.snd_wl1);
    doParsimUnpacking(b,a.snd_wl2);
    doParsimUnpacking(b,a.iss);
    doParsimUnpacking(b,a.rcv_nxt);
    doParsimUnpacking(b,a.rcv_wnd);
    doParsimUnpacking(b,a.rcv_up);
    doParsimUnpacking(b,a.irs);
    doParsimUnpacking(b,a.rcv_adv);
    doParsimUnpacking(b,a.syn_rexmit_count);
    doParsimUnpacking(b,a.syn_rexmit_timeout);
    doParsimUnpacking(b,a.fin_ack_rcvd);
    doParsimUnpacking(b,a.send_fin);
    doParsimUnpacking(b,a.snd_fin_seq);
    doParsimUnpacking(b,a.fin_rcvd);
    doParsimUnpacking(b,a.rcv_fin_seq);
    doParsimUnpacking(b,a.nagle_enabled);
    doParsimUnpacking(b,a.delayed_acks_enabled);
    doParsimUnpacking(b,a.limited_transmit_enabled);
    doParsimUnpacking(b,a.increased_IW_enabled);
    doParsimUnpacking(b,a.full_sized_segment_counter);
    doParsimUnpacking(b,a.ack_now);
    doParsimUnpacking(b,a.afterRto);
    doParsimUnpacking(b,a.ws_support);
    doParsimUnpacking(b,a.ws_enabled);
    doParsimUnpacking(b,a.ws_manual_scale);
    doParsimUnpacking(b,a.snd_ws);
    doParsimUnpacking(b,a.rcv_ws);
    doParsimUnpacking(b,a.rcv_wnd_scale);
    doParsimUnpacking(b,a.snd_wnd_scale);
    doParsimUnpacking(b,a.ts_support);
    doParsimUnpacking(b,a.ts_enabled);
    doParsimUnpacking(b,a.snd_initial_ts);
    doParsimUnpacking(b,a.rcv_initial_ts);
    doParsimUnpacking(b,a.ts_recent);
    doParsimUnpacking(b,a.last_ack_sent);
    doParsimUnpacking(b,a.time_last_data_sent);
    doParsimUnpacking(b,a.sack_support);
    doParsimUnpacking(b,a.sack_enabled);
    doParsimUnpacking(b,a.snd_sack_perm);
    doParsimUnpacking(b,a.rcv_sack_perm);
    doParsimUnpacking(b,a.start_seqno);
    doParsimUnpacking(b,a.end_seqno);
    doParsimUnpacking(b,a.snd_sack);
    doParsimUnpacking(b,a.snd_dsack);
    doParsimUnpacking(b,a.sacks_array);
    doParsimUnpacking(b,a.highRxt);
    doParsimUnpacking(b,a.pipe);
    doParsimUnpacking(b,a.recoveryPoint);
    doParsimUnpacking(b,a.sackedBytes);
    doParsimUnpacking(b,a.sackedBytes_old);
    doParsimUnpacking(b,a.lossRecovery);
    doParsimUnpacking(b,a.sendQueueLimit);
    doParsimUnpacking(b,a.queueUpdate);
    doParsimUnpacking(b,a.dupacks);
    doParsimUnpacking(b,a.snd_sacks);
    doParsimUnpacking(b,a.rcv_sacks);
    doParsimUnpacking(b,a.rcv_oooseg);
    doParsimUnpacking(b,a.rcv_naseg);
    doParsimUnpacking(b,a.maxRcvBuffer);
    doParsimUnpacking(b,a.usedRcvBuffer);
    doParsimUnpacking(b,a.freeRcvBuffer);
    doParsimUnpacking(b,a.tcpRcvQueueDrops);
    doParsimUnpacking(b,a.ecnEchoState);
    doParsimUnpacking(b,a.sndCwr);
    doParsimUnpacking(b,a.gotEce);
    doParsimUnpacking(b,a.gotCeIndication);
    doParsimUnpacking(b,a.ect);
    doParsimUnpacking(b,a.endPointIsWillingECN);
    doParsimUnpacking(b,a.ecnSynSent);
    doParsimUnpacking(b,a.ecnWillingness);
    doParsimUnpacking(b,a.sndAck);
    doParsimUnpacking(b,a.rexmit);
    doParsimUnpacking(b,a.eceReactionTime);
    doParsimUnpacking(b,a.dupthresh);
}

class TcpStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_active,
        FIELD_fork,
        FIELD_snd_mss,
        FIELD_snd_una,
        FIELD_snd_nxt,
        FIELD_snd_max,
        FIELD_snd_wnd,
        FIELD_snd_up,
        FIELD_snd_wl1,
        FIELD_snd_wl2,
        FIELD_iss,
        FIELD_rcv_nxt,
        FIELD_rcv_wnd,
        FIELD_rcv_up,
        FIELD_irs,
        FIELD_rcv_adv,
        FIELD_syn_rexmit_count,
        FIELD_syn_rexmit_timeout,
        FIELD_fin_ack_rcvd,
        FIELD_send_fin,
        FIELD_snd_fin_seq,
        FIELD_fin_rcvd,
        FIELD_rcv_fin_seq,
        FIELD_nagle_enabled,
        FIELD_delayed_acks_enabled,
        FIELD_limited_transmit_enabled,
        FIELD_increased_IW_enabled,
        FIELD_full_sized_segment_counter,
        FIELD_ack_now,
        FIELD_afterRto,
        FIELD_ws_support,
        FIELD_ws_enabled,
        FIELD_ws_manual_scale,
        FIELD_snd_ws,
        FIELD_rcv_ws,
        FIELD_rcv_wnd_scale,
        FIELD_snd_wnd_scale,
        FIELD_ts_support,
        FIELD_ts_enabled,
        FIELD_snd_initial_ts,
        FIELD_rcv_initial_ts,
        FIELD_ts_recent,
        FIELD_last_ack_sent,
        FIELD_time_last_data_sent,
        FIELD_sack_support,
        FIELD_sack_enabled,
        FIELD_snd_sack_perm,
        FIELD_rcv_sack_perm,
        FIELD_start_seqno,
        FIELD_end_seqno,
        FIELD_snd_sack,
        FIELD_snd_dsack,
        FIELD_sacks_array,
        FIELD_highRxt,
        FIELD_pipe,
        FIELD_recoveryPoint,
        FIELD_sackedBytes,
        FIELD_sackedBytes_old,
        FIELD_lossRecovery,
        FIELD_sendQueueLimit,
        FIELD_queueUpdate,
        FIELD_dupacks,
        FIELD_snd_sacks,
        FIELD_rcv_sacks,
        FIELD_rcv_oooseg,
        FIELD_rcv_naseg,
        FIELD_maxRcvBuffer,
        FIELD_usedRcvBuffer,
        FIELD_freeRcvBuffer,
        FIELD_tcpRcvQueueDrops,
        FIELD_ecnEchoState,
        FIELD_sndCwr,
        FIELD_gotEce,
        FIELD_gotCeIndication,
        FIELD_ect,
        FIELD_endPointIsWillingECN,
        FIELD_ecnSynSent,
        FIELD_ecnWillingness,
        FIELD_sndAck,
        FIELD_rexmit,
        FIELD_eceReactionTime,
        FIELD_dupthresh,
    };
  public:
    TcpStateVariablesDescriptor();
    virtual ~TcpStateVariablesDescriptor();

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

Register_ClassDescriptor(TcpStateVariablesDescriptor)

TcpStateVariablesDescriptor::TcpStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpStateVariables)), "")
{
    propertyNames = nullptr;
}

TcpStateVariablesDescriptor::~TcpStateVariablesDescriptor()
{
    delete[] propertyNames;
}

bool TcpStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpStateVariables *>(obj)!=nullptr;
}

const char **TcpStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "implements", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpStateVariablesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "implements")) return "cObject";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 82+base->getFieldCount() : 82;
}

unsigned int TcpStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_active
        0,    // FIELD_fork
        0,    // FIELD_snd_mss
        0,    // FIELD_snd_una
        0,    // FIELD_snd_nxt
        0,    // FIELD_snd_max
        0,    // FIELD_snd_wnd
        0,    // FIELD_snd_up
        0,    // FIELD_snd_wl1
        0,    // FIELD_snd_wl2
        0,    // FIELD_iss
        0,    // FIELD_rcv_nxt
        0,    // FIELD_rcv_wnd
        0,    // FIELD_rcv_up
        0,    // FIELD_irs
        0,    // FIELD_rcv_adv
        0,    // FIELD_syn_rexmit_count
        0,    // FIELD_syn_rexmit_timeout
        0,    // FIELD_fin_ack_rcvd
        0,    // FIELD_send_fin
        0,    // FIELD_snd_fin_seq
        0,    // FIELD_fin_rcvd
        0,    // FIELD_rcv_fin_seq
        0,    // FIELD_nagle_enabled
        0,    // FIELD_delayed_acks_enabled
        0,    // FIELD_limited_transmit_enabled
        0,    // FIELD_increased_IW_enabled
        0,    // FIELD_full_sized_segment_counter
        0,    // FIELD_ack_now
        0,    // FIELD_afterRto
        0,    // FIELD_ws_support
        0,    // FIELD_ws_enabled
        0,    // FIELD_ws_manual_scale
        0,    // FIELD_snd_ws
        0,    // FIELD_rcv_ws
        0,    // FIELD_rcv_wnd_scale
        0,    // FIELD_snd_wnd_scale
        0,    // FIELD_ts_support
        0,    // FIELD_ts_enabled
        0,    // FIELD_snd_initial_ts
        0,    // FIELD_rcv_initial_ts
        0,    // FIELD_ts_recent
        0,    // FIELD_last_ack_sent
        0,    // FIELD_time_last_data_sent
        0,    // FIELD_sack_support
        0,    // FIELD_sack_enabled
        0,    // FIELD_snd_sack_perm
        0,    // FIELD_rcv_sack_perm
        0,    // FIELD_start_seqno
        0,    // FIELD_end_seqno
        0,    // FIELD_snd_sack
        0,    // FIELD_snd_dsack
        FD_ISCOMPOUND,    // FIELD_sacks_array
        0,    // FIELD_highRxt
        0,    // FIELD_pipe
        0,    // FIELD_recoveryPoint
        0,    // FIELD_sackedBytes
        0,    // FIELD_sackedBytes_old
        0,    // FIELD_lossRecovery
        0,    // FIELD_sendQueueLimit
        0,    // FIELD_queueUpdate
        0,    // FIELD_dupacks
        0,    // FIELD_snd_sacks
        0,    // FIELD_rcv_sacks
        0,    // FIELD_rcv_oooseg
        0,    // FIELD_rcv_naseg
        0,    // FIELD_maxRcvBuffer
        0,    // FIELD_usedRcvBuffer
        0,    // FIELD_freeRcvBuffer
        0,    // FIELD_tcpRcvQueueDrops
        0,    // FIELD_ecnEchoState
        0,    // FIELD_sndCwr
        0,    // FIELD_gotEce
        0,    // FIELD_gotCeIndication
        0,    // FIELD_ect
        0,    // FIELD_endPointIsWillingECN
        0,    // FIELD_ecnSynSent
        0,    // FIELD_ecnWillingness
        0,    // FIELD_sndAck
        0,    // FIELD_rexmit
        0,    // FIELD_eceReactionTime
        0,    // FIELD_dupthresh
    };
    return (field >= 0 && field < 82) ? fieldTypeFlags[field] : 0;
}

const char *TcpStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "active",
        "fork",
        "snd_mss",
        "snd_una",
        "snd_nxt",
        "snd_max",
        "snd_wnd",
        "snd_up",
        "snd_wl1",
        "snd_wl2",
        "iss",
        "rcv_nxt",
        "rcv_wnd",
        "rcv_up",
        "irs",
        "rcv_adv",
        "syn_rexmit_count",
        "syn_rexmit_timeout",
        "fin_ack_rcvd",
        "send_fin",
        "snd_fin_seq",
        "fin_rcvd",
        "rcv_fin_seq",
        "nagle_enabled",
        "delayed_acks_enabled",
        "limited_transmit_enabled",
        "increased_IW_enabled",
        "full_sized_segment_counter",
        "ack_now",
        "afterRto",
        "ws_support",
        "ws_enabled",
        "ws_manual_scale",
        "snd_ws",
        "rcv_ws",
        "rcv_wnd_scale",
        "snd_wnd_scale",
        "ts_support",
        "ts_enabled",
        "snd_initial_ts",
        "rcv_initial_ts",
        "ts_recent",
        "last_ack_sent",
        "time_last_data_sent",
        "sack_support",
        "sack_enabled",
        "snd_sack_perm",
        "rcv_sack_perm",
        "start_seqno",
        "end_seqno",
        "snd_sack",
        "snd_dsack",
        "sacks_array",
        "highRxt",
        "pipe",
        "recoveryPoint",
        "sackedBytes",
        "sackedBytes_old",
        "lossRecovery",
        "sendQueueLimit",
        "queueUpdate",
        "dupacks",
        "snd_sacks",
        "rcv_sacks",
        "rcv_oooseg",
        "rcv_naseg",
        "maxRcvBuffer",
        "usedRcvBuffer",
        "freeRcvBuffer",
        "tcpRcvQueueDrops",
        "ecnEchoState",
        "sndCwr",
        "gotEce",
        "gotCeIndication",
        "ect",
        "endPointIsWillingECN",
        "ecnSynSent",
        "ecnWillingness",
        "sndAck",
        "rexmit",
        "eceReactionTime",
        "dupthresh",
    };
    return (field >= 0 && field < 82) ? fieldNames[field] : nullptr;
}

int TcpStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "active") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fork") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "snd_mss") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "snd_una") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "snd_nxt") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "snd_max") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "snd_wnd") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "snd_up") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "snd_wl1") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "snd_wl2") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "iss") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "rcv_nxt") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "rcv_wnd") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "rcv_up") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "irs") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "rcv_adv") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "syn_rexmit_count") == 0) return baseIndex + 16;
    if (strcmp(fieldName, "syn_rexmit_timeout") == 0) return baseIndex + 17;
    if (strcmp(fieldName, "fin_ack_rcvd") == 0) return baseIndex + 18;
    if (strcmp(fieldName, "send_fin") == 0) return baseIndex + 19;
    if (strcmp(fieldName, "snd_fin_seq") == 0) return baseIndex + 20;
    if (strcmp(fieldName, "fin_rcvd") == 0) return baseIndex + 21;
    if (strcmp(fieldName, "rcv_fin_seq") == 0) return baseIndex + 22;
    if (strcmp(fieldName, "nagle_enabled") == 0) return baseIndex + 23;
    if (strcmp(fieldName, "delayed_acks_enabled") == 0) return baseIndex + 24;
    if (strcmp(fieldName, "limited_transmit_enabled") == 0) return baseIndex + 25;
    if (strcmp(fieldName, "increased_IW_enabled") == 0) return baseIndex + 26;
    if (strcmp(fieldName, "full_sized_segment_counter") == 0) return baseIndex + 27;
    if (strcmp(fieldName, "ack_now") == 0) return baseIndex + 28;
    if (strcmp(fieldName, "afterRto") == 0) return baseIndex + 29;
    if (strcmp(fieldName, "ws_support") == 0) return baseIndex + 30;
    if (strcmp(fieldName, "ws_enabled") == 0) return baseIndex + 31;
    if (strcmp(fieldName, "ws_manual_scale") == 0) return baseIndex + 32;
    if (strcmp(fieldName, "snd_ws") == 0) return baseIndex + 33;
    if (strcmp(fieldName, "rcv_ws") == 0) return baseIndex + 34;
    if (strcmp(fieldName, "rcv_wnd_scale") == 0) return baseIndex + 35;
    if (strcmp(fieldName, "snd_wnd_scale") == 0) return baseIndex + 36;
    if (strcmp(fieldName, "ts_support") == 0) return baseIndex + 37;
    if (strcmp(fieldName, "ts_enabled") == 0) return baseIndex + 38;
    if (strcmp(fieldName, "snd_initial_ts") == 0) return baseIndex + 39;
    if (strcmp(fieldName, "rcv_initial_ts") == 0) return baseIndex + 40;
    if (strcmp(fieldName, "ts_recent") == 0) return baseIndex + 41;
    if (strcmp(fieldName, "last_ack_sent") == 0) return baseIndex + 42;
    if (strcmp(fieldName, "time_last_data_sent") == 0) return baseIndex + 43;
    if (strcmp(fieldName, "sack_support") == 0) return baseIndex + 44;
    if (strcmp(fieldName, "sack_enabled") == 0) return baseIndex + 45;
    if (strcmp(fieldName, "snd_sack_perm") == 0) return baseIndex + 46;
    if (strcmp(fieldName, "rcv_sack_perm") == 0) return baseIndex + 47;
    if (strcmp(fieldName, "start_seqno") == 0) return baseIndex + 48;
    if (strcmp(fieldName, "end_seqno") == 0) return baseIndex + 49;
    if (strcmp(fieldName, "snd_sack") == 0) return baseIndex + 50;
    if (strcmp(fieldName, "snd_dsack") == 0) return baseIndex + 51;
    if (strcmp(fieldName, "sacks_array") == 0) return baseIndex + 52;
    if (strcmp(fieldName, "highRxt") == 0) return baseIndex + 53;
    if (strcmp(fieldName, "pipe") == 0) return baseIndex + 54;
    if (strcmp(fieldName, "recoveryPoint") == 0) return baseIndex + 55;
    if (strcmp(fieldName, "sackedBytes") == 0) return baseIndex + 56;
    if (strcmp(fieldName, "sackedBytes_old") == 0) return baseIndex + 57;
    if (strcmp(fieldName, "lossRecovery") == 0) return baseIndex + 58;
    if (strcmp(fieldName, "sendQueueLimit") == 0) return baseIndex + 59;
    if (strcmp(fieldName, "queueUpdate") == 0) return baseIndex + 60;
    if (strcmp(fieldName, "dupacks") == 0) return baseIndex + 61;
    if (strcmp(fieldName, "snd_sacks") == 0) return baseIndex + 62;
    if (strcmp(fieldName, "rcv_sacks") == 0) return baseIndex + 63;
    if (strcmp(fieldName, "rcv_oooseg") == 0) return baseIndex + 64;
    if (strcmp(fieldName, "rcv_naseg") == 0) return baseIndex + 65;
    if (strcmp(fieldName, "maxRcvBuffer") == 0) return baseIndex + 66;
    if (strcmp(fieldName, "usedRcvBuffer") == 0) return baseIndex + 67;
    if (strcmp(fieldName, "freeRcvBuffer") == 0) return baseIndex + 68;
    if (strcmp(fieldName, "tcpRcvQueueDrops") == 0) return baseIndex + 69;
    if (strcmp(fieldName, "ecnEchoState") == 0) return baseIndex + 70;
    if (strcmp(fieldName, "sndCwr") == 0) return baseIndex + 71;
    if (strcmp(fieldName, "gotEce") == 0) return baseIndex + 72;
    if (strcmp(fieldName, "gotCeIndication") == 0) return baseIndex + 73;
    if (strcmp(fieldName, "ect") == 0) return baseIndex + 74;
    if (strcmp(fieldName, "endPointIsWillingECN") == 0) return baseIndex + 75;
    if (strcmp(fieldName, "ecnSynSent") == 0) return baseIndex + 76;
    if (strcmp(fieldName, "ecnWillingness") == 0) return baseIndex + 77;
    if (strcmp(fieldName, "sndAck") == 0) return baseIndex + 78;
    if (strcmp(fieldName, "rexmit") == 0) return baseIndex + 79;
    if (strcmp(fieldName, "eceReactionTime") == 0) return baseIndex + 80;
    if (strcmp(fieldName, "dupthresh") == 0) return baseIndex + 81;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_active
        "bool",    // FIELD_fork
        "uint32_t",    // FIELD_snd_mss
        "uint32_t",    // FIELD_snd_una
        "uint32_t",    // FIELD_snd_nxt
        "uint32_t",    // FIELD_snd_max
        "uint32_t",    // FIELD_snd_wnd
        "uint32_t",    // FIELD_snd_up
        "uint32_t",    // FIELD_snd_wl1
        "uint32_t",    // FIELD_snd_wl2
        "uint32_t",    // FIELD_iss
        "uint32_t",    // FIELD_rcv_nxt
        "uint32_t",    // FIELD_rcv_wnd
        "uint32_t",    // FIELD_rcv_up
        "uint32_t",    // FIELD_irs
        "uint32_t",    // FIELD_rcv_adv
        "int",    // FIELD_syn_rexmit_count
        "omnetpp::simtime_t",    // FIELD_syn_rexmit_timeout
        "bool",    // FIELD_fin_ack_rcvd
        "bool",    // FIELD_send_fin
        "uint32_t",    // FIELD_snd_fin_seq
        "bool",    // FIELD_fin_rcvd
        "uint32_t",    // FIELD_rcv_fin_seq
        "bool",    // FIELD_nagle_enabled
        "bool",    // FIELD_delayed_acks_enabled
        "bool",    // FIELD_limited_transmit_enabled
        "bool",    // FIELD_increased_IW_enabled
        "uint32_t",    // FIELD_full_sized_segment_counter
        "bool",    // FIELD_ack_now
        "bool",    // FIELD_afterRto
        "bool",    // FIELD_ws_support
        "bool",    // FIELD_ws_enabled
        "int",    // FIELD_ws_manual_scale
        "bool",    // FIELD_snd_ws
        "bool",    // FIELD_rcv_ws
        "unsigned int",    // FIELD_rcv_wnd_scale
        "unsigned int",    // FIELD_snd_wnd_scale
        "bool",    // FIELD_ts_support
        "bool",    // FIELD_ts_enabled
        "bool",    // FIELD_snd_initial_ts
        "bool",    // FIELD_rcv_initial_ts
        "uint32_t",    // FIELD_ts_recent
        "uint32_t",    // FIELD_last_ack_sent
        "omnetpp::simtime_t",    // FIELD_time_last_data_sent
        "bool",    // FIELD_sack_support
        "bool",    // FIELD_sack_enabled
        "bool",    // FIELD_snd_sack_perm
        "bool",    // FIELD_rcv_sack_perm
        "uint32_t",    // FIELD_start_seqno
        "uint32_t",    // FIELD_end_seqno
        "bool",    // FIELD_snd_sack
        "bool",    // FIELD_snd_dsack
        "inet::tcp::SackList",    // FIELD_sacks_array
        "uint32_t",    // FIELD_highRxt
        "uint32_t",    // FIELD_pipe
        "uint32_t",    // FIELD_recoveryPoint
        "uint32_t",    // FIELD_sackedBytes
        "uint32_t",    // FIELD_sackedBytes_old
        "bool",    // FIELD_lossRecovery
        "uint32_t",    // FIELD_sendQueueLimit
        "bool",    // FIELD_queueUpdate
        "uint32_t",    // FIELD_dupacks
        "uint32_t",    // FIELD_snd_sacks
        "uint32_t",    // FIELD_rcv_sacks
        "uint32_t",    // FIELD_rcv_oooseg
        "uint32_t",    // FIELD_rcv_naseg
        "uint32_t",    // FIELD_maxRcvBuffer
        "uint32_t",    // FIELD_usedRcvBuffer
        "uint32_t",    // FIELD_freeRcvBuffer
        "uint32_t",    // FIELD_tcpRcvQueueDrops
        "bool",    // FIELD_ecnEchoState
        "bool",    // FIELD_sndCwr
        "bool",    // FIELD_gotEce
        "bool",    // FIELD_gotCeIndication
        "bool",    // FIELD_ect
        "bool",    // FIELD_endPointIsWillingECN
        "bool",    // FIELD_ecnSynSent
        "bool",    // FIELD_ecnWillingness
        "bool",    // FIELD_sndAck
        "bool",    // FIELD_rexmit
        "omnetpp::simtime_t",    // FIELD_eceReactionTime
        "uint32_t",    // FIELD_dupthresh
    };
    return (field >= 0 && field < 82) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpStateVariablesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpStateVariablesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpStateVariablesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpStateVariables'", field);
    }
}

const char *TcpStateVariablesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpStateVariablesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_active: return bool2string(pp->active);
        case FIELD_fork: return bool2string(pp->fork);
        case FIELD_snd_mss: return ulong2string(pp->snd_mss);
        case FIELD_snd_una: return ulong2string(pp->snd_una);
        case FIELD_snd_nxt: return ulong2string(pp->snd_nxt);
        case FIELD_snd_max: return ulong2string(pp->snd_max);
        case FIELD_snd_wnd: return ulong2string(pp->snd_wnd);
        case FIELD_snd_up: return ulong2string(pp->snd_up);
        case FIELD_snd_wl1: return ulong2string(pp->snd_wl1);
        case FIELD_snd_wl2: return ulong2string(pp->snd_wl2);
        case FIELD_iss: return ulong2string(pp->iss);
        case FIELD_rcv_nxt: return ulong2string(pp->rcv_nxt);
        case FIELD_rcv_wnd: return ulong2string(pp->rcv_wnd);
        case FIELD_rcv_up: return ulong2string(pp->rcv_up);
        case FIELD_irs: return ulong2string(pp->irs);
        case FIELD_rcv_adv: return ulong2string(pp->rcv_adv);
        case FIELD_syn_rexmit_count: return long2string(pp->syn_rexmit_count);
        case FIELD_syn_rexmit_timeout: return simtime2string(pp->syn_rexmit_timeout);
        case FIELD_fin_ack_rcvd: return bool2string(pp->fin_ack_rcvd);
        case FIELD_send_fin: return bool2string(pp->send_fin);
        case FIELD_snd_fin_seq: return ulong2string(pp->snd_fin_seq);
        case FIELD_fin_rcvd: return bool2string(pp->fin_rcvd);
        case FIELD_rcv_fin_seq: return ulong2string(pp->rcv_fin_seq);
        case FIELD_nagle_enabled: return bool2string(pp->nagle_enabled);
        case FIELD_delayed_acks_enabled: return bool2string(pp->delayed_acks_enabled);
        case FIELD_limited_transmit_enabled: return bool2string(pp->limited_transmit_enabled);
        case FIELD_increased_IW_enabled: return bool2string(pp->increased_IW_enabled);
        case FIELD_full_sized_segment_counter: return ulong2string(pp->full_sized_segment_counter);
        case FIELD_ack_now: return bool2string(pp->ack_now);
        case FIELD_afterRto: return bool2string(pp->afterRto);
        case FIELD_ws_support: return bool2string(pp->ws_support);
        case FIELD_ws_enabled: return bool2string(pp->ws_enabled);
        case FIELD_ws_manual_scale: return long2string(pp->ws_manual_scale);
        case FIELD_snd_ws: return bool2string(pp->snd_ws);
        case FIELD_rcv_ws: return bool2string(pp->rcv_ws);
        case FIELD_rcv_wnd_scale: return ulong2string(pp->rcv_wnd_scale);
        case FIELD_snd_wnd_scale: return ulong2string(pp->snd_wnd_scale);
        case FIELD_ts_support: return bool2string(pp->ts_support);
        case FIELD_ts_enabled: return bool2string(pp->ts_enabled);
        case FIELD_snd_initial_ts: return bool2string(pp->snd_initial_ts);
        case FIELD_rcv_initial_ts: return bool2string(pp->rcv_initial_ts);
        case FIELD_ts_recent: return ulong2string(pp->ts_recent);
        case FIELD_last_ack_sent: return ulong2string(pp->last_ack_sent);
        case FIELD_time_last_data_sent: return simtime2string(pp->time_last_data_sent);
        case FIELD_sack_support: return bool2string(pp->sack_support);
        case FIELD_sack_enabled: return bool2string(pp->sack_enabled);
        case FIELD_snd_sack_perm: return bool2string(pp->snd_sack_perm);
        case FIELD_rcv_sack_perm: return bool2string(pp->rcv_sack_perm);
        case FIELD_start_seqno: return ulong2string(pp->start_seqno);
        case FIELD_end_seqno: return ulong2string(pp->end_seqno);
        case FIELD_snd_sack: return bool2string(pp->snd_sack);
        case FIELD_snd_dsack: return bool2string(pp->snd_dsack);
        case FIELD_sacks_array: return "";
        case FIELD_highRxt: return ulong2string(pp->highRxt);
        case FIELD_pipe: return ulong2string(pp->pipe);
        case FIELD_recoveryPoint: return ulong2string(pp->recoveryPoint);
        case FIELD_sackedBytes: return ulong2string(pp->sackedBytes);
        case FIELD_sackedBytes_old: return ulong2string(pp->sackedBytes_old);
        case FIELD_lossRecovery: return bool2string(pp->lossRecovery);
        case FIELD_sendQueueLimit: return ulong2string(pp->sendQueueLimit);
        case FIELD_queueUpdate: return bool2string(pp->queueUpdate);
        case FIELD_dupacks: return ulong2string(pp->dupacks);
        case FIELD_snd_sacks: return ulong2string(pp->snd_sacks);
        case FIELD_rcv_sacks: return ulong2string(pp->rcv_sacks);
        case FIELD_rcv_oooseg: return ulong2string(pp->rcv_oooseg);
        case FIELD_rcv_naseg: return ulong2string(pp->rcv_naseg);
        case FIELD_maxRcvBuffer: return ulong2string(pp->maxRcvBuffer);
        case FIELD_usedRcvBuffer: return ulong2string(pp->usedRcvBuffer);
        case FIELD_freeRcvBuffer: return ulong2string(pp->freeRcvBuffer);
        case FIELD_tcpRcvQueueDrops: return ulong2string(pp->tcpRcvQueueDrops);
        case FIELD_ecnEchoState: return bool2string(pp->ecnEchoState);
        case FIELD_sndCwr: return bool2string(pp->sndCwr);
        case FIELD_gotEce: return bool2string(pp->gotEce);
        case FIELD_gotCeIndication: return bool2string(pp->gotCeIndication);
        case FIELD_ect: return bool2string(pp->ect);
        case FIELD_endPointIsWillingECN: return bool2string(pp->endPointIsWillingECN);
        case FIELD_ecnSynSent: return bool2string(pp->ecnSynSent);
        case FIELD_ecnWillingness: return bool2string(pp->ecnWillingness);
        case FIELD_sndAck: return bool2string(pp->sndAck);
        case FIELD_rexmit: return bool2string(pp->rexmit);
        case FIELD_eceReactionTime: return simtime2string(pp->eceReactionTime);
        case FIELD_dupthresh: return ulong2string(pp->dupthresh);
        default: return "";
    }
}

void TcpStateVariablesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

omnetpp::cValue TcpStateVariablesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_active: return pp->active;
        case FIELD_fork: return pp->fork;
        case FIELD_snd_mss: return (omnetpp::intval_t)(pp->snd_mss);
        case FIELD_snd_una: return (omnetpp::intval_t)(pp->snd_una);
        case FIELD_snd_nxt: return (omnetpp::intval_t)(pp->snd_nxt);
        case FIELD_snd_max: return (omnetpp::intval_t)(pp->snd_max);
        case FIELD_snd_wnd: return (omnetpp::intval_t)(pp->snd_wnd);
        case FIELD_snd_up: return (omnetpp::intval_t)(pp->snd_up);
        case FIELD_snd_wl1: return (omnetpp::intval_t)(pp->snd_wl1);
        case FIELD_snd_wl2: return (omnetpp::intval_t)(pp->snd_wl2);
        case FIELD_iss: return (omnetpp::intval_t)(pp->iss);
        case FIELD_rcv_nxt: return (omnetpp::intval_t)(pp->rcv_nxt);
        case FIELD_rcv_wnd: return (omnetpp::intval_t)(pp->rcv_wnd);
        case FIELD_rcv_up: return (omnetpp::intval_t)(pp->rcv_up);
        case FIELD_irs: return (omnetpp::intval_t)(pp->irs);
        case FIELD_rcv_adv: return (omnetpp::intval_t)(pp->rcv_adv);
        case FIELD_syn_rexmit_count: return pp->syn_rexmit_count;
        case FIELD_syn_rexmit_timeout: return pp->syn_rexmit_timeout.dbl();
        case FIELD_fin_ack_rcvd: return pp->fin_ack_rcvd;
        case FIELD_send_fin: return pp->send_fin;
        case FIELD_snd_fin_seq: return (omnetpp::intval_t)(pp->snd_fin_seq);
        case FIELD_fin_rcvd: return pp->fin_rcvd;
        case FIELD_rcv_fin_seq: return (omnetpp::intval_t)(pp->rcv_fin_seq);
        case FIELD_nagle_enabled: return pp->nagle_enabled;
        case FIELD_delayed_acks_enabled: return pp->delayed_acks_enabled;
        case FIELD_limited_transmit_enabled: return pp->limited_transmit_enabled;
        case FIELD_increased_IW_enabled: return pp->increased_IW_enabled;
        case FIELD_full_sized_segment_counter: return (omnetpp::intval_t)(pp->full_sized_segment_counter);
        case FIELD_ack_now: return pp->ack_now;
        case FIELD_afterRto: return pp->afterRto;
        case FIELD_ws_support: return pp->ws_support;
        case FIELD_ws_enabled: return pp->ws_enabled;
        case FIELD_ws_manual_scale: return pp->ws_manual_scale;
        case FIELD_snd_ws: return pp->snd_ws;
        case FIELD_rcv_ws: return pp->rcv_ws;
        case FIELD_rcv_wnd_scale: return (omnetpp::intval_t)(pp->rcv_wnd_scale);
        case FIELD_snd_wnd_scale: return (omnetpp::intval_t)(pp->snd_wnd_scale);
        case FIELD_ts_support: return pp->ts_support;
        case FIELD_ts_enabled: return pp->ts_enabled;
        case FIELD_snd_initial_ts: return pp->snd_initial_ts;
        case FIELD_rcv_initial_ts: return pp->rcv_initial_ts;
        case FIELD_ts_recent: return (omnetpp::intval_t)(pp->ts_recent);
        case FIELD_last_ack_sent: return (omnetpp::intval_t)(pp->last_ack_sent);
        case FIELD_time_last_data_sent: return pp->time_last_data_sent.dbl();
        case FIELD_sack_support: return pp->sack_support;
        case FIELD_sack_enabled: return pp->sack_enabled;
        case FIELD_snd_sack_perm: return pp->snd_sack_perm;
        case FIELD_rcv_sack_perm: return pp->rcv_sack_perm;
        case FIELD_start_seqno: return (omnetpp::intval_t)(pp->start_seqno);
        case FIELD_end_seqno: return (omnetpp::intval_t)(pp->end_seqno);
        case FIELD_snd_sack: return pp->snd_sack;
        case FIELD_snd_dsack: return pp->snd_dsack;
        case FIELD_sacks_array: return omnetpp::toAnyPtr(&pp->sacks_array); break;
        case FIELD_highRxt: return (omnetpp::intval_t)(pp->highRxt);
        case FIELD_pipe: return (omnetpp::intval_t)(pp->pipe);
        case FIELD_recoveryPoint: return (omnetpp::intval_t)(pp->recoveryPoint);
        case FIELD_sackedBytes: return (omnetpp::intval_t)(pp->sackedBytes);
        case FIELD_sackedBytes_old: return (omnetpp::intval_t)(pp->sackedBytes_old);
        case FIELD_lossRecovery: return pp->lossRecovery;
        case FIELD_sendQueueLimit: return (omnetpp::intval_t)(pp->sendQueueLimit);
        case FIELD_queueUpdate: return pp->queueUpdate;
        case FIELD_dupacks: return (omnetpp::intval_t)(pp->dupacks);
        case FIELD_snd_sacks: return (omnetpp::intval_t)(pp->snd_sacks);
        case FIELD_rcv_sacks: return (omnetpp::intval_t)(pp->rcv_sacks);
        case FIELD_rcv_oooseg: return (omnetpp::intval_t)(pp->rcv_oooseg);
        case FIELD_rcv_naseg: return (omnetpp::intval_t)(pp->rcv_naseg);
        case FIELD_maxRcvBuffer: return (omnetpp::intval_t)(pp->maxRcvBuffer);
        case FIELD_usedRcvBuffer: return (omnetpp::intval_t)(pp->usedRcvBuffer);
        case FIELD_freeRcvBuffer: return (omnetpp::intval_t)(pp->freeRcvBuffer);
        case FIELD_tcpRcvQueueDrops: return (omnetpp::intval_t)(pp->tcpRcvQueueDrops);
        case FIELD_ecnEchoState: return pp->ecnEchoState;
        case FIELD_sndCwr: return pp->sndCwr;
        case FIELD_gotEce: return pp->gotEce;
        case FIELD_gotCeIndication: return pp->gotCeIndication;
        case FIELD_ect: return pp->ect;
        case FIELD_endPointIsWillingECN: return pp->endPointIsWillingECN;
        case FIELD_ecnSynSent: return pp->ecnSynSent;
        case FIELD_ecnWillingness: return pp->ecnWillingness;
        case FIELD_sndAck: return pp->sndAck;
        case FIELD_rexmit: return pp->rexmit;
        case FIELD_eceReactionTime: return pp->eceReactionTime.dbl();
        case FIELD_dupthresh: return (omnetpp::intval_t)(pp->dupthresh);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpStateVariables' as cValue -- field index out of range?", field);
    }
}

void TcpStateVariablesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

const char *TcpStateVariablesDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sacks_array: return omnetpp::opp_typename(typeid(SackList));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpStateVariablesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_sacks_array: return omnetpp::toAnyPtr(&pp->sacks_array); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpStateVariablesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

template<> inet::tcp::TcpStateVariables *fromAnyPtr(any_ptr ptr) {
    if (ptr.contains<inet::tcp::TcpStateVariables>()) return static_cast<inet::tcp::TcpStateVariables*>(ptr.get<inet::tcp::TcpStateVariables>());
    if (ptr.contains<omnetpp::cObject>()) return static_cast<inet::tcp::TcpStateVariables*>(ptr.get<omnetpp::cObject>());
    throw cRuntimeError("Unable to obtain inet::tcp::TcpStateVariables* pointer from any_ptr(%s)", ptr.pointerTypeName());
}
}  // namespace omnetpp

