#include <iostream>
#include <vector>
#include <stack>

int solution(std::vector< std::vector<int> > &a){
	const int rowNum = a.size();
	const int columnNum = a[0].size();
	std::vector<int> rowSums(rowNum);
	std::vector<int> columnSums(columnNum);
	int equRows = 0;
	int equColumns = 0;
	std::stack<int>stackSum;

	for(int i = 0; i < rowNum; ++i){
		for(int j = 0; j < columnNum; ++j){
			rowSums[i] += a[i][j];
		}
	}

	for(int i = 0; i < columnNum; ++i){
		for(int j = 0; j < rowNum; ++j){
			columnSums[i] += a[j][i];
		}
	}

	//create the stack for rows sum aggregate
	int sum = 0;
	stackSum.push(sum);
	for(int i = 0; i <= rowNum - 2; ++i){
		sum += rowSums[i];
		stackSum.push(sum);
	}

	//compare the stack top and sum value to determine equilibrum rows
	sum = 0;
	for(int i = rowNum - 1; i >= 0; --i, sum += rowSums[i]){
		if(stackSum.top() == sum){
			++equRows;
		}
		stackSum.pop();
	}

	//create stack for columns aggregate
	sum = 0;
	stackSum.push(sum);
	for(int i = 0; i <= columnNum - 2; ++i){
		sum += columnSums[i];
		stackSum.push(sum);
	}

	//compare the stack top and sum value to determine equilibrum columns
	sum = 0;
	for(int i = columnNum - 1; i >= 0; --i, sum += columnSums[i]){
		if(stackSum.top() == sum){
			++equColumns;
		}
		stackSum.pop();
	}

	//return the number of equilibrum points
	return equRows * equColumns;
}
