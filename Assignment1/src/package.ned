package assignment11;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=356,229");
    submodules:
        Reci: Sender {
            @display("p=40,47");
        }
        Send: Reciever {
            @display("p=274,142");
        }
    connections:
        Reci.out --> Send.in;
        Send.out --> Reci.in;
}

