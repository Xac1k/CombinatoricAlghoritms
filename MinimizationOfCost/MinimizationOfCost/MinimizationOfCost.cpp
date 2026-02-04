// MinimizationOfCost.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <vector> 
#include <unordered_map>
#include "./common/types.hpp"
#include "./common/Graph/graph.hpp"
#include "./reader/reader.hpp"
#include "./timer/Timer.hpp"

std::vector<int> getPlacesWithMinSum(Graph cost, Graph demanding) {
	std::vector<int> minPlacing;
	float sumOfPlacing = FLT_MAX;

	std::vector<int> ManufactureID;
	for (int id = 0; id < cost.sizeX; id++) ManufactureID.push_back(id);

	do
	{
		std::unordered_map<int, int> ManufactureID_PlaceID;
		for (int id = 0; id < ManufactureID.size(); id++) ManufactureID_PlaceID.insert(std::make_pair(ManufactureID[id], id));
		float costOfPlacing = 0;

		for (int id_i = 0; id_i < ManufactureID.size(); id_i++) {
			for (int id_j = 0; id_j < ManufactureID.size(); id_j++) {
				auto count = demanding.getWeight(id_i, id_j);
				auto price = cost.getWeight(ManufactureID_PlaceID[id_i], ManufactureID_PlaceID[id_j]);
				costOfPlacing += price * count;
			}
		}
		costOfPlacing /= 2;

		copy(ManufactureID.begin(), ManufactureID.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
		std::cout << "Sum: " << costOfPlacing << std::endl;

		if (sumOfPlacing > costOfPlacing) {
			minPlacing = ManufactureID;
			sumOfPlacing = costOfPlacing;
		}
	} while (std::next_permutation(ManufactureID.begin(), ManufactureID.end()));

	return minPlacing;
}

int main()
{
	try {
		Timer timer;
		Reader reader;

		std::cout << "Enter relative path to gile CostOfDeliveringOrders" << std::endl;
		std::string pathToCostMatrix;
		std::cin >> pathToCostMatrix;

		std::cout << "Enter relative path to file DemandingCountOfProduct" << std::endl;
		std::string pathToDemandingMatrix;
		std::cin >> pathToDemandingMatrix;

		Graph graphOfCost(reader.fileToMatrix(pathToCostMatrix));
		Graph graphOfDemanding(reader.fileToMatrix(pathToDemandingMatrix));

		if (graphOfCost.sizeX == 0 || graphOfDemanding.sizeX == 0) throw std::runtime_error("graphOfCost or graphOfDemanding is empty");
		if (graphOfCost.sizeX != graphOfDemanding.sizeX) throw std::runtime_error("Demension of graphOfCost and graphOfDemanding isn't equal");

		timer.setTimePoint();
		auto places = getPlacesWithMinSum(graphOfCost, graphOfDemanding);
		timer.setTimePoint();
		timer.printDuration<std::chrono::microseconds>("Time of producing: ");

		std::cout << "Solution: ";
		copy(places.begin(), places.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}