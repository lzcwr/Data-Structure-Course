#include <bits/stdc++.h>
#ifdef __WINDOWS_
#include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);

const int maxn = 50010;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;
const int N = 200005;
const int INF = 1 << 28;

template<typename T>
class BSTNode
{
public:
    T _key;
    BSTNode *_lchild;
    BSTNode *_rchild;
    BSTNode *_parent;

    BSTNode(T key, BSTNode *lchild, BSTNode *rchild, BSTNode *parent):
        _key(key), _lchild(lchild), _rchild(rchild), _parent(parent) {};
};

template<typename T>
class BSTree
{
private:
    BSTNode<T> *_Root ;
public:
    BSTree():_Root(NULL) {};
    ~BSTree() {};
    void insert (T key);

    BSTNode<T>* search (T key) ;
    void preOrder() ;
    void inOrder() ;
    void postOrder() ;

    BSTNode<T>* minimumNode();
    BSTNode<T>* maximumNode ();

    T minimumKey();
    T maximumKey();
    void print();
    void remove(T key);
    BSTNode<T>* predecessor(BSTNode<T>* x);
    BSTNode<T>* sucessor(BSTNode<T>* x);
    void destory ();

private:
    void insert(BSTNode<T>* &tree, BSTNode<T>* z);
    BSTNode<T>* search(BSTNode<T>* &tree, T key) const;
    void preOrder(BSTNode<T>*&tree) const;
    void inOrder(BSTNode<T>*&tree) const;
    void postOrder(BSTNode<T>*&tree) const;
    BSTNode<T>* minimumNode(BSTNode<T> *&tree);
    BSTNode<T>* maximumNode (BSTNode<T> *&tree);
    void print(BSTNode<T>*& tree);
    BSTNode<T>* remove(BSTNode<T>* &tree, BSTNode<T> *z);
    void destory(BSTNode<T>*& tree);
};

template<typename T>
void BSTree<T> ::insert(BSTNode<T>* &tree, BSTNode<T>* z)
{
    BSTNode<T>* parent = NULL;
    BSTNode<T>* temp = tree;
    while(temp != NULL)
    {
        parent= temp;
        if(z -> _key>temp -> _key) temp= temp -> _rchild;
        else temp=temp -> _lchild;
    }
    z -> _parent = parent;
    if(parent == NULL) tree = z;
    else if(z -> _key>parent -> _key) parent -> _rchild = z;
    else parent -> _lchild = z;
}
template <typename T>
void BSTree<T>::insert(T key)
{
    BSTNode<T>* z= new BSTNode<T>(key, NULL, NULL, NULL);
    if(!z) return ;
    insert(_Root, z);
}

template <typename T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* &tree, T key) const
{
    BSTNode<T>* temp = tree;
    while(temp != NULL)
    {
        if(temp -> _key == key) return temp;
        else if(temp -> _key>key) temp = temp -> _lchild;
        else temp = temp -> _rchild;
    }
    return NULL;
}
template <typename T>
BSTNode<T> * BSTree<T>::search(T key)
{
    return search(_Root, key);
}

template<typename T>
void BSTree<T>::preOrder(BSTNode<T>*&tree) const
{
    if(tree)
    {
        cout << tree -> _key << " ";
        preOrder(tree -> _lchild);
        preOrder(tree -> _rchild);
    }
}
template <typename T>
void BSTree<T>::inOrder(BSTNode<T>*&tree) const
{
    if(tree)
    {
        inOrder(tree -> _lchild);
        cout << tree -> _key << " ";
        inOrder(tree -> _rchild);
    }
}
template <typename T>
void BSTree<T>::postOrder(BSTNode<T>*&tree) const
{
    if(tree)
    {
        postOrder(tree -> _lchild);
        postOrder(tree -> _rchild);
        cout << tree -> _key << " ";
    }
}

template<typename T>
void BSTree<T>::preOrder()
{
    preOrder(_Root);
}
template<typename T>
void BSTree<T>::inOrder()
{
    inOrder(_Root);
}
template<typename T>
void BSTree<T>::postOrder()
{
    postOrder(_Root);
}

template <typename T>
BSTNode<T>* BSTree<T>::minimumNode(BSTNode<T>*&tree)
{
    BSTNode<T>* temp = tree;
    while(temp -> _lchild)
        temp= temp -> _lchild;
    return temp;
}
template<typename T>
BSTNode<T>* BSTree<T>::minimumNode()
{
    return minimumNode(_Root);
}

template<typename T>
BSTNode<T>* BSTree<T>::maximumNode(BSTNode<T>* &tree)
{
    BSTNode<T>* temp=tree;
    while(temp -> _rchild)
        temp= temp -> _rchild;
    return temp;
}
template<typename T>
BSTNode<T>* BSTree<T>::maximumNode()
{
    return maximumNode(_Root);
}

template<typename T>
T BSTree<T>::minimumKey()
{
    BSTNode<T> *temp = minimumNode(_Root);
    return temp -> _key;
}
template<typename T>
T BSTree<T>::maximumKey()
{
    BSTNode<T> *temp = maximumNode(_Root);
    return temp -> _key;
}

