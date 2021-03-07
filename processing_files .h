#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

//Структура для хранения информации про страну
struct Country{
    string name;
    int score;
    Country() : score(0)
    {
    }
};

void processTheFile(string pathToFile, vector<Country*> &AllCountries, vector<vector<int>> &Lines);
void processTheLine(string currentLine, vector<Country*> &AllCountries, vector<vector<int>> &Lines);
void countingScores(vector<Country*> &AllCountries, vector<vector<int>> &Lines);
void sortTheVector(vector<Country*> &AllCountries);
void outputTheResult(string pathToDirectory, vector<Country*> &AllCountries);

