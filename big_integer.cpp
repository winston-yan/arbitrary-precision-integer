/*************************************************************************
	> File Name: big_integer.cpp
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Thu 16 Sep 2021 09:28:02 PM CST
 ************************************************************************/

#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
#include <algorithm>
#include <bitset>
#include <string>

#include "common.h"
#include "big_integer.h"

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// constructors, destructors and copy assignment operators
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
    
BigInteger::BigInteger()
: sign_bit(false), digits(1, 0u) {}

BigInteger::BigInteger(size_t n, uint32_t value, bool sign = false)
: sign_bit(sign), digits(n, value) {}

// BEGIN of private constructors

BigInteger::BigInteger(const BigInteger &oth, bool sign)
: sign_bit(sign), digits(oth.digits) {}

BigInteger::BigInteger(BigInteger &&oth, bool sign) noexcept
: sign_bit(sign), digits(std::move(oth.digits)) {}

BigInteger::BigInteger(const BigInteger &oth, size_t lo, size_t hi, bool sign = false)
: sign_bit(sign), digits(hi - lo) {
    for (auto i = 0; i < hi - lo; ++i)
        digits[i] = oth[lo + i];
}

// END of private constructors

BigInteger::BigInteger(std::string s) {
    if (s.size() == 0) 
        new(this) BigInteger();
    Binarizor *bp;
    if (s[0] == '-') 
        sign_bit = true, bp = new Binarizor(s.substr(1));
    else
        sign_bit = false, bp = new Binarizor(s);
    bp->bin_to_uint32(digits);
}

BigInteger::BigInteger(BigInteger &&oth) noexcept
: sign_bit(oth.sign_bit), digits(std::move(oth.digits)) {}

BigInteger &BigInteger::operator=(const BigInteger &oth) {
    if (this == &oth) return *this;
    this->~BigInteger();
    new (this) BigInteger(oth);
    return *this;
}

BigInteger &BigInteger::operator=(BigInteger &&oth) noexcept {
    if (this == &oth) return *this;
    this->~BigInteger();
    new (this) BigInteger(std::move(oth));
    return *this;
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// utility member functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

inline size_t BigInteger::size() const { return digits.size(); }

inline uint32_t BigInteger::operator[](size_t ind) const {
    if (ind >= size()) 
        throw std::out_of_range("INDEX out of range");
    return this->digits[ind];
}

inline uint32_t &BigInteger::operator[](size_t ind) { 
    return this->digits[ind];
}

inline bool BigInteger::is_negative() const { 
    return this->sign_bit; 
}

inline bool BigInteger::is_positive() const { 
    return !this->sign_bit && !is_zero(); 
}

inline bool BigInteger::is_zero() const {
    return digits.size() == 1 && digits[0] == 0; 
}

inline BigInteger BigInteger::negate() const { 
    return BigInteger(*this, !this->sign_bit);
}

void BigInteger::trim() {
    size_t n = digits.size();
    while (--n && digits.back() == 0u) digits.pop_back();
    return ;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &oth) {
    #ifdef VERBOSE 
    out << "sign_bit : " << (oth.sign_bit ? "-" : "None") << std::endl;
    out << "digits part <uint32> : ";
    for (auto it = oth.digits.rbegin(); it != oth.digits.rend(); ++it) 
        out << *it << " ";
    out << std::endl;
    out << "digits part <binary> : ";
    for (auto it = oth.digits.rbegin(); it != oth.digits.rend(); ++it)
        out << std::bitset<32>(*it) << " ";
    out << std::endl;
    out << FG_GREEN("finally    <decimal> : ");
    #endif
    out << (oth.sign_bit ? "-" : "+"); 
    out << Binarizor(oth.digits).bin_to_dec() << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &oth) {
    std::string temp;
    in >> temp;
    oth = temp;
    return in;
}

void BigInteger::print() const {
    std::cout << *this << std::endl;
    return ;
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// comparison functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

bool operator< (const BigInteger &a, const BigInteger &b) {
    if (a.sign_bit ^ b.sign_bit) return a.sign_bit;
    return a.sign_bit ^ BigInteger::_digits_lt(a, b);
}

bool operator==(const BigInteger &a, const BigInteger &b) {
    if (a.sign_bit ^ b.sign_bit) return false;
    if (a.size() - b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] - b[i]) return false;
    }
    return true;
}

bool operator>=(const BigInteger &a, const BigInteger &b) { return !(a < b); }
bool operator> (const BigInteger &a, const BigInteger &b) { return b < a; }
bool operator<=(const BigInteger &a, const BigInteger &b) { return !(b < a); }
bool operator!=(const BigInteger &a, const BigInteger &b) { return !(a == b); }

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// arithmetic functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

inline BigInteger BigInteger::operator-() const {
    return this->negate();
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    if (a.sign_bit ^ b.sign_bit) {
        if (BigInteger::_digits_lt(a, b)) 
            return BigInteger::_sub_digits(b, a);
        return BigInteger::_sub_digits(a, b);
    }
    return BigInteger::_add_digits(a, b);
}

