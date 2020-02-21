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

#include "DLL.h"

Define_Module(DLL);

void DLL::initialize()
{
    address = par("DLLaddr");
    dlln_igate = gate("dlln_in");
    dlln_ogate = gate("dlln_out");
    dllc_igate = gate("dllc_in");
    dllc_ogate = gate("dllc_out");
}

void DLL::handleMessage(cMessage *msg)
{
    if(msg -> getArrivalGate() == dlln_igate)
    {
        //send to DLL 2 of other compound module

        NLmsg *pkt = check_and_cast<NLmsg *>(msg);
        int id = pkt -> getId();
        DLLmsg *frame = new DLLmsg();
        frame -> encapsulate(pkt);
        frame -> setId(id % 2);
        frame -> setType("DATA_FRAME");
        frame -> setSrcAddr("dll_1");
        frame -> setDestAddr("dll_2");
        this -> send(frame, dllc_ogate);
    }

    if(msg -> getArrivalGate() == dllc_igate)
    {
        DLLmsg *frame = check_and_cast<DLLmsg *>(msg);
        if(strcmp(frame -> getSrcAddr(), "dll_1") == 0 && strcmp(frame -> getDestAddr(), "dll_2") == 0)
        {
            //send to NL 2

            cPacket *packet = new cPacket();
            packet = frame -> decapsulate();
            NLmsg *pkt = check_and_cast<NLmsg *>(packet);
            pkt -> setType("DATA_PACKET");
            pkt -> setSrcAddr("dll_2");
            pkt -> setDestAddr("nl_2");
            this -> send(pkt, dlln_ogate);

            //send ack

            DLLmsg *ack = new DLLmsg();
            ack -> setType("ACK_FRAME");
            ack -> setSrcAddr("dll_2");
            ack -> setDestAddr("dll_1");
            this -> send(ack, dllc_ogate);
        }
        else if(strcmp(frame -> getSrcAddr(), "dll_2") == 0 && strcmp(frame -> getDestAddr(), "dll_1") == 0)
        {
            //receiving ACK, delete ACK frame
            delete(frame);
        }

    }
}

