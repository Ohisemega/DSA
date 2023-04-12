#include <iostream>
#include "Rational.hpp"

int main(){
	Rational ration{2, 5};
	Rational ration3{1, 3};
	ration3.subtract(ration, ration3);

	std::cout << "The result is: " << ration3.toRationalString() << std::endl;
}