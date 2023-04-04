#include <iostream>
using namespace std;


void swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}


void print_arr(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << '\n';
	}
}


void Bubble_test(int* a, const int length) {

	bool flag = true;

	for (int i = 0; i < length; i++) {
		for (int j = length-1; j > i; j--) {
			if (a[j] < a[i]) {
				swap(a[j], a[i]);
				flag = false;
			}
		}
	}

	print_arr(a, length);
}


void Select_sort(int* a, const int length) {
	for (int i = 0; i < length; i++) {
		int min = i;

		for (int j = i + 1; j < length; j++) {
			if (a[min] > a[j]) {
				min = j;
			}
		}

		if (i != min) {
			swap(a[i], a[min]);
		}
	}

	print_arr(a, length);
}


void Insert_Sort(int a[], const int& length) {
	int i, j;
	for (int i = 1; i < length; i++) {
		int key = a[i];
		int j = i - 1;
		while ((j >= 0) && a[j]> key) {
			a[j + 1] = a[j];             // 较大的数往后移动一个位置
			j--;
		}
		a[j + 1] = key;
	}
	print_arr(a, length);
}


template<typename T>
void Shell_Sort(T array[], int length) {
	int h = 1;
	while (h < length / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = h; i < length; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				std::swap(array[j], array[j - h]);
			}
		}
		h = h - 3;
	}
	print_arr(array, length);
}


void heapify(int* arr, int i, int n) {
	int largest = i;
	int l_son = i * 2 + 1;
	int r_son = i * 2 + 2;

	if (l_son < n && arr[largest] < arr[l_son]) {
		largest = l_son;
	}
	if (r_son < n && arr[largest] < arr[r_son]) {
		largest = r_son;
	}
	if (largest != i) {
		std::swap(arr[largest], arr[i]);
		heapify(arr, largest, n);
	}
}


void heap_sort(int* arr, int n) {
	// create a heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, i, n);
	}
	// sort
	for (int i = n - 1; i > 0; i--) {
		std::swap(arr[i], arr[0]);
		heapify(arr, 0, i);
	}
	print_arr(arr, n);
}


void merge(int arr[], int tempArr[], int left, int mid, int right) {

	int l_pos = left;
	int r_pos = mid + 1;
	int tempArr_pos = left;

	while (l_pos <= mid && r_pos <= right)
	{
		if (arr[l_pos] < arr[r_pos]) {                 // 左比右小
			tempArr[tempArr_pos++] = arr[l_pos++];
		}
		else {
			tempArr[tempArr_pos++] = arr[r_pos++];
		}
	}
	while (l_pos <= mid) {                             // 把左边剩余的元素放到临时数组中
		tempArr[tempArr_pos++] = arr[l_pos++];
	}
	while (r_pos <= right) {                           // 把左边剩余的元素放到临时数组中
		tempArr[tempArr_pos++] = arr[r_pos++];
	}

	while (left <= right) {                             // 把临时数组中的值赋值给原始数组
		arr[left] = tempArr[left];
		left++;
	}

}


void msort(int arr[], int tempArr[], int left, int right) {
	if (left < right) {                            // 只有一个元素时，不需要排序
		int mid = left + (right - left) / 2;
		// 数组的左半边
		msort(arr, tempArr, left, mid);
		// 数组的右半边
		msort(arr, tempArr, mid + 1, right);
		// 递归
		merge(arr, tempArr, left, mid, right);
	}

}


void merge_sort(int arr[], int length) {
	// 分配辅助数组
	int* tempArr = (int*)malloc(length * sizeof(int));
	if (tempArr) {
		msort(arr, tempArr, 0, length - 1);
		free(tempArr);
	}
	else
	{
		std::cout << "allocate memory failed" << '\n';
	}

	print_arr(arr, length);

}


int Partition(int arr[], int start, int end) {

	int pivotkey;

	pivotkey = arr[start];
	while (start < end) {
		while (start < end && arr[end] >= pivotkey)
			end--;
		std::swap(arr[start], arr[end]);

		while (start < end && arr[start] <= pivotkey)
			start++;
		std::swap(arr[start], arr[end]);
		
	}

	return start;
}

void Qsort(int arr[], int start, int end) {
	
	int pivot;
	if (start < end) {
		pivot = Partition(arr, start, end);

		Qsort(arr, start, pivot - 1);
		Qsort(arr, pivot + 1, end);
	}

}


void Quick_Sort(int arr[], int length) {

	Qsort(arr, 0, length-1);
	print_arr(arr, length);

}


int main() {

	//Fraction f(3, 5);
	//double d = 4.0 + f;
	//std::cout << d << '\n';
	int a[] = { 5, 7, 1, 2, 3, 4, 1, 2 };
	int b[] = { 5, 2, 7, 1, 0, 3, 4, 1, 2 };
	//Bubble_test(a, 8);
	//Select_sort(a, 8);
	//Insert_Sort(b, 9);
	//Shell_Sort(b, 9);
	//heap_sort(b, 9);
	//merge_sort(b, 9);
	Quick_Sort(b, 9);
	return 0;

}


