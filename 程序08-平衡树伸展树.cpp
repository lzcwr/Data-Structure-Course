#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
const int maxm = 1e6 + 5;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;

template <typename T>
struct AVLTreeNode
{
    AVLTreeNode(T value, AVLTreeNode<T>*l, AVLTreeNode<T>*r) :key(value), lchild(l), rchild(r){}

    T key;
    int height;
    AVLTreeNode<T>* lchild;
    AVLTreeNode<T>* rchild;
};

template<typename T>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void print();
    void destory();

    void insert(T key);
    void remove(T key);

    AVLTreeNode<T>* search_recurse(T key);
    AVLTreeNode<T>* search_iterator(T key);
    T minimum();
    T maximum();

    int height();

private:
    AVLTreeNode<T>* root;

private:
    void print(AVLTreeNode<T>* pnode,T key, int direction) const;
    void destory(AVLTreeNode<T>* & pnode);

    int height(AVLTreeNode<T>* pnode) ;
    int max(int a, int b);

    AVLTreeNode<T>* insert(AVLTreeNode<T>* &pnode, T key);
    AVLTreeNode<T>* remove(AVLTreeNode<T>* & pnode, T key);

    AVLTreeNode<T>* minimum(AVLTreeNode<T>*pnode) const;
    AVLTreeNode<T>* maximum(AVLTreeNode<T>*pnode) const;

    AVLTreeNode<T>* search_recurse(AVLTreeNode<T>* pnode, T key) const;
    AVLTreeNode<T>* search_iterator(AVLTreeNode<T>* pnode, T key) const;

    AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* pnode);
    AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* pnode);
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* pnode);
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* pnode);

};

/*构造函数*/
template <typename T>
AVLTree<T>::AVLTree() :root(nullptr){};

/*析构函数*/
template <typename T>
AVLTree<T>::~AVLTree()
{
    destory(root);
}

/*返回两者中的较大者*/
template<typename T>
int AVLTree<T>::max(int a, int b)
{
    return a > b ? a : b;
};

/*返回树中最大节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* pnode)const
{
    if(pnode != nullptr)
    {
        while (pnode -> rchild != nullptr)
            pnode = pnode -> rchild;
        return pnode;
    }
    return nullptr;
};

template<typename T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* presult = maximum(root);
    if(presult != nullptr)
        return presult -> key;
};

/*返回树中最小节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* pnode)const
{
    if(pnode != nullptr)
    {
        while (pnode -> lchild != nullptr)
            pnode = pnode -> lchild;
        return pnode;
    }
    return nullptr;
};

template<typename T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* presult = minimum(root);
    if(presult != nullptr)
        return presult -> key;
};

/*返回一棵树的高度*/
template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* pnode)
{
    if(pnode != nullptr)
    {
        return pnode -> height;
    }
    return 0;
};

template <typename T>
int AVLTree<T>::height()
{
    return height(root);
};

