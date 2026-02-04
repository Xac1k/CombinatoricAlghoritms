#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>

class Timer
{
public:
	void setTimePoint() {
		if (pointID == 0) {
			start = std::chrono::high_resolution_clock::now();
			pointID++;
		}
		if (pointID == 1) {
			end = std::chrono::high_resolution_clock::now();
			pointID = 0;
		}
	}

	template<typename T>
	requires std::is_same_v<T, std::chrono::milliseconds> ||
			std::is_same_v<T, std::chrono::seconds> ||
			std::is_same_v<T, std::chrono::microseconds>

	void printDuration(std::string LetterBefore) {
		auto duration = std::chrono::duration_cast<T>(end - start);
		std::cout << LetterBefore << duration.count() << std::endl;
	}

private:
	int pointID = 0;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};