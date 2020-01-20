#include <iostream>
#include <cstdint>
#include <functional>
#include <fstream>
void practice1()
{
    int32_t a, b;
    std::cout << "Write two dword numbers" << std::endl;
    std::cin >> a >> b;
    uint64_t res = (uint64_t(b) << 32u) | uint32_t(a);
    std::cout << "Result of concatenations in hex: " << std::hex << res << std::endl;
}

void practice1_also()
{
    int32_t a[2];
    std::cout << "Write two dword numbers" << std::endl;
    std::cin >> a[0] >> a[1];
    uint64_t* res = reinterpret_cast<uint64_t*>(a);
    std::cout << "Result of concatenations in hex: " << std::hex << *res << std::endl;
}

void practice2()
{
    //Too easy if we understanding this task like this (a+b) mod 2 -> (15 + 17) mod 2 = 0
    int16_t a, b;
    std::cout << "Write two word numbers" << std::endl;
    std::cin >> a >> b;
    uint16_t res = (a + b) % 2;
    std::cout << "Result of sum mod 2" << res << std::endl;
}

void practice2_alternative()
{
    //Too easy if we understanding this task like this (a + b) mod 2 per bit -> (15 xor 17) = 30
    int16_t a, b;
    std::cout << "Write two word numbers" << std::endl;
    std::cin >> a >> b;
    int16_t res = a ^ b;
    std::cout << "Result of xor in hex" << std::hex << res << std::endl;
}

void practice3()
{
    //Too easy if we understanding this task like this a + b, but with work around 2^31 + 2^31 = 2^32 -> results is 64 bit length
    int32_t a, b;
    std::cout << "Write two dword numbers" << std::endl;
    std::cin >> a >> b;
    int64_t res = int64_t(a) + b;
    std::cout << "Result of sum" << res << std::endl;
}

void practice3_alternative()
{
    //Too easy if we understanding this task like this a + b, but without work around 2^31 + 2^31 = 0 -> results is 32 bit length
    int32_t a, b;
    std::cout << "Write two dword numbers" << std::endl;
    std::cin >> a >> b;
    int32_t res = a + b;
    std::cout << "Result of sum" << res << std::endl;
}

void practice4()
{
    // wtf???
    // i think this is task for agreement, he will tell what task means
    // this code show how to make substitute for numbers row from 0 to 5 into row from 5 to 0
    // if you're lazy, as me) you can write random substitute else you should write only a result values into array of substitute
    int16_t substitute[] =
    {
        5, 4, 3, 2, 1, 0,
    };
    int16_t a;
    std::cout << "Write word number" << std::endl;
    std::cin >> a;
    std::cout << "Result of substitute" << substitute[a] << std::endl;
}

void practice5()
{
    //really crazy task:
    //first implementation:
    // all numbers are signed -> that means we sum values from -2^16 to 2^16-1 -> [-32768, -32767, ...., 0, 1, 2,... 32767]
    // for learning more please see wiki twos-complement: https://ru.wikipedia.org/wiki/%D0%94%D0%BE%D0%BF%D0%BE%D0%BB%D0%BD%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4

    // as you can see we have many pair like (32767, 1) (32766, 2) ... (-32766, -2) (-32767, -1) (-32768, 0) -> all sums is 32768 or -32768 -> 2^16 or -2^16
    // but sum by mod 2^32 -> -2^16 mod 2^32 = 2^16 = 32768 |
    //                         2^16 + 2 ^ 16 = 0 (mod 2^32) |
    // and we have many pairs (-32767, -1) and (32767, 1)   |  ->  sums([-32768, -32767, ...., 0, 1, 2,... 32767]) =
    // and only one (-32768, 0)                             |    = sums( sums(sums(-32767, -1), sums((32767, 1))), sums(-32768, 0)) = sums(-32768, 0) = 32768
    //second implementation:
    // all numbers are unsigned -> that means we sum values from 0 to 2^32-1
    // and this the same logic: let's make a pairs
    // (1, 2^32 - 1), (2, 2^32 - 2), (3, 2^32 - 3) ... (2^16 - 1, 2^32 - 2^16 + 1) and last one (0, 2^16)
    // by mod 2^32 it too easy to calculate sum 0 + 0 + 0 + 2^16
    uint32_t results = 32768; // or you can write uint32_t results = 0x8000;
    std::cout << "Result of sums all 16bits values mod 2^32 is" << results << std::endl;
}

