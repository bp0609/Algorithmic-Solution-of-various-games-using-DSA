#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<string.h>
using namespace std;

// Player is defines to be 1 if the current player is alice and -1 if the current player is bob
long long bestscore(vector<int> available,vector<int> alice,vector<int> bob, int player, long long& count){
    int no_candidate=1;
    long long myscore,oppscore;
    long long netscore,maxnetscore=LONG_LONG_MIN;
    for(int i=0;i<available.size();i++){
        if(available[i]){
            available[i]=0;
            no_candidate=0;
            myscore=(player==1) ? (alice[i]-1):(bob[i]-1);
            oppscore=bestscore(available,alice,bob,(-1*player), count);
            netscore=myscore-oppscore;
            maxnetscore=(netscore>maxnetscore) ? netscore:maxnetscore;
            available[i]=1;
        }
    }
    if(no_candidate){
        count++;
        return 0;
    }
    else{
        count++;
        return maxnetscore;
    }
}


int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> available(n,1);
        vector<int> alice(n,0);
        vector<int> bob(n,0);
        for(int i=0;i<n;i++){
            cin>>alice[i];
        }
        for(int i=0;i<n;i++){
            cin>>bob[i];
        }
        long long count=0;
        cout<<bestscore(available,alice,bob,1, count)<<endl;
        cout<<count<<endl<<endl;
    }
    return 0;
}