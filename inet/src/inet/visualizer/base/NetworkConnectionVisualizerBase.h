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
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_NETWORKCONNECTIONVISUALIZERBASE_H
#define __INET_NETWORKCONNECTIONVISUALIZERBASE_H

#include "inet/visualizer/base/VisualizerBase.h"
#include "inet/visualizer/util/NetworkNodeFilter.h"

namespace inet {

namespace visualizer {

class INET_API NetworkConnectionVisualizerBase : public VisualizerBase, public cListener
{
  protected:
    NetworkNodeFilter nodeFilter;
    cFigure::Color lineColor;
    cFigure::LineStyle lineStyle = cFigure::LINE_SOLID;
    double lineWidth = NaN;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleParameterChange(const char *name) override;

    virtual void createNetworkConnectionVisualization(cModule *startNetworkNode, cModule *endNetworkNode) = 0;
};

} // namespace visualizer

} // namespace inet

#endif // ifndef __INET_NETWORKCONNECTIONVISUALIZERBASE_H

