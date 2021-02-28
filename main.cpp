#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;
using namespace std;
void processTheFile(string pathToFile);

//Структура для хранения информации про страну
struct Country{
    string name;
    int score;
};

//Храним все страны в одном векторе
vector<Country> AllCountries;

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
    //TODO: нужно открыть файл на чтение и работать со структурой
}