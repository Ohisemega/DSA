#include <iostream>
#include <vector>
#include <utility>

void quick_sel(std::vector<int>& nums, int l, int r){
    int itr = l - 1;
    int ri = r;
    int gri = ri-1;
    int partition = nums[ri];
    int i = l;
    while(i < r-l+1 && itr < gri){
        if(nums[i] <= partition){
            ++itr;
        }else{
            std::swap(nums[i], nums[gri]);
            --gri;
            continue;
        }
        ++i;
    }
    std::swap(nums[ri], nums[++gri]);
}


int main(){
        std::vector<int> vec{0, 1, 2, 3, 4, 6, 5};
        quick_sel(vec, 4, vec.size()-1);
        for(auto i : vec)
            std::cout << i << " ";
        std::cout << "\n";
}