BigInteger &BigInteger::operator+=(const BigInteger &oth) {
    if (this == &oth) return this->operator=(*this + oth);
    if (this->sign_bit ^ oth.sign_bit) {
        if (BigInteger::_digits_lt(*this, oth))
            return this->operator=(BigInteger::_sub_digits(oth, *this));
        return BigInteger::_fetch_and_sub_digits(oth);
    }
    return BigInteger::_fetch_and_add_digits(oth);
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
    return a + (-b);
}

BigInteger &BigInteger::operator-=(const BigInteger &oth) {
    return this->operator+=(-oth);
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
    return BigInteger(BigInteger::_mul_digits(a, b), a.sign_bit ^ b.sign_bit);
}

BigInteger &BigInteger::operator*=(const BigInteger &oth) {
    return this->operator=(*this * oth);
} 

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
    if (b.is_zero()) 
        throw std::invalid_argument("DIVIDED By ZERO!");
    return BigInteger(BigInteger::_div_digits(a, b).first, a.sign_bit ^ b.sign_bit);
}

BigInteger &BigInteger::operator/=(const BigInteger &oth) {
    return this->operator=(*this / oth);
}

BigInteger operator%(const BigInteger &a, const BigInteger &b) {
    if (b.is_zero()) 
        throw std::invalid_argument("MODULO By ZERO!");
    return BigInteger(BigInteger::_div_digits(a, b).second, a.sign_bit ^ b.sign_bit);
}

BigInteger &BigInteger::operator%=(const BigInteger &oth) {
    return this->operator=(*this % oth);
}

BigInteger operator^(const BigInteger &a, uint32_t e) {
    if (a.is_zero() && !e) 
        throw std::range_error("ZERO to the power of ZERO is undefined");
    BigInteger ret(1, 1u), tmp(a);
    int clz = __builtin_clz(e);

    for (int shift = 0; shift < 32 - clz; ++shift) {
        std::cout << FG_RED("shift is : ") << shift << std::endl;
        if (e & (static_cast<uint32_t>(1) << shift)) {
            std::cout << ret << tmp << std::endl;
            ret *= tmp;
            std::cout << ret << std::endl;
        }
        tmp *= tmp;
    }
    return ret;
}

BigInteger &BigInteger::operator^=(uint32_t e) {
    return this->operator=(*this ^ e);
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// auxiliary functions
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void BigInteger::__complement() {
    for (auto &i : digits) 
        i = ~i;
    return ;
} 

void BigInteger::__ripple_adder_32(uint32_t a, uint32_t b, uint32_t &r, uint32_t &carry) {
    uint64_t c  = static_cast<uint64_t>(a)
                + static_cast<uint64_t>(b)
                + static_cast<uint64_t>(carry);
    carry = static_cast<uint32_t>(c >> 32);
    r = static_cast<uint32_t>(c & 0xffffffff);
    return ;
}

BigInteger &BigInteger::_fetch_and_add_digits(const BigInteger &oth) {
    D(assert(this != &oth));
    size_t n1 = this->size(), n2 = oth.size();
    const size_t n = std::max(n1, n2);
    this->digits.resize(n);

    uint32_t carry = 0u;
    for (int i = 0; i < n; ++i) {
        BigInteger::__ripple_adder_32(
            digits[i], 
            i < n2 ? oth[i] : 0u,
            digits[i],
            carry);
    }
    if (carry) this->digits.push_back(carry);
    return *this;
}

BigInteger BigInteger::_add_digits(const BigInteger &a, const BigInteger &b) {
    size_t n1 = a.size(), n2 = b.size();
    const size_t n = std::max(n1, n2);
    BigInteger ret(n, 0u, a.sign_bit);

    uint32_t carry = 0u;
    for (int i = 0; i < n; ++i) {
        BigInteger::__ripple_adder_32(
            i < n1 ? a[i] : 0u,
            i < n2 ? b[i] : 0u,
            ret[i],
            carry);
    }
    if (carry) ret.digits.push_back(carry);
    return ret;
}

BigInteger &BigInteger::_fetch_and_sub_digits(const BigInteger &oth) {
    D(assert(this != &oth));
    D(assert(!BigInteger::_digits_lt(*this, oth)));
    BigInteger tmp(oth, false); // sign_bit doesn't matter
    tmp.digits.resize(this->size());
    tmp.__complement();
    
    uint32_t carry = 1u;
    for (int i = 0; i < this->size(); ++i) {
        __ripple_adder_32(digits[i], tmp[i], digits[i], carry);
    }
    // neglect carryout
    this->trim();
    return *this;
}

BigInteger BigInteger::_sub_digits(const BigInteger &a, const BigInteger &b) {
    D(assert(!BigInteger::_digits_lt(a, b)));
    BigInteger ret(b, a.sign_bit);
    ret.digits.resize(a.size());
    ret.__complement();
    
    uint32_t carry = 1u;
    for (int i = 0; i < ret.size(); ++i) {
        __ripple_adder_32(ret[i], a[i], ret[i], carry);
    }
    // neglect carryout
    ret.trim();
    return ret;
}
    
void BigInteger::__mul_adder_64(uint32_t a1, uint32_t a2, size_t pos) {
    uint64_t c  = static_cast<uint64_t>(a1)
                * static_cast<uint64_t>(a2);
    uint32_t carry = 0u;
    BigInteger::__ripple_adder_32(
        digits[pos],
        static_cast<uint32_t>(c & 0xffffffff),
        digits[pos],
        carry);
    BigInteger::__ripple_adder_32(
        digits[pos + 1], 
        static_cast<uint32_t>(c >> 32), 
        digits[pos + 1],
        carry);
    pos += 2;
    while (carry) {
        BigInteger::__ripple_adder_32(
            digits[pos], 
            0u,
            digits[pos],
            carry);
        ++pos;
    }
    return ;
}

BigInteger BigInteger::_mul_digits(const BigInteger &a, const BigInteger &b) {
    size_t n1 = a.size(), n2 = b.size();
    BigInteger ret(n1 + n2, 0u, a.sign_bit ^ b.sign_bit);

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            ret.__mul_adder_64(a[i], b[j], i + j);
        }
    }

    ret.trim();
    return ret;
}

