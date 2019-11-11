#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;


template <class F> class Nodo
{
	private:
		F key;
		Nodo *next;
	public:
		Nodo()
		{
			key=-1;
			next=NULL;
		}

		Nodo(F key)
		{
			this->key=key;
			next=NULL;
		}

		void setKey(F key){this->key=key;}
		F getKey(){return key;}
		
		void setNext(Nodo *next){this->next=next;}
		Nodo* getNext(){return next;}

};

template <class H> class Pila{
private:
	Nodo<H> *head;

public:
	Pila()
	{
		head=NULL;
	}

	Pila* push(H key)
	{		
		Nodo<H> *n=new Nodo<H>(key);
		if(head==NULL)
			{
				head=n;
				return this;
			}
		n->setNext(head);
		head=n;
		return this;
	}

	H pop()
	{
		if(head!=NULL)
		{
			Nodo<H> *tmp=head;
			head=head->getNext();
			H k=tmp->getKey();
			delete tmp;
			return k;
		}
		else
			{
				return (H) -1;
			}
		
	}

	void stampa()
	{
		Nodo<H> *tmp=head;
		while(tmp!=NULL)
		{
			cout<<tmp->getKey()<<" ";
			tmp=tmp->getNext();
		}
		cout<<endl;
	}

};

template<class T> class Coda{
private:
	Nodo<T> *head;

public:
	Coda()
	{
		head=NULL;
	}

	Coda* enqueue(T key)
	{
		Nodo<T> *n=new Nodo<T>(key);
		if(head==NULL)
		{
			head=n;
			head->setKey(n->getKey());
			return this;
		}
		else
			{
				Nodo<T> *tmp=head;
				while(tmp->getNext())
					tmp=tmp->getNext();

				tmp->setNext(n);

				return this;
			}
	}

	T dequeue()
	{
		if(head==NULL)
		return (T) -1;
		else
			{
				Nodo<T> *tmp=head;
				T k=tmp->getKey();
				head=head->getNext();
				delete tmp;
				return k; 
			}
	}

	void stampa()
	{
		Nodo<T> *tmp=head;
		while(tmp)
		{
			cout<<tmp->getKey()<<" ";
			tmp=tmp->getNext();
		}
		cout<<endl;
	}


};

int main()
{
	Pila<int> *p=new Pila<int>();
	
	p=p->push(11)->push(28)->push(3)->push(58)->push(41);
	cout<<p->pop()<<endl;
	p->stampa();

	Coda<int> *c=new Coda<int>();

	c=c->enqueue(11)->enqueue(22)->enqueue(22)->enqueue(33)->enqueue(44);
	cout<<c->dequeue()<<endl;
	c->stampa();
	
}
