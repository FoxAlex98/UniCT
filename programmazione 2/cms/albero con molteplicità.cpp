#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdlib>

using namespace std;

template<class H> class Nodo{
private:
    H *key;
    int mult;
    Nodo<H> *left, *right, *parent;
public:
    Nodo(H key)
    {
        this->key=new H(key);
        left = right = parent = NULL;
        mult=1;
    }

    void setKey(H key){this->key=new H(key);}
    void setLeft(Nodo<H> *left){this->left=left;}
    void setRight(Nodo<H> *right){this->right=right;}
    void setParent(Nodo<H> *parent){this->parent=parent;}
    void setMult(int n){mult+=n;}

    H getKey(){return *key;}
    Nodo<H>* getLeft(){return left;}
    Nodo<H>* getRight(){return right;}
    Nodo<H>* getParent(){return parent;}
    int getMult(){return mult;}
};

int max(int a, int b)
{
    return a>b?a:b;
}

template<class F> class BST{
private:
    int n;
    Nodo<F> *root , *current;

    _inorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            _inorder(x->getLeft() , out);
            for(int i=0;i<x->getMult();i++)
            out<<x->getKey()<<" ";
            _inorder(x->getRight() , out);
        }
    }

    _preorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            for(int i=0;i<x->getMult();i++)
            out<<x->getKey()<<" ";
            _preorder(x->getLeft() , out);
            _preorder(x->getRight() , out);
        }
    }

    _postorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            _postorder(x->getLeft() , out);
            _postorder(x->getRight() , out);
            for(int i=0;i<x->getMult();i++)
            out<<x->getKey()<<" ";
        }
    }

    Nodo<F>* _minimo(Nodo<F>* tmp)
    {
        while(tmp->getLeft()!=NULL) tmp=tmp->getLeft();
        return tmp;
    }

    Nodo<F>* _massimo(Nodo<F>* tmp)
    {
        while(tmp->getRight()!=NULL) tmp=tmp->getRight();
        return tmp;
    }

    Nodo<F>* _search(Nodo<F> *tmp, F x)
    {
        if(!tmp) return NULL;
        if(x==tmp->getKey()) return tmp;
        if(x<tmp->getKey())
            return _search(tmp->getLeft(), x);
            else
            return _search(tmp->getRight(), x);
    }

    int _altezza(Nodo<F> *tmp)
    {
        if(!tmp) return 0;
        return max(_altezza(tmp->getLeft()) , _altezza(tmp->getRight()))+1;
    }

    void _canc(Nodo<F> *r, F x)
    {
        Nodo<F> *tmp=_search(r, x);
        if(!tmp) return;

        if(tmp->getMult()!=1)
        {
            tmp->setMult(-1);
        }
        else
        {


        Nodo<F> *parent = tmp->getParent();
        if(!tmp->getLeft() || !tmp->getRight())
        {
            n--;
            Nodo<F> *figlio=tmp->getRight();
            if(tmp->getLeft()) figlio = tmp->getLeft();

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
            Nodo<F> *succ=_successore(tmp);
            tmp->setKey(succ->getKey());
            _canc(tmp->getRight(), succ->getKey());
        }
        return;

        }
    }

    Nodo<F>* _successore(Nodo<F>* tmp)
    {
        if(tmp->getRight())
            return _minimo(tmp->getRight());
        Nodo<F> *p = tmp->getParent();
        while(p!=NULL && p->getKey()<tmp->getKey())
            p=p->getParent();
        return p;
    }

    Nodo<F>* _predecessore(Nodo<F>* tmp)
    {
        if(tmp->getLeft())
            return _massimo(tmp->getLeft());
        Nodo<F> *p = tmp->getParent();
        while(p!=NULL && p->getKey()>tmp->getKey())
            p=p->getParent();
        return p;
    }

public:

    BST()
    {
        root = current = NULL;
    }

    BST<F>* insert(F x)
    {
        Nodo<F> *tmp=search(x);
        if(tmp)
            {
                tmp->setMult(1);
                return this;
            }
        Nodo<F> *node = root;
        Nodo<F> *p = NULL;
        while(node!=NULL)
        {
            p=node;
            if(x<=node->getKey()) node=node->getLeft();
            else node=node->getRight();
        }
        Nodo<F>* newn=new Nodo<F>(x);
        if(p==NULL)
        {
            root = newn;
            return this;
        }
        if(x<=p->getKey())
            p->setLeft(newn);
        else p->setRight(newn);
        newn->setParent(p);
        return this;
    }

    void canc(F x) {
      _canc(root, x);
    }

void inorder(ostream& out)
    {
        _inorder(root, out);
        out<<endl;
    }

    void preorder(ostream& out)
    {
        _preorder(root, out);
        out<<endl;
    }

    void postorder(ostream& out)
    {
        _postorder(root, out);
        out<<endl;
    }

    Nodo<F>* search(F x)
    {
        return _search(root,x);
    }

    int altezza()
    {
        return _altezza(root);
    }

    F predecessore(F x)
    {
        Nodo<F> *tmp=_search(root , x);
        if(tmp->getKey()==_minimo(root)->getKey())
            return -1;
        else
            return _predecessore(tmp)->getKey();
    }
};

int main()
{
 ifstream in("input.txt");
 ofstream out("output.txt");

 int N;
 string s,tipo,ordinamento;

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
