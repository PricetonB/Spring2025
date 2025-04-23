
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


#include "include/Person.h"
#include "include/Group.h"


//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------







int main(int argc, char *argv[])
{

    Group group = Group();

    int running = true;

    //get people from csv file and add to vector of people 
    std::ifstream f("people.csv");
    std::vector<std::string> lines;
    std::string line;
    std::vector<Person> people;
    while (getline(f, line))
    {
        lines.push_back(line);
    }
    f.close();

    int id_counter = 0; // Temporary counter for id. Needs refactored where the group class handles csv file not person class to better manage ids.
    for (std::string l : lines)
    {
        std::stringstream ss(l);
        std::string name;
        std::string feet;
        std::string inches;
        std::string weight;
        std::string bodyfat;
        std::string sex;
        getline(ss, name, ',');
        getline(ss, feet, ',');
        getline(ss, inches, ',');
        getline(ss, weight, ',');
        getline(ss, bodyfat, ',');
        getline(ss, sex, ',');
        Person person(name, std::stoi(inches), std::stoi(feet), sex[0], std::stof(weight), std::stoi(bodyfat), id_counter++);
        people.push_back(person);
    }

    // append people in vector of people to txt file and add them to group object
    for (Person person : people)
    {
        person.append_person_to_file("output.txt");
        group.add_person_from_person_object(person);
    }

//now that the csv file has been read and the group object has been populated with people, we can start the menu loop to add people
// and get information about the group and people in the group.


    while (running)
    {
        int choice;
        std::cout << "Please type a number from actions below and press enter \n ";
        std::cout << "1 = Add Person \n 2 = Get Person Information \n 3 = Get Group Information \n 4 = Quit \n 5 = Change Person Information \n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            group.add_person();
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
        // added for assignment 11 to manage setters for person class
        case 5:
            group.change_person_info();
            break;
        default:
            std::cout << choice << " is not a valid choice \n ";
            break;
        }
    }

    return 0;
}
