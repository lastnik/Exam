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
    // перестановка байтов в четверном слове
    uint8_t permutation[] =
    {
        4, 0, 2, 7, 3, 1, 5, 6
    };
    auto P = [permutation](uint64_t a)
    {
        uint64_t result = 0;
        for(int i = 0; i < 8;i++)
        {
            result |= uint64_t(a & 0xFF) << permutation[i];
            a = a >> 8;
        }
        return result;
    };
    std::cout << "Write qword number" << std::endl;
    uint64_t a;
    std::cin >> a;
    std::cout << "Result of permutation " << std::hex << P(a);
}
void practice9()
{
//замена байтов в двойном слове(каждый 4 бита заменяются)
    uint8_t substitution[] =
    {
        9, 1, 8, 15, 0, 3, 4, 7,
        6, 2, 5, 14, 11, 10, 12, 13
    };
    auto S = [substitution](uint32_t a)
    {
        uint32_t result = 0;
        for(int i = 0; i < 8;i++)
        {
            result = substitution[a & 0xF];
            a = a >> 4; result = result << 4;
        }
        return result;
    };
    std::cout << "Write qword number" << std::endl;
    uint32_t a;
    std::cin >> a;
    std::cout << "Result of substitution " << std::hex << S(a);
}
void practice10()
{
    // замена 4 - > 6
    uint8_t substitution[] =
    {
            18, 2, 16, 30, 1, 40, 8, 7,
            6, 35, 10, 28, 11, 48, 24, 30
    };
    auto S = [substitution](uint32_t a)
    {
    uint32_t result = 0;
    for(int i = 0; i < 8;i++)
    {
        result = substitution[a & 0xF];
        a = a >> 4; result = result << 6;
    }
    return result;
    };
    std::cout << "Write qword number" << std::endl;
    uint32_t a;
    std::cin >> a;
    std::cout << "Result of substitution " << std::hex << S(a);
}
void practice11()
{
    //замена байтов в четверном слове(каждый байт заменяется)
    uint8_t substitution[] =
    {
        252,  238,  221,  17,  207,  110,  49,  22,  251,  196,  250,  218,  35,
        197,  4,  77,  233,119,  240,  219,  147,  46,  153,  186,  23,  54,  241,
        187,  20,  205,  95,  193,  249,  24,  101,90,  226, 92,  239,  33,  129,
        28,  60,  66,  139,  1,  142,  79,  5,  132,  2,  174,  227,  106,  143,
        160,  6,  11,  237,  152,  127,  212,  211,  31,  235,  52,  44,  81,  234,
        200,  72,  171,  242,  42,104,  162,  253,  58,  206,  204,  181,  112,  14,
        86,  8,  12,  118,  18,  191,  114,  19,  71,  156, 183, 93,  135,  21,  161,
        150,  41,  16,  123,  154,  199,  243,  145,  120,  111,  157,  158,  178,
        177,  50,  117,  25,  61,  255,  53,  138,  126,  109,  84,  198,  128,  195,
        189,  13,  87,  223,245,  36,  169,  62,  168,  67,  201,  215,  121,  214,  246,
        124,  34,  185,  3,  224,  15,  236,222,  122,148,  176,  188,  220,  232,  40,  80,
        78,  51,  10,  74,  167,  151,  96,  115,  30,  0,98,  68,  26,  184,  56,  130,  100,
        159,  38,  65,  173,  69,  70,  146,  39,  94,  85,  47,  140,  163,165,  125,  105,
        213,  149,  59,  7,  88,  179,  64,  134,  172,  29,  247,  48,  55,  107,  228,  136,
        217, 231,  137,  225,  27,  131,  73,  76,  63,  248,  254,  141,  83,  170,  144,  202,
        216,  133,97,  32,  113,  103,  164,  45,  43,  9,  91,  203,  155,  37,  208,  190,  229,
        108,  82,  89,  166,116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182
    };
    auto S = [substitution](uint64_t a)
    {
        uint64_t result = 0;
        for(int i = 0; i < 8;i++)
        {
            result = substitution[a & 0xFF];
            a = a >> 8; result = result << 8;
        }
        return result;
    };
    std::cout << "Write qword number" << std::endl;
    uint64_t a;
    std::cin >> a;
    std::cout << "Result of substitution " << std::hex << S(a);
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
    uint8_t substitution[] =
    {
        252,  238,  221,  17,  207,  110,  49,  22,  251,  196,  250,  218,  35,
        197,  4,  77,  233,119,  240,  219,  147,  46,  153,  186,  23,  54,  241,
        187,  20,  205,  95,  193,  249,  24,  101,90,  226, 92,  239,  33,  129,
        28,  60,  66,  139,  1,  142,  79,  5,  132,  2,  174,  227,  106,  143,
        160,  6,  11,  237,  152,  127,  212,  211,  31,  235,  52,  44,  81,  234,
        200,  72,  171,  242,  42,104,  162,  253,  58,  206,  204,  181,  112,  14,
        86,  8,  12,  118,  18,  191,  114,  19,  71,  156, 183, 93,  135,  21,  161,
        150,  41,  16,  123,  154,  199,  243,  145,  120,  111,  157,  158,  178,
        177,  50,  117,  25,  61,  255,  53,  138,  126,  109,  84,  198,  128,  195,
        189,  13,  87,  223,245,  36,  169,  62,  168,  67,  201,  215,  121,  214,  246,
        124,  34,  185,  3,  224,  15,  236,222,  122,148,  176,  188,  220,  232,  40,  80,
        78,  51,  10,  74,  167,  151,  96,  115,  30,  0,98,  68,  26,  184,  56,  130,  100,
        159,  38,  65,  173,  69,  70,  146,  39,  94,  85,  47,  140,  163,165,  125,  105,
        213,  149,  59,  7,  88,  179,  64,  134,  172,  29,  247,  48,  55,  107,  228,  136,
        217, 231,  137,  225,  27,  131,  73,  76,  63,  248,  254,  141,  83,  170,  144,  202,
        216,  133,97,  32,  113,  103,  164,  45,  43,  9,  91,  203,  155,  37,  208,  190,  229,
        108,  82,  89,  166,116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182
    };
    uint8_t permutation[] =
    {
        4, 0, 2, 7, 3, 1, 5, 6
    };
    std::string str;
    std::cout << "Write a string" << std::endl;
    std::cin >> str;
    uint64_t IV = 0xF1E0F1E0F1E0F1E0;
    uint64_t hash = 0;
    uint64_t p = 0;
    auto S = [substitution](uint64_t a)
    {
        uint64_t result = 0;
        for(int i = 0; i < 8;i++)
        {
            result = substitution[a & 0xFF];
            a = a >> 8; result = result << 8;
        }
        return result;
    };
    auto P = [permutation](uint64_t a)
    {
        uint64_t result = 0;
        for(int i = 0; i < 8;i++)
        {
            result |= (a & 0xFF) << permutation[i];
            a = a >> 8;
        }
        return result;
    };
    for(auto i : str)
    {
        if(p == 8)
        {
            p = 0;
            for(int i = 0; i < 8; i++)
            {
                hash = P(S(hash));
            }
        }
        hash = hash ^ (uint64_t(i) << p * 8);
        p++;
    }
    for(int i = 0; i < 8; i++)
    {
        hash = P(S(hash));
    }
    std::cout << "Hash : " << std::hex << hash;
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
    std::fstream in;
    std::vector<uint8_t> sums(0);
    in.open("input.txt",std::ios::in);
    if(in.is_open())
    {
        while(!in.eof())
        {
            char c = 0;
            in.get(c);
            if (!in.eof())
                sums.push_back(c);
        }
    }
    in.close();
    in.open("input.xor",std::ios::out);
    std::string pas;
    std::cout << "Write a password" << std::endl;
    std::cin >> pas;
    std::vector<uint8_t> Xor(0);
    for(size_t i = 0; i < pas.size(); i++)
    {
        Xor.push_back(pas[i]);
    }
    size_t index = 0;
    for(auto i : sums)
    {
        in << (i ^ Xor[index]);
        index++;
        index %= Xor.size();
    }
    in.close();
}
int main()
{
    // practice"№"();
    // practice1();
    practice13();
}