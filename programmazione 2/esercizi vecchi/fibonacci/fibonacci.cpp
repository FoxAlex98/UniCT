#include<iostream>
#include<fstream>

using namespace std;

int fibonacci(int f)
{
    int v[f];
    v[0]=1;
    v[1]=1;
    for(int i=2;i<f;i++)
    {
        v[i]=v[i-1]+v[i-2];
    }
    return v[f-1];
}

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,fib;
  for(int i=0;i<10;i++)
  {
      in>>N;
      fib=fibonacci(N);
      out<<fib<<endl;
  }

  in.close();
  out.close();
  return 0;
}
