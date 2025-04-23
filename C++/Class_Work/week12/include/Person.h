#ifndef PERSON_H
#define PERSON_H

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>




class Person
{
private:
    char m_sex;
    std::string m_first_name;
    int m_weight_class_id;
    int m_height_feet;
    int m_height_inches;
    int m_body_fat_percent;
    int m_id;
    float m_weight_pounds;
    float m_bmi;

    void m_calculate_bmi(int feet, int inches, float pounds);
    void m_calculate_the_fatness(float bmi, int body_fat_percent, char sex);

public:
    Person(std::string name, int height_inches, int height_feet, char sex, float pounds, int fat_percent, int id);

    // Getters
    char get_sex();
    std::string get_first_name();
    int get_height_feet();
    int get_height_inches();
    int get_body_fat_percent();
    int get_person_id();
    float get_weight();
    float get_bmi();
    int get_weight_class_id();

    // Setters
    void set_name(std::string name);
    void set_height(int feet, int inches);
    void set_weight(float pounds);
    void set_body_fat(int fat);
    void set_sex(char sex);

    // File handling
    void append_person_to_file(std::string file_name);
};

#endif // PERSON_H

