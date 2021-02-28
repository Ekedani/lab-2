#include "processing_files.h"

void processTheFile(string pathToFile, vector<Country*> AllCountries) {
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
        processTheLine(currentLine, AllCountries);
        i++;
    }

    //Закрытие файла
    inFile.close();
}

//TODO: Исправить баг с передачей пустой строки в функцию
void processTheLine(string currentLine, vector<Country*> AllCountries){
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

void sortTheVector(vector<Country*> AllCountries){
    //Сортировка вставками
    for(int i = 1; i < AllCountries.size(); i++){
        for(int j = i; j > 0 && AllCountries[j - 1]->score > AllCountries[j]->score; j--){
            swap(AllCountries[j - 1],AllCountries[j]);
        }
    }
}

void outputTheResult(vector<Country*> AllCountries){
    //Создание файла на запись
    ofstream outFile;
    //TODO: проверь правильно ли будет создаваться файл
    outFile.open("result.csv");

    //Запись результатов в файл
    //TODO: нужно согласовать в каком порядке и что мы собираемся выводить
    //UPD: Балл,Страна,КоличествоГолосов
    //Баллы: 12, 10, 8, 7, 6, 5, 4, 3, 2, 1
    for(int countryNum = 0; countryNum < 10; countryNum++){
        //TODO: сделай так, чтобы в файл выводились нужные баллы
        int mark = 12;

        //TODO: проверь правильный ли будет вывод в файле result по такому принципу
        outFile << mark << "," << AllCountries[countryNum]->name << "," << AllCountries[countryNum]->score << endl;
    }
    //TODO: проверь результат: если он не будет совпадать с итогом, то обрати внимание на передачу вектора в функции

    //Закрытие файла
    outFile.close();
}


