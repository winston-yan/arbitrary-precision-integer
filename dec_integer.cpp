/*************************************************************************
	> File Name: dec_integer.cpp
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Fri 17 Sep 2021 02:21:37 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>

#include "common.h"
#include "dec_integer.h"

DecInteger::DecInteger(int n = 0)
: std::vector<int>(1, n % 10) {}

DecInteger::DecInteger(DecInteger &&oth) noexcept
: std::vector<int>(std::move(oth)) {}

DecInteger &DecInteger::operator=(const DecInteger &oth) {
    if (this == &oth) return *this;
    this->~DecInteger();
    new(this) DecInteger(oth);
    return *this;
}

DecInteger &DecInteger::operator=(DecInteger &&oth) noexcept {
    if (this == &oth) return *this;
    this->~DecInteger();
    new(this) DecInteger(std::move(oth));
    return *this;
}

DecInteger operator+(const DecInteger &a, const DecInteger &b) {
    size_t n1 = a.size(), n2 = b.size();
    const size_t n = std::max(n1, n2);
    DecInteger ret;
    ret.resize(n + 1);
    for (size_t i = 0; i < n; ++i) {
        ret[i] += (i < n1 ? a[i] : 0) + (i < n2 ? b[i] : 0);
        ret[i + 1] += ret[i] / 10;
        ret[i] %= 10;
    }
    ret.trim();
    return ret;
}

DecInteger &DecInteger::operator+=(const DecInteger &oth) {
    if (this == &oth) *this = *this + oth;
    else this->_fetch_and_add(oth);
    return *this;
}

DecInteger &DecInteger::_fetch_and_add(const DecInteger &oth) {
    size_t n1 = this->size(), n2 = oth.size();
    const size_t n = std::max(n1, n2);
    this->resize(n + 1);
    for (size_t i = 0; i < n; ++i) {
        at(i) += oth[i];
        at(i + 1) += at(i) / 10;
        at(i) %= 10;
    }
    this->trim();
    return *this;
}

void DecInteger::trim() {
    while (back() == 0) pop_back();
    return ;
}

std::ostream &operator<<(std::ostream &out, const DecInteger &oth) {
    for (auto it = oth.rbegin(); it != oth.rend(); ++it) 
        out << *it;
    return out;
}

BEGINS(dec_test)

int main() {
    int n = 33;
    DecInteger a(1);
    for (int i = 0; i < n; ++i) {
        a += a;
        std::cout << a << std::endl;
    }
    
    return 0;
}
ENDS(dec_test)
