#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<sstream>

using namespace std;

template <class H> class Stack{
    private:
        int top,len;
        H *v;
    public:
        Stack(int len)
        {
            this->len=len;
            v=new H[len];
            top=0;
        }

        void push(H x)
        {
            v[top++]=x;
        }

        void pop()
        {
            top--;
        }

        void stampa(ostream& out)
        {
            if(top==0)
                cout<<"lo stack e' vuoto";
            for(int i=top-1;i>=0;i--)
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
          Stack<int> *s=new Stack<int>(N);
          int a;
          for(int i=0;i<N;i++)
            {
                in>>stringa;
                if(stringa=="pop")
                    s->pop();
                else
                {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->push(a);
                }
            }
            s->stampa(out);
       }
       else if(t=="double")
       {
            Stack<double> *s=new Stack<double>(N);
            double a;
            for(int i=0;i<N;i++)
            {
                in>>stringa;
                if(stringa=="pop")
                    s->pop();
                else
                {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->push(a);
                }
            }
            s->stampa(out);
       }
       else if(t=="bool")
       {
            Stack<bool> *s=new Stack<bool>(N);
            bool a;
            for(int i=0;i<N;i++)
            {
            in>>stringa;
                if(stringa=="pop")
                    s->pop();
                else
                {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->push(a);
                }
            }
            s->stampa(out);
       }
       else if(t=="char")
       {
        Stack<char> *s=new Stack<char>(N);
        char a;
        for(int i=0;i<N;i++)
        {
                in>>stringa;
                if(stringa=="pop")
                    s->pop();
                else
                {
                 stringstream ss(stringa.substr(1));
                 ss>>a;
                 s->push(a);
                }
        }
        s->stampa(out);
       }

    }

    in.close();
    out.close();
}
