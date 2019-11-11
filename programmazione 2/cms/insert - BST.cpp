#include<cstdlib>
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;
template <class H> class Nodo
{
private:
    H *key;
    Nodo<H> *parent, *left, *right;

public:
    Nodo<H>(H key)
    {
        this->key=new H(key);
        parent = left = right = 0;
    }
    void setKey(H key)
    {
        this->key=key;
    }
    void setParent(Nodo<H>* parent)
    {
        this->parent=parent;
    }
    void setLeft(Nodo<H>* left)
    {
        this->left=left;
    }
    void setRight(Nodo<H>* right)
    {
        this->right=right;
    }

    H getKey(){return *key;}
    Nodo<H>* getParent(){return parent;}
    Nodo<H>* getLeft(){return left;}
    Nodo<H>* getRight(){return right;}

};

template <class F> class BST
{
private:
    Nodo<F> *root, *current;
    int n;

    void _inorder(Nodo<F> *x , ostream &out)
    {
        if(x)
        {
         _inorder(x->getLeft() , out);
         out<<x->getKey()<<" ";
         _inorder(x->getRight() , out);
        }
    }

    void _preorder(Nodo<F> *x , ostream &out)
    {
        if(x)
        {
         out<<x->getKey()<<" ";
         _preorder(x->getLeft() , out);
         _preorder(x->getRight() , out);
        }
    }

    void _postorder(Nodo<F> *x , ostream &out)
    {
        if(x)
        {
            _postorder(x->getLeft() , out);
            _postorder(x->getRight() , out);
            out<<x->getKey()<<" ";
        }
    }

public:

    BST()
    {
        root = current = NULL;
        n=0;
    }

    BST<F>* insert(F x)
    {
        Nodo<F> *node = root;
        Nodo<F> *p = NULL;

        while(node!=NULL)
        {
            p = node;
            if(x <= node->getKey())
            node=node->getLeft();
            else
            node=node->getRight();
        }
        Nodo<F> *newn = new Nodo<F>(x);
        n++;
        if(p==NULL)
        {
            root=newn;
            return this;
        }
        if(x <= p->getKey())
            p->setLeft(newn);
        else
            p->setRight(newn);
        newn->setParent(p);
        return this;
    }

    void inorder(ostream &out)
    {
        _inorder(root,out);
         out<<endl;
    }
    void preorder(ostream &out)
    {
        _preorder(root,out);
         out<<endl;
    }
    void postorder(ostream &out)
    {
        _postorder(root,out);
         out<<endl;
    }

};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    string tipo,ordinamento;

    for(int k=0;k<100;k++)
    {
        in>>tipo>>N>>ordinamento;

        if(tipo=="int")
        {
            BST<int>* a=new BST<int>();
            int x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            if(ordinamento=="inorder")
                a->inorder(out);
            else if(ordinamento=="preorder")
                a->preorder(out);
            else
                a->postorder(out);
        }

        else if(tipo=="double")
        {
            BST<double>* a=new BST<double>();
            double x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            if(ordinamento=="inorder")
                a->inorder(out);
            else if(ordinamento=="preorder")
                a->preorder(out);
            else
                a->postorder(out);
        }

        else if(tipo=="char")
        {
            BST<char>* a=new BST<char>();
            char x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            if(ordinamento=="inorder")
                a->inorder(out);
            else if(ordinamento=="preorder")
                a->preorder(out);
            else
                a->postorder(out);
        }

        else if(tipo=="bool")
        {
            BST<bool>* a=new BST<bool>();
            bool x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            if(ordinamento=="inorder")
                a->inorder(out);
            else if(ordinamento=="preorder")
                a->preorder(out);
            else
                a->postorder(out);
        }

    }

    in.close();
    out.close();
}
