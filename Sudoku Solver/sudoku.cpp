#include <cstdio>
#include <cassert>
#include <utility>

#include "stack.hpp"

typedef struct {
    int b[9][9]; // 0 is the blank cell.
} sudoku;

void clear(bool seen[10])
{
    for (int i = 0; i < 10; ++i) {
        seen[i] = false;
    }
}

int is_valid(const sudoku& s)
{
    bool seen[10];
    for (int row = 0; row < 9; ++row) {
        clear(seen);
        for (int col = 0; col < 9; ++col) {
            int v = s.b[row][col];
            if (v && seen[v]) { return false; }
            seen[v] = true;
        }
    }
    for (int col = 0; col < 9; ++col) {
        clear(seen);
        for (int row = 0; row < 9; ++row) {
            int v = s.b[row][col];
            if (v && seen[v]) { return false; }
            seen[v] = true;
        }
    }
    int boxrow = 0;
    int boxcol = 0;
    while (boxrow < 9) {
        while (boxcol < 9) {
            clear(seen);
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    int v = s.b[boxrow+r][boxcol+c];
                    if (v && seen[v]) { return false; }
                    seen[v] = true;
                }
            }
            boxcol += 3;
        }
        boxrow += 3;
        boxcol = 0;
    }
    return true;
}

sudoku place(const sudoku& s, int i, int j, int v)
{
    sudoku t = s;
    // printf("Placing %d at (%d, %d)\n", v, i, j);
    assert(t.b[i][j] == 0);
    t.b[i][j] = v;
    return t;
}

void print_board(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v = s.b[r][c];
            if (v) printf("%d ", s.b[r][c]);
            else printf(". ");
        }
        printf("\n");
    }
}

void read_board(sudoku& s)
{
    int v;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            scanf("%d", &v);
            s.b[r][c] = v;
        }
    }
}

bool is_full(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (s.b[r][c] == 0) return false;
        }
    }
    return true;
}

std::pair<int, int> find_first_blank(const sudoku& s)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (s.b[r][c] == 0) return { r, c };
        }
    }
    assert(0);
}

sudoku solve(const sudoku& s)    //s is sudoku board & we used const so we can't modify it.
{
    stack<sudoku> st;               //st is a stack which stores board (NOT integers in this case).
    push(st, s);                    // pushing a board to stack
    while (!is_empty(st)) {
        sudoku v = pop(st);         //v is a board which initialised to topmost board in the stack.
        if (is_full(v)) {           //As stack contains only valid boards and if a valid board is full,
            return v;               //that means it is our final answer
        }
        auto pos = find_first_blank(v);
        for (int val = 1; val <= 9; ++val) {
            sudoku u = place(v, pos.first, pos.second, val);
            if (is_valid(u)) {
                push(st, u);                              // stack ke andar hum only valid boards push kar rahe hai.
            }                                             // aur uske baad loop vapas chal raha hai toh hum top board ko pop kar rahe hai stack mai se
        }
    }
    assert(0);
}

sudoku recursion(const sudoku& s,bool* validity){
    if(is_full(s)){
        return s;
    }
    auto pos = find_first_blank(s);
    sudoku u,v;
    for (int val = 1; val <= 9; ++val) {
            u = place(s, pos.first, pos.second, val);
            if (is_valid(u)) {
                v=recursion(u,validity);
                if(validity){
                    *validity=true;
                    return v;
                }
                *validity=true;                              // stack ke andar hum valid boards push kar rahe hai.
            }                                             // aur uske baad loop vapas chal raha hai toh hum top board ko pop kar rahe hai
        }
    *validity=false;
    return u;
}

int main()
{
    sudoku s;
    read_board(s);
    print_board(s);
    printf("===\n");
    // bool val=true;
    // sudoku t = recursion(s,&val);
    sudoku t = solve(s);
    print_board(t);

    return 0;
}