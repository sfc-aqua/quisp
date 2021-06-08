//
// Copyright (C) 2012 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_DSCPMARKER_H
#define __INET_DSCPMARKER_H

#include "inet/common/INETDefs.h"
#include "inet/queueing/base/PacketQueueingElementBase.h"
#include "inet/queueing/contract/IPassivePacketSink.h"
#include "inet/queueing/contract/IActivePacketSource.h"
#include "inet/common/packet/Packet.h"

namespace inet {

/**
 * DSCP Marker.
 */
class INET_API DscpMarker : public queueing::PacketQueueingElementBase, public queueing::IPassivePacketSink, public queueing::IActivePacketSource
{
  protected:
    std::vector<int> dscps;

    int numRcvd = 0;
    int numMarked = 0;

    static simsignal_t packetMarkedSignal;

  public:
    DscpMarker() {}

    virtual bool supportsPushPacket(cGate *gate) const override { return true; }
    virtual bool supportsPopPacket(cGate *gate) const override { return false; }

    virtual queueing::IPassivePacketSink *getConsumer(cGate *gate) override { return this; }
    virtual void handleCanPushPacket(cGate *gate) override { }

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    virtual void refreshDisplay() const override;

    virtual bool canPushSomePacket(cGate *gate = nullptr) const override { return true; }
    virtual bool canPushPacket(Packet *packet, cGate *gate = nullptr) const override { return true; }
    virtual void pushPacket(Packet *packet, cGate *gate = nullptr) override;

    virtual bool markPacket(Packet *msg, int dscp);
};

} // namespace inet

#endif // ifndef __INET_DSCPMARKER_H

