#include<iostream>
#include<fstream>

using namespace std;

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,indicemin;
  float minimo,massimo,diffmassima;
  for(int k=0;k<10;k++)
  {
   in>>N;
   float v[N];
   float differenza[N];
   for(int z=0;z<N;z++)
   {
       in>>v[z];
   }
   for(int z=0;z<N;z++)
   {
         minimo=v[z];

           massimo=v[z];
           for(int i=z;i<N;i++)
            {
                if(v[i]>massimo)
                    massimo=v[i];
            }

        differenza[z]=massimo-minimo;
   }
   diffmassima=differenza[0];
   for(int j=0;j<N;j++)
   {
       if(differenza[j]>diffmassima)
        diffmassima=differenza[j];
   }
    out<<diffmassima<<endl;
   }

  in.close();
  out.close();
  return 0;
}
