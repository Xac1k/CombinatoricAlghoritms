#pragma once
#include <string>

int CharToInt(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	}
	throw std::runtime_error("Invalid character in the input value.");
}

char IntToChar(int val) {
	if (val < 10) {
		return static_cast<char>('0' + val);
	}
	return static_cast<char>('A' + (val - 10));
}

int StringToInt(const std::string& str, int radix) {
	bool minus = false;
	int idx = 0;
	int res = 0;
	while (!((str[idx] > '0' && str[idx] < '9') || (str[idx] == '-'))) idx++;

	if (str[idx] == '-') {
		minus = true;
		idx++;
	}
	for (; idx < str.length(); idx++) {
		int digit = CharToInt(str[idx]);
		if (digit > radix) {
			throw std::runtime_error("Invalid digit in the input value for the given source notation.");
		}
		if ((INT_MAX / 10 == res && digit > INT_MAX % 10) || (res > INT_MAX - digit / radix)) {
			throw std::runtime_error("String to Int overflow conversation.");
		}
		res = res * radix + digit;
	}
	return minus ? -res : res;
}

std::string IntToString(int n, int radix) {
	std::string res;
	bool minus = n < 0;
	n = minus ? -n : n;

	while (n > 0) {
		int remainder = n % radix;
		res = IntToChar(remainder) + res;
		n /= radix;
	}
	return minus ? '-' + res : res;
}