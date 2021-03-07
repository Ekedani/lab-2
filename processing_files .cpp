#include "processing_files .h"

void processTheFile(string pathToFile, vector<Country*> &AllCountries, vector<vector<int>> &Lines){
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
        processTheLine(currentLine, AllCountries, Lines);
        i++;
    }

    //Закрытие файла
    inFile.close();
}

void processTheLine(string currentLine, vector<Country*> &AllCountries, vector<vector<int>> &Lines){
    //Создание элемента в векторе стран
    AllCountries.push_back(new Country());

    //Чтение и запись названия страны
    string separator = ",";
    AllCountries.back()->name = currentLine.substr(0, currentLine.find(separator));

    vector <int> Current_line;

    //Подсчет общего количества баллов
    string scoreString = currentLine.substr(currentLine.find(separator) + 1);
    int current_index = scoreString.find(separator);
    while(current_index != string::npos){
        int current_score = stoi(scoreString.substr(0, current_index));
        Current_line.push_back(current_score);
        scoreString.erase(0, current_index + 1);
        current_index = scoreString.find(separator);
    }
    int current_score = stoi(scoreString.substr(0, current_index));
    Current_line.push_back(current_score);
    Lines.push_back(Current_line);
}

void countingScores(vector<Country*> &AllCountries, vector<vector<int>> &Lines){
    int ranking[10] = {12,10,8,7,6,5,4,3,2,1};
    for (int column = 0; column < Lines[0].size(); ++column) {
        int i = 0;
        while(i<Lines.size()) {
            int max = 0;
            int ind_max = 0;
            for (int row = 0; row < Lines.size(); ++row) {
                if (Lines[row][column] > max) {
                    max = Lines[row][column];
                    ind_max = row;
                }
            }
            Lines[ind_max][column] = -1;
            AllCountries[ind_max]->score += ranking[i];
            i++;
            if(i>=10) break;
        }
    }
}

void sortTheVector(vector<Country*> &AllCountries){
    //Сортировка вставками
    for(int i = 1; i < AllCountries.size(); i++){
        for(int j = i; j > 0 && AllCountries[j - 1]->score < AllCountries[j]->score; j--){
            swap(AllCountries[j - 1],AllCountries[j]);
        }
    }
}

void outputTheResult(string pathToDirectory, vector<Country*> &AllCountries){
    //Создание файла на запись
    ofstream outFile;
    outFile.open(pathToDirectory + "result.csv");

    //Запись 10 лучших из вектора в файл
    for (int i = 0; i < 10; ++i) {
        outFile << (*AllCountries[i]).name << ","
                <<(*AllCountries[i]).score << endl;
    }
    //Закрытие файла
    outFile.close();
}
