#include <iostream>
#include <vector>
#include <stack>

int solution(std::vector< std::vector<int> > &a){
	const int rowNum = a.size();
	const int columnNum = a[0].size();
	std::vector<int> rowSums(rowNum);
	std::vector<int> columnSums(columnNum);
	std::vector<int> equilibrumRows((rowNum/2) + 1);
	std::vector<int> equilibrumColumns((columnNum/2) + 1);
	std::stack<int>stack;

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
	stack.push(sum);
	for(int i = rowNum - 2; i >= 0; --i){
		sum += rowSums[i];
		stack.push(sum);
	}

	//compare the stack top and sum value to determine equilibrum rows
	sum = 0;
	for(int i = rowNum - 1; i >= 0; --i, sum += rowSums[i]){
		if(stack.top() == sum){
			equilibrumRows.push_back(i);
		}
		stack.pop();
	}

	//create stack for columns aggregate
	sum = 0;
	stack.push(sum);
	for(int i = columnNum - 2; i >= 0; --i){
		sum += columnSums[i];
		stack.push(sum);
	}

	//compare the stack top and sum value to determine equilibrum columns
	sum = 0;
	for(int i = columnNum - 1; i >= 0; --i, sum += columnSums[i]){
		if(stack.top() == sum){
			equilibrumColumns.push_back(i);
		}
		stack.pop();
	}
	return equilibrumRows.size() * equilibrumColumns.size();
}
