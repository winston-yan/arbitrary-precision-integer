/*************************************************************************
	> File Name: main.cpp
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Wed 22 Sep 2021 11:36:16 AM CST
 ************************************************************************/

#include <iostream>
#include <limits>

#include "main.h"

#define MSG(msg) do { \
    std::cout << FG_BLUE(msg) << std::endl; \
} while (0)

BEGINS(ctor)

#define TEST(x) do { \
    BigInteger(std::string(#x)).print(); \
} while (0)

int main() {
    TEST(-4294967295);
    TEST(4294967295);
    TEST(-4294967296);
    TEST(4294967296);
    TEST(123123123);
    return 0;
}

ENDS(ctor)

BEGINS(trans_ctor)

int main() {
    BigInteger(static_cast<uint64_t>(-4294967295)).print();
    BigInteger(static_cast<uint64_t>(4294967295)).print();
    BigInteger(static_cast<uint64_t>(-4294967296)).print();
    BigInteger(static_cast<uint64_t>(4294967296)).print();
    BigInteger(static_cast<uint64_t>(123123123)).print();
    
    MSG("boundary test for BigInteger(uint64_t): ");
    BigInteger(std::numeric_limits<int64_t>::min()).print();
    BigInteger(std::numeric_limits<int64_t>::max()).print();

    return 0;
}


ENDS(trans_ctor)

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
    ctor::main();
    trans_ctor::main();
    // add::main();
    // dec_in_and_out::main();
    return 0;
}
