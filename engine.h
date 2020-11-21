#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include <windows.h>
#include "board.h"

struct Engine {
    struct Board brd;
    bool aliveRules[9]; // if cell is alive and {0, 1, 2, 3, 4, 5, 6, 7, 8} neighbors alive: true if alive next round
    bool deadRules[9]; // above, but if cell is dead
    bool wrap;
    int rnd;
};

struct Engine setup_engine(struct Board b, bool* alive_rules, bool* dead_rules, bool wrap)
{
    struct Engine e;
    e.brd = b;
    for(int i=0;i<9;i++)
    {
        e.aliveRules[i] = alive_rules[i];
        e.deadRules[i] = dead_rules[i];
    }
    e.wrap = wrap;
    e.rnd = 0;
    return e;
}

void advance_round(struct Engine* e)
{
    int bsize_x = e->brd.size_x;
    int bsize_y = e->brd.size_y;
    // create next round's board
    struct Board new_brd = make_board(bsize_x,bsize_y);
    clear_board(&new_brd);
    // fill next round's board by looping over the old one
    for(int i=0; i < e->brd.size_x; i++)
    {
        for(int j=0; j < e->brd.size_y; j++)
        {
            int n_alive_neighbors = 0;
            int left_x = i-1;
            int right_x = i+1;
            int up_y = j-1;
            int down_y = j+1;
            if(e->wrap)
            {
                if(i==0) left_x = bsize_x-1;
                if(i==bsize_x-1) right_x = 0;
                if(j==0) up_y = bsize_y-1;
                if(j==bsize_y-1) down_y = 0;
            }
            // check for alive neighbors within board
            if(left_x>=0 && 
                e->brd.is_alive[left_x+j*bsize_x]) n_alive_neighbors++; // left
            if(right_x<bsize_x && 
                e->brd.is_alive[right_x+j*bsize_x]) n_alive_neighbors++; // right
            if(up_y>=0 && 
                e->brd.is_alive[i+up_y*bsize_x]) n_alive_neighbors++; // up
            if(down_y<bsize_y && 
                e->brd.is_alive[i+down_y*bsize_x]) n_alive_neighbors++; // down
            if(left_x>=0 && up_y>=0 && 
                e->brd.is_alive[left_x+up_y*bsize_x]) n_alive_neighbors++; // up-left
            if(left_x>=0 && down_y<bsize_y && 
                e->brd.is_alive[left_x+down_y*bsize_x]) n_alive_neighbors++; // down-left
            if(right_x<bsize_x && up_y>=0 && 
                e->brd.is_alive[right_x+up_y*bsize_x]) n_alive_neighbors++; // up-right
            if(right_x<bsize_x && down_y<bsize_y && 
                e->brd.is_alive[right_x+down_y*bsize_x]) n_alive_neighbors++; // down-right
            // write state for cell according to rules
            if(e->brd.is_alive[i+j*bsize_x]) write_state(&new_brd,i,j,e->aliveRules[n_alive_neighbors]);
            else write_state(&new_brd,i,j,e->deadRules[n_alive_neighbors]);
        }
    }
    delete_board(&(e->brd));
    e->brd = new_brd;
}

void run_engine(struct Engine* e, int update_time_ms)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h,&bufferInfo);
    while(1)
    {
        SetConsoleCursorPosition(h,bufferInfo.dwCursorPosition);
        printf("round %d\n",e->rnd);
        print_state(&(e->brd));
        advance_round(e);
        e->rnd++;
        Sleep(update_time_ms);
    }
}

#endif