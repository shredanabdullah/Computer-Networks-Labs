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

#include "Sender.h"

Define_Module(Sender);

void Sender::initialize()
{
    // TODO - Generated method body
    // Initialize the conversation by sending the first message.
       cMessage *msg = new cMessage("Tic_0");
       send(msg, "out");
}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
            // Check if it's time to stop the conversation.
               if (counter1 > 9) {
                   delete msg;
                   return;
               }

               // Generate the next message based on the current counter.
               std::string str;
               if (counter1 % 2 != 0) {
                   // Toc's turn
                   str = "T0c_" + std::to_string(counter1);

               }
               else{
                   str = " ";
               }
               // Create a new message with the generated name
                       cMessage *nextMsg = new cMessage(str.c_str()); // Convert to const char* when creating the message

                       // Send the message and increment the counter.
                       send(nextMsg, "out");
                       counter1++;
}
