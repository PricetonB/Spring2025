#include "include/Group.h"


    //
    void Group::m_print_weight_class_percentages()
    {
        if (m_group_count != 0)
        {
            if (m_weight_class_counts[0] != 0)
            {
                std::cout << "overweight members: "
                          << (static_cast<float>(m_weight_class_counts[0]) / m_group_count) * 100
                          << "% \n";
            }
            else
            {
                std::cout << "overweight members: 0% \n";
            }

            if (m_weight_class_counts[1] != 0)
            {
                std::cout << "probably not overweight members: "
                          << (static_cast<float>(m_weight_class_counts[1]) / m_group_count) * 100
                          << "% \n";
            }
            else
            {
                std::cout << "probably not overweight members: 0% \n";
            }

            if (m_weight_class_counts[2] != 0)
            {
                std::cout << "normal members: "
                          << (static_cast<float>(m_weight_class_counts[2]) / m_group_count) * 100
                          << "% \n";
            }
            else
            {
                std::cout << "normal members: 0% \n";
            }

            if (m_weight_class_counts[3] != 0)
            {
                std::cout << "underweight members: "
                          << (static_cast<float>(m_weight_class_counts[3]) / m_group_count) * 100
                          << "% \n";
            }
            else
            {
                std::cout << "underweight members: 0% \n";
            }
        }
        else
        {
            std::cout << "Group count is zero. Cannot calculate percentages.\n";
        }

        return;
    }

    void Group::m_print_person_info(Person person)
    {

        std::cout << "Name: " << person.get_first_name() << "\n";
        std::cout << "Height: " << person.get_height_feet() << "," << person.get_height_inches() << "\n";
        std::cout << "Weight: " << person.get_weight() << "\n";
        std::cout << "Body Fat Percentage: " << person.get_body_fat_percent() << "\n";
        std::cout << "Sex: " << person.get_sex() << "\n";
        std::cout << "BMI: " << person.get_bmi() << "\n";
        std::cout << "Weight Class: " << m_weight_class_names[person.get_weight_class_id()] << "\n";
    }

    //-------------------------------------------------------------------------------------

    void Group::m_calculate_group_bmi_avg()
    {
        if (m_group_count == 0)
        {
            m_group_bmi_avg = 0; // No people, so average BMI is 0
            return;
        }

        float total_bmi = 0;
        for (Person person : m_people)
        {
            total_bmi += person.get_bmi();
        }

        m_group_bmi_avg = total_bmi / m_group_count;
    }

    // Function to calculate the average BMI for male members of the group
    void Group::m_calculate_male_bmi_avg()
    {
        if (m_male_count == 0)
        {
            m_male_bmi_avg = 0; // No males in the group
            return;
        }

        float total_bmi_males = 0;
        for (Person person : m_people)
        {
            if (person.get_sex() == 'm')
            {
                total_bmi_males += person.get_bmi();
            }
        }

        m_male_bmi_avg = total_bmi_males / m_male_count;
    }

    // Function to calculate the average BMI for female members of the group
    void Group::m_calculate_female_bmi_avg()
    {
        if (m_female_count == 0)
        {
            m_female_bmi_avg = 0; // No females in the group
            return;
        }

        float total_bmi_females = 0;
        for (Person person : m_people)
        {
            if (person.get_sex() == 'f')
            {
                total_bmi_females += person.get_bmi();
            }
        }

        m_female_bmi_avg = total_bmi_females / m_female_count;
    }

  Group::Group()
        : m_group_count(0),
          m_male_count(0),
          m_female_count(0),
          m_male_bmi_avg(0),
          m_female_bmi_avg(0),
          m_group_bmi_avg(0) {}

    void Group::print_group_info()
    {
        if (m_group_count == 0)
        {
            std::cout << "there are no people in the group \n";
            return;
        }

        std::cout << "Number of people in group: " << m_group_count << "\n";
        std::cout << "Group BMI average: " << m_group_bmi_avg << "\n";
        std::cout << "Male BMI average: " << m_male_bmi_avg << "\n";
        std::cout << "Female BMI average: " << m_female_bmi_avg << "\n";
        m_print_weight_class_percentages();
    }

    void Group::print_person_info(int person_id)
    {
        if (person_id > m_group_count - 1)
        {
            std::cout << "UNABLE TO FIND PERSON ID " << person_id << "\n";
            return;
        }
        m_print_person_info(m_people[person_id]);
    }

    std::vector<Person> Group::get_people()
    {
        return m_people;
    }

    void Group::add_person()
    {
        std::string name;
        int feet;
        int inches;
        float pounds;
        int body_fat_percent;
        char sex;
        int person_id;

        std::cout << "please enter your first name " << "\n";
        std::cin >> name;

        std::cout << "please enter your height in feet " << "\n";
        std::cin >> feet;

        std::cout << "how many inches on top of those feet? " << "\n";
        std::cin >> inches;

        std::cout << "please enter how many pounds you are " << "\n";
        std::cin >> pounds;

        std::cout << "please enter your body fat percent " << "\n";
        std::cin >> body_fat_percent;

        std::cout << "Male or female? Type m or f. " << "\n";
        std::cin.ignore(); // Clear leftover newline from previous input
        std::cin >> sex;   // Read a single char
        
        while (sex != 'm' && sex != 'f') {
            std::cout << "Try again. Type m or f for male or female and press enter.\n";
            std::cin >> sex;
        }

        person_id = m_group_count;

        Person person_to_add = Person(name, inches, feet, sex, pounds, body_fat_percent, person_id);
        m_people.push_back(person_to_add);
        m_weight_class_counts[person_to_add.get_weight_class_id()]++;

        m_group_count += 1;
        if (sex == 'm')
        {
            m_male_count += 1;
            m_calculate_male_bmi_avg();
        }
        if (sex == 'f')
        {
            m_female_count += 1;
            m_calculate_female_bmi_avg();
        }
        m_calculate_group_bmi_avg();

        std::cout << "PERSON CREATED! PERSON ID IS " << person_id << "\n";
    }

    void Group::add_person_from_person_object(Person person_to_add)
    {
        m_people.push_back(person_to_add);
        m_weight_class_counts[person_to_add.get_weight_class_id()]++;
    
        m_group_count += 1;
        if (person_to_add.get_sex() == 'm')
        {
            m_male_count += 1;
            m_calculate_male_bmi_avg();
        }
        if (person_to_add.get_sex() == 'f')
        {
            m_female_count += 1;
            m_calculate_female_bmi_avg();
        }
        m_calculate_group_bmi_avg();
    }

    //function added to manage setters for assignment 11
    void Group::change_person_info()
    {
        int id;
        std::cout << "Enter the ID of the person to change: ";
        std::cin >> id;
    
        if (id < 0 || id >= m_people.size())
        {
            std::cout << "Invalid ID.\n";
            return;
        }
    
        std::string name;
        int feet, inches, fat;
        float weight;
        char sex;
    
        std::cout << "Enter new first name: ";
        std::cin >> name;
        std::cout << "Enter new height (feet): ";
        std::cin >> feet;
        std::cout << "Enter new height (inches): ";
        std::cin >> inches;
        std::cout << "Enter new weight in pounds: ";
        std::cin >> weight;
        std::cout << "Enter new body fat percentage: ";
        std::cin >> fat;
        std::cout << "Enter new sex (m/f): ";
        std::cin >> sex;
    
        m_people[id].set_name(name);
        m_people[id].set_height(feet, inches);
        m_people[id].set_weight(weight);
        m_people[id].set_body_fat(fat);
        m_people[id].set_sex(sex);
    
        std::cout << "Person updated.\n";
    
        // You might want to recalculate group BMI averages here:
        m_calculate_group_bmi_avg();
        m_calculate_male_bmi_avg();
        m_calculate_female_bmi_avg();
    }
    




