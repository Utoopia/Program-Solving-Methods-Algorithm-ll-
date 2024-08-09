#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define endl '\n'
using namespace std;

ifstream fin("rbt.inp");
ofstream fout("rbt.out");

enum Color
{
    RED,
    BLACK
};
struct node
{
    int key;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    Color color = BLACK;
};
typedef node* Node;
class RBTREE
{
private:
    Node root;     
    Node branch; 

    Node IsKey(int key)
    {
        Node t = root;
        Node parent = NULL;

        while (t != NULL && t->key != key)
        {
            parent = t;
            t = (key < parent->key) ? parent->left : parent->right;
        }
        return t;
    }

    void Insert(int key)
    {
        Node x = this->root, y = nullptr;
        Node z = new node();
        z->key = key;
        z->color = RED;
        z->parent = nullptr;
        z->left = branch;
        z->right = branch;

        while (x != branch)
        {
            y = x;
            if (x->key < key)
                x = x->right;
            else
                x = x->left;
        }

        z->parent = y;

        if (y == nullptr)
            root = z;
        else if (z->key > y->key)
            y->right = z;
        else
            y->left = z;

        if (z->parent == nullptr)
        {
            z->color = BLACK;
            return;
        }

        if (z->parent->parent == nullptr)
        {
            return;
        }
        InsertCase(z);

        return;
    }

    void InsertCase(Node z)
    {
        while (z != root && z->parent->color == RED)
        {
            Node grandparent = z->parent->parent;
            Node uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
            bool side = (z->parent == grandparent->left) ? true : false;

            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }

            else
            {
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                side ? RotateRight(grandparent) : RotateLeft(grandparent);
            }
        }
        root->color = BLACK;
    }

    bool Delete(int key)
    {
        Node z = IsKey(key);
        if (!z)
            return false;
        else
        {
            Node x, y;
            Color OriginalColor = z->color;

            if (z->left == branch)
            {
                x = z->right;
                tp(z, z->right);
            }
            else if (z->right == branch)
            {
                x = z->left;
                tp(z, z->left);
            }
            else
            {
                y = tree_minimum(z->right);
                OriginalColor = y->color;
                x = y->right;

                if (y->parent == z)
                {                  
                    x->parent = y;
                }
                else
                {
                    tp(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                tp(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (OriginalColor == BLACK)
            {
                DelCase(x);
            }
        }
        return true;
    }

    void DelCase(Node x)
    {
        Node s;
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;

                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateLeft(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        RotateRight(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    RotateLeft(x->parent);
                    x = root;
                }
            }

            else
            {
                s = x->parent->left;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateRight(x->parent);
                    s = x->parent->left;
                }

                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        RotateLeft(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    RotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
        root->color = BLACK;
    }

    void tp(Node u, Node v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }
    void RotateLeft(Node x)
    {
        Node y;

        y = x->right;
        x->right = y->left;
        if (y->left != branch) { y->left->parent = x; }
        y->parent = x->parent;

        if (!x->parent) { root = y; }
        else if (x == x->parent->left) { x->parent->left = y; }
        else { x->parent->right = y; }
        x->parent = y;
        y->left = x;
    }
    void RotateRight(Node y)
    {
        Node x;

        x = y->left;
        y->left = x->right;
        if (x->right != branch) { x->right->parent = y; }
        x->parent = y->parent;

        if (!y->parent) { root = x; }
        else if (y == y->parent->left) { y->parent->left = x; }
        else { y->parent->right = x; }
        y->parent = x;
        x->right = y;
    }

    void searchKey(Node root, int key)
    {
        if (root != branch)
        {
            if (key == root->key) {
                string sColor = (root->color == RED) ? "RED" : "BLACK";
                fout << "color(" << root->key << "): " << sColor << endl;
                return;
            }

            if (key < root->key) { searchKey(root->left, key); }
            else { searchKey(root->right, key); }
        }
    }

public:
    RBTREE()
    {
        branch = new node;
        branch->color = BLACK;
        branch->left = nullptr;
        branch->right = nullptr;
        branch->parent = nullptr;
        root = branch;
    }

    Node tree_minimum(Node x)
    {
        while (x->left != branch)
        {
            x = x->left;
        }
        return x;
    }
    
    Node tree_maximum(Node x)
    {
        while (x->right != branch)
        {
            x = x->right;
        }
        return x;
    }

    void Start()
    {
        char c;
        int i;

        while (true)
        {
            fin >> c >> i;
            if (i < 0) { return; }
            else {
                if (c == 'i') { Insert(i); }
                else if (c == 'd') { Delete(i); }
                else if (c == 'c') { searchKey(root, i); }
            }
        }
    }
};

int main()
{
    RBTREE tree;
    tree.Start();

    return 0;
}