#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

template<typename T>
//调整堆，i代表要调整的节点
void adjust(vector<T> &v, int i, const int &n){
    int child;
    T temp;
    for(temp=move(v[i]); 2*i+1<n; i=child){
        child=2*i+1;
        if(child !=n-1 && v[child]<v[child+1]){
            ++child;
        }
        if(temp <v[child]){
            v[i]=move(v[child]);
        }
        else{
            break;
        }
    }
    v[i]=move(temp);
}

template<typename T>
void sort_Heap(vector<T> &v){
    for(int i=v.size()/2-1; i>=0; --i){
        adjust(v,i,v.size());
    }
    for(int j=v.size()-1; j>0; --j){
        swap(v[0],v[j]);
        adjust(v,0,j);
    }
}

template<typename T>
void print(const vector<T> &vec){
    for(int i=0; i<vec.size(); ++i){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}
