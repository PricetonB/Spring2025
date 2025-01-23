#include <iostream>



int main () {
  std::string name;
  int feet;
  int inches;
  float pounds;
  std::cout << "please enter your name, height in feet, height in inches, and weight in pounds. press enter after each input." << "\n";
  std::cin >> name >> feet >> inches >> pounds;
  float bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
  std::cout << "hello " << name << " your bmi is " << bmi << "\n";
  return 0;
}
