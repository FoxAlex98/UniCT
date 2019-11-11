#include <iostream>
#include <fstream>
using namespace std;

int min(int* A, int dim)
{
	int min = A[0], index = 0;
	for(int i = 1; i < dim; i++)
	{
		if(A[i] < min)
		{
			min = A[i];
			index = i;
		}
	}
	return index;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	for(int r = 0; r < 100; r++)
	{
		int N, diff = 0, index;
		in >> N;
		int arr[N];
		for(int i = 0; i < N; i++) in >> arr[i];
		for(int i = 0; i < N-1; i++)
		{
			index = min(arr, N);
			diff += index - i;
			arr[index] = arr[i];
			arr[i] = 101; // val predef
		}
		out << diff << endl;
	}
	in.close();
	out.close();
}
