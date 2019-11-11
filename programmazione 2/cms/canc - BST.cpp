#include<cstdlib>
#include<cstring>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

template <class H> class Nodo{
private:
    H *key;
    Nodo<H> *parent, *left, *right;
public:
    Nodo(H key)
    {
        this->key=new H(key);
        parent = left = right = NULL;
    }
    void setKey(H key){this->key=new H(key);}
    void setLeft(Nodo<H>* left){this->left=left;}
    void setRight(Nodo<H>* right){this->right=right;}
    void setParent(Nodo<H>* parent){this->parent=parent;}
    H getKey(){return *key;}
    Nodo<H>* getLeft(){return left;}
    Nodo<H>* getRight(){return right;}
    Nodo<H>* getParent(){return parent;}
};

template <class F> class BST{
private:
    Nodo<F> *root, *current;
    int n;

    Nodo<F>* _rsearch(Nodo<F>* tmp, F x)
    {
        if(!tmp) return NULL;
        if(tmp->getKey()==x)
            return tmp;
        else
        {
            if(x <= tmp->getKey())
                return _rsearch(tmp->getLeft(), x);
            else
                return _rsearch(tmp->getRight(), x);
        }
    }

    Nodo<F>* _minimo(Nodo<F> *tmp)
    {
        while(tmp->getLeft()!=NULL)
            tmp=tmp->getLeft();
        return tmp;
    }

    Nodo<F>* _massimo(Nodo<F> *tmp)
    {
        while(tmp->getRight()!=NULL)
            tmp=tmp->getRight();
        return tmp;
    }

    void _inorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
         _inorder(x->getLeft(), out);
         out<<x->getKey()<<" ";
         _inorder(x->getRight(), out);
        }
    }

    void _preorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            out<<x->getKey()<<" ";
            _preorder(x->getLeft(), out);
            _preorder(x->getRight(), out);
        }
    }

    void _postorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            _postorder(x->getLeft(), out);
            _postorder(x->getRight(), out);
            out<<x->getKey()<<" ";
        }
    }

    Nodo<F>* _successore(Nodo<F> *tmp)
    {
     if(tmp->getRight())
     return _minimo(tmp->getRight());
     Nodo<F> *p = tmp->getParent();
     while(p!=NULL && p->getKey()<tmp->getKey())
        p=p->getParent();
     return p;
    }


    void _canc(Nodo<F>* r, F x)
    {
        Nodo<F> *tmp = _rsearch(r,x);
        if(!tmp) return;
        Nodo<F> *parent = tmp->getParent();
        if(!tmp->getLeft() || !tmp->getRight())
        {
            n--;
            Nodo<F> *figlio = tmp->getRight();
            if(tmp->getLeft()) figlio=tmp->getLeft();

            if(!parent) root=figlio;
            else
            {
                if(tmp==parent->getLeft()) parent->setLeft(figlio);
                else parent->setRight(figlio);
            }
            if(figlio) figlio->setParent(parent);
        }
        else
        {
            Nodo<F> *succ = _successore(tmp);
            tmp->setKey(succ->getKey());
            _canc(tmp->getRight(), succ->getKey());
        }
        return;
    }

public:
    BST()
    {
        n=0;
        root = current = NULL;
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

    void inorder(ostream& out)
    {
        _inorder(root,out);
        out<<endl;
    }

    void preorder(ostream& out)
    {
        _preorder(root,out);
        out<<endl;
    }

    void postorder(ostream& out)
    {
        _postorder(root,out);
        out<<endl;
    }

    void canc(F x)
    {
        _canc(root, x);
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    string tipo,ordinamento,s;

    for(int k=0;k<100;k++)
    {
        in>>tipo>>N>>ordinamento;

        if(tipo=="int")
        {
            int x;
            BST<int> *b=new BST<int>();
            for(int i=0;i<N;i++)
            {
                in>>s;
                if(s.substr(0,3)=="ins")
                {
                    stringstream ss(s.substr(4));
                    ss>>x;
                    b->insert(x);
                }
                else
                {
                    stringstream ss(s.substr(5));
                    ss>>x;
                    b->canc(x);
                }
            }

            if(ordinamento=="inorder")
                b->inorder(out);
            else if(ordinamento=="preorder")
                b->preorder(out);
            else
                b->postorder(out);

        }

        else if(tipo=="bool")
        {
            bool x;
            BST<bool> *b=new BST<bool>();
            for(int i=0;i<N;i++)
            {
                in>>s;
                if(s.substr(0,3)=="ins")
                {
                    stringstream ss(s.substr(4));
                    ss>>x;
                    b->insert(x);
                }
                else
                {
                    stringstream ss(s.substr(5));
                    ss>>x;
                    b->canc(x);
                }
            }

            if(ordinamento=="inorder")
                b->inorder(out);
            else if(ordinamento=="preorder")
                b->preorder(out);
            else
                b->postorder(out);

        }

        else if(tipo=="double")
        {
            double x;
            BST<double> *b=new BST<double>();
            for(int i=0;i<N;i++)
            {
                in>>s;
                if(s.substr(0,3)=="ins")
                {
                    stringstream ss(s.substr(4));
                    ss>>x;
                    b->insert(x);
                }
                else
                {
                    stringstream ss(s.substr(5));
                    ss>>x;
                    b->canc(x);
                }
            }

            if(ordinamento=="inorder")
                b->inorder(out);
            else if(ordinamento=="preorder")
                b->preorder(out);
            else
                b->postorder(out);

        }

        else if(tipo=="char")
        {
            char x;
            BST<char> *b=new BST<char>();
            for(int i=0;i<N;i++)
            {
                in>>s;
                if(s.substr(0,3)=="ins")
                {
                    stringstream ss(s.substr(4));
                    ss>>x;
                    b->insert(x);
                }
                else
                {
                    stringstream ss(s.substr(5));
                    ss>>x;
                    b->canc(x);
                }
            }

            if(ordinamento=="inorder")
                b->inorder(out);
            else if(ordinamento=="preorder")
                b->preorder(out);
            else
                b->postorder(out);

        }
    }

    in.close();
    out.close();
}
