#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;
void processTheFile(string pathToFile);
void processTheLine(string currentLine);

//Структура для хранения информации про страну
struct Country{
    string name;
    int score;
    Country() : score(0)
    {
    }
};

//Храним все страны в одном векторе
vector<Country*> AllCountries;

int main() {
    //Ввод папки с файлами
    string pathToDirectory;
    cout << "Please, enter the path to your folder" << endl;
    cin >> pathToDirectory;

    //Формирование вектора с путями к файлам указанной папки
    vector<string> pathsToFiles;
    for (const auto & entry : fs::directory_iterator(pathToDirectory)) {
        pathsToFiles.push_back(entry.path().string());
    }

    //Обработка каждого файла папки
    for (int i = 0; i < pathsToFiles.size(); ++i) {
        processTheFile(pathsToFiles[i]);
    }
    return 0;
}

void processTheFile(string pathToFile) {
    //Открытие файла на чтение
    ifstream inFile;
    inFile.open(pathToFile);

    //Считываем количество стран в файле
    int numberOfLines;
    inFile >> numberOfLines;

    //Итерация по странам
    string currentLine;
    int i = 0;
    while(i<=numberOfLines){
        getline(inFile, currentLine);
        processTheLine(currentLine);
        i++;
    }

    //Закрытие файла
    inFile.close();
}

void processTheLine(string currentLine){
    //Создание элемента в векторе стран
    AllCountries.push_back(new Country());

    //Чтение и запись названия страны
    string separator = ",";
    AllCountries.back()->name = currentLine.substr(0, currentLine.find(separator));

    //Подсчет общего количества баллов
    string scoreString = currentLine.substr(currentLine.find(separator) + 1);
    int current_index = scoreString.find(separator);
    while(current_index != string::npos){
        int current_score = stoi(scoreString.substr(0, current_index));
        AllCountries.back()->score += current_score;
        scoreString.erase(0, current_index + 1);
    }
}