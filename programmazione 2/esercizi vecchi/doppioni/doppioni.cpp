#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,conta=0;
  int *v,*d;
  bool flag;
  for(int i=0;i<10;i++)
  {
    in>>N;
    v=new int[N];
    d=new int[N];
    for(int j=0;j<N;j++)
    {
        in>>v[j];
        d[i]=0;
    }
    conta=0;
    for(int k=0;k<N;k++)
    {
        flag=false;
        for(int h=0;h<N;h++)
             {
                 if(d[h]==v[k])
                 {
                     flag=true;
                 }
             }
             if(!flag)
                 {
                     d[k]=v[k];
                     for(int z=0;z<N;z++)
                     {
                        if(v[k]==v[z]&&k!=z)
                        {
                            conta++;
                        }
                     }
                 }
    }
    out<<conta<<endl;
  }



  in.close();
  out.close();
  return 0;
}
