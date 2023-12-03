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

#include "receiver.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
}

void Receiver::handleMessage(cMessage *msg)
{
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    std::string msgStr = mmsg->getPayload();
    int msgSize = msgStr.length();

    // check if errors occurred or not
    bits countBits (mmsg->getM_header());
    std::bitset<8> parity(countBits);
    for(int i = 0; i< msgSize;i++)
    {
        bits payloadBits (msgStr[i]);
        parity = parity ^ payloadBits;
    }
    parity = parity ^ bits(mmsg->getM_Trailer());
    if (parity.to_ulong() == 0)
    {
        // error free
        EV << "message received: "<<msgStr <<endl;
        std::cout << "message received: "<<msgStr<<endl;
        mmsg->setM_Type(1);
    }
    else
    {
        // error occurred
        EV << "Error occurred" <<endl;
        std::cout << "Error occurred" <<endl;
        mmsg->setM_Type(0);
    }
    // send withou delay from receiver as it was not mentioned to add delay from receiver
    send(mmsg,"out");

}
