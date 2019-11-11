#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in("input.txt");
  ofstream out("output.txt");
  int N,F,n;
  bool flag;
  for(int i=0;i<10;i++)
  {
      flag=false;

       in>>N>>F;

      for(int j=0;j<N;j++)
      {
        in>>n;
        if(F==n)
        {
         out<<j+1<<endl;
         flag=true;
        }

      }
      if(!flag)
        out<<"0"<<endl;
  }
  in.close();
  out.close();
  return 0;
}
