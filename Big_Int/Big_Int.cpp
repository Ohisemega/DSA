#include "Big_Int.hpp"
#include <iostream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <stdexcept>

BigInt::BigInt(){

}

BigInt::BigInt(const BigInt& copy){//copy constructor
	// performs a deep copy
	std::cout << "Calling the copy constructor for a deep copy" << "\n";
	for (int i = digits-1; i >= copy.checkLeadingZeroes(); --i){
		this->integers[i] = copy[i];
	}
}


BigInt::BigInt(BigInt&& moveObj) noexcept{//move constructor
	std::cout << "Calling the move constructor for a swap" << "\n";
	*this = std::move(moveObj);
}

BigInt::BigInt(unsigned long long int val){
	int i, b;
	for(i = digits - 1; i >= 0; --i){
		b = val % 10;
		this->integers[i] = b;
		val = val/10;
	}
	if(i <= 0 && val != 0) throw std::invalid_argument("The value provided is too large!");
}

void BigInt::swap(BigInt& other) noexcept{
	using std::swap;
	swap(this->integers, other.integers);
}

BigInt::BigInt(const std::string& numberStr){
	if(numberStr.size() < digits){
		int i, j;
		for(i = digits - numberStr.length(), j = 0; i < digits; ++i, ++j){
			if(isdigit(numberStr[j])){
				char t = numberStr[j];
				this->integers[i] = t - '0';
			}else{
				throw std::invalid_argument("The string contains non-digit values!");
			}
		}
	}else{
		throw std::invalid_argument("The string provided is too large!");
	}
}

BigInt& BigInt::operator=(const BigInt& copy){// Assignment operator
	// performs a deep copy
	std::cout << "Calling the operator constructor for a deep copy" << "\n";
	for (int i = digits-1; i >= copy.checkLeadingZeroes(); --i){
		this->integers[i] = copy[i];
	}
	return *this;
}

// BigInt& BigInt::operator=(BigInt copy){
// 	swap(copy);
// 	return *this;
// }

// BigInt& BigInt::operator=(BigInt&& right) noexcept{
// 	swap(right);
// 	return *this;
// }

BigInt BigInt::operator+(const BigInt& right) const{
	int val, i, carry = 0;
	BigInt ret{};
	size_t max = (right.checkLeadingZeroes() > this->checkLeadingZeroes() ? right.checkLeadingZeroes() : this->checkLeadingZeroes());
	for ( i = digits-1; i >= 0/*max - 1*/; --i){
		val = this->integers[i] + right[i] + carry;
		val > 9 ? (carry = 1, val %= 10) : carry = 0;
		ret.integers[i] = val;
	}
	if(i <= 0 && carry != 0) throw std::invalid_argument("This addition is too large for the class");
	return ret;
}

BigInt BigInt::operator-(const BigInt& right) const{
	BigInt ret{};
	BigInt temp{*this};
	temp.print();
	if(temp < right) throw std::invalid_argument ("I don't want to handle a negative BigInt (consider switching the integers positions)");
	int val = 0;
	
	for (int i = digits - 1; i >= this->checkLeadingZeroes(); --i){
		val = temp.integers[i] - right.integers[i];
		if(val < 0){
			val = (temp.integers[i]+10) - right.integers[i];
			temp.integers[i-1] = temp.integers[i-1] - 1;
		}
		ret.integers[i] = val;
	}
	return ret;
}

BigInt& BigInt::operator+=(const BigInt& right){
	*this = *this + right;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& right){
	*this = *this - right;
	return *this;
}

BigInt& BigInt::operator++(){
	// BigInt temp{1};
	*this = *this + BigInt(1);
	return *this;
}

BigInt& BigInt::operator--(){
	// BigInt temp{1};
	this->integers[digits-1] = this->integers[digits-1] - 1;
	// *this = *this - BigInt(1);
	return *this;
}

BigInt BigInt::operator++(int){
	BigInt ret{*this};
	// BigInt temp{1};
	*this = *this + BigInt(1);
	return ret;
}

