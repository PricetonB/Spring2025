//week six 
//

// i need a function that will take all user inputs and store them into vectors
// its noted i can probably create vectors in main and pass them to void function
// im not sure what the void function should do. 
// another function could take calc bmi and weight class function and calculate average bmi seperated by sex. 
// these functions have been implemented with m_calculate_bmi, m_calculate_male_bmi_avg, m_calculate_female_bmi_avg
// my plan is to make a vector in main that stores user inputs as instructed
// i will do this buy adding a get people function in the group class that returns vector of Person ojbects.
// i will call this function in main and set a local variable people. when a person is added people will be updated. 
// this isnt totally efficeint because every time we add a person we are copying the entire vector of people objects to main from group object. 
// it would be more efficient to add a Person object each time they are created but this creates two different person vectors and 
// could get confusing in the future so we will just copy the person vector from group object. 
// since Person objects hold all user inputs we now have a vector that is holding all user inputs in main. 

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>



//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


class Person {
private:
  std::string m_sex;
  std::string m_first_name;
  int m_weight_class_id;   // overweight = 0, probably not overweight = 1, normal weight = 2, under weight = 3
  int m_height_feet;
  int m_height_inches;
  int m_body_fat_percent;
  int m_id;
  float m_weight_pounds;
  float m_bmi;


  void m_calculate_bmi(int feet, int inches, float pounds) {
    m_bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
  }

   void m_calculate_the_fatness(float bmi, int body_fat_percent, std::string sex) {
     if (bmi > 25) {
       if (sex == "male" && body_fat_percent > 24) {
         m_weight_class_id = 0;
         return;
       }
       if (sex == "female" && body_fat_percent > 31) {
        m_weight_class_id = 0;
         return;
       }
       m_weight_class_id = 1;
       return;
     }
     if (bmi > 18.5) {
       m_weight_class_id = 2;
       return;
     }
     m_weight_class_id = 3;
     return;
   }






public:
  Person(std::string name, int height_inches, int height_feet, std::string sex, float pounds, int fat_percent, int id)
    : m_first_name(name), 
      m_height_inches(height_inches), 
      m_height_feet(height_feet),
      m_sex(sex), 
      m_weight_pounds(pounds),
      m_body_fat_percent(fat_percent),
      m_id(id){
    m_calculate_bmi(m_height_feet, m_height_inches, m_weight_pounds);
    m_calculate_the_fatness(m_bmi, m_body_fat_percent, m_sex);
  }

  std::string get_sex() {
    return m_sex;
  }

  std::string get_first_name() {
    return m_first_name;
  }

  int get_height_feet() {
    return m_height_feet;
  }

  int get_height_inches() {
    return m_height_inches;
  }

  int get_body_fat_percent() {
    return m_body_fat_percent;
  }

  int get_person_id() {
    return m_id;
  }

  float get_weight() {
    return m_weight_pounds;
  }

  float get_bmi() {
    return m_bmi;
  }

  int get_weight_class_id() {
    return m_weight_class_id;
  }


};

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------







class Group {
private:


  int m_group_count; // number of people in the group
  int m_male_count;  // number of males in the group
  int m_female_count; // number of females in group
  float m_group_bmi_avg; // 
  float m_male_bmi_avg;
  float m_female_bmi_avg;
  std::vector<Person> m_people;
  std::unordered_map<int, int> m_weight_class_counts = {{0,0}, {1,0}, {2,0}, {3,0}};   // weight_class_id : number of people in that weight class 
  std::string m_weight_class_names[4] = {"overweight", "probably not overweight", "normal", "underweight" };  

  
// 
void m_print_weight_class_percentages() {
    if (m_group_count != 0) {
        if (m_weight_class_counts[0] != 0) {
            std::cout << "overweight members: " 
                      << (static_cast<float>(m_weight_class_counts[0]) / m_group_count) * 100 
                      << "% \n";
        } else {
            std::cout << "overweight members: 0% \n";
        }

        if (m_weight_class_counts[1] != 0) {
            std::cout << "probably not overweight members: " 
                      << (static_cast<float>(m_weight_class_counts[1]) / m_group_count) * 100 
                      << "% \n";
        } else {
            std::cout << "probably not overweight members: 0% \n";
        }

        if (m_weight_class_counts[2] != 0) {
            std::cout << "normal members: " 
                      << (static_cast<float>(m_weight_class_counts[2]) / m_group_count) * 100 
                      << "% \n";
        } else {
            std::cout << "normal members: 0% \n";
        }

        if (m_weight_class_counts[3] != 0) {
            std::cout << "underweight members: " 
                      << (static_cast<float>(m_weight_class_counts[3]) / m_group_count) * 100 
                      << "% \n";
        } else {
            std::cout << "underweight members: 0% \n";
        }
    } else {
        std::cout << "Group count is zero. Cannot calculate percentages.\n";
    }

    return;
}


