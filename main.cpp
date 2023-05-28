#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct list {
  std::string name;
  std::string lastname;
  char date[10]{};
  int salary = 0;
};

bool checkName(std::string &name) {
  if (!(std::isalpha(static_cast<unsigned char>(name[0]))) ||
      !(std::isupper(static_cast<unsigned char>(name[0])))) {
    return false;
  } else {
    for (int i = 1; i < name.length(); ++i) {
      if (!(std::isalpha(static_cast<unsigned char>(name[i])))) {
        return false;
      }
    }
  }
  return true;
}

bool checkDate(const char *date) {
  if (date[2] != '.' && date[5] != '.') {
    return false;
  }
  return true;
}
void recordFile(std::string &path, std::vector<list> &data) {
  std::ofstream file(path, std::ios::app);
  if (!file.is_open()) {
    std::cout << "Error opening file!" << std::endl;
  }
  for (int i = 0; (i < data.size()); ++i) {
    file << data.at(i).name << " " << data.at(i).lastname
         << " " << data.at(i).date << " " << data.at(i).salary << std::endl;
  }
  file.close();
}
void printFile(std::string &path) {

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Error opening file!" << std::endl;
  }
  while (!file.eof()) {
    list person;
    file >> person.name >> person.lastname
         >> person.date >> person.salary;
    if (person.name.empty())
      break;
    std::cout << person.name << " " << person.lastname << " "
              << person.date << " " << person.salary << std::endl;
  }
  file.close();
}
int main() {
  std::vector<list> data{};
  list person;
  std::string command;
  std::string path = "file.txt";
  do {
    std::cout << "Enter the command <list> or <add>. For exit input <exit>:" << std::endl;
    std::cin >> command;
    if (command == "add") {
      std::cout << "Input name:";
      std::cin >> person.name;
      if (!checkName(person.name)) {
        std::cout << "Incorrect name!" << std::endl;
        continue;
      }
      std::cout << "Input lastname:";
      std::cin >> person.lastname;
      if (!checkName(person.lastname)) {
        std::cout << "Incorrect lastname!" << std::endl;
        continue;
      }
      std::cout << "Input date: ";
      std::cin >> person.date;
      if (!checkDate(person.date)) {
        std::cout << "Incorrect date!" << std::endl;
        continue;
      }
      std::cout << "Input salary: ";
      std::cin >> person.salary;
      if (person.salary <= 0) {
        std::cout << "Incorrect salary!" << std::endl;
        break;
      }
      data.push_back(person);
      recordFile(path, data);
    } else if (command == "list") {
      printFile(path);
    }
  } while (command != "exit");
  return 0;
}
