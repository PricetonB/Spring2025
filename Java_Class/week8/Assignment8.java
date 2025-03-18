//week 8 java assigment



class Person {
    String name;
    int feet;
    int inches;
    double weight;
    int bodyfat;
    char sex;
    double bmi;
    char weightclass;

    public Person(String name, int feet, int inches, double weight, int bodyfat, char sex) {
        this.name = name;
        this.feet = feet;
        this.inches = inches;
        this.weight = weight;
        this.bodyfat = bodyfat;
        this.sex = sex;
        calcBMI(feet, inches, weight);
        calcWeightClass(bmi, bodyfat, sex);
        System.out.println("Object created for " + name);
    }

    public void calcBMI(int feet, int inches, double weight) {
        bmi = weight / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
    }

    public void calcWeightClass(double bmi, int bodyfat, char sex) {
        if (bmi > 25) {
            if (sex == 'm' && bodyfat > 24) {
                weightclass = 'o';
                return;
            }
            if (sex == 'f' && bodyfat > 31) {
                weightclass = 'o';
                return;
            }
            weightclass = 'p';
            return;
        }
        if (bmi > 18.5) {
            weightclass = 'n';
            return;
        }
        weightclass = 'u';
    }
}

public class Assignment8 {
    public static void main(String[] args) {
        Person person_one = new Person("Keith", 5, 5, 150, 20, 'm');
    }
}

