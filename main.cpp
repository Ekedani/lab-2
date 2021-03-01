#include "processing_files.h"

int main() {
    vector<Country*> AllCountries;
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
        processTheFile(pathsToFiles[i], AllCountries);
    }
    sortTheVector(vector<Country*> AllCountries);
    outputTheResult(pathToDirectory, vector<Country*> AllCountries);
    return 0;
}