  void m_print_person_info(Person person) {
    
    std::cout << "Name: " << person.get_first_name() << "\n";
    std::cout << "Height: " << person.get_height_feet() << "," << person.get_height_inches() << "\n";
    std::cout << "Weight: " << person.get_weight() << "\n";
    std::cout << "Body Fat Percentage: " << person.get_body_fat_percent() << "\n";
    std::cout << "Sex: " << person.get_sex() << "\n";
    std::cout << "BMI: " << person.get_bmi() << "\n";
    std::cout << "Weight Class: " << m_weight_class_names[person.get_weight_class_id()] << "\n";
  }

//-------------------------------------------------------------------------------------

  void m_calculate_group_bmi_avg() {
    if (m_group_count == 0) {
      m_group_bmi_avg = 0;  // No people, so average BMI is 0
      return;
    }

    float total_bmi = 0;
    for (Person person : m_people) {
      total_bmi += person.get_bmi();
    }

    m_group_bmi_avg = total_bmi / m_group_count;
  }

  // Function to calculate the average BMI for male members of the group
  void m_calculate_male_bmi_avg() {
    if (m_male_count == 0) {
      m_male_bmi_avg = 0;  // No males in the group
      return;
    }

    float total_bmi_males = 0;
    for (Person person : m_people) {
      if (person.get_sex() == "male") {
        total_bmi_males += person.get_bmi();
      }
    }

    m_male_bmi_avg = total_bmi_males / m_male_count;
  }

  // Function to calculate the average BMI for female members of the group
  void m_calculate_female_bmi_avg() {
    if (m_female_count == 0) {
      m_female_bmi_avg = 0;  // No females in the group
      return;
    }

    float total_bmi_females = 0;
    for (Person person : m_people) {
      if (person.get_sex() == "female") {
        total_bmi_females += person.get_bmi();
      }
    }

    m_female_bmi_avg = total_bmi_females / m_female_count;
  }


public:

  Group()
   :m_group_count(0),
    m_male_count(0),
    m_female_count(0),
    m_male_bmi_avg(0),
    m_female_bmi_avg(0),
    m_group_bmi_avg(0) {}

  void print_group_info() {
    if (m_group_count == 0) {
      std::cout << "there are no people in the group \n";
      return;
    }

    std::cout << "Number of people in group: " << m_group_count << "\n";
    std::cout << "Group BMI average: " << m_group_bmi_avg << "\n";
    std::cout << "Male BMI average: " << m_male_bmi_avg << "\n" ;
    std::cout << "Female BMI average: " << m_female_bmi_avg << "\n";
    m_print_weight_class_percentages();
  }

  void print_person_info(int person_id) {
    if (person_id > m_group_count - 1) {
      std::cout << "UNABLE TO FIND PERSON ID " << person_id << "\n";
      return;
    }
    m_print_person_info(m_people[person_id]);
  }

  //added for assignment 6
  std::vector<Person> get_people() {
    return m_people;
  }



  void add_person() {
    std::string name;
    int feet;
    int inches;
    float pounds;
    int body_fat_percent;
    std::string sex;
    int person_id;

    
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

    std::cout << "Male or female? " << "\n";
    std::cin.ignore();  
    std::getline(std::cin, sex);  

    while (sex != "male" && sex != "female") {
        std::cout << "Try again. Type male or female all lowercase and press enter. \n";
        std::getline(std::cin, sex);  
    }


    person_id = m_group_count;
 
    Person person_to_add = Person(name, inches, feet, sex, pounds, body_fat_percent, person_id);
    m_people.push_back(person_to_add);
    m_weight_class_counts[person_to_add.get_weight_class_id()]++;



    m_group_count += 1;
    if (sex == "male") {
      m_male_count += 1;
      m_calculate_male_bmi_avg();
      
      
    }
    if (sex == "female") {
      m_female_count +=1;
      m_calculate_female_bmi_avg();
    }
    m_calculate_group_bmi_avg();


    std::cout << "PERSON CREATED! PERSON ID IS " << person_id << "\n";
  }

};







int main (int argc, char *argv[]) {
  std::vector<Person> people = {}; //assignment 6 addition

  Group group = Group();

  int running = true;

  while (running) {
    int choice;
    std::cout << "Please type a number from actions below and press enter \n ";
    std::cout << "1 = Add Person \t 2 = Get Person Information \t 3 = Get Group Information \t 4 = Quit \n";
    std::cin >> choice;

    switch (choice) {
      case 1:
        group.add_person();
        people = group.get_people(); //assignment 6 addition
        break;
      case 2:
        int id_entered;
        std::cout << "Please enter persons ID: \n";
        std::cin >> id_entered;
        group.print_person_info(id_entered);
        break;
      case 3:
        group.print_group_info();
        break;
      case 4:
        running = false;
        break;
      default:
        std::cout << choice << " is not a valid choice \n ";
        break;
    
    }

  
  }



  return 0;
}



