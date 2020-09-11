/** \file ResourceManager.cc
 *  \authors cldurand
 *  \date 2018/05/25
 *
 *  \brief ResourceManager
 */
#include <modules/ResourceManager.h>

namespace quisp {
namespace modules {

Define_Module(ResourceManager);

void ResourceManager::initialize() { EV << "ResourceManager booted\n"; }

void ResourceManager::handleMessage(cMessage *msg) {}

}  // namespace modules
}  // namespace quisp
