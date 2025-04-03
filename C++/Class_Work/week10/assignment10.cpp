//week 10
//
//

 

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
  inline static int total_people = 0;
  inline static int total_males = 0;
  inline static int total_females = 0;



  Person(std::string name, int feet, int inches, double weight, int bodyfat, char sex)
    : name(name), feet(feet), inches(inches), weight(weight), bodyfat(bodyfat), sex(sex)
  {
    calcBMI(feet, inches, weight);
    calcWeightClass(bmi, bodyfat, sex);
    total_people++;
    if (sex == 'm') {
      total_males++;
    }
    if (sex == 'f') {
      total_females++;
    }
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
    outfile 
  << this->name << " "  
  << this->feet << "," 
  << this->inches << " weight:" 
  << this->bodyfat << " sex:" 
  << this->sex << " bmi:"
  << this->bmi << " weightclass:" 
  << this->weightclass << "\n";
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

  //print_weightclass_distribution();
  
  return 0;



}







