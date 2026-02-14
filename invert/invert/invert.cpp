// invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <string>
#include <filesystem>
#include <fstream>
#include <array>
#include <regex>
#include <cmath>

std::string helpText = R"(invert.exe - 3x3 matrix inversion. Finds inverse matrix and outputs coefficients to stdout.

Usage:
  invert.exe <FilePath> - Invert 3x3 matrix from file
  invert.exe - Invert 3x3 matrix from stdin
)";

using Matrix3f = std::array<std::array<float, 3>, 3>;
using Matrix2f = std::array<std::array<float, 2>, 2>;

//TODO: Почему лучше использовать статическую

std::string BuildFullPath(const std::string& relativePath)
{
	std::string globalPath = std::filesystem::current_path().string() + "\\" + relativePath;
	return globalPath;
}

bool IsIntOrFloat(std::string& val) {
	static const std::regex pattern(R"(^[+-]?\d+(?:\.\d+)?[fF]?$)");
	return std::regex_match(val, pattern);
}

void GetFromFile(std::string inputParam, Matrix3f& matrix) {
	std::ifstream iFile(BuildFullPath(inputParam), std::ios::binary);
	if (!iFile.is_open()) {
		throw std::runtime_error("Failed to open input file: " + inputParam + '\n');
	}

	std::string line;
	int yLines = 0;
	while (std::getline(iFile, line)) {
		std::stringstream ss(line);
		std::string cell;
		int xLines = 0;

		while (ss >> cell) {
			if (IsIntOrFloat(cell)) matrix[yLines][xLines++] = std::stof(cell);
			else throw std::runtime_error("Invalid matrix");
			if (xLines > 2)
				throw std::runtime_error("The matrix isn't 3x3");
		}
		if (xLines != 3)
			throw std::runtime_error("The matrix isn't 3x3");
		yLines++;
	}
	if (yLines != 3)
		throw std::runtime_error("The matrix isn't 3x3");
}

std::tuple<Matrix3f, bool> GetInputParams(int argc, char* argv[]) {
	Matrix3f matrix({ {} });
	std::string val;

	switch (argc)
	{
	case 1: {
		std::cout << "Please input a 3x3 matrix:" << std::endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cin >> val;
				if (IsIntOrFloat(val)) {
					matrix[i][j] = std::stof(val);
				}
				else {
					throw std::runtime_error("Invalid matrix");
				}
			}
		}
		break;
	}
	case 2: {
		std::string inputParam = static_cast<std::string>(argv[1]);
		if (inputParam == "-h") {
			std::cout << helpText;
			return std::make_tuple(matrix, 1);
		}
		else {
			GetFromFile(inputParam, matrix);
		}
		break;
	}
	default:
		throw std::runtime_error("Unrecognized signature of func");
		break;
	}

	return std::make_tuple(matrix, 0);
}

float DetermineMatrix(Matrix3f mat) {
	return mat[0][0] * mat[1][1] * mat[2][2]
		+ mat[0][1] * mat[1][2] * mat[2][0]
		+ mat[0][2] * mat[1][0] * mat[2][1]
		- mat[0][0] * mat[1][2] * mat[2][1]
		- mat[1][0] * mat[0][1] * mat[2][2]
		- mat[0][2] * mat[1][1] * mat[2][0];
}

float DetermineMatrix(Matrix2f mat) {
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

Matrix2f MinorMatrix3f(Matrix3f mat, int ignoredI, int ignoredJ) {
	Matrix2f mat2f({ {} });
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if (i == ignoredI or j == ignoredJ) continue;

			int iRes = i > ignoredI ? i - 1 : i;
			int jRes = j > ignoredJ ? j - 1 : j;
			mat2f[iRes][jRes] = mat[i][j];
		}
	}

	return mat2f;
}

Matrix3f MatrixAlgebraicAdditions(Matrix3f mat) {
	Matrix3f matOfAdditions({ {} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto minor = MinorMatrix3f(mat, i, j);
			auto val = ((i + j) % 2 == 0 ? 1 : -1) * DetermineMatrix(minor);
			matOfAdditions[i][j] = val;
		}
	}

	return matOfAdditions;
}

Matrix3f Transponate(Matrix3f mat) {
	Matrix3f transponentMat({ {} });

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			transponentMat[j][i] = mat[i][j];
		}
	}

	return transponentMat;
}

Matrix3f Invert(Matrix3f mat) {
	Matrix3f invMat({ {} });
	auto matOfAdditions = MatrixAlgebraicAdditions(mat);
	//auto matOfAdditionsT = Transponate(matOfAdditions);
	auto det = DetermineMatrix(mat);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto val = (1.f / det) * matOfAdditions[i][j];
			invMat[i][j] = val;
		}
	}

	return invMat;
}

void PrintMatrix3f(Matrix3f mat) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try {
		auto [mat, progEnd] = GetInputParams(argc, argv);
		if (progEnd) return 0;

		auto det = DetermineMatrix(mat);
		if (det == 0)
			throw std::runtime_error("Non-invertible");

		auto matrix = Invert(mat);
		PrintMatrix3f(matrix);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}