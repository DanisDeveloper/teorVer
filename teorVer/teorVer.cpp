/*
ƒано 36 карт. ¬ыт€гивают 3 случайные карты.
Ќайти веро€тность, что все выт€нутые карты окажутс€ разных мастей и номиналов
*/


#include <iostream>
#include<random>
#include<vector>
#include<chrono>
#include<string>
#include<fstream>

const int generations = 50;
const int iterations = 1'000'000;

bool contains(std::vector<std::pair<int, int>> cards, std::pair<int, int> card);
bool isUnique(std::vector<std::pair<int, int>> cards);
std::string convertSecond(long long seconds);
int generation(int g);

int main(){
	auto start_program = std::chrono::high_resolution_clock::now();

	int counterOfGenerations[generations];
	for (int g = 0; g < generations; g++) // поколени€ нужны, чтобы имитировать запуск программы несколько раз
	{
		counterOfGenerations[g] = generation(g);
		std::cout << std::endl;
	}

	std::cout << "Generations = " << generations << std::endl;
	std::cout << "Iterations = " << iterations << std::endl;
	std::cout << std::endl;

	double averageResult = 0;
	for (int g = 0; g < generations; g++)
	{
		std::cout << "Positive cases of generation " << g + 1 << " = " << counterOfGenerations[g] << std::endl;
		averageResult += counterOfGenerations[g];
	}
	averageResult /= (generations*iterations);
	std::cout << std::endl;
	std::cout << "Average result = " << averageResult << std::endl;

	auto end_program = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = end_program - start_program;
	std::string time_str = convertSecond(std::chrono::duration_cast<std::chrono::seconds>(time).count());
	std::cout << "Time of program (hh:mm:ss) = " << time_str << std::endl;


	//запись результатов в файл
	std::fstream file;
	file.open("results.txt", std::fstream::out);
	if (file.is_open()) {
		file << "Generations : " << generations << std::endl;
		file << "Iterations : " << iterations << std::endl<< std::endl;
		for (int g = 0; g < generations; g++)
		{
			file << "Positive cases of generation " << g + 1 << " = " << counterOfGenerations[g] << std::endl;
		}
		file << std::endl << "Average result = " << averageResult << std::endl;
		file << "Time of program (hh:mm:ss) = " << time_str << std::endl;
	}
}

bool contains(std::vector<std::pair<int, int>> cards, std::pair<int, int> card) {
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards[i].first == card.first && cards[i].second == card.second) return true;
	}
	return false;
}

bool isUnique(std::vector<std::pair<int, int>> cards) {
	for (int i = 0; i < cards.size(); i++)
	{
		for (int j = 0; j < cards.size(); j++)
		{
			if (i == j) continue;
			if (cards[i].first == cards[j].first) return false;
			if (cards[i].second == cards[j].second) return false;
		}
	}
	return true;
}

std::string convertSecond(long long seconds) {
	long long hours = seconds / 3600;
	seconds %= 3600;
	long long minutes = seconds / 60;
	seconds %= 60;
	return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}

int generation(int g) {
	//хороший рандомайзер
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> randMast(0, 3);
	std::uniform_int_distribution<> randNominal(6, 14);

	int counterPositiveCases = 0;
	for (int i = 0; i < iterations; i++) {
		std::cout << "generation = " << g + 1 << "\titer = " << i + 1;
		// генераци€ 3 карт
		std::vector<std::pair<int, int>> threeCards{ {0,0},{0,0},{0,0} };
		for (int j = 0; j < 3; j++)
		{
			bool flag = true;
			while (flag) {
				std::pair<int, int> card = std::make_pair(randMast(mt), randNominal(mt));
				if (!contains(threeCards, card)) {
					threeCards[j] = card;
					flag = false;
				}
			}
		}
		std::cout << "\tCards =";
		for (int k = 0; k < 3; k++)
		{
			std::cout << "\t{" << threeCards[k].first << ", " << threeCards[k].second << "}, ";
		}
		//

		if (isUnique(threeCards)) {
			std::cout << "\tUnique";
			counterPositiveCases++;
		}
		std::cout << std::endl;
	}
	return counterPositiveCases;
}