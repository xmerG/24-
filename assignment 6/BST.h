/**
 * @file BST.h 
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;
 // namespace name

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}


    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height=1;          //节点高度

        /**
         * @brief 构造函数，接受常量引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int _height=0)
            : element{ theElement }, left{ lt }, right{ rt }, height{_height}{}

        /**
         * @brief 构造函数，接受右值引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int _height=0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{_height}{}
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针                
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode * &t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr, 
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
            /// 如果元素已存在，则不进行插入
            /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
        balance(t);
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
            balance(t);

    }

    /**
     * @brief 递归从树中移除指定的元素
     * 
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    void remove(const Comparable &x, BinaryNode * &t) {
        /// 这个逻辑其实是 find and remove, 从 t 开始
        if (t == nullptr) {
            return;  /// 元素不存在
        }
        else if (x < t->element) {
            remove(x, t->left);
        } 
        else if (x > t->element) {
            remove(x, t->right);
        } 
        /// 进入以下这两个分支，都是说明找到了要删除的元素
        else if (t->left != nullptr && t->right != nullptr) {
            BinaryNode *t1=detachMin(t->right);
            BinaryNode *oldt=t;
            t1->left=t->left;
            t1->right=t->right;
            t=t1;
            delete oldt;
        } else {
            /// 有一个或没有子节点的情形是简单的
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }
    /*BinaryNode *detachMin(BinaryNode *&t){
        if(t->left!=nullptr){
            return detachMin(t->left);
        }
        else{
            BinaryNode *oldt=t;
            t=t->right;
            oldt->right=nullptr;
            return oldt;
        }
    }*/

    BinaryNode *detachMin(BinaryNode *&t){
        if(t==nullptr){
            return nullptr;
        }
        else{
            BinaryNode *parent=nullptr;
            BinaryNode *current=t;
            while(current->left!=nullptr){
                parent=current;
                current=current->left;
            }
            //如果最小元素的节点不是根节点t
            if(parent!=nullptr){
                parent->left=current->right;
            }
            //如果是根节点
            else{
                t=current->right;
            }
            current->right=nullptr;
            return current;

        }
    } 
    /*void remove(const Comparable &x, BinaryNode *&t){
        //空BST直接返回
        if(t==nullptr){
            return;
        }
        //追踪当前节点和父亲节点
        BinaryNode *parent=nullptr;
        BinaryNode *current=t;
        //要找的元素不在当前位置，更新parent和crruent
        while (current !=nullptr && (current->element>x || current->element < x)){
            if(x<current->element){
                parent=current;
                current=current->left;
            }
            else {
                parent=current;
                current=current->right;
            }
        }
        //要删除的元素不在tree里面，不处理
        if(current==nullptr){
            return;
        }
        //此时要删除的节点就是current指向的节点
        //如果要删除的节点左右子结点均不为空，使用current的右节点代替当前节点
        if(current->left!=nullptr && current->right!=nullptr){
            BinaryNode *newroot=detachMin(current->right);
            newroot->left=current->left;
            newroot->right=current->right;
            current->left=nullptr;
            current->right=nullptr;
            //此时要删除的节点就是root，current指向root
            if(parent==nullptr){
                t=newroot;
            }
            //要删除的节点还有父节点，这时候要把newroot接到父节点上
            else if(x<parent->element){
                parent->left=newroot;
            }
            else{
                parent->right=newroot;
            }
        }
        //要删除的节点只有一个子节点
        else{
            //要删除parent的左节点
            if(x<parent->element){
                parent->left=(current->left != nullptr) ? current->left : current->right;
            }
            else{
                parent->right=(current->left != nullptr) ? current->left : current->right;
            }
            current->left=nullptr;
            current->right=nullptr;
        }   
        delete current;
    }  */

   

    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

        //增加一个平衡函数，能够将删除后的树变成平衡树
    static const int tolerance=1;

    int factor(BinaryNode *t){
        return height(t->left)-height(t->right);
    }

    void balance(BinaryNode *&t){
        if(t==nullptr){
            return;
        }
        int a=factor(t);
        //左边树更高
        if(a>tolerance){
            int b=factor(t->left);
            if(b>0){
                //左子树的左孩子更高
                singleRightRotation(t);
            }
            else{
                doubleLeftRotation(t);
            }
        }
        else if(-a>tolerance){
            int b=factor(t->right);
            if(b<0){
                singleLeftRotation(t);
            }
            else{
                doubleRightRotation(t);
            }
        }
        t->height=max(height(t->left),height(t->right))+1;
    }




    //左节点的左孩子引起失衡,右旋
    void singleRightRotation(BinaryNode *&t){
        BinaryNode *t1=t->left;
        t->left=t1->right;
        t1->right=t;
        t->height=max(height(t->left),height(t->right))+1;
        t1->height=max(height(t1->left),height(t1->right))+1;
        t=t1;
    }

    //右节点的右孩子引起失衡，左旋
    void singleLeftRotation(BinaryNode *&t){
        BinaryNode *t1=t->right;
        t->right=t1->left;
        t1->left=t;
        t->height=max(height(t->left),height(t->right))+1;
        t1->height=max(height(t1->left),height(t1->right))+1;
        t=t1;

    }

    //左节点的右孩子引起失衡
    void doubleLeftRotation(BinaryNode *&t){
        singleLeftRotation(t->left);
        singleRightRotation(t);
    }

    //右节点的左孩子引起失衡
    void doubleRightRotation(BinaryNode *&t){
        singleRightRotation(t->right);
        singleLeftRotation(t);
    }

    int height( BinaryNode *t ) const{
        if(t==nullptr){
            return 0;
        }
        else{
            return t->height;
        }
    }

    void updateHeight(BinaryNode *t){
        if(t==nullptr){
            return;
        }
        else{
            t->height=max(height(t->left),height(t->right));
        }
    }

};


#endif
