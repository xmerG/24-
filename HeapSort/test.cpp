#include<iostream>
#include<vector>
#include"HeapSort.h"
#include<random>
#include<algorithm>
#include<chrono>
using namespace std;

const int N=1000000;

enum class testType{
    random,
    ascending,
    descending,
    duplicate
};

class Check{
private:
    vector<int> v;
public:
    Check(){}
    Check(const int &n, const testType &type=testType::random){
        mt19937 rnd(19260817);
    if(type==testType::random){
        for(int i=0; i<n; ++i){
            v.push_back(rnd());
        }
    }
    }    

    void compareTime(){
        make_heap(v.begin(),v.end());
        auto start1=chrono::high_resolution_clock::now();
        sort_heap(v.begin(), v.end());
        auto end1=chrono::high_resolution_clock::now();
        auto duration1=chrono::duration_cast<chrono::milliseconds>(end1-start1);
        cout<<"STL sort_heap() takes "<<duration1.count()<<" milliseconds."<<endl;
        
        auto start2=chrono::high_resolution_clock::now();
        HeapSort(v);
        auto end2=chrono::high_resolution_clock::now();
        auto duration2=chrono::duration_cast<chrono::milliseconds>(end2-start2);
        cout<<"My heapSort takes "<<duration2.count()<<" milliseconds."<<endl;
    }
};


void test(const testType &btype=testType::random){
    Check c1(N, btype);
    c1.compareTime();
}


int main(){
    test();
    return 0;
}