#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include<tuple>
#include<cmath>
#include<queue>
#include<assert.h>
// #include "queue.hpp"
using namespace std;

struct board{
    int arr[3][3];
};

enum {
    X=1,
    O=2
};

void print_board(const board& board){
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            cout<<board.arr[r][c]<<" ";
        }
        cout<<endl;
    }
    return;
}

pair<int,int> find_space(const board& board){
    int r=0,c=0;
    for(r=0;r<3;r++){
        for(c=0;c<3;c++){
            if(board.arr[r][c]==0){
                return make_pair(r,c);
            }
        }
    }
    assert(0);
}
bool checkvalid(const board& board ){           //Want 1's on the top

    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            if(board.arr[r][c]>1){return false;}
            if((r*c==1)){
                if(board.arr[1][1]!=0){return false;}
            }
        }
    }
    return true;
}

int ord(const board& board){
    int o=0;
    int i=0;
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++){
            o+=board.arr[r][c]*pow(7,i);
            i++;
        }
    }
    return o;
}

board up(board b, int r, int c){
    board bnew=b;
    int val=b.arr[r-1][c];
    if(val==1){val=6;}
    else if(val==2){val=5;}
    else if(val==5){val=1;}
    else if(val==6){val=2;}
    
    bnew.arr[r][c]=val;
    bnew.arr[r-1][c]=0;
    
    return bnew;
}

board down(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r+1][c];
    if(val==1){val=5;}
    else if(val==2){val=6;}
    else if(val==5){val=2;}
    else if(val==6){val=1;}
    bnew.arr[r][c]=val;
    bnew.arr[r+1][c]=0;
    return bnew;
}

board left(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r][c-1];
    if(val==1){val=4;}
    else if(val==2){val=3;}
    else if(val==3){val=1;}
    else if(val==4){val=2;}
    bnew.arr[r][c]=val;
    bnew.arr[r][c-1]=0;
    return bnew;
}

board right(const board& b, int r, int c){
    board bnew=b;
    int val=b.arr[r][c+1];
    if(val==1){val=3;}
    else if(val==2){val=4;}
    else if(val==3){val=2;}
    else if(val==4){val=1;}
    bnew.arr[r][c]=val;
    bnew.arr[r][c+1]=0;
    return bnew;
}

uint8_t visited[40353600]={0};
uint64_t parent[40353600];

vector<char> solve(const board& b){
   
    int count=0;
    queue<board> q;             
    q.push(b);
    visited[ord(b)] = 'S';          //S means start
    int maxSize=0;
    while(!q.empty()){
        board u=q.front();
        maxSize=(maxSize<q.size())? q.size():maxSize;
        q.pop();
        if(checkvalid(u)){
            vector<char> moves;
            int o=ord(u);
            while(visited[o]!='S'){
                moves.push_back(visited[o]);
                o=parent[o];
            }
            std::reverse(moves.begin(), moves.end());
            print_board(u);
            cout<<"Size of queue "<<q.size();
            cout<<"\n The total boards added in queue "<<count;
            cout<<"Max size of cube is "<<maxSize<<endl;
            return moves;
        }   

        auto p=find_space(u);
        int row= p.first;
        int col= p.second;
        // cout<<row<<col<<endl;
        board a,b,c,d;
        if(row!=0){
            a=up(u,row,col);              //move the empty box/space up i.e move move upper box down
            int aord = ord(a);
            if (!visited[aord]) {
                visited[aord] = 'U';
                parent[aord] = ord(u);
                q.push(a);count++;
            }
        }
        if(row!=2){
            b = down(u,row,col);  
            int bord = ord(b);
            if (!visited[bord]) {
                visited[bord] = 'D';
                parent[bord] = ord(u);
                q.push(b);count++;
            }
        }
        if(col!=0){
            c = left(u,row,col);
            int cord = ord(c);
            if (!visited[cord]) {
                visited[cord] = 'L';
                parent[cord] = ord(u);
                q.push(c);count++;
            }
        }
        if(col!=2){
            d = right(u,row,col);
            int dord = ord(d);
            if (!visited[dord]) {
                visited[dord] = 'R';
                parent[dord] = ord(u);
                q.push(d);count++;
            }
        }
    }
    vector<char> v;
    v.push_back(0);
    return v;
}



// cout<<"We are assuming that one face of the cube is X and the opposite face of it is valued 2 and the rest four faces are plane"<<endl;
//There are 6 orentations possible for each cube and we assign values to each of these 6 orentations
//such that if top face == 1 then assign value to that cube to be 1
//if bottom face == 1 then assign value to that cube to be 2                         
//if left face == 1 then assign value to that cube to be 3 
//enter 0 when the place is empty                        
void read_board(board& b){                               //T B L R U D
    for(int r=0;r<3;r++){                                //1 2 3 4 5 6 0
        for(int c=0;c<3;c++){
            if(r*c==1){
                b.arr[r][c]=0;
            }
            else{
                int val=2;
                // cin>>val;
                assert(val!=0);
                b.arr[r][c]=val;
            }
        }
    }
    return;
}

int main(){
    board b;
    read_board(b);
    print_board(b);
   
    auto moves=solve(b);
    
    if(moves[0]==0){
        cout<<"The board is unsolvable";
    }
    cout<<"Total number of moves required "<<moves.size();
    for(char c: moves){
        cout<<c<<endl;
    }
    return  0;
}