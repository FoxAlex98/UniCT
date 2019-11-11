#include<iostream>
#include<fstream>

using namespace std;

int hanoi(int disk, int start, int end, int free, int limite) {
	int passi;
	if (disk == 1) {
		//cout << "Muovi il disco " << disk << " dal piolo " << start << " al piolo " << end << endl;
		passi = 1;
	}
	else {
		passi = hanoi(disk-1, start, free, end, limite);
		//cout << "Muovi il disco " << disk << " dal piolo " << start << " al piolo " << end << endl;
		passi ++;
		passi += hanoi(disk-1, free, end, start, limite);
		if(passi==limite)
        {
            return end;
        }
	}
}

int main()
{
  ifstream in;
  ofstream out;
  in.open ("input.txt");
  out.open("output.txt");

  int N,M,i,j;
  for(int k=0;k<3;k++)
  {
   in>>N>>M;
   int f=hanoi(N,1,3,2,M);
   cout<<f<<endl;
  }

  in.close();
  out.close();
  return 0;
}
