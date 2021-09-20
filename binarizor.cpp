/*************************************************************************
	> File Name: binarizor.cpp
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Sat 18 Sep 2021 02:13:15 PM CST
 ************************************************************************/

#include <iostream>
#include <deque>
#include <algorithm>
#include <cassert>

#include "common.h"
#include "binarizor.h"

Binarizor::Binarizor(std::string dec) {
    this->dec_to_bin(std::move(dec));
}

Binarizor::Binarizor(const std::deque<uint32_t> &data)
: bin(32 * data.size(), '0'){
    this->uint32_to_bin(data);
}

bool Binarizor::dec_nzero(std::string &dec) const {
    for (auto &c : dec)
        if (c != '0') return true;
    return false;
}

void Binarizor::dec_to_bin(std::string dec) {
    assert(bin.size() == 0);
    int temp;
    while (dec_nzero(dec)) {
        temp = 0;
        for (int i = 0; dec[i]; ++i) {
            temp = temp * 10 + (dec[i] - '0');
            dec[i] = temp / 2 + '0';
            temp %= 2;
        }
        bin += temp + '0';
    }
    return ;
}

void Binarizor::uint32_to_bin(const std::deque<uint32_t> &data) {
    assert(data.size() * 32 == bin.size());
    int pos = 0;
    for (const auto &n : data) {
        for (int shift = 0; shift < 32; ++shift, ++pos)
            if (n & (1 << shift)) ++bin[pos];
    }
    return ;
}

void Binarizor::bin_to_uint32(std::deque<uint32_t> &data) {
    assert(data.size() == 0);
    int shift = 0;
    for (const auto &c : bin) {
        if (shift % 32 == 0) data.push_back(0);
        if (c == '1') data.back() |= 1 << (shift % 32); 
        ++shift;
    }
    return ;
}

DecInteger Binarizor::bin_to_dec() {
    DecInteger t(1), ret(0);
    for (const auto &c : bin) {
        if (c == '1') ret += t;
        t += t;
    }
    return ret;
}

std::ostream &operator<<(std::ostream &out, const Binarizor &oth) {
    out << "Binarizor content : ";
    for (auto it = oth.bin.rbegin(); it != oth.bin.rend(); ++it)
        out << *it;
    return out;
}

