#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void Merge(int* vett, int sx, int c, int dx){
    int i = sx;
    int j = c+1;
    int k = 0;
    int tmp[dx-sx+1];

    while(i <= c && j <= dx){
        if(vett[i] < vett[j]){
            tmp[k] = vett[i];
            i++;
        }
        else{
            tmp[k] = vett[j];
            j++;
        }
        k++;
    }

    while(i <= c){
        tmp[k] = vett[i];
        i++; k++;
    }

    while(j <= dx){
        tmp[k] = vett[j];
        j++; k++;
    }

    for(int i =  sx; i <= dx; i++)
        vett[i] = tmp[i - sx];
}

void MergeSort(int* vett, int sx, int dx, int &contatore){
    if(sx < dx){
        int c = (sx+dx)/2;//troviamo il centro
        contatore += vett[sx];
        MergeSort(vett, sx, c, contatore);
        MergeSort(vett, c+1, dx, contatore);
        Merge(vett, sx, c, dx);

    }
}




int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n;
        in>>n;
        int* vett = new int[n];
        for(int j = 0; j < n; j++){
            int tmp;
            in >> tmp;
            //cout<<tmp<<" ";
            vett[j] = tmp;
        }
        //cout<<endl;
        int contatore = 0;
        MergeSort(vett, 0, n-1, contatore);
        out << contatore << endl;
        delete vett;
    }

}