/*左旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* proot)
{
    AVLTreeNode<T>* prchild = proot -> rchild;
    proot -> rchild = prchild -> lchild;
    prchild -> lchild = proot;

    proot -> height = max(height(proot -> lchild),height(proot -> rchild))+1;
    prchild -> height = max(height(prchild -> lchild), height(prchild -> rchild)) + 1;

    return prchild;
};

/*右旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename  T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>*proot)
{
    AVLTreeNode<T>* plchild = proot -> lchild;
    proot -> lchild = plchild -> rchild;
    plchild -> rchild = proot;

    proot -> height = max(height(proot -> lchild), height(proot -> rchild)) + 1;
    plchild -> height = max(height(plchild -> lchild), height(plchild -> rchild)) + 1;

    return plchild;
};

/*先左后右做旋转*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* proot)
{
    proot -> lchild= leftRotation(proot -> lchild);
    return rightRotation(proot);
};
/*先右旋再左旋*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* proot)
{
    proot -> rchild = rightRotation(proot -> rchild);
    return leftRotation(proot);
};

/*插入操作*/
/*递归地进行插入*/
/*返回插入后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &pnode, T key)
{
    if(pnode == nullptr)
    {
        pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
    }
    else if(key > pnode -> key)
    {
        pnode -> rchild = insert(pnode -> rchild, key);
        if(height(pnode -> rchild) - height(pnode -> lchild) == 2)
        {
            if(key > pnode -> rchild -> key)
                pnode=leftRotation(pnode);
            else if(key < pnode -> rchild -> key)
                pnode=rightLeftRotation(pnode);
        }
    }
    else if(key < pnode -> key)
    {
        pnode -> lchild = insert(pnode -> lchild, key);
        if(height(pnode -> lchild) - height(pnode -> rchild) == 2)
        {
            if(key < pnode -> lchild -> key)
                pnode = rightRotation(pnode);
            else if(key>pnode -> lchild -> key)
                pnode = leftRightRotation(pnode);
        }
    }
    pnode -> height = max(height(pnode -> lchild), height(pnode -> rchild)) + 1;
    return pnode;
};

template <typename T>
void AVLTree<T>::insert(T key)
{
    insert(root, key);
};

/*递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(T key)
{
    return search_recurse(root,key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(AVLTreeNode<T>* pnode, T key) const
{
    if(pnode != nullptr)
    {
        if(key == pnode -> key)
            return pnode;
        if(key > pnode -> key)
            return search_recurse(pnode -> rchild,key);
        else
            return search_recurse(pnode -> lchild,key);
    }
    return nullptr;
};

/*非递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(T key)
{
    return search_iterator(root, key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(AVLTreeNode<T>* pnode, T key) const
{
    while (pnode != nullptr)
    {
        if(pnode -> key == key)
            return pnode;
        else if(key > pnode -> key)
            pnode = pnode -> rchild;
        else
            pnode = pnode -> lchild;
    }
    return nullptr;
};

/*删除指定元素*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* & pnode, T key)
{
    if(pnode != nullptr)
    {
        if(key == pnode -> key)
        {
            if(pnode -> lchild != nullptr&&pnode -> rchild != nullptr)
            {
                if(height(pnode -> lchild) > height(pnode -> rchild))
                {
                    AVLTreeNode<T>* ppre = maximum(pnode -> lchild);
                    pnode -> key = ppre -> key;
                    pnode -> lchild = remove(pnode -> lchild, ppre -> key);
                }
                else
                {
                    AVLTreeNode<T>* psuc = minimum(pnode -> rchild);
                    pnode -> key = psuc -> key;
                    pnode -> rchild = remove(pnode -> rchild, psuc -> key);
                }
            }
            else
            {
                AVLTreeNode<T> * ptemp = pnode;
                if(pnode -> lchild != nullptr)
                    pnode = pnode -> lchild;
                else if(pnode -> rchild != nullptr)
                    pnode = pnode -> rchild;
                delete ptemp;
                return nullptr;
            }
        }
        else if(key > pnode -> key)
        {
            pnode -> rchild =  remove(pnode -> rchild, key);
            if(height(pnode -> lchild) - height(pnode -> rchild) == 2)
            {
                if(height(pnode -> lchild -> rchild)>height(pnode -> lchild -> lchild))
                    pnode = leftRightRotation(pnode);
                else
                    pnode = rightRotation(pnode);
            }
        }
        else if(key < pnode -> key)
        {
            pnode -> lchild= remove(pnode -> lchild, key);
            if(height(pnode -> rchild) - height(pnode -> lchild) == 2)
            {
                if(height(pnode -> rchild -> lchild)>height(pnode -> rchild -> rchild))
                    pnode = rightLeftRotation(pnode);
                else
                    pnode = leftRotation(pnode);
            }
        }
        return pnode;
    }
    return nullptr;
};
template<typename T>
void AVLTree<T>::remove(T key)
{
    root = remove(root, key);
};


/*销毁AVL树*/
template<typename T>
void AVLTree<T>::destory(AVLTreeNode<T>* & pnode)
{
    if(pnode != nullptr)
    {
        destory(pnode -> lchild);
        destory(pnode -> rchild);
        delete pnode;
        pnode = nullptr;
    }
};
template<typename T>
void AVLTree<T>::destory()
{
    destory(root);
}

void solve()
{
    AVLTree<int> a;
    for (int i = 0; i < 10; i++)
        a.insert(i);
    cout << "树高：" << a.height() << endl;
  
    cout << "删除元素10"<<endl;
    a.remove(10);
 
    AVLTreeNode<int>* b = a.search_iterator(10);
 
    if (b != nullptr) cout << b->key;
    else cout << "无此元素" << endl;
    system("pause");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();

#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif

    return 0;
}
