//week 3
#include <iostream>


 void calculate_the_fatness(float bmi, int body_fat_percent, std::string sex) {
   if (bmi > 25) {
     if (sex == "male" && body_fat_percent > 24) {
       std::cout << "OVERWEIGHT!! \n";
       return;
     }
     if (sex == "female" && body_fat_percent > 31) {
       std::cout << "OVERWEIGHT!! \n";
       return;
     }
     std::cout << "probably not overweight \n";
     return;
   }
   if (bmi > 18.5) {
     std::cout << "normal weight \n";
     return;
   }
   std::cout << "underweight \n";
   return;
 }



int main () {
  std::string name;
  int feet;
  int inches;
  float pounds;
  int body_fat_percent;
  std::string sex;
  float bmi;

  
  std::cout << "please enter your first name "  << "\n";
  std::cin >> name; 

  std::cout << "please enter your height in feet "  << "\n";
  std::cin >> feet ; 

  std::cout << "how many inches on top of those feet? "  << "\n";
  std::cin >> inches; 

  std::cout << "please enter how many pounds you are "  << "\n";
  std::cin >> pounds; 

  std::cout << "please enter your body fat percent "  << "\n";
  std::cin >> body_fat_percent; 

  std::cout << "male or female? "  << "\n";
  std::cin >> sex; 

  
  bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
  std::cout << "hello " << name << " your bmi is " << bmi << "\n";

  calculate_the_fatness(bmi,body_fat_percent,sex);


return 0;
}
