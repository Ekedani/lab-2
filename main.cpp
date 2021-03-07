#include "processing_files .h"

int main() {
    //Храним все страны в одном векторе
    vector<Country*> AllCountries;

    vector<vector<int>> Lines;

    //Ввод папки с файлами
    string pathToDirectory;
    cout << "Please, enter the path to your folder" << endl;
    cin >> pathToDirectory;

    //Формирование вектора с путями к файлам указанной папки
    vector<string> pathsToFiles;
    for (const auto & entry : fs::directory_iterator(pathToDirectory)) {
        pathsToFiles.push_back(entry.path().string());
    }

    cout << "=========================" << endl;
    //Обработка каждого файла папки
    for (int i = 0; i < pathsToFiles.size(); ++i) {
        cout << pathsToFiles[i] << endl;
        processTheFile(pathsToFiles[i], AllCountries, Lines);
    }

    countingScores(AllCountries, Lines);
    sortTheVector(AllCountries);
    outputTheResult(pathToDirectory, AllCountries);
    return 0;
}

