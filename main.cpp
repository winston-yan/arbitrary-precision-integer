/*************************************************************************
	> File Name: main.cpp
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Wed 22 Sep 2021 11:36:16 AM CST
 ************************************************************************/

#include <iostream>

#include "main.h"

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
