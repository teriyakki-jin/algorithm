#include <iostream>
#include <vector>

using namespace std;

vector <int> arr;

void swap(int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void insert_sort(int k, int N){
	int cnt = 0;
	bool is_true  = false;
	for (int i = 1; i < N; i++) {
		int tmp = arr[i];
		int j = i;
		is_true = false;

		while (j >=1 && arr[j-1] > tmp ) {
				arr[j] = arr[j-1];
				cnt++;
				j--;
		}
		if (i != j-1) {
			arr[j ] = tmp;
			if(j !=0) cnt++;

			if (i >= k) {
				is_true = true;
				break;
			}
		}
	}

	if(N >=k && is_true) cout << cnt << endl;
}


void Adjust(int i, int n) {
	int root = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] <= arr[root])
		root = left;
	if (right < n && arr[right] <= arr[root])
		root = right;
	if (root != i) {
		swap(i, root);
		Adjust(root,n);
	}
}

void heap_sort(int k) {
	int n = arr.size();
	int cnt = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
		Adjust(i, n);

	for (int i = n - 1; i >= 0; i--) {
		cnt++;
		swap(0, i);
		Adjust(0, i);

		if (cnt == k) {
			for (int j = 0; j < i; j++) {
				cout << arr[j] << endl;
			}
			return;
		}
	}
}

int q_cnt = 0;
bool is_print = false;
void quick_sort(int k, int low, int high) {

	if (low >= high) return;

	if (q_cnt == k) {
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << '\n';
			is_print = true;
		}
		q_cnt++;
		return;
	}
	else if (q_cnt > k)
		return;

	int pivot = low;
	int pivot_value = arr[pivot];
	int left = low + 1;
	int right = high;
	while (left <= right) {
		while (arr[left] <= pivot_value && left <= high) left++;
		while (arr[right] > pivot_value && right > low) right--;

		if (right <= left) swap(right, pivot);
		else swap(left, right);
	}

	if (q_cnt == k) {
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << '\n';
			is_print = true;
		}
		q_cnt++;
	}
	else if (q_cnt > k)
		return;
	else
		q_cnt++;

	quick_sort(k, low, right - 1);
	quick_sort(k, right + 1, high);

}
void choose_sort(int k, int N) {

	for (int j = 0; j < k; j++) {
		int min_v = j;
		for (int i = j + 1; i < N; i++) {
			if (arr[min_v] > arr[i]) {
				min_v = i;

			}

		}
		int tmp = arr[j];
		arr[j] = arr[min_v];
		arr[min_v] = tmp;
	}
	for (int i = 0; i < N; i++) {
		cout  <<  arr[i] << '\n';
		 //res.push_back(arr[i]);
	}
}
int main(void) {
	int choose, k;
	cin >> choose >> k;
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		arr.push_back(t);
	}

	if (choose == 1) {
		insert_sort(k, N);
	}
	else if (choose == 2) {
		choose_sort(k, N);
	}

	else if (choose == 3) {
		heap_sort(k);
	}
	else if (choose == 4) {
		quick_sort(k , 0 , arr.size() - 1);
	}
	if(!is_print)
			for (int i = 0; i < N; i++) {
				cout << arr[i] << endl;
			}

    else
        return 0;
}
