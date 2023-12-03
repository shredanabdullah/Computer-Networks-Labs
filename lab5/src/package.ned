package lab5;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=339,216");
    submodules:
        sender: Sender {
            @display("p=46,163");
        }
        receiver: Receiver {
            @display("p=291,44");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}

