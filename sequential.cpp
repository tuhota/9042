#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>

using std::cout;
using std::endl;

using namespace std::chrono;
using namespace std;

void random_array(int array[], unsigned long size)
{
	for (int i = 0; i < size; i++)
	{
		//Randomly populate the vector with number 0-99
		array[i] = rand() % 100;
	}
}

int partition_array(int arr[], int l, unsigned long r)
{
	int i = l + 1;
	int j = r;
	int key = arr[l];
	int temp;
	
	while(true)
	{
		while(i < r && key >= arr[i])
			i++;
		while(key < arr[j])
			j--;

		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			temp = arr[l];
			arr[l] = arr[j];
			arr[j] = temp;
			return j;
		}
	}
}

void quick_sort(int arr[], int l, unsigned long r)
{
	if(l < r)
	{
		int p = partition_array(arr, l, r);
		
		quick_sort(arr, l, p-1);
		quick_sort(arr, p+1, r);
	}
}

void output_array(int arr[], int n)
{
	for(int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}


int main()
{
	unsigned long size = 100000;
	int array[size];
	random_array(array, size);

	//int array[] = {9, 6, 3, 7, 2, 12, 5, 1};
	//int size = 8;
	
	auto start = high_resolution_clock::now();
	
	quick_sort(array, 0, size-1);
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;
		
	//output_array(array, size);
	
	return 0;
}
