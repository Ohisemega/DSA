#include "Big_Int.hpp"
#include <utility>
#include <iostream>

void dummyFunc(BigInt&& b){
	std::cout << "This is a test to see how the move semantics constructor works" << std::endl;
	BigInt&& Concrete  = std::move(b);
	Concrete.print();
}

int main(){
	// BigInt first{670934567123285674};
	BigInt first1{670934565932085674};
	BigInt Second2{"999991246847291833423732543257755993030347457483302213845684874838374744491223344"};

	BigInt first{200};
	BigInt Second{"800"};

	// BigInt first{9999988881234};
	// BigInt Second{"321874567903"};

	// BigInt first{9999999999876};
	// BigInt Second{"999999599999"};


	// 	BigInt first{2};
	// BigInt Second{"5"};

	// long long a = 670934567123285674;
	// long long b = 7491223344;
	// BigInt first{2};
	// BigInt Second{"1"};
	first1.print();
	std::cout << std::endl;
	Second2.print();


	// BigInt fourth{99999999999};
	// ++fourth;
	// std::cout << "First is: "; first.print();
	// long long third = a * b;
	// std::cout << "This is the original leading zeroes count of first: " << first.ch << std::endl;
	BigInt multResult{first1 * Second2};
	multResult.print();
	std::cout << "Hey This is the now temp: " << std::endl;
	BigInt temp = first1 * Second2;
	std::cout << "This is the now temp: " << std::endl;
	temp.print();
	// std::cout << "This is the current leading zeroes count of first: " << first.leadingZeroes << std::endl;
	BigInt two{3447585940030339};
	dummyFunc(BigInt(0));
	BigInt third{two};
	third += temp;
	BigInt fourth = third - BigInt(1);
	++third;
	std::cout << "This is third: ";
	third.print();
	std::cout << "This is fourth: ";
	fourth.print();
	BigInt(1).print();
}