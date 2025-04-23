
#include "include/Person.h"
#include <fstream> 

Person::Person(std::string name, int height_inches, int height_feet, char sex, float pounds, int fat_percent, int id)
    : m_first_name(name),
      m_height_inches(height_inches),
      m_height_feet(height_feet),
      m_sex(sex),
      m_weight_pounds(pounds),
      m_body_fat_percent(fat_percent),
      m_id(id)
{
    m_calculate_bmi(m_height_feet, m_height_inches, m_weight_pounds);
    m_calculate_the_fatness(m_bmi, m_body_fat_percent, m_sex);
}

void Person::m_calculate_bmi(int feet, int inches, float pounds)
{
    m_bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
}

void Person::m_calculate_the_fatness(float bmi, int body_fat_percent, char sex)
{
    if (bmi > 25)
    {
        if (sex == 'm' && body_fat_percent > 24)
        {
            m_weight_class_id = 0;
            return;
        }
        if (sex == 'f' && body_fat_percent > 31)
        {
            m_weight_class_id = 0;
            return;
        }
        m_weight_class_id = 1;
        return;
    }
    if (bmi > 18.5)
    {
        m_weight_class_id = 2;
        return;
    }
    m_weight_class_id = 3;
}


char Person::get_sex() { return m_sex; }
std::string Person::get_first_name() { return m_first_name; }
int Person::get_height_feet() { return m_height_feet; }
int Person::get_height_inches() { return m_height_inches; }
int Person::get_body_fat_percent() { return m_body_fat_percent; }
int Person::get_person_id() { return m_id; }
float Person::get_weight() { return m_weight_pounds; }
float Person::get_bmi() { return m_bmi; }
int Person::get_weight_class_id() { return m_weight_class_id; }

 //setters added for assignment 11
void Person::set_name(std::string name) {
    m_first_name = name;
}

void Person::set_height(int feet, int inches) {
    m_height_feet = feet;
    m_height_inches = inches;
    m_calculate_bmi(feet, inches, m_weight_pounds);
    m_calculate_the_fatness(m_bmi, m_body_fat_percent, m_sex);
}

void Person::set_weight(float pounds) {
    m_weight_pounds = pounds;
    m_calculate_bmi(m_height_feet, m_height_inches, pounds);
    m_calculate_the_fatness(m_bmi, m_body_fat_percent, m_sex);
}

void Person::set_body_fat(int fat) {
    m_body_fat_percent = fat;
    m_calculate_the_fatness(m_bmi, fat, m_sex);
}

void Person::set_sex(char sex) {
    m_sex = sex;
    m_calculate_the_fatness(m_bmi, m_body_fat_percent, sex);
}

// lazy way of handling the csv implementation from chapter 9
void Person::append_person_to_file(std::string file_name)
{
    std::ofstream outfile(file_name, std::ios::app);
    outfile
        << m_first_name << " "
        << m_height_feet << "," << m_height_inches
        << " weight:" << m_body_fat_percent
        << " sex:" << m_sex
        << " bmi:" << m_bmi
        << " weightclass:" << m_weight_class_id
        << "\n";
    outfile.close();
}

