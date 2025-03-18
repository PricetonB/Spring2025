//assignment 8
//were going to add a constructor
//


#include <iostream>
#include <string>

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
};



int main() {
  Person person_one("Keith", 5, 5, 150, 20, 'm'); 
  return 0;
}

