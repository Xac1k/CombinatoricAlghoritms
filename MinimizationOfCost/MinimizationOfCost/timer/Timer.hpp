#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>
#include <cmath>

class Timer
{
public:
	void start() {
		startPoint = std::chrono::high_resolution_clock::now();
	}

	void end() {
		endPoint = std::chrono::high_resolution_clock::now();
	}

	void printDuration(std::string LetterBefore) {
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint);
		seconds = (double)duration.count() / 1000;
		std::cout << LetterBefore << seconds << std::endl;
	}

	void estimate(int nWish, int nCurr) {
		factorial(nCurr, nWish);


	}

private:
	int pointID = 0;
	std::chrono::steady_clock::time_point startPoint;
	std::chrono::steady_clock::time_point endPoint;
	long double seconds = 0;

	long long timeOfEarth = 4.54 * std::pow(10, 9);
	long long timeOfUniverse = 13.8 * std::pow(10, 9);

	unsigned long int factorial(unsigned int from, unsigned int to)
	{
		int res = 1, i;
		for (i = from; i <= to + 1; i++)
			res *= i;
		return res;
	}
};