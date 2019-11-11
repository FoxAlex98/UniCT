#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

template<class T> class Nodo{
private:
	T key;
	Nodo *left,*right,*parent;
public:
	Nodo(T key)
	{
		this->key=key;
		left=right=parent=NULL;
	}

	void setKey(T key){this->key=key;}
	void setLeft(Nodo* left){this->left=left;}
	void setRight(Nodo* right){this->right=right;}
	void setParent(Nodo* parent){this->parent=parent;}

	T getKey(){return key;}
	Nodo* getLeft(){return left;}
	Nodo* getRight(){return right;}
	Nodo* getParent(){return parent;}

};


int max(int a, int b){return (a>b)?a:b;}

template<class H> class BST{
private:
	Nodo<H>* root;
	int cont=0;


void _preorder(Nodo<H> *tmp, ostream& out)
	{
		if(tmp)
		{
			out<<tmp->getKey()<<" ";
			_preorder(tmp->getLeft(), out);
			_preorder(tmp->getRight(), out);
		}
	}

	void _inorder(Nodo<H> *tmp, ostream& out)
	{
		if(tmp)
		{
			_inorder(tmp->getLeft(), out);
			out<<tmp->getKey()<<" ";
			_inorder(tmp->getRight(), out);
		}
	}

	void _postorder(Nodo<H> *tmp, ostream& out)
	{
		if(tmp)
		{
			_postorder(tmp->getLeft(), out);
			_postorder(tmp->getRight(), out);
			out<<tmp->getKey()<<" ";
		}
	}

	int _altezza(Nodo<H>* tmp)
	{
		if(!tmp) return 0;
		return max(_altezza(tmp->getLeft()),_altezza(tmp->getRight()))+1;
	}

	Nodo<H>* rsearch(Nodo<H>* tmp, H key)
	{
		if(!tmp) return NULL;
		if(tmp->getKey()==key) return tmp;
		else
			{
				if(key<=tmp->getKey())
				return rsearch(tmp->getLeft(), key);
				else
				return rsearch(tmp->getRight(), key);
			}
	}

int _livello(H key)
	{
		int c=0;
		Nodo<H> *tmp=rsearch(root,key);
		if(!tmp) return -1;		
		while(tmp!=root)
			{
				c++;
				tmp=tmp->getParent();
			}
		return c;
	}

Nodo<H>* _minimo(Nodo<H> *tmp)
{
	while(tmp->getLeft())
		tmp=tmp->getLeft();
	return tmp;
}

Nodo<H>* _massimo(Nodo<H> *tmp)
{
	while(tmp->getRight())
		tmp=tmp->getRight();
	return tmp;
}

Nodo<H>* succ(Nodo<H>* tmp)
{
	if(tmp->getRight())
		return _minimo(tmp->getRight());
	Nodo<H> *p=tmp->getParent();
	while(p!=NULL && p->getKey()<tmp->getKey())
			p=p->getParent();
	return p;
}

Nodo<H>* prec(Nodo<H> *tmp)
{
	if(tmp->getLeft())
		return _massimo(tmp->getLeft());
	Nodo<H> *p=tmp->getParent();
	while(p!=NULL && p->getKey()>tmp->getKey())
			p=p->getParent();
	return p;
}

void _canc(Nodo<H>* r,H key)
{
	Nodo<H> *tmp=rsearch(r,key);
	if(!tmp)
	{
		cout<<"il nodo non esiste "<<endl;
		return;
	}
	
	Nodo<H> *p=tmp->getParent();
	if(!tmp->getLeft() || !tmp->getRight())
	{
		Nodo<H> *figlio=tmp->getLeft();
		if(tmp->getRight())
		figlio=tmp->getRight();

		if(p==NULL)
		{
			root=figlio;
			return;
		}

		if(p->getLeft()==tmp)
			p->setLeft(figlio);
		else
			p->setRight(figlio);
		
		if(figlio!=NULL)
		figlio->setParent(p);		
	}
	else
		{
			Nodo<H>* next=succ(tmp);
			tmp->setKey(next->getKey());
			_canc(tmp->getRight(),next->getKey());
		}


}


public:
	BST()
	{
		root=NULL;
		cont=0;
	}

	BST<H>* insert(H key)
	{
		Nodo<H> *n=new Nodo<H>(key);
		Nodo<H> *tmp=root;
		Nodo<H> *p=NULL;
		while(tmp!=NULL)
		{
			p=tmp;
			if(key<=tmp->getKey())
				tmp=tmp->getLeft();
			else
				tmp=tmp->getRight();
		}
		if(p==NULL)
		{
			root=n;
			return this;
		}

		if(key<=p->getKey())
			p->setLeft(n);
		else
			p->setRight(n);
		n->setParent(p);
		return this;
	}

	void preorder(ostream& out)
	{
		_preorder(root,out);
		out<<endl;
	}

	void inorder(ostream& out)
	{
		_inorder(root,out);
		out<<endl;
	}

	void postorder(ostream& out)
	{
		_postorder(root,out);
		out<<endl;
	}
	
	void altezza()
	{
		cout<<"l'altezza dell'albero e' "<<_altezza(root)<<endl;
	}

	void ricerca(H key)
	{
		Nodo<H>* tmp=rsearch(root,key);
		if(tmp)
			cout<<"Nodo trovato"<<endl;
		else
			cout<<"Nodo non trovato"<<endl;		
	}

	void livello(H key)
	{
		if(_livello(key)==-1)
		cout<<"il nodo non esiste :("<<endl;
		else
		cout<<"il nodo "<<key<<" esiste :) e si trova al livello "<<_livello(key)<<endl;
	}

	void minimo()
	{
		cout<<"il minimo dell'albero e' "<<_minimo(root)->getKey()<<endl;
	}

	void massimo()
	{
		cout<<"il massimo dell'albero e' "<<_massimo(root)->getKey()<<endl;
	}

	void predecessore(H key)
	{
		Nodo<H> *tmp=rsearch(root,key);
		cout<<"il predecessore di "<<key<<" e' "<<prec(tmp)->getKey()<<endl;
	}

	void successore(H key)
	{
		Nodo<H> *tmp=rsearch(root,key);
		cout<<"il successore di "<<key<<" e' "<<succ(tmp)->getKey()<<endl;
	}

	void cancella(H key, ostream& out)
	{
		_canc(root,key);
		cout<<"ho cancellato il "<<key<<endl;
		preorder(out);
		inorder(out);
		postorder(out);
	}

	void stampa()
	{
		cout<<"preorder "; preorder(cout);
		cout<<"inorder "; inorder(cout);
		cout<<"postorder "; postorder(cout);				
	}

};

int main()
{
	int n;
	cout<<"numero vettore"<<endl;
	cin>>n;
	cout<<"numeri del vettore"<<endl;
	int v[n];	
	for(int i=0;i<n;i++)
		cin>>v[i];

	BST<int> *b=new BST<int>();
	for(int i=0;i<n;i++)
		b->insert(v[i]);

	b->stampa();


}
