#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N;
  string *s;
  for(int i=0;i<10;i++)
  {
      in>>N;
      s=new string[N];
      string max;
      for(int j=0;j<N;j++)
      {
          in>>s[j];
      }
      max="";
      for(int k=0;k<N;k++)
      {

          if(s[k].length()>max.length())
              max=s[k];


            else if(s[k].length()==max.length())
                        {
                         if(s[k]>max)
                            max=s[k];
                        }
      }
        out<<max<<endl;
  }

  in.close();
  out.close();
  return 0;
}
