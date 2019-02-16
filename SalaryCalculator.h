#ifndef SALARYCALCULATOR_H
#define SALARYCALCULATOR_H
#include <iostream>

class SalaryCalculator {

public:
  void printMenu();
  void printListFiles();
  void readFile(std::string);

private:
  float TAXRATE{0.31};
  std::string MAINFILE{"19files.txt"};

  void addFile();
  void printTable();
  void editSettings();

};

#endif