void practice6()
{
    // cyclic shift 16bits length values
    // also he can say somethings like this: "Make this for 32bits length values / or 64bits etc."
    // you can change only uint16_t to uint32_t and etc.
    // unsigned value is important because we need zero extended right shift
    // if you are using signed values, right shift become sign extended
    // if you use uint8_t 11th left shift becomes 3rd left shift
    uint16_t a;
    std::cout << "Write word number" << std::endl;
    std::cin >> a;
    // python style :) govnokod ;)
    uint16_t cyclic_shift_11 = (a << (11 % (sizeof(a) * 8))) | (a >> (uint64_t(sizeof(a) * 8 - 11 - 1) % (sizeof(a) * 8)));
    std::cout << "Result of cyclic shifting" << cyclic_shift_11<< std::endl;
};
void practice6_alternative()
{
    // normal case per bit shifting
    uint16_t a;
    std::cout << "Write word number" << std::endl;
    std::cin >> a;
    uint16_t cyclic_shift_11 = 0;
    constexpr uint64_t shiftVal = 11 % (sizeof(a) * 8);
    for(uint64_t t = 0; t < sizeof(a) * 8; t++)
    {
        uint16_t pos = (t + shiftVal) % (sizeof(a) * 8);
        if(a & (1u << t))
        {
            cyclic_shift_11 |= (1u << pos);
        }
    }
    std::cout << "Result of cyclic shifting" << cyclic_shift_11<< std::endl;
}
void practice7()
{
    //same as 4
    // add values to permutation mask
    uint32_t permuteMask[32] =
    {
        1, 0, 3, 2, 5, 4, 7, 6,
        9, 8, 11, 10, 13, 12, 15, 14,
        17, 16, 19, 18, 24, 20, 23, 22,
        25, 24, 27, 26, 32, 28, 31, 30,
    };
    uint32_t a;
    uint32_t permuteA = 0;
    std::cout << "Write dword number" << std::endl;
    std::cin >> a;
    for(uint64_t t = 0; t < 32; t++)
    {
        permuteA |= ((a >> t) & 1) << permuteMask[t];
    }
    std::cout << "Result of cyclic shifting" << permuteA<< std::endl;
}

void practice8()
{
    //wtf?
}
void practice9()
{
    //wtf?
}
void practice10()
{
    //wtf?
}
void practice11()
{
    //wtf?
}
void practice12()
{
    int matrixA[8][8] =
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        1, 2, 3, 4, 5, 6, 7, 0,
        2, 3, 4, 5, 6, 7, 0, 1,
        3, 4, 5, 6, 7, 0, 1, 2,
        4, 5, 6, 7, 0, 1, 2, 3,
        5, 6, 7, 0, 1, 2, 3, 4,
        6, 7, 0, 1, 2, 3, 4, 5,
        7, 0, 1, 2, 3, 4, 5, 6
    };
    int matrixB[8][8] =
    {
       -0,-1,-2,-3,-4,-5,-6,-7,
       -1,-2,-3,-4,-5,-6,-7,-0,
       -2,-3,-4,-5,-6,-7,-0,-1,
       -3,-4,-5,-6,-7,-0,-1,-2,
       -4,-5,-6,-7,-0,-1,-2,-3,
       -5,-6,-7,-0,-1,-2,-3,-4,
       -6,-7,-0,-1,-2,-3,-4,-5,
       -7,-0,-1,-2,-3,-4,-5,-6
    };
    uint32_t a;
    std::cout << "Write number of column, which will replaced" << std::endl;
    std::cin >> a;
    for(auto i = 0; i < 8;i++)
    {
        auto s = matrixA[i][a];
        matrixA[i][a] = matrixB[i][a];
        matrixB[i][a] = s;
    }
}
void practice13()
{
    //wtf????
    // hash (IV xor data -> substitution -> permutation -> hash)
}

void practice14()
{
    //input:
    //      input.txt
    //      input1.txt
    //output:
    //      sum mod 2^32
    //remark
    //      accumulation values of symbols, which have ascii format
    //      'a' == 97 etc. (possible :) i don't now really value of char 'a' in ascii, just look pic in google ;)
    std::fstream in;
    uint32_t sums = 0;
    in.open("input.txt",std::ios::in);
    if(in.is_open())
    {
        while(!in.eof())
        {
            char c = 0;
            in.get(c);
            if (!in.eof()) sums += c;
        }
    }
    in.close();
    in.open("input1.txt",std::ios::in);
    if(in.is_open())
    {
        while(!in.eof())
        {
            char c = 0;
            in.get(c);
            if (!in.eof()) sums += c;
        }
    }
    in.close();
    std::cout << "sums of files(mod 2^32) is " <<  sums;
}

void practice15()
{

}
int main()
{
    // practice"№"();
    // practice1();
    practice1();
}