#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<string.h>
using namespace std;

int encode_available(vector<int> available){
    int i=1;
    int idx=0;
    for(auto v: available){
        idx+=v*i;
        i*=2;
    }
    return idx;
}

// Player is defines to be 1 if the current player is alice and -1 if the current player is bob
long long bestscore(vector<int> available,vector<int> alice,vector<int> bob, int player, vector<long long>& storedScores){
    int no_candidate=1;
    long long myscore,oppscore;
    long long netscore,maxnetscore=LONG_LONG_MIN;
    if(storedScores[encode_available(available)]>LONG_LONG_MIN){
        return storedScores[encode_available(available)];
    }
    for(int i=0;i<available.size();i++){
        if(available[i]){
            available[i]=0;
            no_candidate=0;
            myscore=(player==1) ? (alice[i]-1):(bob[i]-1);
            oppscore=bestscore( available, alice, bob, (-1*player), storedScores);
            netscore=myscore-oppscore;
            maxnetscore=(netscore>maxnetscore) ? netscore:maxnetscore;
            available[i]=1;
        }
    }
    if(no_candidate){
        return 0;
    }
    else{
        storedScores[encode_available(available)]=maxnetscore;
        return maxnetscore;
    }
}

int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<long long> storedScores(pow(2,n),LONG_LONG_MIN);
        vector<int> available(n,1);
        vector<int> alice(n,0);
        vector<int> bob(n,0);
        for(int i=0;i<n;i++){
            cin>>alice[i];
        }
        for(int i=0;i<n;i++){
            cin>>bob[i];
        }
        cout<<bestscore(available,alice,bob,1,storedScores)<<endl;
    }
    return 0;
}
