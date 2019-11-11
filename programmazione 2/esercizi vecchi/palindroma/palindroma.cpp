#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N;
  int conta=0,contap=0;
  for(int i=0;i<10;i++)
  {
      in>>N;
      string s[N];
      int ind[N];
      contap=0;
      for(int j=0;j<N;j++)
      {
          in>>s[j];
          conta=0;
          int l=s[j].length();
          for(int k=0;k<l/2;k++)
          {
             if(s[j][k]!=s[j][l-k-1])
                conta++;
          }
          if(conta<=1)
            {
                ind[contap]=j;
                contap++;
            }
      }
      out<<contap<<" ";
      for(int z=0;z<contap;z++)
      {
          out<<s[ind[z]]<<" ";
      }
      out<<endl;
  }

  in.close();
  out.close();
  return 0;
}
