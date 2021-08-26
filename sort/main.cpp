#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "SortTestHelper.h"

using namespace std;

//冒泡
template<typename T>
void bubbleSort(T arr[], int n) {

	bool flag;
	for (int i = 0; i < n - 1; ++i) {

		flag = true;;
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
			break;
	}
}

template<typename T>
void bubbleSort2(T arr[], int n) {

	int newn; // 使用newn进行优化

	do {
		newn = 0;
		for (int i = 1; i < n; i++)
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);

				// 记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
				newn = i;
			}
		n = newn;
	} while (newn > 0);
}

//选择
template<typename T>
void selectionSort(T arr[], int n) {

	for (int i = 0; i < n; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < n; ++j)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		swap(arr[i], arr[minIndex]);
	}
}

template<typename T>
void selectionSort2(T arr[], int n) {

	int left = 0, right = n - 1;
	while (left < right) {
		int minIndex = left;
		int maxIndex = right;

		// 在每一轮查找时, 要保证arr[minIndex] <= arr[maxIndex]
		if (arr[minIndex] > arr[maxIndex])
			swap(arr[minIndex], arr[maxIndex]);

		for (int i = left + 1; i < right; i++)
			if (arr[i] < arr[minIndex])
				minIndex = i;
			else if (arr[i] > arr[maxIndex])
				maxIndex = i;

		swap(arr[left], arr[minIndex]);
		swap(arr[right], arr[maxIndex]);

		left++;
		right--;
	}
}

//插入 //数组的有序性越强,用时越短 //最快可达到O(n)
template<typename T>
void insertionSort(T arr[], int n) {

	for (int i = 1; i < n; ++i) {

		//1.1
		//寻找元素arr[i]合适的插入位置
		//for (int j = i; j > 0; --j) {
		//	if (arr[j] < arr[j - 1])
		//		swap(arr[j], arr[j - 1]);
		//	else
		//		break;
		//}

		//1.2
		//for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
		//	swap(arr[j], arr[j - 1]);

		//1.3
		T e = arr[i];
		int j; // j保存元素e应该插入的位置
		//for (j = i - 1; j >= 0 && arr[j] > tmp; --j)
		for (j = i; j > 0 && arr[j - 1] > e; --j) 
			arr[j] = arr[j - 1];
		arr[j] = e;
	}
}

template<typename T>
void shellSort(T arr[], int n) {

	// 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
	int h = 1;
	while (h < n / 3)
		h = 3 * h + 1;

	while (h >= 1) {

		// h-sort the array
		for (int i = h; i < n; i++) {

			// 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
			T e = arr[i];
			int j;
			for (j = i; j >= h && e < arr[j - h]; j -= h)
				arr[j] = arr[j - h];
			arr[j] = e;
		}

		h /= 3;
	}
}




int main()
{
	int n = 50000;
	int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int *arr2 = SortTestHelper::copyIntArray(arr1, n);
	int *arr3 = SortTestHelper::copyIntArray(arr1, n);
	int *arr4 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
	SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
	//SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
	SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;

	return 0;
}