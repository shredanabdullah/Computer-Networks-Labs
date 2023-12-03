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

#include "sender.h"

Define_Module(Sender);


void Sender::ErrorNPrint(MyMessage_Base* msg)
{
    // TODO - Generated method body

       std::cout<< "Enter your message: "<<endl;

         // Read the input from the user
         std::string inputString;
         std::cin >> inputString;

         std::string parity;
         std::string one_character;
         std::string reversedString;
         std::string bitstream;


         EV << "You entered: " << inputString << std::endl;

         int charCount = inputString.length() + 2;

             std::string character_count_string = std::bitset<8>(charCount).to_string();
             bitstream+=character_count_string;

                     for(int i=0;i<8;i++)
                     {
                         int columnParity = bitstream[character_count_string.length() - 1 - i] - '0';

                                  for (int j = 0; j < inputString.length(); j++) {
                                      if(i==0)
                                      {

                                      bitstream += std::bitset<8>((int)inputString[j]).to_string();

                                      }

                                      one_character= std::bitset<8>((int)inputString[j]).to_string();

                                      columnParity^=(one_character[one_character.length() - 1 - i] - '0');

                                  }
                                  parity += (columnParity == 0) ? '0' : '1';
                              }
                     // Loop through the inputString in reverse and append characters to reversedString
                     for (int i = parity.length() - 1; i >= 0; i--) {
                         reversedString += parity[i];
                     }
                     parity = reversedString;

                  bitstream += std::bitset<8>(parity).to_string();
                  //EV << "original bit stream:\n";
                    for (int i = 0; i < bitstream.length(); i += 8) {
                        std::bitset<8> charBits(bitstream.substr(i, 8));
                        EV << charBits << "\n";
                    }
                // Introduce a 50% chance of a single bit error
                if ((this->par("run").intValue())%2==0) {
                    int errorBitIndex = intuniform(0, bitstream.length() - 1);
                    bitstream[errorBitIndex] = (bitstream[errorBitIndex] == '0') ? '1' : '0';
                   // EV << "Bit " << errorBitIndex << " was modified\n";
                    // Print the bit stream with each element on a separate row
                    //EV << "bit stream in case of error:\n";
                      for (int i = 0; i < bitstream.length(); i += 8) {
                          std::bitset<8> charBits(bitstream.substr(i, 8));
                          EV << charBits << "\n";
                      }
                }
                // Convert the bit stream back to a C-string
                   std::string stringSend;
                   for (int i = 0; i < bitstream.length(); i += 8) {
                       std::bitset<8> charBits(bitstream.substr(i, 8));
                       stringSend += (char)charBits.to_ulong();
                   }

                   this->par("run").setIntValue( this->par("run").intValue()+1);

                   //EV << "message send:"<<stringSend<<"\n";

                   msg->setName(stringSend.c_str());

     ////printt
                   EV <<"Message Header: " <<msg->getM_header()<<endl;
                   EV <<"Message Trailer: " <<msg->getM_Trailer()<<endl;
                   EV <<"Message Type: " <<msg->getM_Type()<<endl;
                   EV <<"Message Payload: " <<msg->getPayload()<<endl;
}
void Sender::initialize()
{
    // TODO - Generated method body
    MyMessage_Base *msg = new MyMessage_Base();
    ErrorNPrint(msg);

    int rand = uniform(0,1)*10;
    if (rand>=7)
    {
        sendDelayed(msg, 0.2, "out");
    }
    else
    {
        send(msg,"out");
    }

}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    //if ack, notack
    if (mmsg->getM_Type() == 1 || mmsg->getM_Type() == 0 )
    {
        ErrorNPrint(mmsg);
        int rand = uniform(0,1)*10;
        if (rand>=7)
        {
            sendDelayed(mmsg, 0.2, "out");
        }
        else
        {
            send(mmsg,"out");
        }
    }

    else{

        cancelAndDelete(msg);
    }

}
