#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

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

        void stampa(ostream& out)
        {
            for(int i=0;i<top;i++)
                out<<v[i]<<" ";
                out<<endl;
        }

        bool isFull()
        {
            return (top == len);
        }

        bool isEmpty()
        {
            return (top==0);
        }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N;
    string t,stringa;
    for(int k=0;k<100;k++)
    {
       in>>t>>N;
       if(t=="int")
       {
          Queue<int> *s=new Queue<int>(N);
          int a;
          for(int i=0;i<N;i++)
            {
             in>>stringa;
             if(stringa=="dequeue")
                s->dequeue();
             else
             {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->enqueue(a);
             }
            }
            s->stampa(out);
       }
       else if(t=="double")
       {
        Queue<double> *s=new Queue<double>(N);
        double a;
        for(int i=0;i<N;i++)
            {
             in>>stringa;
             if(stringa=="dequeue")
                s->dequeue();
             else
             {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->enqueue(a);
             }
            }
            s->stampa(out);
       }
       else if(t=="bool")
       {
        Queue<bool> *s=new Queue<bool>(N);
        bool a;
        for(int i=0;i<N;i++)
            {
             in>>stringa;
             if(stringa=="dequeue")
                s->dequeue();
             else
             {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->enqueue(a);
             }
            }
            s->stampa(out);
       }
       else if(t=="char")
       {
        Queue<char> *s=new Queue<char>(N);
        char a;
        for(int i=0;i<N;i++)
            {
             in>>stringa;
             if(stringa=="dequeue")
                s->dequeue();
             else
             {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->enqueue(a);
             }
            }
            s->stampa(out);
       }

    }

    in.close();
    out.close();
}
