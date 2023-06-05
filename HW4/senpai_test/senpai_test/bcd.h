#ifndef __BCD_H__
#define __BCD_H__
#include <iostream>
#include <iomanip>
#include <string>
#define MASK1111(unit) (0xFLL << (unit << 2))
using namespace std;

class BCD64 {
public:
	BCD64() : bcd(0) {
	}

	BCD64(uint64_t bcd) : bcd(bcd) {
	}

	BCD64(const BCD64& bcd_obj) : bcd(bcd_obj.bcd) {}

	BCD64(string& num_str) : bcd(0) {
		if (num_str.size() > 16)
			throw "Error: the length of the number should be <= 16";
		for (int i = 0; i < num_str.size(); i++)
			bcd = (bcd << 4) | (num_str[i] - '0');
	}

	BCD64 add(BCD64& num, unsigned char* carryout = nullptr, unsigned char carryin = 0) {
		static const uint64_t bcd_add6[2] = { 0, 6 };
		uint64_t add_6s = 0;
		unsigned char carry = carryin;
		for (int i = 0; i < sizeof(bcd) << 1; i++) {
			uint8_t bcd_4bit = ((bcd & MASK1111(i)) >> (i << 2));
			bcd_4bit += ((num.bcd & MASK1111(i)) >> (i << 2));
			bcd_4bit += carry;
			carry = (bcd_4bit >= 10);
			add_6s |= bcd_add6[carry] << (i << 2);
		}
		BCD64 sum(bcd + num.bcd + carryin + add_6s);
		if (carryout)
			*carryout = carry;
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