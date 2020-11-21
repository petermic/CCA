#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Board {
    int size_x;
    int size_y;
    bool* is_alive;
};

struct Board make_board(int size_x,int size_y)
{
    struct Board b;
    b.size_x = size_x;
    b.size_y = size_y;
    b.is_alive = (bool *) malloc(size_x*size_y*sizeof(bool));
    return b;
}

void delete_board(struct Board* b)
{
    free(b->is_alive);
}

void clear_board(struct Board* b)
{
    for(int i=0;i<b->size_x;i++)
    {
        for(int j=0;j<b->size_y;j++)
        {
            b->is_alive[i+j*b->size_x] = false;
        }
    }
}

bool write_state(struct Board* b, int i, int j, bool state)
{
    if(i<0 || i>=b->size_x || j<0 || j>=b->size_y) return false;
    b->is_alive[i+j*b->size_x] = state;
    return true;
}

void print_state(struct Board* b)
{
    for(int j=0;j<b->size_y;j++)
    {
        for(int i=0;i<b->size_x;i++)
        {
            printf(b->is_alive[i+j*b->size_x] ? "O" : ".");
            printf(" ");
        }
        printf("\n");
    }
}

#endif