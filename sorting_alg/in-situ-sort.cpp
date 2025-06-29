#include <iostream>

template <typename T>
void print(T arr[9]){
	for(int t = 0; t < 9; ++t){
		std::cout << arr[t] << " ";
	}
	std::cout << "\n";
}

void insituItem (char data[9], int a[9], int N){
	for (int i = 0; i < N; ++i){
		char v = data[i];
		int j, k;
		for(k = i; a[k] != i; k = a[j]){
			j = k;
			std::cout << a[k] << " " << i << "\n";
			// data[k] = data[a[k]]; 
			print(a);
		}
		std::swap(data[k], data[i]);
		data[k] = v;
		std::swap(a[k], a[i]);
		std::cout << "\n";
		print(data);
		print(a);
		// break;
	}
}

int main(){
	char data[9] = {'c', 'h', 'b', 'e', 'a', 'g', 'z', 'd', 'f'};
	int a[9] = {3, 8, 2, 5, 1, 7, 0, 4, 6};
	insituItem(data, a, 9);
}
