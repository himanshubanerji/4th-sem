#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int> &v, int low, int mid, int high) {

	vector <int> temp;
	int left = low;
	int right = mid+1;
	while(left <= mid && right <= high) {

		if(v[left] <= v[right]) {
			temp.push_back(v[left]);
			left++;
		}
		else {
			temp.push_back(v[right]);
			right++;
		}
	}

	while(left <= mid) {
		temp.push_back(v[left++]);
	}
	while(right <= high) {
		temp.push_back(v[right++]);
	}

	for(int i=low; i<=high; i++) {
		v[i] = temp[i-low];
	}


}



void mergeSort(vector<int> &v, int low, int high) {

	if(low >= high)  return;

	int mid = low + (high - low)/2;  // mid = (low+high)/2
	mergeSort(v, low, mid);
	mergeSort(v, mid+1, high);
	merge(v,low, mid, high);
}


int main() {
	vector<int> v = {10,2,4,8,7};

	int low = 0;
	int high = v.size() - 1;

	cout << "Before Sorting" << endl;
	for(auto i: v) {
		cout << i << " ";
	}

	cout << endl;
	mergeSort(v, low, high);

	cout << "After Sorting" << endl;
	for(auto i: v) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}