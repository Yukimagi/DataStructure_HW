#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <iomanip>
#include <string>
#define MASK1111(unit) (0xFLL << (unit << 2))
using namespace std;

class Array {
public:
    Array() {

    }

    // BCD_Array(uint64_t b) {

    //     bcd=new uint8_t[8];
    //     c=8;

    //     for(int i=0;i<sizeof(bcd);i++)
    //     {
    //         bcd[i]=b&0xffLL;
    //         b>>=4;
    //     }
    // }

    Array(const Array& bcd_obj) {

        bcd = new uint8_t[bcd_obj.c];
        c = bcd_obj.c;

        for (int i = 0; i < c; i++)
        {
            bcd[i] = bcd_obj.bcd[i];

        }

    }

    Array(string& num_str) {

        c = num_str.size() / 2 + num_str.size() % 2;
        bcd = new uint8_t[c];

        int cnt = c - 1;

        for (int i = num_str.size() - 1; i >= 0; i--)
        {
            if ((i - num_str.size() + 1) % 2 == 0)
                bcd[cnt] = num_str[i] - '0';
            else
                bcd[cnt] += (num_str[i] - '0') << 4, cnt--;

        }

    }

    Array add(Array& num) {
        static const uint64_t bcd_add6[2] = { 0, 6 };



        int new_size = max(c, num.c);
        uint8_t* sum = new uint8_t[new_size];

        unsigned char carry = 0;


        for (int i = 0; i < new_size; i++) {

            uint8_t sum8bit_l = 0;
            uint8_t sum8bit_h = 0;


            if (i >= c) sum8bit_l = (num.bcd[num.c - 1 - i] & 0xf) + carry, sum8bit_h = (num.bcd[num.c - 1 - i] & 0xf0) >> 4;
            else if (i >= num.c) sum8bit_l = (bcd[c - 1 - i] & 0xf) + carry, sum8bit_h = (bcd[c - 1 - i] & 0xf0) >> 4;
            else sum8bit_l = (bcd[c - 1 - i] & 0xf) + (num.bcd[num.c - 1 - i] & 0xf) + carry, sum8bit_h = ((bcd[c - 1 - i] & 0xf0) + (num.bcd[num.c - 1 - i] & 0xf0)) >> 4;

            carry = 0;

            if (sum8bit_l >= 0xa)
                sum8bit_h += 0x1, sum8bit_l -= 0xa;

            if (sum8bit_h >= 0xa)
                sum8bit_h -= 0xa, carry = 1;

            sum[new_size - 1 - i] = (sum8bit_h << 4) + sum8bit_l;


        }

        Array r;
        if (carry)
        {

            r.bcd = new uint8_t[new_size + 1];
            r.c = new_size + 1;
            r.bcd[0] = 1;

            for (int i = 1; i < new_size + 1; i++)
            {
                r.bcd[i] = sum[i - 1];
            }
            delete[] sum;

        }
        else
        {
            r.bcd = sum;
            r.c = new_size;
        }

        //cout<<r<<endl;




        return r;
    }

    friend ostream& operator<<(ostream& sout, Array& num) {

        sout << hex;

        bool leadingZero = 1;


        for (int i = 0; i < num.c; i++)
        {
            if (leadingZero && ((num.bcd[i] & 0xf0) != 0))
                leadingZero = 0;

            if (!leadingZero)
                sout << (int)((num.bcd[i] & 0xf0) >> 4);

            if (leadingZero && ((num.bcd[i] & 0xf) != 0))
                leadingZero = 0;

            if (!leadingZero)
                sout << (int)(num.bcd[i] & 0xf);



        }
        sout << dec;
        return sout;
    }

private:
    uint8_t* bcd;
    int c;

};

#endif

