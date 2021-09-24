# Arbitrary Precision Integer
An arbitrary precision INTEGER class, by using **BASE-2^32 ripple-carry adder**. 

## Compiling and Usage

To compile (using g++ 7.4.0 myself):

```shell
$ make clean
$ make
```

Expected compiling flow (under Ubuntu 18.04 x86-64) :

```shell
g++ -c -O2 -DDEBUG -Wall  main.cpp -o main.o
g++ -c -O2 -DDEBUG -Wall  binarizor.cpp -o binarizor.o
g++ -c -O2 -DDEBUG -Wall  dec_integer.cpp -o dec_integer.o
g++ -c -O2 -DDEBUG -Wall  big_integer.cpp -o big_integer.o
g++ -O2 -DDEBUG -Wall  -o main main.o binarizor.o dec_integer.o big_integer.o 
g++ -c -DVERBOSE -O2 -DDEBUG -Wall  big_integer.cpp -o big_integer_v.o
g++ -DVERBOSE -O2 -DDEBUG -Wall  -o mainv main.o big_integer_v.o binarizor.o dec_integer.o 
binarizor.cpp dec_integer.cpp main.cpp big_integer.cpp
binarizor.o dec_integer.o main.o big_integer.o
```



Executable file `main` introduce APIs and functionalities of `BigInteger` class.

Executable file `mainv` can check the verbose output of `BigInteger` with binary form, decimal form and 2^32-base form.



## Introduction

Here I use base-4294967296 for addition, subtraction, multiplication, division, modulo and exponential.

The core unit is a ripple-carry adder, which look like this, inspired by the ALU bit-wise ripple-carry adder.

```cpp
void BigInteger::__ripple_adder_32(uint32_t a, uint32_t b, uint32_t &r, uint32_t &carry) {
    uint64_t c  = static_cast<uint64_t>(a)
                + static_cast<uint64_t>(b)
                + static_cast<uint64_t>(carry);
    carry = static_cast<uint32_t>(c >> 32);
    r = static_cast<uint32_t>(c & 0xffffffff);
    return ;
}
```



### Arithmetic Time Complexity

| Arithmetic op | N-bit op M-bit (N > M)                                 | Ω                   |
| ------------- | ------------------------------------------------------ | ------------------- |
| +             | O(N)                                                   | Ω(N)                |
| -             | O(N) (1 '+' op)                                        | Ω(N)                |
| *             | O(M N) (N-bit '+' op for M times)                      | Ω(N log N)          |
| /             | O(M N) (M-bit '*' op and '-' op for N times and )      | Ω(N log N)          |
| %             | O(M N) (1 '/' op)                                      | Ω(N log N)          |
| ^             | O(N^(2M)) (sum(N^i-bit '*' op) where i is from 1 to M) | complexity is crazy |



### Converting Complexity 

I designed a "binarizor" to convert base-10 and base-2^32 to binary string and a decimal big integer class for input and output visualization for numbers. Converting complexity is O(n^2).

Since all the computation is encapsulated in base-2^32, only when the input and output of decimal numbers happen, converting complexity will take place.



| member functions         | N-bit Input |
| ------------------------ | ----------- |
| DecInteger::operator+=   | O(N)        |
| Binarizor::dec_to_bin    | O(N^2)      |
| Binarizor::bin_to_dec    | O(N^2)      |
| Binarizor::uint32_to_bin | O(N)        |
| Binarizor::bin_to_uint32 | O(N)        |
| cout << BigInteger       | O(N^2)      |
| cin >> BigInteger        | O(N^2)      |



## Coming Next

1. Design a calculator to test the computation performance.
2. Improve the system-based integer base: for 64bit system using base-2^64 if the architecture has uint128 instruction, for 32bit system using base-2^32 now if the architecture has uint64 instruction.
3. Improve multiplication operation: **Fast Fourier Transform** can be applied to multiplication, with **O(nlogn)** complexity where n is scale of bits
4. Improve division operation: After FFT multiply applied, we can make div and mod operation under **O(nlogn)** complexity where n is scale of bits
5. Thinking...



## License

Bundler is available under an [MIT License](https://github.com/winston-yan/arbitrary-precision-integer/blob/main/LICENSE).
