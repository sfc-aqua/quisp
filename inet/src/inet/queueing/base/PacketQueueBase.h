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

#ifndef __INET_PACKETQUEUEBASE_H
#define __INET_PACKETQUEUEBASE_H

#include "inet/queueing/base/PacketQueueingElementBase.h"
#include "inet/queueing/contract/IPacketQueue.h"

namespace inet {
namespace queueing {

class INET_API PacketQueueBase : public PacketQueueingElementBase, public IPacketQueue
{
  protected:
    const char *displayStringTextFormat = nullptr;
    int numPushedPackets = -1;
    int numPoppedPackets = -1;
    int numRemovedPackets = -1;
    int numDroppedPackets = -1;
    int numCreatedPackets = -1;

  protected:
    virtual void initialize(int stage) override;
    virtual void emit(simsignal_t signal, cObject *object, cObject *details = nullptr) override;

    virtual void updateDisplayString();

  public:
    virtual bool canPopSomePacket(cGate *gate) const override { return getNumPackets() > 0; }
    virtual bool canPushSomePacket(cGate *gate) const override { return true; }
};

} // namespace queueing
} // namespace inet

#endif // ifndef __INET_PACKETQUEUEBASE_H

