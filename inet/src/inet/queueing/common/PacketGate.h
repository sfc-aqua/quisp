//
// Copyright (C) OpenSim Ltd.
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
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#ifndef __INET_PACKETGATE_H
#define __INET_PACKETGATE_H

#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IPacketSink.h"
#include "inet/queueing/contract/IPacketSource.h"

namespace inet {
namespace queueing {

class INET_API PacketGate : public PacketProcessorBase, public IPacketSource, public IPacketSink
{
  protected:
    cGate *inputGate = nullptr;
    IActivePacketSource *producer = nullptr;
    IPassivePacketSource *provider = nullptr;

    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;
    IActivePacketSink *collector = nullptr;

    int changeIndex = 0;
    std::vector<simtime_t> changeTimes;
    bool isOpen_ = false;

    cMessage *changeTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void scheduleChangeTimer();
    virtual void processChangeTimer();

  public:
    virtual ~PacketGate() { cancelAndDelete(changeTimer); }

    virtual bool isOpen() const { return isOpen_; }
    virtual void open();
    virtual void close();

    virtual IPassivePacketSink *getConsumer(cGate *gate) override { return this; }
    virtual IPassivePacketSource *getProvider(cGate *gate) override { return this; }

    virtual bool supportsPushPacket(cGate *gate) const override { return true; }
    virtual bool canPushSomePacket(cGate *gate) const override;
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override;
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual bool supportsPopPacket(cGate *gate) const override { return true; }
    virtual bool canPopSomePacket(cGate *gate) const override;
    virtual Packet *canPopPacket(cGate *gate) const override;
    virtual Packet *popPacket(cGate *gate) override;

    virtual void handleCanPushPacket(cGate *gate) override;
    virtual void handleCanPopPacket(cGate *gate) override;
};

} // namespace queueing
} // namespace inet

#endif // ifndef __INET_PACKETGATE_H

