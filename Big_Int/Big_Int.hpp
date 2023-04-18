#ifndef BIG_INT
#define BIG_INT

#include <array>
#include <string>

class BigInt{
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	public:
		BigInt(const BigInt&);
		BigInt(unsigned long long int = 0);
		BigInt(const std::string&);//conversion constructor

		//Mathematical Operations;
		BigInt& operator=(const BigInt& right);
		BigInt operator+(const BigInt&) const;
		BigInt& operator+=(const BigInt& right){
			*this = *this + right;
			return *this;
		}
		BigInt operator-(const BigInt&) const;
		BigInt& operator-=(const BigInt& right){
			*this = *this - right;
			return *this;
		}
		BigInt& operator++(){
			BigInt temp{1};
			*this = *this + temp;
			return *this;
		}
		BigInt& operator--(){
			BigInt temp{1};
			*this = *this - temp;
			return *this;
		}
		BigInt operator++(int){
			BigInt ret{*this};
			BigInt temp{1};
			*this = *this + temp;
			return ret;
		}
		BigInt operator--(int){
			BigInt ret{*this};
			BigInt temp{1};
			*this = *this - temp;
			return ret;
		}

		BigInt operator*(const BigInt& right) const;
		BigInt& operator*=(const BigInt& right){
			(*this) = (*this) * right;
			return *this;
		}
		//Element operations
		short& operator[](int);
		short operator[](int) const;

		//comparison symbols
		bool isZero() const;
		bool  operator==(const BigInt&) const;
		bool  operator>(const BigInt&) const;
		bool  operator<(const BigInt& right) const{
			return !(*this > right);
		}
		bool  operator<=(const BigInt& right) const{
			return (*this < right || *this == right) ;
		}
		bool  operator>=(const BigInt& right) const{
			return (*this > right || *this == right) ;
		}
		bool  operator!=(const BigInt& right) const{
			return !(*this == right);
		}

		//print operation
		void print()const;
	private:
		static const int digits = 1000;
		std::array<short, digits>integers{};
		size_t checkLeadingZeroes()const;
		
};

#endif