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

#include "NL.h"

Define_Module(NL);

void NL::initialize()
{
    address = par("NLaddr");
    nl_igate = gate("nl_in");
    nl_ogate = gate("nl_out");
    counter = 1;

    if(address == 1)
    {
        //for CM1
        cMessage *event = new cMessage();
        scheduleAt(0, event);
    }
}

void NL::handleMessage(cMessage *msg)
{
    if(msg -> isSelfMessage())
    {
        //send to DLL 1
        if(counter <= 10)
        {
            counter++;
            NLmsg *pkt = new NLmsg();
            pkt -> setId(counter);
            pkt -> setType("DATA_PACKET");
            pkt -> setSrcAddr("nl_1");
            pkt -> setDestAddr("dll_1");
            this -> send(pkt, nl_ogate);

            cMessage *event = new cMessage();
            scheduleAt(simTime() + 200, event);
        }
    }
    else
    {
        //received at NL2, delete msg
        delete(msg);
    }
}
