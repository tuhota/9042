#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>

#include <omp.h>

using std::cout;
using std::endl;

using namespace std::chrono;
using namespace std;

#define SIZE 100000
#define THREADS 2

void random_array(int array[], unsigned long size)
{
	for (unsigned long i = 0; i < size; i++)
	{
		//Randomly populate the vector with number 0-99
		array[i] = rand() % 100;
	}
}

int partition(int arr[], int l, int r)
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

void quickSort(int arr[], int l, int r)
{
	if(l < r)
	{
		int p = partition(arr, l, r);
		
		#pragma omp task shared(arr) if(r - l > SIZE) 
		quickSort(arr, l, p - 1); 
		#pragma omp task shared(arr) if(r - l > SIZE)
		quickSort(arr, p + 1, r); 
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
	unsigned long size = SIZE;
	int array[size];
	random_array(array, size);
	
	/*
	int array[] = {9, 6, 3, 7, 2, 12, 5, 1};
	int size = 8;
	*/
	
	omp_set_dynamic(0);
	omp_set_num_threads(THREADS);
	
	auto start = high_resolution_clock::now();
	
	#pragma omp parallel
	{
		#pragma omp single
		quickSort(array, 0, size-1);
	}
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;

	//output_array(array, size);

	return 0;
}
