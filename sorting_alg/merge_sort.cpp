#include <vector>


void merge(std::vector<int>& nums, const int start, const int mid, const int end, std::vector<int>& sorted) {
    int i = start;
    int j = mid+1;
    int counter;
    for (; i <= mid; ++i){
        sorted[i] = nums[i];
    }
    for (; j <= end; ++j){
        sorted[j] = nums[j];
    }
    i = start; j = mid+1;
    for(counter = start; counter <= end && i <= mid && j <= end; ++counter) {
        if(sorted[i] <= sorted[j]){
            nums[counter] = sorted[i];
            ++i;
        } else {
            nums[counter] = sorted[j];
            ++j;
        }
    }

    if(i <= mid) {
        while(i <= mid) {
            nums[counter] = sorted[i];
            ++i; ++counter;
        }
    }
    
    if(j <= end) {
        while(j <= end) {
            nums[counter] = sorted[j];
            ++j; ++counter;
        }
    }
}

void merge_sort(std::vector<int>& nums, int s, int e, std::vector<int>& sorted) {
    if(e > s) {
        int mid = ((e - s) >> 1) + s;
        merge_sort(nums, s, mid, sorted);
        merge_sort(nums, mid+1, e, sorted);
        merge(nums, s, mid, e, sorted);
    }
}
