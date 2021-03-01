#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;
void processTheFile(string pathToFile);
void processTheLine(string currentLine);
void sortTheVector();
void outputTheResult(string pathToDirectory);

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
    sortTheVector();
    outputTheResult(pathToDirectory);
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
    inFile.ignore();
    while(i<numberOfLines){
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
        current_index = scoreString.find(separator);
    }
    int current_score = stoi(scoreString.substr(0, current_index));
    AllCountries.back()->score += current_score;
}

void sortTheVector(){
    //Сортировка вставками
    for(int i = 1; i < AllCountries.size(); i++){
        for(int j = i; j > 0 && AllCountries[j - 1]->score < AllCountries[j]->score; j--){
            swap(AllCountries[j - 1],AllCountries[j]);
        }
    }
}

void outputTheResult(string pathToDirectory){
    //Создание файла на запись
    ofstream outFile;
    outFile.open(pathToDirectory + "result.csv");

    //Запись 10 лучших из вектора в файл
    int ranking[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 10; ++i) {
        outFile << (*AllCountries[i]).name << ","
        <<(*AllCountries[i]).score << "," << ranking[i] << endl;
    }
    //Закрытие файла
    outFile.close();
}
