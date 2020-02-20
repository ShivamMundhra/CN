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

network Network
{
    @display("bgb=243,121");
    submodules:
        C1: CompModule {
            c_address = 1;
        }
        C2: CompModule {
            c_address = 2;
            @display("p=182,30");
        }
    connections:
        C1.c_out --> C2.c_in;
        C2.c_out --> C1.c_in;
}
