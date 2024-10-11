#include "LinkedList.h"

int main()
{
    //测试重载后的remove函数
    SingleLinkedList<int> a1{1,2,3,4,5};
    a1.remove(3);
    a1.printList();

    SingleLinkedList<int> a{1,2,3,4,5};
    int a_get=a.getCurrentVal();
    cout<<a_get<<endl;

    SingleLinkedList<char> b{'a', 'c', 'e'};
    b.setCurrentVal('g');
    b.printList();

    SingleLinkedList<char> e;
    cout<<b.isEmplty()<<" "<<e.isEmplty()<<endl;

    SingleLinkedList<double> c1;
    SingleLinkedList<double> c2{1.5, 2.0, 9.0, 4.7};
    SingleLinkedList<double> c3;
    c3=c2;
    c1.insert(3.0);
    c2.insert(8.8);
    bool f_c3=c3.find(2.0);
    c3.insert(8.8);
    c1.printList();
    c2.printList();
    c3.printList();

    e.remove();
    c1.remove();
    bool f = c2.find(9.0);
    c2.remove();
    e.printList();
    c1.printList();
    c2.printList();



    return 0;
};