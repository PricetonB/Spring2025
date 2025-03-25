//assignment 9 
//
//ive been reading a book about operating system code for linux and im on the thread section
//it talks about how threads are created and used for atomic processes that cant be interupted
//i want to play with this c thread library and it turns out...its fully compatible with c++
//so im going to read from the csv file as instructed however im also going to add a user input
//for thread count at the beginning of main. then i will divy up the csv file for example with
//2 threads the first one gets first half of csv and second thread gets second half of csv.
//setting it up this way doesnt require locks because the threads never mess with each others data.
//im going to start a timer at beginning of main and kill it at end printing the time it took to run code.
//feel free to play around with different thread numbers and file sizes to see speed difference. 

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>



class Person {
public:
  std::string name; 
  int feet;
  int inches;
  double weight;
  int bodyfat;
  char sex;
  double bmi;
  char weightclass;

  Person(std::string name, int feet, int inches, double weight, int bodyfat, char sex)
    : name(name), feet(feet), inches(inches), weight(weight), bodyfat(bodyfat), sex(sex)
  {
    calcBMI(feet, inches, weight);
    calcWeightClass(bmi, bodyfat, sex);
    std::cout << "Object created for " << name << "\n";
  }

  void calcBMI(int feet, int inches, double weight) {
    bmi = weight / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
  }

  void calcWeightClass(double bmi, int bodyfat, char sex) {
    if (bmi > 25) {
      if (sex == 'm' && bodyfat > 24) {
        weightclass = 'o'; // overweight
        return;
      }
      if (sex == 'f' && bodyfat > 31) {
        weightclass = 'o'; // overweight
        return;
      }
      weightclass = 'p'; // probably not overweight
      return;
    }
    if (bmi > 18.5) {
      weightclass = 'n'; // not overweight
      return;
    }
    weightclass = 'u'; // underweight
  }

  void append_person_to_file(std::string file_name) {
    
    std::ofstream outfile(file_name, std::ios::app);
    outfile << this->name << " "  << this->feet << ", " 
  << this->inches << " " << "weight: " 
  << this->bodyfat << "sex: " << this->sex 
  << "bmi: " << this->bmi << "weightclass: " << this->weightclass << "\n";
    outfile.close();
    return;
  }
};



int main() {
  Person person_one("Keith", 5, 5, 150, 20, 'm'); 
  std::ifstream f("datafile.csv");
  std::vector<std::string> lines;
  std::string line;
  std::vector<Person> people;
  while(getline(f,line)) {
    lines.push_back(line);
  }
  f.close();

  for(std::string l : lines) {
    std::stringstream ss(l);
    std::string name;
    std::string feet;
    std::string inches;
    std::string weight;
    std::string bodyfat;
    std::string sex;
    getline(ss, name,',');
    getline(ss, feet,',');
    getline(ss, inches,',');
    getline(ss, weight,',');
    getline(ss, bodyfat,',');
    getline(ss, sex,',');
    Person person(name,std::stoi(feet),std::stoi(inches),std::stoi(weight),std::stoi(bodyfat),sex[0]);
    people.push_back(person);
  }


  for (Person person : people) {
    person.append_person_to_file("output.txt");

  }

  
  return 0;



}



























