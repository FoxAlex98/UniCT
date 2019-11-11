#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<fstream>

using namespace std;

template <class F> class Nodo{
private:
	F key;
	Nodo *parent,*left,*right;
public:
	Nodo(F key)
	{
	 this->key=key;
	 parent,left,right=NULL;
	}

	void setParent(Nodo *parent){this->parent=parent;}
	void setLeft(Nodo *left){this->left=left;}
	void setRight(Nodo *right){this->right=right;}

	Nodo* getParent(){return parent;}
	Nodo* getLeft(){return left;}
	Nodo* getRight(){return right;}

};


template <class H> class BST{
private:
	int cont;
	Nodo<H> *root;

Nodo<H>* minimo(Nodo<H>* tmp)
{
	while(tmp->getLeft())
		tmp=tmp->getLeft();
	return tmp;
}

Nodo<H>* massimo(Nodo<H>* tmp)
{
	while(tmp->getRight())
		tmp=tmp->getRight();
	return tmp;

}

Nodo<H>* successore(Nodo<H> *tmp)
{
	if(tmp->getRight())
	return minimo(tmp->getRight());

	Nodo<H> *p=tmp->getParent();
	while(p!=NULL && p->getKey()<tmp->getKey())
		p=p->getParent();
	return p;
}

Nodo<H>* _preorder(Nodo<H>* tmp)
{
	if(tmp)
	{
		cout<<tmp->getKey()<<" ";
		_preorder(tmp->getLeft());
		_preorder(tmp->getRight());
	}
}

Nodo<H>* _inorder(Nodo<H>* tmp)
{
	if(tmp)
	{
		_inorder(tmp->getLeft());
		cout<<tmp->getKey()<<" ";
		_inorder(tmp->getRight());
	}
}

Nodo<H>* _postorder(Nodo<H>* tmp)
{
	if(tmp)
	{
		_postorder(tmp->getLeft());
		_postorder(tmp->getRight());
		cout<<tmp->getKey()<<" ";
	}
}

Nodo<H>* _rsearch(Nodo<H>* tmp, H key)
{
	if(!tmp) return NULL;
	if(tmp->getKey()==key)
	return tmp;

	if(key<=tmp->getKey())
	return _rsearch(tmp->getLeft(),key);
	else
	return _rsearch(tmp->getRight(),key); 
}

public:
		BST()
		{
			root=NULL;
			cont=0;
		}


	BST* insert(H key)
	{
		Nodo<H> *tmp=root;
		Nodo<H> *p=NULL;
		
		while(!tmp)
		{
			p=tmp;
			if(key<=tmp->getKey())
			tmp=tmp->getLeft();
			else
			tmp=tmp->getRight();
		}
		
		Nodo<H> *n=new Nodo<H>(key);		

		if(p==NULL)
		{
			root=n;
			return this;
		}
		
		if(key<=tmp->getKey())
			tmp->setLeft(n);
		else
			tmp->setRight(n);
		n->setParent(p);

	}


 void preorder()
 {
	_preorder(root);
	cout<<endl;
 }

 void inorder()
 {
	_inorder(root);
	cout<<endl;
 }

 void postorder()
 {
	_postorder();
	cout<<endl;
 }


};

int main()
{
	cout<<"hello word"<<endl;
}
