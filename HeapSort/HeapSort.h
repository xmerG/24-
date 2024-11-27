#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

template<typename T>
void HeapSort(vector<T> &vec){
    int n=vec.size();
    make_heap(vec.begin(),vec.end());
    for(int i=n-1; i>0; --i){
        pop_heap(vec.begin(),vec.begin()+i+1);
    }
}

template<typename T>
void print(const vector<T> &vec){
    for(auto i: vec){
        cout<<i<<" ";
    }
    cout<<endl;
}