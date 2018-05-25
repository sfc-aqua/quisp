/** \file ResourceManager.h
 *  \authors cldurand
 *  \date 2018/05/25
 *
 *  \brief ResourceManager
 */

#ifndef MODULES_RESOURCEMANAGER_H_
#define MODULES_RESOURCEMANAGER_H_
#include <omnetpp.h>
#include "../classical_messages_m.h"
using namespace omnetpp;

/** \class ResourceManager ResourceManager.h
 *  \todo Documentation of the class header.
 *
 *  \brief ResourceManager
 */
class ResourceManager : public cSimpleModule
{
    private:
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
    public:
};

#endif /* MODULES_RESOURCEMANAGER_H_ */