template<typename T>
void BSTree<T>::print(BSTNode<T>*& tree)
{
    if(tree)
    {
        // if(tree -> _lchild)
        // 	cout << "Node --" << tree -> _key << "-- has left child --" << tree -> _lchild -> _key << endl;
        // else
        // 	cout << "Node --" << tree -> _key << "-- has no left child" << endl;
        // if(tree -> _rchild)
        // 	cout << "Node --" << tree -> _key << "-- has right child --" << tree -> _rchild -> _key << endl;
        // else
        // 	cout << "Node --" << tree -> _key << "-- has no right child" << endl;
        cout << tree -> _key << '(';
        print(tree -> _lchild);
        printf(",");
        print(tree -> _rchild);
        printf(")");
    }
    else printf("#");
}
template<typename T>
void BSTree<T>::print()
{
    print(_Root);
}

template <typename T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T>* x)
{
    if(x -> _key == minimumNode(_Root) -> _key) return NULL;
    BSTNode <T> * y = NULL;
    y = search(_Root, x -> _key);
    if(y == NULL) return NULL;
    if(y -> _lchild != NULL)
        return maximumNode(y -> _lchild);
    BSTNode<T>* parent = y -> _parent;
    if(parent -> _rchild == y)
        return parent;
    while(parent != NULL && parent -> _rchild == NULL)
        parent=parent -> _parent;
    return parent;
}

template <typename T>
BSTNode<T>* BSTree<T>::sucessor(BSTNode<T>* x)
{
    if(x -> _key == maximumNode(_Root) -> _key)
        return NULL;
    BSTNode<T>* y = NULL;
    y = search(_Root, x -> _key);
    if(!y) return NULL;
    if(y -> _rchild != NULL)
        return minimumNode(y -> _rchild);
    BSTNode <T>* parent = y -> _parent;
    if(y -> _parent -> _lchild == y)
        return parent;
    while(parent != NULL)
    {
        if(parent -> _lchild != NULL && parent != y -> _parent)
            return parent;
        parent=parent -> _parent;
    }
    return NULL;
}

template <class T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>* &tree, BSTNode<T> *z)
{
    BSTNode<T> *x=NULL;
    BSTNode<T> *y=NULL;
    if ((z -> _lchild == NULL) || (z -> _rchild == NULL) ) y = z;
    else y = sucessor(z);
    if (y -> _lchild != NULL) x = y -> _lchild;
    else x = y -> _rchild;
    if (x != NULL) x -> _parent = y -> _parent;
    if (y -> _parent == NULL) tree = x;
    else if (y == y -> _parent -> _lchild) y -> _parent -> _lchild = x;
    else y -> _parent -> _rchild= x;
    if (y != z) z -> _key = y -> _key;
    return y;
}
template<typename T>
void BSTree<T>::remove(T key)
{
    BSTNode<T> *z, *node;
    if ((z = search(_Root, key)) != NULL)
        if ( (node = remove(_Root, z)) != NULL)
            delete node;
}

template<typename T>
void BSTree<T>::destory(BSTNode<T>*& tree)
{
    if(tree -> _lchild != NULL) destory(tree -> _lchild);
    if(tree -> _rchild != NULL) destory(tree -> _rchild);
    if(tree -> _lchild == NULL && tree -> _rchild == NULL)
    {
        delete(tree);
        tree = NULL;
    }
}
template<typename T>
void BSTree<T>::destory()
{
    destory(_Root);
}

void solve()
{
    BSTree<char> s;
    char a;
    cout << "Enter Your BST Node: " << endl;
    while(cin >> a) s.insert(a);
    cin.clear();

    cout << "Your BST: " << endl;
    s.print();
    printf("\n");
    // cout << "Enter Your Query: " << endl;
    // while(cin >> a)
    // {
    // 	BSTNode<char>* findnode = s.search(a);
    // 	if(!findnode)
    // 	{
    // 		cout << "Invalid Input" << endl;
    // 		s.insert(a);
    // 		cout << a << "has been inserted, Your BST：" << endl;
    // 		s.inOrder();
    // 		cout << endl;
    // 	}
    // 	else cout << findnode -> _key << "Success" << endl;
    // }
    // cin.clear();
    // cout << "Please Enter you query to get it's PreNode: " << endl;
    // BSTNode<char>* findPreNode = new BSTNode<char>(1, NULL, NULL, NULL);
    // while(cin >> findPreNode -> _key)
    // {
    // 	BSTNode<char>* preNode ;
    // 	if((preNode = s.predecessor(findPreNode)) != NULL)
    // 	{
    // 		cout << "PreNode: ";
    // 		cout << preNode -> _key << endl;
    // 	}
    // 	else cout << "No PreNode" << endl;
    // 	if((preNode = s.sucessor(findPreNode)) != NULL)
    // 	{
    // 		cout << "SuccNode: ";
    // 		cout << preNode -> _key << endl;
    // 	}
    // 	else cout << "No SuccNode" << endl;
    // }
    // cin.clear();
    cout << "Enter the Node you want to Del: " << endl;
    while(cin >> a)
    {
        s.remove(a);
        cout << "Your BST after Delete: " << endl;
        s.print();
        printf("\n");
    }
    cin.clear();
    // BSTNode<char>* maxNode = s.minimumNode();
    // if(!maxNode)
    // 	cout << "MinNode: " << maxNode -> _key << endl;
    // BSTNode<char>* minNode = s.maximumNode();
    // if(!minNode)
    // 	cout << "MaxNode: " << minNode -> _key << endl;
    cout << "Your BST has been destoryed." << endl;
    s.destory();
    s.inOrder();
    system("pause");
}

int main()
{
// #ifndef ONLINE_JUDGE
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
// #endif

    solve();

// #ifndef ONLINE_JUDGE
//  fclose(stdin);
//  fclose(stdout);
//  system("out.txt");
// #endif

    return 0;
}
