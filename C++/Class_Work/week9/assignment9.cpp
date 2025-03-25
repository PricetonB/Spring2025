//assignment 9 
//
//ive been reading a book about operating system code for linux and im on the thread section
//it talks about how threads are created and used for atomic processes that cant be interupted
//i want to play with this c thread library and it turns out...its fully compatible with c++
//so im going to read from the csv file as instructed however im also going to add a user input
//for thread count at the beginning of main. then i will divy up the csv file for example with
//2 threads the first one gets first half of csv and second thread gets second half of csv.
//setting it up this way doesnt require locks because the threads never mess with each others data.
//im going to start a timer at beginning of main and kill it at end printing the time it took to run code.
//feel free to play around with different thread numbers and file sizes to see speed difference. 
// below the code is a commented out code segment that is my finished 
// assignment before multi threading was implemented since i intend to use ai to help with multithreading.
//


#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <pthread.h>     // POSIX threads
#include <chrono>        // for timing

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
        : name(name), feet(feet), inches(inches), weight(weight), bodyfat(bodyfat), sex(sex) {
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
                weightclass = 'o'; return;
            }
            if (sex == 'f' && bodyfat > 31) {
                weightclass = 'o'; return;
            }
            weightclass = 'p'; return;
        }
        if (bmi > 18.5) {
            weightclass = 'n'; return;
        }
        weightclass = 'u';
    }

    void append_person_to_file(std::string file_name) {
        std::ofstream outfile(file_name, std::ios::app);
        outfile << this->name << " "
                << this->feet << ","
                << this->inches << " weight:"
                << this->bodyfat << " sex:"
                << this->sex << " bmi:"
                << this->bmi << " weightclass:"
                << this->weightclass << "\n";
        outfile.close();
    }
};

// Structure to pass data to threads
struct ThreadData {
    const std::vector<std::string>* lines;
    size_t start;
    size_t end;
    std::vector<Person>* people;
    pthread_mutex_t* mutex;
};

// Thread function
void* processLines(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    std::vector<Person> local_people;

    for (size_t i = data->start; i < data->end && i < data->lines->size(); i++) {
        std::stringstream ss((*data->lines)[i]);
        std::string name, feet, inches, weight, bodyfat, sex;
        getline(ss, name, ',');
        getline(ss, feet, ',');
        getline(ss, inches, ',');
        getline(ss, weight, ',');
        getline(ss, bodyfat, ',');
        getline(ss, sex, ',');
        Person person(name, std::stoi(feet), std::stoi(inches),
        std::stoi(weight), std::stoi(bodyfat), sex[0]);
        local_people.push_back(person);
    }

    // Lock and merge results
    pthread_mutex_lock(data->mutex);
    data->people->insert(data->people->end(), local_people.begin(), local_people.end());
    pthread_mutex_unlock(data->mutex);

    pthread_exit(NULL);
}

int main() {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Get thread count from user
    int thread_count;
    std::cout << "Enter number of threads to use: ";
    std::cin >> thread_count;

    // Read CSV file
    std::ifstream f("datafile.csv");
    std::vector<std::string> lines;
    std::string line;
    while (getline(f, line)) {
        lines.push_back(line);
    }
    f.close();

    // Prepare threading
    std::vector<Person> people;
    std::vector<pthread_t> threads(thread_count);
    std::vector<ThreadData> thread_data(thread_count);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    size_t lines_per_thread = lines.size() / thread_count;

    // Create threads
    for (int i = 0; i < thread_count; i++) {
        thread_data[i].lines = &lines;
        thread_data[i].start = i * lines_per_thread;
        thread_data[i].end = (i == thread_count - 1) ? lines.size() : (i + 1) * lines_per_thread;
        thread_data[i].people = &people;
        thread_data[i].mutex = &mutex;

        int rc = pthread_create(&threads[i], NULL, processLines, &thread_data[i]);
        if (rc) {
            std::cerr << "Error creating thread: " << rc << std::endl;
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up mutex
    pthread_mutex_destroy(&mutex);

    // Write results to file
    for (const Person& person : people) {
        person.append_person_to_file("output.txt");
    }

    // Calculate and display execution time
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

    return 0;
}










/* 

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>



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

  void append_person_to_file(std::string file_name) {
    
    std::ofstream outfile(file_name, std::ios::app);
    outfile 
  << this->name << " "  
  << this->feet << "," 
  << this->inches << " weight:" 
  << this->bodyfat << " sex:" 
  << this->sex << " bmi:"
  << this->bmi << " weightclass:" 
  << this->weightclass << "\n";
    outfile.close();
    return;
  }
};



int main() {
  Person person_one("Keith", 5, 5, 150, 20, 'm'); 
  std::ifstream f("datafile.csv");
  std::vector<std::string> lines;
  std::string line;
  std::vector<Person> people;
  while(getline(f,line)) {
    lines.push_back(line);
  }
  f.close();

  for(std::string l : lines) {
    std::stringstream ss(l);
    std::string name;
    std::string feet;
    std::string inches;
    std::string weight;
    std::string bodyfat;
    std::string sex;
    getline(ss, name,',');
    getline(ss, feet,',');
    getline(ss, inches,',');
    getline(ss, weight,',');
    getline(ss, bodyfat,',');
    getline(ss, sex,',');
    Person person(name,std::stoi(feet),std::stoi(inches),std::stoi(weight),std::stoi(bodyfat),sex[0]);
    people.push_back(person);
  }


  for (Person person : people) {
    person.append_person_to_file("output.txt");

  }

  //print_weightclass_distribution();
  
  return 0;



}



*/



