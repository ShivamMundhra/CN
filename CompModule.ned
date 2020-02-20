
module CompModule
{
    parameters:
        int c_address;
        @display("bgb=328,245");
    gates:
        input c_in;
        output c_out;
    submodules:
        NL: NL {
            n_Addr = c_address;
            @display("p=33,98");
        }
        DLL: DLL {
            d_Addr = c_address;
            @display("p=263,98");
        }
    connections:
        c_in --> DLL.CInputGate;
        DLL.COutputGate --> c_out;
        NL.outputGate --> DLL.NLInputGate;
        DLL.NLOutputGate --> NL.inputGate;
}
