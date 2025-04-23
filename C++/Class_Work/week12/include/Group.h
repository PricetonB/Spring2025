
#ifndef GROUP_H
#define GROUP_H


#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Person.h"


class Group
{
private:
    int m_group_count;
    int m_male_count;
    int m_female_count;
    float m_group_bmi_avg;
    float m_male_bmi_avg;
    float m_female_bmi_avg;

    std::vector<Person> m_people;
    std::unordered_map<int, int> m_weight_class_counts;
    std::string m_weight_class_names[4];

    void m_print_weight_class_percentages();
    void m_print_person_info(Person person);
    void m_calculate_group_bmi_avg();
    void m_calculate_male_bmi_avg();
    void m_calculate_female_bmi_avg();

public:
    Group();

    void print_group_info();
    void print_person_info(int person_id);
    std::vector<Person> get_people();
    void add_person();
    void add_person_from_person_object(Person person_to_add);
    void change_person_info();
};

#endif // GROUP_H

