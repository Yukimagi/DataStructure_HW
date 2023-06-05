#ifndef MYBCD_H
#define MYBCD_H
//#define MASK1111(unit) (0xFLL << (unit << 2))//*******刪
/*#include <iostream>
#include <iomanip>*/
#include <iostream>
using namespace std;
class BCD64 {
public:
    BCD64() :bcd(0) {};

    BCD64(uint64_t b) :bcd(b) {};


    BCD64(const BCD64& bcd_obj) :bcd(bcd_obj.bcd) {};

    BCD64(string &num_str) :bcd(0) {
        if (num_str.size() > 16)
            throw "Error: the length of the number should be <= 16";
        for (auto i : num_str)//動態變數
        {
            bcd = bcd << 4;

            bcd += i - '0';
        }
    };

    BCD64(const char* str) :bcd(0) {//new

        string num_str(str);
        for (auto i : num_str)
        {
            bcd = bcd << 4;

            bcd += i - '0';
        }
    };

    BCD64 add(BCD64& num, unsigned char* carry_io = nullptr) {


        int rel[16] = { 0 };//存16元素

        uint64_t a = num.bcd, b = bcd;//被加與加數

        int now = *carry_io;

        for (int i = 15; i >= 0; i--)
        {
            int cnt = 1;

            for (int j = 0; j < 4; j++)//做2進制加法
            {
                now += (a & 1) * cnt + (b & 1) * cnt;
                a = a >> 1;
                b = b >> 1;
                cnt *= 2;
                //cout<<a<<" "<<b<<" "<<now<<endl;
            }
            //cout<<now<<endl;
            if (now >= 10)//進位=1
                rel[i] = now - 10, now = 1;
            else//進位=0
                rel[i] = now, now = 0;

        }

        if (now == 1)//進位=1
            *carry_io = 1;
        else//進位=0
            *carry_io = 0;

        uint64_t r = 0;

        for (int i = 0; i < 16; i++)
        {//將值左移4位元
            r = r << 4;
            //加
            r += rel[i];
        }

        return r;

    };


    friend ostream& operator<<(ostream& sout, BCD64& num) {//friend函式來重載 <<

        int rel[16] = { 0 };//存16元素

        uint64_t tmp = num.bcd;
        int st = -1;
        for (int i = 15; i >= 0; i--)//共16值
        {
            int now = 0;
            int cnt = 1;
            for (int j = 0; j < 4; j++)//每值4位元做2進制轉10進制
            {
                now += (tmp & 1) * cnt;
                tmp = tmp >> 1;//將值右移1位元
                cnt *= 2;
            }
            //cout<<now<<endl;
            rel[i] = now;//將值放入陣列

            if (now != 0)//如果非0
                st = i;//則st=i
        }

        string out = "";

        if (st == -1)//結果是0
            out = "0";
        else//轉乘char到out
        {
            for (int i = st; i < 16; i++)
                out += char(rel[i] + '0');

        }


        sout << out;//輸出

        return sout;
    };

private:
    uint64_t bcd;
};

#endif
