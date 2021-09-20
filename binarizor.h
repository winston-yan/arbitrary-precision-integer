/*************************************************************************
	> File Name: binarizor.h
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Sat 18 Sep 2021 01:39:27 PM CST
 ************************************************************************/

#ifndef _BINARIZOR_H
#define _BINARIZOR_H

#include "dec_integer.h"

class Binarizor {
    std::string bin;
public :
    Binarizor(std::string);
    Binarizor(const std::deque<uint32_t> &data);

    void bin_to_uint32(std::deque<uint32_t> &data);
    void uint32_to_bin(const std::deque<uint32_t> &data);
    void dec_to_bin(std::string);
    DecInteger bin_to_dec();

    friend std::ostream &operator<<(std::ostream &out, const Binarizor &);
private:
    bool dec_nzero(std::string &) const;
};

#endif
