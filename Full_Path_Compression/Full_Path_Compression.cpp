#include <iostream>

#define N 1000

int main(){
	int objArray[N] = {0};
	int weightArray[N] = {0};
	for (int t = 0; t < N; ++t){
		objArray[t] = t;
		weightArray[t] = 1;
	}
	int p, q, i, j;
	while(std::cin >> p >> q){
		int i,j;
		int newp = i;
		int newq = j;
		for(i = p; i != objArray[i]; i = objArray[i]);
		newp = p;
		while(objArray[newp] != i){
			newp = objArray[p];
			objArray[p] = i; //p = 2
			weightArray[newp] -= weightArray[p];
			p = newp;
		}
		for(j = q; j != objArray[j]; j = objArray[j]);
		newq = q;
		while(objArray[newq] != j){
			newq = objArray[q];
			objArray[q] = j;
			q = newq;
		}
		//std::cout << "\n";
		//std::cout << "The roots of p: " << p << " and q: " <<q << " are "<< i << ", " << j << "\n";
		//for (int k = 0; k < N; ++k ) std::cout << objArray[k] << " ";
		//std::cout << "\n";
		if(i == j){
			std::cout << "Previously Connected" << std::endl;
			continue;
		}else{
			if (weightArray[i] < weightArray[j]){
				weightArray[j] += weightArray[i];
				objArray[i] = j;
			}else{
				weightArray[i] += weightArray[j];
				objArray[j] = i;
			}
			std::cout << "-->" << p << " " << q << std::endl;
			//for (int k = 0; k < N; ++k ) std::cout << objArray[k] << " ";
			//std::cout << "\n";
		}
	}
}