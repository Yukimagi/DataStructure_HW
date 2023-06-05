#ifndef __BCD_H__
#define __BCD_H__
#include <iostream>
#include <iomanip>
#include <string>
#define MASK1111(unit) (0xFLL << (unit << 2))
using namespace std;

class BCD64 {
public:
	// The usage of constructor/methods
	// Notice that BCD64's data member - `bcd` stores the encoded number. 
	//請注意 BCD64 的數據成員 - `bcd` 存儲編碼後的數字。
	BCD64() : bcd(0) {
	}

	BCD64(uint64_t bcd) : bcd(bcd) {
	}

	BCD64(const BCD64& bcd_obj) : bcd(bcd_obj.bcd) {}

	BCD64(string& num_str) : bcd(0) {
		for (auto i : num_str) {
			bcd = bcd << 4;
			bcd += i - '0';
		}
	}

	BCD64(const char* str) :bcd(0) {//new
		string num_str(str);
		for (auto i : num_str)
		{
			bcd = bcd << 4;
			bcd += i - '0';
		}
	};

	BCD64 add(BCD64& num, unsigned char* carry_io = nullptr) {
		static const uint64_t bcd_add6[2] = { 0, 6 };
		uint64_t add_6s = 0;
		unsigned char carry = *carry_io;
		for (int i = 0; i < sizeof(bcd) << 1; i++) {
			uint8_t bcd_4bit = ((bcd & MASK1111(i)) >> (i << 2));
			bcd_4bit += ((num.bcd & MASK1111(i)) >> (i << 2));
			bcd_4bit += carry;
			carry = (bcd_4bit >= 10);
			add_6s |= bcd_add6[carry] << (i << 2);
		}
		BCD64 sum(bcd + num.bcd + *carry_io + add_6s);
		if (carry_io)
			*carry_io = carry;
		return sum;
	}

	friend ostream& operator<<(ostream& sout, BCD64& num) {
		sout << hex << num.bcd << dec;
		return sout;
	}

private:
	uint64_t bcd;
};

#endif

