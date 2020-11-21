#include <stdio.h>
#include "board.h"
#include "engine.h"

int main()
{
    struct Board b = make_board(25,25);
    printf("made board of size (%d,%d)\n",b.size_x,b.size_y);
    clear_board(&b);
    // glider
    write_state(&b,2,2,true);
    write_state(&b,3,3,true);
    write_state(&b,3,4,true);
    write_state(&b,2,4,true);
    write_state(&b,1,4,true);
    // beacon, period 2
    write_state(&b,15,4,true);
    write_state(&b,16,4,true);
    write_state(&b,15,5,true);
    write_state(&b,18,6,true);
    write_state(&b,18,7,true);
    write_state(&b,17,7,true);
    // penta-decathlon
    write_state(&b,1,20,true);
    write_state(&b,2,20,true);
    write_state(&b,3,20,true);
    write_state(&b,4,20,true);
    write_state(&b,5,20,true);
    write_state(&b,6,20,true);
    write_state(&b,7,20,true);
    write_state(&b,8,20,true);
    write_state(&b,9,20,true);
    write_state(&b,10,20,true);
    // Conway's Game of Life rules
    bool alive_rules[9] = {false,false,true,true,false,false,false,false,false};
    bool dead_rules[9] = {false,false,false,true,false,false,false,false,false};
    struct Engine eng = setup_engine(b,alive_rules,dead_rules,true);
    run_engine(&eng,100);
    delete_board(&(eng.brd));
    return 0;
}