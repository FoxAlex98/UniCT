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
  string c;
  for(int j=0;j<10;j++)
  {
    in>>N;
    in>>c;
    string s[N];
    for(int i=0;i<N;i++)
      {
          in>>s[i];
          if(s[i].find(c)!=-1)
          {
              out<<s[i]<<" ";
          }
      }
      out<<endl;
  }

  in.close();
  out.close();
  return 0;
}
