#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>

using namespace std;

template<class F> class Nodo{
private:
	F key;
	Nodo<F> *next;
public:
	Nodo(F key)
	{
		this->key=key;
	}

	void setKey(F key){this->key=key;}
	void setNext(Nodo<F> *next){this->next=next;}

	F getKey(){return key;}
	Nodo<F>* getNext(){return next;}
};

template<class H> class Lista{
private:
	H id;
	Nodo<H> *head;
	Lista<H> *next;
public:
	Lista(H id)
	{
		this->id=id;
		head=NULL;
		next=NULL;
	}

	void setNext(Lista<H> *next){this->next=next;}
	
	Lista<H>* getNext(){return next;}

	void setId(H id){this->id=id;}
	H getId(){return id;}

	void insert(H key)
	{
		Nodo<H> *n=new Nodo<H>(key);
		if(head==NULL)
			head=n;
		else if(key<head->getKey())
			{
				n->setNext(head);
				head=n;
			}
		else
			{
				Nodo<H> *tmp=head;
				while((tmp->getNext()!=NULL) && (tmp->getNext()->getKey()<key))
					tmp=tmp->getNext();
				
				if(tmp->getNext()==NULL)
					tmp->setNext(n);
				else
					{
						n->setNext(tmp->getNext());
						tmp->setNext(n);
					}
			}
	}

	Nodo<H>* cerca(H key)
	{
		Nodo<H> *tmp=head;
		while(!tmp && tmp->getKey()!=key)
		tmp=tmp->getNext();
		return tmp; 
	}


	void canc(H key)
	{
		if(head==NULL)
		{
			cout<<"la lista è vuota"<<endl;
			return;
		}

		Nodo<H>* tmp=head;		
		
		if(head->getKey()==key)
		{	
			head=head->getNext();
			delete tmp;
		}
		else
			{
			 while(tmp->getNext()!=NULL && tmp->getNext()->getKey()!=key)	
				 tmp=tmp->getNext();
				
			 if(tmp->getNext()!=NULL)
				{
					Nodo<H> *prev=tmp->getNext();
					tmp->setNext(prev->getNext());
					delete prev;
				}
			}
		
	}

	void stampa(ostream& out)
	{
		Nodo<H>* tmp=head;
		while(tmp)
		{
			out<<","<<tmp->getKey();
			tmp=tmp->getNext();
		}
	}



};

template <class T> class Grafo{
private:
	Lista<T> *head;
public:
	Grafo()
	{
		head=NULL;
	}

	void ins(T id)
	{
		Lista<T>* l=new Lista<T>(id);
		if(head==NULL)
		{
			head=l;
			return;
		}
		else if(id<head->getId())
			{
				l->setNext(head);
				head=l;
				return;
			}
		Lista<T> *tmp=head;
		while(tmp->getNext()!=NULL && tmp->getNext()->getId()<id)
			tmp=tmp->getNext();

		if(tmp->getNext()==NULL)
			{
				tmp->setNext(l);
			}
		else
			{
				l->setNext(tmp->getNext());
				tmp->setNext(l);
			}
		return;
	}

	void inserisciarco(T a, T b)
	{
		Lista<T> *tmp=head;
		while(tmp->getId()!=a)
		tmp=tmp->getNext();
		tmp->insert(b);
	}

	void stampa(ostream& out)
	{
		Lista<T> *tmp=head;	
		while(tmp!=NULL)
		{
			out<<"("<<tmp->getId();
			tmp->stampa(out);
			out<<") ";
			tmp=tmp->getNext();
		}
		out<<endl;
	}

};

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	for(int i=0;i<100;i++)
		{
			int N,nop;
			string tipo,a1,a2;
			
			in>>N>>nop>>tipo;
			
			if(tipo=="int")
			{
				Grafo<int> *g=new Grafo<int>();
				int n,n1,n2;
				for(int j=0;j<N;j++)
				{
					in>>n;
					g->ins(n);
				}

				for(int j=0;j<nop;j++)
				{
					in>>a1>>a2;
					n1=stoi(a1.substr(1));
					n2=stoi(a2.substr(0,a2.length()-1));
					g->inserisciarco(n1,n2);
				}
				g->stampa(out);
			}
			else if(tipo=="double")
			{
				Grafo<double> *g=new Grafo<double>();
				double n,n1,n2;
				for(int j=0;j<N;j++)
				{
					in>>n;
					g->ins(n);
				}

				for(int j=0;j<nop;j++)
				{
					in>>a1>>a2;
					n1=stod(a1.substr(1));
					n2=stod(a2.substr(0,a2.length()-1));
					g->inserisciarco(n1,n2);
				}
				g->stampa(out);
			}
			else if(tipo=="char")
			{
				Grafo<char> *g=new Grafo<char>();
				char n;
				for(int j=0;j<N;j++)
				{
					in>>n;
					g->ins(n);
				}

				for(int j=0;j<nop;j++)
				{
					in>>a1>>a2;
					g->inserisciarco(a1[1],a2[0]);
				}
				g->stampa(out);
			}
		}

	in.close();
	out.close();
}
