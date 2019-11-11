#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

int p=0,inizio=0,fine=0;//p numero del passo

void hanoi(int disk, int start, int end, int free, int m);

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int n,m;//n numero dischi, m mossa ricercata

    for(int k=0;k<100;k++)
    {
        p=inizio=fine=0;
        in>>n>>m;
        hanoi(n,1,3,2,m);
        out<<inizio<<" "<<fine<<endl;
    }

  in.close();
  out.close();
}

void hanoi(int disk, int start, int end, int free, int m) {

    if(inizio==0)//se è stato trovato inizia a non fare più chiamate ricorsive
    {
      if (disk == 1) {
		p++;
		//cout<<"passi "<<p<<endl;
		//cout << "Muovi il disco " << disk << " dal piolo " << start << " al piolo " << end << endl;
		if(p==m)
            {//cout<<"il disco e' partito da "<<start<< " ed e' arrivato in "<<end<<endl;
                 inizio=start;
                 fine=end;
            }

	}
	else {
		hanoi(disk-1, start, free, end, m);//muovi il disco da start a end
		p++;
		if(p==m)
                {
                 //cout<<"il disco e' partito da "<<start<< " ed e' arrivato in "<<end<<endl;
                 inizio=start;
                 fine=end;
                }
            else
                hanoi(disk-1, free, end, start, m);
         }
    }
}
