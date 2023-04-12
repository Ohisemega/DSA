#include "rational.hpp"
#include <sstream>

void Rational::reducedForm(int& n, int& d){
	int hcf = this->hcf(n, d);
	n /= hcf;
	d /= hcf;
}

int Rational::hcf(int& nu, int& de) const{
	int max = std::max(nu, de);
	max /= 2;
	int hcfVal = 1;
	for(int i = 2; i < max; ++i ){
		if((nu % i == 0) && (de % i == 0)) hcfVal = i;
	}
	return hcfVal;
}

Rational::Rational(int n, int d) : numerator{n}, denominator{d}{

}

Rational::Rational(int n) : Rational{n, 1}{//delagating constructor

}

//copy constructor
Rational::Rational(Rational& copy){
	this->numerator = copy.numerator;
	this->denominator = copy.denominator;
}

void Rational::add(Rational& rat1, Rational& rat2 ){
	int n = (rat1.numerator*rat2.denominator) + (rat2.numerator*rat1.denominator);
	int d = rat1.denominator*rat2.denominator;
	reducedForm(n, d);
	this->numerator = n;
	this->denominator = d;
}

void Rational::subtract(Rational& rat1, Rational& rat2 ){
	int n = (rat1.numerator*rat2.denominator) - (rat2.numerator*rat1.denominator);
	int d = rat1.denominator*rat2.denominator;
	reducedForm(n, d);
	this->numerator = n;
	this->denominator = d;
}

void Rational::multiply(Rational& rat1, Rational& rat2 ){
	int n = (rat1.numerator*rat2.numerator);
	int d = (rat2.denominator*rat1.denominator);
	reducedForm(n, d);
	this->numerator = n;
	this->denominator = d;
}

void Rational::divide(Rational& rat1, Rational& rat2 ){
	int n = (rat1.numerator*rat2.denominator);
	int d = (rat2.numerator*rat1.denominator);
	reducedForm(n, d);
	this->numerator = n;
	this->denominator = d;
}

std::string Rational::toRationalString() const{
	std::ostringstream output;
	output << this->numerator << '/' << this->denominator;
	return output.str();
}

