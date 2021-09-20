/*************************************************************************
	> File Name: big_integer.h
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Thu 16 Sep 2021 09:19:27 PM CST
 ************************************************************************/

#ifndef _BIG_INTEGER_H
#define _BIG_INTEGER_H

#include "binarizor.h"
#include "dec_integer.h"

class BigInteger {
    bool sign_bit;
    std::deque<uint32_t> digits;

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// constructors, destructors and copy assignment operators
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----

public :

    BigInteger();
    ~BigInteger() = default;
    
    BigInteger(std::string);
    BigInteger(size_t, uint32_t, bool);
    
    BigInteger(const BigInteger &) = default;
    BigInteger(BigInteger &&) noexcept;

    BigInteger& operator=(const BigInteger &);
    BigInteger& operator=(BigInteger &&) noexcept;

private:

    BigInteger(const BigInteger &, bool);
    BigInteger(BigInteger &&, bool) noexcept;

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// utility member functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

public :

    inline size_t size() const;
    inline uint32_t operator[](size_t) const;
    inline uint32_t &operator[](size_t);
    inline bool is_negative() const;
    inline bool is_positive() const;
    inline bool is_zero() const;
    inline BigInteger negate() const;
    void trim();
    void print() const;
    friend std::ostream &operator<<(std::ostream &out, const BigInteger &);
    friend std::istream &operator>>(std::istream &in, BigInteger &);

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// comparison functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

    friend bool operator< (const BigInteger &, const BigInteger &);
    friend bool operator>=(const BigInteger &, const BigInteger &);
    friend bool operator> (const BigInteger &, const BigInteger &);
    friend bool operator<=(const BigInteger &, const BigInteger &);
    friend bool operator==(const BigInteger &, const BigInteger &);
    friend bool operator!=(const BigInteger &, const BigInteger &);

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// arithmetic functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

    inline BigInteger operator-() const;
    friend BigInteger operator+(const BigInteger &, const BigInteger &);
    BigInteger &operator+=(const BigInteger &);
    friend BigInteger operator-(const BigInteger &, const BigInteger &);
    BigInteger &operator-=(const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    BigInteger &operator*=(const BigInteger &);
    friend BigInteger operator/(const BigInteger &, const BigInteger &);
    BigInteger &operator/=(const BigInteger &);
    friend BigInteger operator%(const BigInteger &, const BigInteger &);
    BigInteger &operator%=(const BigInteger &);
    friend BigInteger operator^(const BigInteger &, const BigInteger &);
    BigInteger &operator^=(const BigInteger &);
    friend BigInteger operator^(const BigInteger &, uint64_t);
    BigInteger &operator^=(uint64_t);
    
    BigInteger &operator++();
    BigInteger &operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
    
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// auxiliary functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

private:

    void __complement();
    static void __ripple_adder_32(uint32_t, uint32_t, uint32_t &, uint32_t &);
    BigInteger &_fetch_and_add_digits(const BigInteger &);
    static BigInteger _add_digits(const BigInteger &, const BigInteger &);
    BigInteger &_fetch_and_sub_digits(const BigInteger &);
    static BigInteger _sub_digits(const BigInteger &, const BigInteger &);
    void __multpl_adder_64(uint32_t, uint32_t, size_t);
    static bool _digits_less_than(const BigInteger &, const BigInteger &);


};

#endif
