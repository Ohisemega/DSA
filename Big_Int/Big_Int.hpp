#ifndef BIG_INT_H
#define BIG_INT_H

#include <array>
#include <string>

class BigInt{
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	public:
		BigInt();		
		BigInt(const BigInt&);
		BigInt(unsigned long long int num);
		BigInt(const std::string&); // conversion constructor
		BigInt(BigInt&& moveCopy) noexcept;

		//Mathematical Operations
		BigInt& operator=(const BigInt& copy);
		// BigInt& operator=(BigInt copy);
		// BigInt& operator=(BigInt&& right) noexcept;
		
		void swap(BigInt&) noexcept;
		operator std::string() const; // conversion operator to a string
		BigInt operator+(const BigInt&) const;
		BigInt& operator+=(const BigInt& right);
		BigInt operator-(const BigInt&) const;
		BigInt& operator-=(const BigInt& right);
		BigInt& operator++();
		BigInt& operator--();
		BigInt operator++(int);
		BigInt operator--(int);
		BigInt operator*(const BigInt& right) const;
		BigInt& operator*=(const BigInt& right);

		//Element operations
		short& operator[](int);
		constexpr short operator[](int) const;

		//comparison symbols
		constexpr bool isZero() const;
		bool  operator==(const BigInt&) const;
		bool  operator>(const BigInt&) const;
		bool  operator<(const BigInt& right) const;
		bool  operator<=(const BigInt& right) const{
			return (*this < right || *this == right) ;
		}
		bool  operator>=(const BigInt& right) const;
		bool  operator!=(const BigInt& right) const;

		//print operation
		void print()const;
	private:
		char sign;
		static constexpr int digits = 1000;
		std::array<short, digits>integers{};
		constexpr size_t checkLeadingZeroes()const;
		
};

#endif /* end #define BIG_INT_H*/