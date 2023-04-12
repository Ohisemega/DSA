#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

class Rational{
	public:
		Rational(int = 1, int = 1);
		Rational(int);
		Rational(Rational&);
		void add(Rational&, Rational&);
		void subtract(Rational&, Rational&);
		void multiply(Rational&, Rational&);
		void divide(Rational&, Rational&);
		std::string toRationalString() const;
		double toDouble() const;
	private:
		int numerator;
		int denominator;
		void reducedForm(int&, int&);
		int hcf(int&, int&)const;
};


#endif