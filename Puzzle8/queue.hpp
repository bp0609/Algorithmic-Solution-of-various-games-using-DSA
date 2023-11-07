#include <assert.h>
#include<iostream>
using namespace std;

template <typename T, int Size>
struct queue {
    T* elts=new T[Size];
    int front;
    int back;
    int len;

    queue() {
        len = 0;
        back = 0;
        front = 0;
    }
};

template <typename T, int Size>
bool empty(const queue<T, Size> &q)
{
    return (q.len == 0);
}

template <typename T, int Size>
void enqueue(queue<T, Size> &q, const T& e)
{
    assert (q.len < Size);
    q.elts[q.back] = e;
    q.back = (q.back + 1) % Size;
    ++q.len;
}

template <typename T, int Size>
T dequeue(queue<T, Size> &q)
{
    assert (q.len > 0);
    T e = q.elts[q.front];
    q.front = (q.front + 1 ) % Size;
    --(q.len);
    return e;
}

template <typename T, int Size>
void deletion(queue<T, Size> &q){
    cout<<"Deleted";
    delete []q.elts ;
}