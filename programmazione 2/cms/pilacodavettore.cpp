#include <iostream>
#include <fstream>

#define EMPTY -1
using namespace std;

template <class G> class Queue {
	private:
		int len, n, tail, head, current;
		G *v;
		static int c;
	public:

		Queue(int len) {
			n = 0;
			this->len = len;
			v = new G[len];
			head = tail = 0;
		}
		
		Queue<G>* enqueue(G x) {
			if(n==len) 
				{
					cout<<"Coda Piena"<<endl;
					return this;
				}
			v[tail] = x;
			tail++;
			n++;
			return this;
		}
		
		G dequeue() {
			if(n==0) return -1;
			G r = v[head];
			head++;
			n--;
			return r;
		}

		void print()
		{
			for(int i=head;i<tail;i++)
				cout<<v[i]<<" ";
			cout<<endl;
		}
		
		int size() {return n;}
		int isEmpty() { return (n==0); }
		
		void reset() {current = 0;}

};

template <class H> class Pila{
private:
	int head,n,len;
	H *v;
	
public:
	Pila(int len)
	{
		this->len=len;
		v=new H[len];
		n=0;
		head=0;
	}

	Pila<H>* push(H x)
	{
		if(n==len)
			{
				cout<<"la Pila e' piena";
				return this;
			}
		v[head]=x;
		head++;
		n++;
		return this;
	}

	H pop()
	{
		H key=v[head];
		head--;
		n--;
		return key;
	}

	void print()
	{
		for(int i=0;i<n;i++)
			cout<<v[i]<<" ";
		cout<<endl;
	}
};

int main()
{
	int n=10;
	cout<<"CODA"<<endl;
	Queue<int> *q=new Queue<int>(n);
	q->enqueue(5)->enqueue(6)->enqueue(7)->enqueue(8)->enqueue(9)->enqueue(10)->enqueue(11)->enqueue(12)->enqueue(13)->enqueue(14)->enqueue(15)->enqueue(16);
	q->dequeue();
	q->dequeue();
	q->enqueue(100)->enqueue(30);
	q->dequeue();
	q->print();

	cout<<"STACK"<<endl;
	Pila<int> *p=new Pila<int>(n);
	p->push(5)->push(6)->push(7)->push(8)->push(9)->push(1)->push(2)->push(3)->push(4);
	p->print();
	p->pop();
	p->print();
}
