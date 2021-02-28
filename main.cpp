#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;
using namespace std;

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
    return 0;
}