BigInt BigInt::operator--(int){
	BigInt ret{*this};
	// BigInt temp{1};
	this->integers[digits-1] = this->integers[digits-1] - 1;
	return ret;
}

BigInt BigInt::operator*(const BigInt& right) const{
	BigInt ret{};
	if(this->isZero() || right.isZero()) return ret;
	int power1 = (digits) - this->checkLeadingZeroes();
	int power2 = (digits) - right.checkLeadingZeroes();
	int power = power2 + power1;
	if(power >=digits) throw std::invalid_argument("Numbers too large to multiply!");
	BigInt carry{};
	int sum, val;
	for (int i = 1, carryCount = digits - 1; i <= power; ++i, --carryCount){
		sum = 0; val = 0;
		for (int k = digits - i, j = digits - 1; k < digits && j > 0; ++k, --j){
			if(this->integers[k] != 0 && right.integers[j] != 0){
				val = (this->integers[k]*right.integers[j]);
				if(val > 9 || ((sum+val) > 9)) {
					carry[carryCount - 1] += (val / 10); 
					sum += (val % 10);
					for(int x = carryCount-1; x >= 0; --x){//flush carry array
						if(sum > 9){
							carry[carryCount - 1] += (sum / 10);
							sum %= 10;
						}
						if(carry[x] > 9) {
							carry[x-1] += (carry[x] / 10);
							carry[x] %= 10;
						}

						if(carry[x-1] <= 9) break;	
					}
				}else{
					sum += val;
				}
			}
		}
		ret.integers[carryCount] = sum;
	}
	ret += carry;
	return ret;
}

BigInt& BigInt::operator*=(const BigInt& right){
	(*this) = (*this) * right;
	return *this;
}

bool BigInt::isZero() const{
	for(int i = digits - 1, j = 0; i > j; --i, ++j){
		if(this->integers[i] != 0 || this->integers[j] != 0){
			return false;
		}
	}
	return true;
}

bool BigInt::operator==(const BigInt& right) const{
	if(this->checkLeadingZeroes() != right.checkLeadingZeroes()) return false;
	for(int i = digits - 1; i >= this->checkLeadingZeroes(); --i){
		if(this->integers[i] != right.integers[i]) return false;
	}
 	return true;
}

bool BigInt::operator>(const BigInt& right) const{
	int zeroes1 = this->checkLeadingZeroes();
	int zeroes2 = right.checkLeadingZeroes();
	bool val = false;
	if(zeroes1 < zeroes2){
		val = true;
	}else if(zeroes1 > zeroes2 || *this == right){
		val = false;
	}else{
		for(int i = zeroes1; i < digits; ++i){
			if(this->integers[i] > right.integers[i]){
				val = true;
			}else if(this->integers[i] < right.integers[i]){
				val = false;
			}
		}
	}
	return val;
}

bool BigInt::operator<(const BigInt& right) const{
	return !(*this > right);
}

bool BigInt::operator>=(const BigInt& right) const{
	return (*this > right || *this == right) ;
}

bool BigInt::operator!=(const BigInt& right) const{
	return !(*this == right);
}

size_t BigInt::checkLeadingZeroes() const{
	int i = 0;
	for(; i < digits; ++i){
		if(this->integers[i] != 0) return i;
	}
	return i;
}

std::ostream& operator<<(std::ostream& output, const BigInt& bigInt){
	for(int n = bigInt.checkLeadingZeroes(); n < 100; ++n){
		output << bigInt[n];
	}
	return output;
}

void BigInt::print() const{
	for (int i = this->checkLeadingZeroes(); i < digits; ++i)
	{
		std::cout << (*this)[i];
	}
	std::cout <<std::endl;
}

short& BigInt::operator[](int subscript){
	if(subscript < 0 || subscript >= digits) throw std::out_of_range{"Subscript out of range1"};
	return integers[subscript]; //return reference to this element
}

short BigInt::operator[](int subscript) const{
	if(subscript < 0 || subscript >= digits) throw std::out_of_range{"Subscript out of range2"};
	return integers[subscript]; //return copy of this element
}

