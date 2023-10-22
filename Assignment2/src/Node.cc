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
        gameFinished = false;
        secretNumber = intuniform(0, 10);  // Generate a random secret number between 0 and 10
        EV << "Secret number: " << secretNumber << endl;

        // Start with Player2's behavior
        if (strcmp(this->getName(), "player2") == 0) {
            playerGuess = intuniform(0, 10);  // Simulate Player2's initial guess
            EV << "Player2: Initial guess: " << playerGuess << endl;

            cMessage *guessMsg = new cMessage("Guess");
            guessMsg->setKind(playerGuess);
            send(guessMsg, "out");
        }
    // TODO - Generated method body
}

void Node::handleMessage(cMessage *msg)
{
    if (!gameFinished) {
            if (strcmp(this->getName(), "player1") == 0) {
                int guess = msg->getKind();  // Retrieve the guess sent by Player2

                if (guess == secretNumber) {
                    EV << "Player1: Correct guess received! The secret number was " << secretNumber << endl;
                    cMessage *guessMsg = new cMessage("Correct Guess");
                    send(guessMsg, "out");
                    cancelAndDelete(guessMsg);
                    gameFinished = true;
                  //  endSimulation();  // Terminate the simulation
                } else {
                   EV << "Player1: Wrong guess received. The guess was " << guess << endl;
                    cMessage *guessMsg = new cMessage("Wrong Guess");
                    send(guessMsg, "out");
                }
            } else if (strcmp(this->getName(), "player2") == 0) {
                // Player2 continues to send guesses until a correct guess is made
                playerGuess = intuniform(0, 10);  // Simulate Player2's guess
              EV << "Player2: Sending guess: " << playerGuess << endl;

                cMessage *guessMsg = new cMessage("Guess");
                guessMsg->setKind(playerGuess);
                send(guessMsg, "out");
            }
        }

        delete msg;





    // TODO - Generated method body
}
