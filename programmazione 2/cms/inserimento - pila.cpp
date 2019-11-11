#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>

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

        H pop()
        {
            if(isEmpty())
                return 0;
            return v[--top];
        }

        void stampa(ostream& out)
        {
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
    string t;
    for(int k=0;k<100;k++)
    {
       in>>t>>N;
       if(t=="int")
       {
          Stack<int> *s=new Stack<int>(N);
          int a;
          for(int i=0;i<N;i++)
            {
             in>>a;
             s->push(a);
            }
            s->stampa(out);
       }
       else if(t=="double")
       {
        Stack<double> *s=new Stack<double>(N);
        double a;
        for(int i=0;i<N;i++)
        {
         in>>a;
         s->push(a);
        }
        s->stampa(out);
       }
       else if(t=="bool")
       {
        Stack<bool> *s=new Stack<bool>(N);
        bool a;
        for(int i=0;i<N;i++)
        {
         in>>a;
         s->push(a);
        }
        s->stampa(out);
       }
       else if(t=="char")
       {
        Stack<char> *s=new Stack<char>(N);
        char a;
        for(int i=0;i<N;i++)
        {
         in>>a;
         s->push(a);
        }
        s->stampa(out);
       }

    }

    in.close();
    out.close();
}
