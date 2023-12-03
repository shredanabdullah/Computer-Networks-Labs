//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    EV<<"starting Node "<<this->getIndex()<<endl;
    // TODO - Generated method body
    if(this->getIndex()==0)
    {
        cMessage * msg=new cMessage("start");
        msg->setKind(1);
        cGate *myPort = gate("port$o", 0);
        send(msg,myPort);
    }

}

void Node::handleMessage(cMessage *msg)
{

    if(this->getIndex()==0)
    {
        EV<<"the Nodes in the network is "<<msg->getKind()<<endl;
        cancelAndDelete(msg);
    }
    else{
        msg->setKind(msg->getKind()+1);
        cGate *myPort = gate("port$o", 1);
        send(msg,myPort);
    }
    // TODO - Generated method body
}
