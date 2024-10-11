#include <initializer_list>
#include <iostream>
#include<string>
#include<cstdlib>
using namespace std;

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmplty() const;

    int getSize() const;
    void emptyList();
    bool find (const T &_val);
    SingleLinkedList(){};
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val); 

    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;  
    /// 删除 currentPos 后面的元素
    void remove();                       
    void remove(T _val);         //重载remove函数，修改当前的设计        
};

template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;    
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}
template<typename T>
T SingleLinkedList<T>::getCurrentVal() const{
    if(currentPos==nullptr){
        cerr<<"Empty current position! Can't get value!"<<endl;
        exit(1);
    }
    else{
        return currentPos->data;
    }
}
template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val){
    if(currentPos==nullptr){
        cerr<<"Empty current position! Can't get value!"<<endl;
        exit(1);
    }
    else{
        currentPos->data=_val;
    }
}
template<typename T>
bool SingleLinkedList<T>::isEmplty() const{
    if(head==nullptr){
        return true;
    }
    else{
        return false;
    }
}
template<typename T>
void SingleLinkedList<T>::insert(T _val){
    Node* newnode=new Node(_val);
    if(head ==nullptr){
        head=newnode;
        currentPos=head;
        ++size;
    }
    else{
        Node* newnode=new Node(_val);
        newnode->next=currentPos->next;
        currentPos->next=newnode;
        ++size;
    }
}
template<typename T>
void SingleLinkedList<T>::remove(){
    if(head==nullptr ){} //如果链表是空链表，什么都不做
    
    //如果只有一个元素删除此元素
    else if(size==1){
        delete head;
        head=nullptr;
        currentPos=head;
        size=0;
    }
    //如果当前元素就是最后一个,删掉最后一个元素，并且让currentpos指向删除之后单链表的最后一个元素
    else if(currentPos==nullptr){
        Node* p=head;
        while (p->next->next!=nullptr){
            p=p->next;
        }
        delete p->next;
        p->next=nullptr;
        currentPos=p;
        --size;        
    }
    //如果当前指针的位置不是最后一个元素，删掉后一个
    else{
        Node* p=currentPos->next->next;
        delete currentPos->next;
        currentPos->next=p;
        --size;
    } 
}

template<typename T>
void SingleLinkedList<T>::remove(T _val){
    if(find(_val)){
        Node* p=head;
        while (p->next!=currentPos){
            p=p->next;
        }
        Node* p1=p->next->next;
        delete p->next;
        p->next=p1;
        currentPos=p;     
        --size;
    }
    else{
        cerr<<"the value you put is not in current single linked list"<<endl;
        exit(1);
    }
}