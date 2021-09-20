/*************************************************************************
	> File Name: dec_integer.h
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Fri 17 Sep 2021 02:15:31 PM CST
 ************************************************************************/

#ifndef _DEC_INTEGER_H
#define _DEC_INTEGER_H

#include <vector>

class DecInteger : public std::vector<int> {
public :
    DecInteger(int);
    ~DecInteger() = default;
    DecInteger(const std::string &);

    DecInteger(const DecInteger &) = default;
    DecInteger(DecInteger &&) noexcept;

    DecInteger &operator=(const DecInteger &);
    DecInteger &operator=(DecInteger &&) noexcept;

    DecInteger &operator+=(const DecInteger &);

    friend DecInteger operator+(const DecInteger &, const DecInteger &);
private:

    DecInteger &_fetch_and_add(const DecInteger &);
    void trim();
};

std::ostream &operator<<(std::ostream &, const DecInteger &);

#endif
