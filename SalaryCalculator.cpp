#include "SalaryCalculator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

void SalaryCalculator::addFile(){
  std::string filename{};
  cout << "Enter filename: ";
  cin >> filename;
  std::cout << '\n';
  std::ofstream temp(filename);

  if(!temp){
    cerr << "Unable to open data file '" + filename + "'." << endl;
    return;
  }
  temp.close();

  std::ofstream fw;
  fw.open(MAINFILE, std::ios_base::app);
  if(!fw){
    cerr << "Unable to open data file '" << MAINFILE << "'." << endl;
    return;
  }
  fw << filename << endl;
  fw.close();
  cout << "File '" << filename << "' added succesful." << endl;
  cout << endl;
}

void SalaryCalculator::editSettings(){
  cout << "The default source file is '" << MAINFILE << "'."<< endl;
  cout << "Enter the new source filename: ";
  std::string filename{};
  cin >> filename;
  std::ifstream fr(filename);
  if(!fr){
    cerr << "Unable to open file '" << filename
    << "'. Please check the file." << endl;
    cout << endl;
    return;
  }
  MAINFILE = filename;
  cout << "File found. Successfully changed source file to '" << filename
  << "'." << endl;
  cout << "The default tax rate is: " << TAXRATE << endl;
  cout << "Enter new tax: ";
  float newTax{};
  cin >> newTax;
  if(newTax != TAXRATE){
    TAXRATE = newTax;
    cout << "Tax has been Successfully changed." << endl;
  }
  cout << endl;
}

void SalaryCalculator::printListFiles(){
  std::ifstream fr(MAINFILE);
  if(!fr){
    cerr << "Unable to open file '" << MAINFILE << "'." << endl;
    return;
  }

  std::string filename{};
  cout << "\nThe files are: " << endl;
    while(getline(fr, filename)){
    cout << filename << endl;
  }
  cout << endl;
  fr.close();
}

void SalaryCalculator::readFile(std::string filename){
  if(filename == MAINFILE){
    std::ifstream fr(filename);
    if(!fr){
      cerr << "Unable to open data file '" << filename << "'." << endl;
      return;
    }

    std::string line{};
    while(getline(fr, line)){
      readFile(line);
      cout << endl;
    }
    fr.close();
  }
  // read data and print as table
  else{
    std::ifstream data(filename);
    if(!data){
      std::cerr << "Unable to open data file " << filename << "." << std::endl;
      return;
    }

    std::string line{};
    getline(data,line); //omit the first line
    std::cout << "TIME TABLE " << filename << std::endl;
    std::cout << "================" << std::endl;
    std::cout << std::setfill(' ') << std::setw(13) << std::right << "Date"
        << std::setw(6) << std::right << "Hours"
        << std::setw(12) << std::right << "Salary_hour"
        << std::setw(9) << std::right << "Salary" << std::endl;
    std::cout << std::setw(40) << std::setfill('-') <<"" << std::endl;

    float hours{};
    int sum_salary{};

    while(getline(data,line)){
      std::istringstream ss(line);
      std::string l1{}, l2{}, l3{};
      getline(ss, l1, ' ');
      getline(ss, l2, ' ');
      getline(ss, l3, ' ');
      float h{stof(l2)};
      int s{static_cast<int>(h*stoi(l3))};

      cout << std::setw(13) << std::right << std::setfill(' ')  << l1
      << std::setw(6) << std::right << l2 << std::setw(12)
      << std::right << l3 << std::setw(9) << std::right << s << '\n';
      hours += h;
      sum_salary += s;
    }
    data.close();
    cout << std::setw(40) << std::setfill('-') << "" << endl;
    cout << std::setprecision(3) <<"You earned totally on " << hours << " hours: " << sum_salary << " kr" << std::endl;
    if(hours!=0)
      cout << "Salary per hour is: " << static_cast<int>(sum_salary/hours) << " kr" << std::endl;
    cout << "After tax: " << static_cast<int>(sum_salary*(1-TAXRATE)) << " kr" << std::endl;
  }
}

void SalaryCalculator::printTable(){
 readFile(MAINFILE);
}

void SalaryCalculator::printMenu(){
  int choice{0};
  cout << "MENU" << endl;
  cout << "1. Print table" << endl;
  cout << "2. Print list of files" << endl;
  cout << "3. Add file to list of files" << endl;
  cout << "4. Edit source file and tax rate" << endl;
  cout << "5. Exit menu" << endl;
  cout << "Enter your choice: ";
  cin >> choice;
  switch (choice) {
    case 1:
      printTable();
      break;
    case 2:
      printListFiles();
      printMenu();
      break;
    case 3:
      addFile();
      printMenu();
      break;
    case 4:
      editSettings();
      printMenu();
    default:
      break;
  }
}

int main() {
  cout << "Welcome to Salary calculator!" << '\n';
  cout << "This program will sum all the hours and salary." << endl;
  SalaryCalculator *sc = new SalaryCalculator;
  sc->printMenu();
  delete sc;
}
