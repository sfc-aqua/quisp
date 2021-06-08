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

#ifndef __INET_PACKETMULTIPLEXER_H
#define __INET_PACKETMULTIPLEXER_H

#include "inet/queueing/base/PassivePacketSinkBase.h"
#include "inet/queueing/contract/IActivePacketSource.h"

namespace inet {
namespace queueing {

class INET_API PacketMultiplexer : public PassivePacketSinkBase, public IActivePacketSource
{
  protected:
    std::vector<cGate *> inputGates;
    std::vector<IActivePacketSource *> producers;

    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;

  protected:
    virtual void initialize(int stage) override;

  public:
    virtual IPassivePacketSink *getConsumer(cGate *gate) override { return consumer; }

    virtual bool supportsPopPacket(cGate *gate) const override { return false; }
    virtual bool supportsPushPacket(cGate *gate) const override { return true; }

    virtual bool canPushSomePacket(cGate *gate) const override { return consumer->canPushSomePacket(outputGate); }
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override { return consumer->canPushPacket(packet, gate); }
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void handleCanPushPacket(cGate *gate) override;
};

} // namespace queueing
} // namespace inet

#endif // ifndef __INET_PACKETMULTIPLEXER_H

