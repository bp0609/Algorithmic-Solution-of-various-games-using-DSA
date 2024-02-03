#include <stdio.h>
#include <assert.h>
#include<conio.h>
#include "test.h"

/*
 * The status of a line.
 */
enum
{
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
#define board_size (15)
typedef char board_t[board_size];
typedef char player_t; /* A player should be RED or BLUE. */

player_t other_player(player_t player)
{
    switch (player)
    {
    case RED:
        return BLUE;
    case BLUE:
        return RED;
    default:
        assert(0);
    }
}

int has_lost(board_t board, player_t player)
{
    int c = 4;
    for (int i = 0; i < 4; i++)
    {   
        if ((board[i]!=player))
        {   
            c=c+3-i;
            continue;
        }
        for (int j = i + 1; j < 5; j++)
        {
            if (board[j] == board[i])
            {   
                
                if (board[i] == board[j + c])
                {   
                    return 1;
                }
            }
        }
        c=c+3-i;
    }
    
    c=3;
    for (int i = 5; i < 8; i++)
    {
        if ((board[i]!=player))
        {   
            c=c+7-i;
            continue;
        }
        for (int j = i + 1; j <= 8; j++)
        {   
            if (board[j] == board[i])
            {  
                if (board[i] == board[j + c])
                {   
                    return 1;
                }
            }
        }
        c=c+7-i;
    }

    c=2;
    for (int i = 9; i < 11; i++)
    {
        if ((board[i]!=player))
        {
            c=c+10-i;
            continue;
        }
        for (int j = i + 1; j <= 11; j++)
        {
            if (board[j] == board[i])
            {
                if (board[i] == board[j + c])
                {   
                    return 1;
                }
            }
        }
        c=c+10-i;
    }
    if(board[12]==player)
    {    if ((board[12] == board[13]) && (board[12] == board[14]))
        { 
            return 1;
        }
    }
    return 0;
}

int is_full(board_t board)
{ // if board full--->1 and if not full-->0
    for (int i = 0; i < board_size; i++)
    {
        if (board[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

typedef struct
{
    int line;  /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t candidate;
    int no_candidate=1;
    int flag=0;
    int line;
    for(int i=0;i<board_size;i++){
        if(board[i]==0){
            board[i]=player;
            if(!has_lost(board,player)){
                board[i]=other_player(player);
                if(!has_lost(board,other_player(player))){
                    board[i]=NO;
                    return (move_t){
                        i,
                        0
                    };
                }
                else{
                    candidate=(move_t){
                        i,
                        0
                    };
                    no_candidate=0;
                }
            }
            else{
                if(no_candidate){
                    candidate=(move_t){
                        i,
                        0
                    };
                    no_candidate=0;
                }
            }
            board[i]=NO;
        }
    }
    return candidate;
}


void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i)
    {
        switch (board[i])
        {
        case RED:
            printf("R  ");
            break;
        case BLUE:
            printf("B  ");
            break;
        default:
            printf("0  ");
        }
    }
    printf("\n");
}
void print_num(){
    for(int i=0;i<10;i++){
        printf("%d  ",i);
    }
    for(int i=10;i<15;i++){
        printf("%d ",i);
    }

    printf("\n");
}

int main()
{   
    player_t player,current;
    char c;
    printf("Select a player---> RED or BLUE\n");
    scanf("%s",&c);
    switch(c){
        case 'R':player=RED;break;
        case 'B':player=BLUE;break;
        default: player=RED;
    }

    board_t board;
    move_t response;
    // Initiating board
    for (int i = 0; i < board_size; i++)
    {
        board[i] = 0;
    }
    // print_board(board);
    current=player;
    int line;
    while(1){
        print_board(board);
        if (current==player){
            print_num();
            scanf("%d",&line);
            assert(!(board[line]));
            board[line]=current;
        }
        else{
            response=best_move(board,current);
            board[response.line]=current;
        }
        if(has_lost(board,current)){
            print_board(board);
            print_num();
            printf("Player %s has won!\n", (other_player(current)==RED) ? "RED":"BLUE");
            break;
        }
        else if(is_full(board)){
            print_board(board);
            print_num();
            printf("Draw.\n");
            break;
        }
        current=other_player(current);
    }
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}