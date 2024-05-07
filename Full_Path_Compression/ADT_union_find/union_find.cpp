#include "union_find.hpp"
#include <iostream>

union_find::union_find(uint64_t N){
    this->idObject = new uint64_t[N]{};
    this->weight = new uint64_t[N]{};
    this->arraySize = N;
    for (size_t i = 0; i < N; i++){
        this->idObject[i] = i;
        this->weight[i] = 1;
    }
}

union_find::~union_find(){
    delete [] this->idObject;
    delete [] this->weight;
}

uint64_t union_find::find(uint64_t& t){
    for(; t != idObject[t]; t = idObject[t])
        idObject[t] = idObject[idObject[t]];
    return t;
}

bool union_find::find(uint64_t& p, uint64_t& q){
    return find(p) == find(q);
}

void union_find::unite(uint64_t p, uint64_t q){
    if(find(p, q)){
        std::cout << "Previously Connected\n";
        return;
    }else{
        if(this->weight[p] < this->weight[q]){
            this->weight[q] += this->weight[p];
            this->idObject[p] = q;
        }else{
            this->weight[p] += this->weight[q];
            this->idObject[q] = p;
        }
    }
}

uint64_t union_find::nodeConnected(uint64_t id){
    return this->weight[id];
}