BigInteger BigInteger::_mul_digits_uint32(const BigInteger &a, uint32_t e) {
    size_t n1 = a.size();
    BigInteger ret(n1 + 1, 0u, false);

    for (int i = 0; i < n1; ++i) {
        ret.__mul_adder_64(a[i], e, i);
    }

    ret.trim();
    return ret;
}


std::pair<BigInteger, BigInteger> BigInteger::_div_digits(const BigInteger &a, const BigInteger &b) {
    D(assert(BigInteger::_digits_le(b, a)));
    size_t n1 = a.size(), n2 = b.size();
    int pos = n1 - 1;
    BigInteger quot(pos + 1, 0u), remd(1, a[pos], false); // do not care sign bit
    
    while (1) {
        while (BigInteger::_digits_lt(remd, b)) {
            if (pos <= 0) {
                quot.trim();
                remd.trim();
                return {quot, remd};
            }
            remd.digits.push_front(a[--pos]);
        }
        for (int shift = 31; shift >= 0; --shift) {
            uint32_t exp = (quot[pos] | (1 << shift));
            if (BigInteger::_digits_le(_mul_digits_uint32(b, exp), remd))
                quot[pos] |= (1 << shift);
        }
        // calculate remainder
        remd._fetch_and_sub_digits(_mul_digits_uint32(b, quot[pos]));
        remd.trim();
    }
    return {};
}

bool BigInteger::_digits_lt(const BigInteger &a, const BigInteger &b) {
    size_t n1 = a.size(), n2 = b.size();
    if (n1 - n2) return n1 < n2;
    for (int i = n1 - 1; i >= 0; --i) 
        if (a[i] - b[i]) return a[i] < b[i];
    return false;
}

bool BigInteger::_digits_le(const BigInteger &a, const BigInteger &b) {
    return !BigInteger::_digits_lt(b, a);
}

bool BigInteger::_digits_lt_range(const BigInteger &a, const BigInteger &b, size_t b_lo, size_t b_hi) {
    size_t n1 = a.size(), n2 = b_hi - b_lo;
    if (n1 - n2) return n1 < n2;
    for (int i = n2 - 1; i >= 0; --i)
        if (a[i] - b[i + b_lo]) return a[i] < b[i + b_lo];
    return false;
}

bool BigInteger::_digits_lt_range(const BigInteger &a, size_t a_lo, size_t a_hi, const BigInteger &b) {
    size_t n1 = a_hi - a_lo, n2 = b.size();
    if (n1 - n2) return n1 < n2;
    for (int i = n1 - 2; i >= 0; --i)
        if (a[i + a_lo] - b[i]) return a[i + a_lo] < b[i];
    return false;
}

bool BigInteger::_digits_le_range(const BigInteger &a, const BigInteger &b, size_t b_lo, size_t b_hi) {
    return !BigInteger::_digits_lt_range(b, b_lo, b_hi, a);
}

bool BigInteger::_digits_le_range(const BigInteger &a, size_t a_lo, size_t a_hi, const BigInteger &b) {
    return !BigInteger::_digits_lt_range(b, a, a_lo, a_hi);
}

BEGINS(ctor)

#define TEST(x) do { \
    BigInteger(std::string(#x)).print(); \
} while (0)

int main() {
    TEST(-4294967295);
    TEST(4294967296);
    TEST(123123123);
    return 0;
}

ENDS(ctor)

BEGINS(add)

int main() {
    BigInteger a(std::string("4294967295"));
    BigInteger b(std::string("1"));
    BigInteger c(a + b);
    c.print();
    // a._fetch_and_add_digits(b);
    a.print();
    b.print();
    
    return 0;
}

ENDS(add)

BEGINS(dec_in_and_out)

int main() {
    BigInteger a, b;
    while (std::cin >> a >> b) {
        std::cout << a << b << std::endl;
        // std::cout << (a / b) << std::endl;
        // std::cout << (a % b) << std::endl;
        std::cout << (a ^ 10) << std::endl;
    }
    return 0;
}

ENDS(dec_in_and_out)

int main() {
    // ctor::main();
    // add::main();
    dec_in_and_out::main();
    return 0;
}
