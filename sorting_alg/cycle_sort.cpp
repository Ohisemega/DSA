#include <iostream>
#include <vector>
void firstMissingPositive(std::vector<int>& nums) {
    int temp;
    int i = 0; // cycle start
    int cnt = 0;
    while(i < nums.size() /*&& cnt < 20*/){
        int curr = nums[i];
        if(curr != i+1 && curr != nums[curr-1] && curr <= nums.size() && nums[i] > 0){
            std::swap(nums[i], nums[curr-1]);
        }else{
            ++i;
        }
        /*for(auto itr : nums)
            std::cout << itr << ' ';
        std::cout << " | " << i << '\n';*/
    }
}


int main(){
        std::vector<int>vec{-3,9,16,4,5,16,-4,9,26,2,1,19,-1,25,7,22,2,-7,14,2,5,-6,1,17,3,24,-4,17,15};
        //std::vector<int> vec{2, 3, 1};
        firstMissingPositive(vec);
        for (auto itr : vec)
            std::cout << itr << ' ';
        std::cout << '\n';
}
