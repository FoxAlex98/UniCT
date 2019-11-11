#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<sstream>

using namespace std;

template<class H> class Nodo{
private:
	H key;
	Nodo<H>* next;
public:
	Nodo(H key)
	{
		this->key=key;
		next=NULL;
	}

	void setKey(H key){this->key=key;}
	void setNext(Nodo<H>* next){this->next=next;}

	H getKey(){return key;}
	Nodo<H>* getNext(){return next;}
};

template<class H> class Stack{
private:
	Nodo<H>* head;

public:
	Stack()
	{
		head=NULL;
	}

	Stack<H>* push(H key)
	{
		Nodo<H>* n=new Nodo<H>(key);
		n->setNext(head);
		head=n;
	}

	H pop()
	{
		Nodo<H>* tmp=head;
		H k=tmp->getKey();
		head=head->getNext();
		delete tmp;
		return k;
	}

	void stampa(ostream& out)
	{
		Nodo<H>* tmp=head;
		while(tmp)
		{
			out<<tmp->getKey()<<" ";
			tmp=tmp->getNext();
		}
	}

	bool isEmpty()
	{
		return (head==NULL);
	}

};

template<class H> class Squeue{
private:
	Stack<H> *s1;
	Stack<H> *s2;

public:
	Squeue()
	{
		s1=new Stack<H>();
		s2=new Stack<H>();
	}

	Squeue<H>* enqueue(H key)
	{
		s1->push(key);
	}

	void dequeue()
	{
		if(s2->isEmpty())
		{
			while(!s1->isEmpty())
			{
				s2->push(s1->pop());
			}
			s2->pop();
		}
		else
			s2->pop();
	}

	void stampa(ostream& out)
	{
		Stack<H>* s3=new Stack<H>();
		while(!s1->isEmpty())
			{
				s3->push(s1->pop());
			}
		s2->stampa(out);
		s3->stampa(out);
	}

};



int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N;
	string tipo,op;

	for(int k=0;k<100;k++)
	{
		in>>tipo>>N;
		
		if(tipo=="int")
		{
			Squeue<int> *s=new Squeue<int>();
			for(int i=0;i<N;i++)
			{
				in>>op;
				if(op=="dequeue")
					{
						s->dequeue();
					}
				else if(op[0]=='i')
					{
						op=op.substr(1);
						stringstream ss(op);
						int n;
						ss>>n;
						s->enqueue(n);
					}
			}
			s->stampa(out);
			out<<endl;		
		}

		else if(tipo=="char")
		{
			Squeue<char> *s=new Squeue<char>();
			for(int i=0;i<N;i++)
			{
				in>>op;
				if(op=="dequeue")
					{
						s->dequeue();
					}
				else if(op[0]=='i')
					{
						op=op.substr(1);
						stringstream ss(op);
						char n;
						ss>>n;
						s->enqueue(n);
					}
			}
			s->stampa(out);
			out<<endl;		
		}
		
		else if(tipo=="bool")
		{
			Squeue<bool> *s=new Squeue<bool>();
			for(int i=0;i<N;i++)
			{
				in>>op;
				if(op=="dequeue")
					{
						s->dequeue();
					}
				else if(op[0]=='i')
					{
						op=op.substr(1);
						stringstream ss(op);
						bool n;
						ss>>n;
						s->enqueue(n);
					}
			}
			s->stampa(out);
			out<<endl;		
		}

		if(tipo=="double")
		{
			Squeue<double> *s=new Squeue<double>();
			for(int i=0;i<N;i++)
			{
				in>>op;
				if(op=="dequeue")
					{
						s->dequeue();
					}
				else if(op[0]=='i')
					{
						op=op.substr(1);
						stringstream ss(op);
						double n;
						ss>>n;
						s->enqueue(n);
					}
			}
			s->stampa(out);
			out<<endl;		
		}


	}

	in.close();
	out.close();
}
