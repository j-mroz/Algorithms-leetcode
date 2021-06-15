#include <iostream>

// 0001101(0) -> 3:2:1:1
// 0011001(1) -> 2:2:2:1
// 0010011(2) -> 2:1:2:2 
// 0111101(3) -> 1:4:1:1
// 0100011(4) -> 1:1:3:2
// 0110001(5) -> 1:2:3:1
// 0101111(6) -> 1:1:1:4
// 0111011(7) -> 1:3:1:2
// 0110111(8) -> 1:2:1:3
// 0001011(9) -> 3:1:1:2

int barcode_digit_old(const char *buff, unsigned size, unsigned width) {
	static unsigned codes[10][4] = {
		{3, 2, 1, 1},
		{2, 2, 2, 1},
		{2, 1, 2, 2},
		{1, 4, 1, 1},
		{1, 1, 3, 2},
		{1, 2, 3, 1},
		{1, 1, 1, 4},
		{1, 3, 1, 2},
		{1, 2, 1, 3},
		{3, 1, 1, 2}
	};
	// find the code
	unsigned code[4] = {0, 0, 0, 0};
	// char bit = 0;
	char bit = '0';
	unsigned pos = 0;
	for (unsigned i = 0; i < size && pos < 4; ++i) {
		if (buff[i] == bit) {
			code[pos]++;
		} else if (++pos < 4) {
			// switch between 0 and 1
			bit =  '0' + ((bit+1) & ('\1')); // bit = '0' + (bit + 1)%2;
			code[pos] = 1;
		}
	}

	// normalize the code
	for (unsigned i = 0; i < 4; ++i) {
		code[i] /= width;
	}

	for (unsigned i = 0; i < 10; ++i) {
		if (codes[i][0] == code[0] && codes[i][1] == code[1] &&
			codes[i][2] == code[2] && codes[i][3] == code[3])
			return i;
	}

	return -1;
}

int barcode_digit(const char *buff, unsigned size, unsigned width) {
	unsigned code_buff[4] = {0, 0, 0, 0};
	char bit = '1';
	for (unsigned pos = 0, i = 0; pos < 4; ++pos) {
		bit =  '0' + ((bit+1) & 0x1); // this will do bit = '0' + (bit + 1)%2;
		for ( ; i < size && buff[i] == bit; ++i)
			code_buff[pos]++;
	}

	unsigned code = ((code_buff[0]/width) << 12) + 
					((code_buff[1]/width) << 8)  + 
					((code_buff[2]/width) << 4)  + 
					(code_buff[3]/width);

	switch (code) {
		case 0x3211: return 0;
		case 0x2221: return 1;
		case 0x2122: return 2;
		case 0x1411: return 3;
		case 0x1132: return 4;
		case 0x1231: return 5;
		case 0x1114: return 6;
		case 0x1312: return 7;
		case 0x1213: return 8;
		case 0x3112: return 9;
	}

	return -1;
}

int barcode(const char *buff, unsigned size, unsigned width, unsigned &sum) {
	int digits[8];
	int result = 0;
	sum = 0;

	for (int i = 0, pos = 0; i < size; i += 7) {
		int digit = barcode_digit(buff+i, 7, width);
		if (digit < 0)
			return -1;
		result = result*10 + digit;
		digits[pos++] = digit;
		sum += digit;
	}

	unsigned hash = (digits[0] + digits[2] + digits[4] + digits[6])*3 + 
		   			(digits[1] + digits[3] + digits[5]);
	if ((hash + digits[7])%10 != 0)
		return -1;

	return result;
}

int main() {

	const char* test_codes[10] = {
		"0001101",
		"0011001",
		"0010011",
		"0111101",
		"0100011",
		"0110001",
		"0101111",
		"0111011",
		"0110111",
		"0001011"
	};
	for (int i = 0; i < 10; ++i)
		std::cout << barcode_digit(test_codes[i], 7, 1) << std::endl;
	std::cout << barcode_digit("00000011001111", 14, 2) << std::endl;

	const char* bin_code = "01110110110001011101101100010110001000110100100110111011";
	unsigned sum;
	int res = barcode(bin_code, 56, 1, sum);
	std::cout << res << std::endl;
	std::cout << sum << std::endl;

	return 0;
}