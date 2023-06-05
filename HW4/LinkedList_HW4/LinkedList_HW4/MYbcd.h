#ifndef MYBCD_H
#define MYBCD_H
//#define MASK1111(unit) (0xFLL << (unit << 2))//*******�R
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
        for (auto i : num_str)//�ʺA�ܼ�
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


        int rel[16] = { 0 };//�s16����

        uint64_t a = num.bcd, b = bcd;//�Q�[�P�[��

        int now = *carry_io;

        for (int i = 15; i >= 0; i--)
        {
            int cnt = 1;

            for (int j = 0; j < 4; j++)//��2�i��[�k
            {
                now += (a & 1) * cnt + (b & 1) * cnt;
                a = a >> 1;
                b = b >> 1;
                cnt *= 2;
                //cout<<a<<" "<<b<<" "<<now<<endl;
            }
            //cout<<now<<endl;
            if (now >= 10)//�i��=1
                rel[i] = now - 10, now = 1;
            else//�i��=0
                rel[i] = now, now = 0;

        }

        if (now == 1)//�i��=1
            *carry_io = 1;
        else//�i��=0
            *carry_io = 0;

        uint64_t r = 0;

        for (int i = 0; i < 16; i++)
        {//�N�ȥ���4�줸
            r = r << 4;
            //�[
            r += rel[i];
        }

        return r;

    };


    friend ostream& operator<<(ostream& sout, BCD64& num) {//friend�禡�ӭ��� <<

        int rel[16] = { 0 };//�s16����

        uint64_t tmp = num.bcd;
        int st = -1;
        for (int i = 15; i >= 0; i--)//�@16��
        {
            int now = 0;
            int cnt = 1;
            for (int j = 0; j < 4; j++)//�C��4�줸��2�i����10�i��
            {
                now += (tmp & 1) * cnt;
                tmp = tmp >> 1;//�N�ȥk��1�줸
                cnt *= 2;
            }
            //cout<<now<<endl;
            rel[i] = now;//�N�ȩ�J�}�C

            if (now != 0)//�p�G�D0
                st = i;//�hst=i
        }

        string out = "";

        if (st == -1)//���G�O0
            out = "0";
        else//�୼char��out
        {
            for (int i = st; i < 16; i++)
                out += char(rel[i] + '0');

        }


        sout << out;//��X

        return sout;
    };

private:
    uint64_t bcd;
};

#endif
