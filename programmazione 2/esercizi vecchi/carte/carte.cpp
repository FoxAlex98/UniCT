#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,i,j,min;
  string key;
  for(int k=0;k<3;k++)
  {
   in>>N;
   string v[N];
   for(int z=0;z<N;z++)
   {
       in>>v[z];

       for(i=0;i<=z;i++)
       {
          min=i;
          for(j=i+1;j<10;j++)
              if(v[j]>=v[min])
              min=j;
                  if(i!=min)
                  {
                      string temp=v[min];
                      v[min]=v[i];
                      v[i]=temp;
                  }
       }

       for(int i=0;i<z;i++)
        cout<<v[i]<<" ";
        cout<<",";
    }
    cout<<endl;





  }

  in.close();
  out.close();
  return 0;
}
