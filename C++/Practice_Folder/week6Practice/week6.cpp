//going to make some text/
//

#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Model: Person class
class Person {
private:
    std::string m_sex;
    std::string m_first_name;
    int m_weight_class_id;   // overweight = 0, probably not overweight = 1, normal weight = 2, underweight = 3
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
        m_id(id) {
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

// Model: Group class
class Group {
private:
    int m_group_count;
    int m_male_count;
    int m_female_count;
    float m_group_bmi_avg;
    float m_male_bmi_avg;
    float m_female_bmi_avg;
    std::vector<Person> m_people;
    std::unordered_map<int, int> m_weight_class_counts = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};  // weight_class_id : number of people in that weight class
    std::string m_weight_class_names[4] = {"overweight", "probably not overweight", "normal", "underweight"};

public:
    Group()
        : m_group_count(0),
        m_male_count(0),
        m_female_count(0),
        m_male_bmi_avg(0),
        m_female_bmi_avg(0),
        m_group_bmi_avg(0) {}

    void add_person(std::string name, int height_feet, int height_inches, std::string sex, float pounds, int body_fat_percent) {
        int person_id = m_group_count;
        Person person_to_add(name, height_inches, height_feet, sex, pounds, body_fat_percent, person_id);
        m_people.push_back(person_to_add);
        m_weight_class_counts[person_to_add.get_weight_class_id()]++;

        m_group_count += 1;
        if (sex == "male") {
            m_male_count += 1;
        } else if (sex == "female") {
            m_female_count += 1;
        }

        m_calculate_group_bmi_avg();
        m_calculate_male_bmi_avg();
        m_calculate_female_bmi_avg();
    }

    void m_calculate_group_bmi_avg() {
        if (m_group_count == 0) {
            m_group_bmi_avg = 0;
            return;
        }

        float total_bmi = 0;
        for (Person person : m_people) {
            total_bmi += person.get_bmi();
        }
        m_group_bmi_avg = total_bmi / m_group_count;
    }

    void m_calculate_male_bmi_avg() {
        if (m_male_count == 0) {
            m_male_bmi_avg = 0;
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

    void m_calculate_female_bmi_avg() {
        if (m_female_count == 0) {
            m_female_bmi_avg = 0;
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

    int get_group_count() {
        return m_group_count;
    }

    float get_group_bmi_avg() {
        return m_group_bmi_avg;
    }

    float get_male_bmi_avg() {
        return m_male_bmi_avg;
    }

    float get_female_bmi_avg() {
        return m_female_bmi_avg;
    }

    std::vector<Person>& get_people() {
        return m_people;
    }
};

// View: GTK GUI
class View {
private:
    Group& m_group; // Reference to the Model (Group)

    GtkWidget *m_window;
    GtkWidget *m_vbox;
    GtkWidget *m_add_person_button;
    GtkWidget *m_get_person_info_button;
    GtkWidget *m_get_group_info_button;
    GtkWidget *m_quit_button;

public:
    View(Group& group) : m_group(group) {
        gtk_init(NULL, NULL);

        // Create window
        m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(m_window), "Person and Group Info");
        gtk_window_set_default_size(GTK_WINDOW(m_window), 400, 300);

        // Create vertical box container
        m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_container_add(GTK_CONTAINER(m_window), m_vbox);

        // Create buttons
        m_add_person_button = gtk_button_new_with_label("Add Person");
        m_get_person_info_button = gtk_button_new_with_label("Get Person Information");
        m_get_group_info_button = gtk_button_new_with_label("Get Group Information");
        m_quit_button = gtk_button_new_with_label("Quit");

        // Add buttons to the box
        gtk_box_pack_start(GTK_BOX(m_vbox), m_add_person_button, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(m_vbox), m_get_person_info_button, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(m_vbox), m_get_group_info_button, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(m_vbox), m_quit_button, TRUE, TRUE, 0);

        // Show all widgets
        gtk_widget_show_all(m_window);

        // Connect signals
        g_signal_connect(m_add_person_button, "clicked", G_CALLBACK(&View::on_add_person_clicked), this);
        g_signal_connect(m_get_person_info_button, "clicked", G_CALLBACK(&View::on_get_person_info_clicked), this);
        g_signal_connect(m_get_group_info_button, "clicked", G_CALLBACK(&View::on_get_group_info_clicked), this);
        g_signal_connect(m_quit_button, "clicked", G_CALLBACK(&View::on_quit_clicked), this);

        // Close window event
        g_signal_connect(m_window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    }

    // Callback when Add Person button is clicked
    static void on_add_person_clicked(GtkWidget* widget, gpointer data) {
        View* view = static_cast<View*>(data);
        std::string name = "John Doe";  // Replace with a dialog to input name
        int height_feet = 5, height_inches = 9;
        std::string sex = "male";
        float weight = 180.0f;
        int body_fat_percent = 20;

        view->m_group.add_person(name, height_feet, height_inches, sex, weight, body_fat_percent);
        std::cout << "Person added!" << std::endl;
    }

    // Callback when Get Person Information button is clicked
    static void on_get_person_info_clicked(GtkWidget* widget, gpointer data) {
        View* view = static_cast<View*>(data);
        if (view->m_group.get_group_count() > 0) {
            Person& person = view->m_group.get_people()[0];  // Get the first person for simplicity
            std::cout << "Name: " << person.get_first_name() << "\n";
            std::cout << "Height: " << person.get_height_feet() << " feet " << person.get_height_inches() << " inches\n";
            std::cout << "Weight: " << person.get_weight() << "\n";
            std::cout << "Body Fat: " << person.get_body_fat_percent() << "%\n";
            std::cout << "BMI: " << person.get_bmi() << "\n";
        }
    }

    // Callback when Get Group Information button is clicked
    static void on_get_group_info_clicked(GtkWidget* widget, gpointer data) {
        View* view = static_cast<View*>(data);
        std::cout << "Group Info:\n";
        std::cout << "Total Members: " << view->m_group.get_group_count() << "\n";
        std::cout << "Group BMI Average: " << view->m_group.get_group_bmi_avg() << "\n";
        std::cout << "Male BMI Average: " << view->m_group.get_male_bmi_avg() << "\n";
        std::cout << "Female BMI Average: " << view->m_group.get_female_bmi_avg() << "\n";
    }

    // Callback when Quit button is clicked
    static void on_quit_clicked(GtkWidget* widget, gpointer data) {
        gtk_main_quit();
    }

    // Start the GTK main loop
    void run() {
        gtk_main();
    }
};

// Main function: MVC setup
int main() {
    Group group;       // Model
    View view(group);  // View

    // Run the application (view + controller in one)
    view.run();

    return 0;
}

