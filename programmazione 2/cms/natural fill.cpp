#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdlib>

using namespace std;

template<class H> class Nodo{
private:
    H *key;
    Nodo<H> *left, *right, *parent;
public:
    Nodo(H key)
    {
        this->key=new H(key);
        left = right = parent = NULL;
    }

    void setKey(H key){this->key=new H(key);}
    void setLeft(Nodo<H> *left){this->left=left;}
    void setRight(Nodo<H> *right){this->right=right;}
    void setParent(Nodo<H> *parent){this->parent=parent;}

    H getKey(){return *key;}
    Nodo<H>* getLeft(){return left;}
    Nodo<H>* getRight(){return right;}
    Nodo<H>* getParent(){return parent;}
};

template <class H> class Queue{
    private:
        int top,head,len;
        H *v;
    public:
        Queue(int len)
        {
            this->len=len;
            v=new H[len];
            top = 0;
            head = len;
        }

        void enqueue(H x)
        {
            v[top++]=x;
        }

        void dequeue()
		{
			for(int i = 0; i < top-1; i++)
			{ v[i] = v[i+1]; }
			top--;
		}

        H primo()//stampa il primo elemento della coda
        {
            return v[0];
        }

        void stampa()
        {
            for(int i=0;i<top;i++)
                cout<<v[i]<<" ";
                cout<<endl;
        }
};

template<class F> class BST{
private:
    int n;
    Nodo<F> *root , *current;

    void _postorder(Nodo<F>* x, ostream& out)
    {
        if(x)
        {
            _postorder(x->getLeft() , out);
            _postorder(x->getRight() , out);
            out<<x->getKey()<<" ";
        }
    }

    Nodo<F>* _min(Nodo<F>* tmp)
    {
        while(tmp->getLeft()!=NULL) tmp=tmp->getLeft();
        return tmp;
    }

    void _naturalfill(Nodo<F>* x, Queue<F> & q)
    {
        if(x)
        {
            _naturalfill(x->getLeft() , q);
             x->setKey(q.primo());
             q.dequeue();
            _naturalfill(x->getRight() , q);
        }
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
            p=node;
            if(x<=node->getKey()) node=node->getLeft();
            else node=node->getRight();
        }
        Nodo<F>* newn=new Nodo<F>(x);
        n++;
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

    void postorder(ostream& out)
    {
        _postorder(root, out);
        out<<endl;
    }

	void naturalfill(Queue<F> & q)
    {
        _naturalfill(root , q);
    }
};

int main()
{
 ifstream in("input.txt");
 ofstream out("output.txt");

     int N;
    string tipo;

    for(int k=0;k<100;k++)
    {
        in>>tipo>>N;

        if(tipo=="int")
        {
            BST<int>* a=new BST<int>();
            Queue<int>* q=new Queue<int>(N);
            int x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            for(int i=0;i<N;i++)
            {
                in>>x;
                q->enqueue(x);
            }
                a->naturalfill(*q);
                a->postorder(out);
        }

        if(tipo=="double")
        {
            BST<double>* a=new BST<double>();
            Queue<double>* q=new Queue<double>(N);
            double x;
            for(int i=0;i<N;i++)
            {
                in>>x;
                a->insert(x);
            }
            for(int i=0;i<N;i++)
            {
                in>>x;
                q->enqueue(x);
            }
                a->naturalfill(*q);
                a->postorder(out);
        }

    }

 in.close();
 out.close();
}
