#include<iostream>
#include<vector>
#include"HeapSort.hpp"
#include<random>
#include<algorithm>
#include<chrono>
#include <numeric> 
using namespace std;

const int N=1000000;

enum class testType{
    random,
    ascending,
    descending,
    duplicate
};

template<typename T>
void Checkorder(const vector<T> &v){
    for(int i=0; i<v.size()-1;++i){
        if(v[i]>v[i+1]){
            cerr<<"Not ordered"<<endl;
            return;
        }
    }
    cout<<"the sequence is already an increasing sequence!"<<endl;
}

class Check{
private:
    vector<int> v;
    vector<int> v1;
public:
    Check(){}
    Check(const int &n, const testType &type=testType::random){
        mt19937 rnd(19260817);
        v.resize(n,0);
    if(type==testType::random){
        for(int i=0; i<n; ++i){
            v[i]=rnd();
        }
    }

    else if(type==testType::ascending){
        iota(v.begin(), v.end(),1);
    }

    else if(type==testType::descending){
        iota(v.begin(),v.end(),2);
        reverse(v.begin(),v.end());
    }

    else if(type==testType::duplicate){
    // 创建随机数生成器
    random_device rd; // 随机数种子
    mt19937 gen(rd()); // 使用Mersenne Twister生成器
    uniform_int_distribution<> dis(1,1000); 
    for(int i=0; i<n;++i){
        v[i]=dis(gen);
    }
    }
    v1=v;
    }    

    void compareTime(){
        make_heap(v.begin(),v.end());
        auto start1=chrono::high_resolution_clock::now();
        sort_heap(v.begin(), v.end());
        auto end1=chrono::high_resolution_clock::now();
        auto duration1=chrono::duration_cast<chrono::milliseconds>(end1-start1);
        cout<<"STL sort_heap() takes "<<duration1.count()<<" milliseconds."<<endl;
        
        auto start2=chrono::high_resolution_clock::now();
        sort_Heap(v1);
        auto end2=chrono::high_resolution_clock::now();
        auto duration2=chrono::duration_cast<chrono::milliseconds>(end2-start2);
        cout<<"My heapSort takes "<<duration2.count()<<" milliseconds."<<endl;
        Checkorder(v1);
    }
};


void test(){
    cout << "------------------------------" << endl;
    cout<<"random sequence:"<<endl;
    Check c1(N);
    c1.compareTime();

    cout<<"------------------------------" << endl;
    cout<< "ascending  sequence:"<<endl;
    Check c2(N,testType::ascending);
    c2.compareTime();


    cout <<"------------------------------" << endl;
    cout<< "descending  sequence:"<<endl;
    Check c3(N,testType::ascending);
    c3.compareTime();


    cout <<"------------------------------" << endl;
    cout<< "duplicate  sequence:"<<endl;
    Check c4(N,testType::duplicate);
    c4.compareTime();
}


int main(){
    test();
    return 0;
}