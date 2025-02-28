//week 7 java
//
//as the assignments go on im finding my work is deviating more and more from the assigment specification
//for this reason i have scrapped everything and started over
// the assignment 7 code example did not show a constructor so i have left that out of person class and left main blank



public class Person {
    String name;
    int feet;
    int inches;
    double weight;

    int bodyfat;
    char sex;

    double bmi;
    char weightclass; // o, p, n, u = overweight, probably not overweight, not overweight, underweight


    public void calcBMI(int feet, int inches, double weight) {
        bmi = weight / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
    }

    public void calcWeightClass(double bmi, int bodyfat, char sex) {
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

    public static void main(String[] args) {
    }
}

