package lab2final;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=281,238");
    submodules:
        player2: Node {
            @display("p=46,49");
        }
        player1: Node {
            @display("p=202,140");
        }
    connections:
        player2.out --> player1.in;
        player1.out --> player2.in;
}

