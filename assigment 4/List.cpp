#include "List.h"
#include <iostream>
using namespace std;

int main()
{
    List<int> l1;  //测试默认构造函数
    List<double> l2{1.2, 1.3, 1.4, 1.5 };  //初始化列表
    List<int>l6=l1;
    const List<double>l3=l2; //测试拷贝构造函数
    List<int> l4{1,2,3};
    l4.empty(); //测试empty函数
    l1.print();
    for(int i=0; i<5;++i){
        l1.push_front(i);
    }                                         //测试pushfront函数
    for(int i=0; i<5; ++i){
        l6.push_back(i);
    }                    //测试左值引用的pushback函数
    for(int i=0; i<2;++i){
        l1.push_front(i+10);
    }
    for(int i=0; i<2; ++i){
        l6.push_back(i+10);
    }                   //测试右值引用的pushback函数
    l1.print();
    l6.print();
    l1.front()=1; //测试动态的front函数
    l6.back()=0; //测试动态的back函数
    l1.pop_back();  //测试popfront函数
    l6.pop_front();
    l1.print();
    l6.print();
    cout<<"the first element in l3 is "<<l3.front()<<endl;; //测试静态的front函数
    cout<<"the last elemnet in l3 is "<<l3.back()<<endl;; //测试静态的back函数
    l3.print();
    l1=l4; //测试赋值运算符
    l1.print();
    //测试移动构造函数
    List<int>l, l7;
    for(int i=0; i<3; ++i){
        l.push_back(i);
    }
    List<int> l5=move(l);
    l7=move(l5);
    l7.resize(6,1);
    l7.print();
    cout<<"to check if 10 is in l7"<<l7.find(10)<<endl;
    cout<<"to check if 1 is in l7"<<l7.find(1)<<endl;
    cout<<"show that if l2 is empty "<<l2.empty()<<endl;;

    cout<<"the size of l5 is "<<l5.size()<<endl;  //测试size函数

    auto itr1=l2.begin();
    ++itr1;
    l2.insert(itr1, 0.03);
    itr1++;
    l2.insert(itr1,0.02+0.02);
    ++itr1;
    l2.erase(itr1);
    l2.print();

    auto itr2=l2.end();
    --itr2;
    --itr2;
    l2.insert(itr2, 0.0);
    itr2--;
    l2.insert(itr2, 0.01);
    itr2--;
    l2.erase(itr2);
    l2.print();
    l2.erase(l2.begin(), l2.end());
    l2.print();
    //测试链表为空或者只有一个元素的情况
    List<int> l8;
    auto itr3 = l8.begin();
    if (itr3 == l8.end()) {
        cout << "the list is empty" << endl;
    }
    l8.push_back(10);
    auto itr4 = l8.begin();
    cout << "Single element: " << *itr4 << endl;



  //  for (int i = 0; i < 10; ++i)
   // {
     //   l1.push_back(i);
    //}

   // l1.pop_back();


//for (auto it = l2.begin(); it != l2.end(); ++it)
//{
  //  std::cout << *it << std::endl;
//}

//     List<int> lst = {1, 2, 3, 4, 5};
//     for (auto &x : lst)
//     {
//         std::cout << x << "\t";
//     }
//     std::cout << std::endl;

//     List<int> lst2 = List<int> {5, 6};



//     lst2 = std::move(lst);
//     for (auto &x : lst2)
//     {
//         std::cout << x << "\t";
//     }
//     std::cout << std::endl;

    return 0;
}
