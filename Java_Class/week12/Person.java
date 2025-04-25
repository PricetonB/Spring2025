import java.io.*;
import java.util.ArrayList;
import java.util.List;

class Person {
    private String name;
    private int feet;
    private int inches;
    private double weight;
    private int bodyfat;
    private char sex;
    private double bmi;
    private char weightclass;

    static int total_people = 0;
    static int total_males = 0;
    static int total_females = 0;

    public Person(String name, int feet, int inches, double weight, int bodyfat, char sex) {
        this.name = name;
        this.feet = feet;
        this.inches = inches;
        this.weight = weight;
        this.bodyfat = bodyfat;
        this.sex = sex;

        calcBMI(feet, inches, weight);
        calcWeightClass(bmi, bodyfat, sex);

        total_people++;
        if (sex == 'm') {
            total_males++;
        }
        if (sex == 'f') {
            total_females++;
        }

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

    public void appendPersonToFile(String fileName) throws IOException {
        PrintWriter outfile = new PrintWriter(new FileWriter(fileName, true));
        outfile.printf("%s %d,%d weight:%f bodyfat:%d sex:%c bmi:%f weightclass:%c%n",
            this.name, this.feet, this.inches, this.weight, this.bodyfat, 
            this.sex, this.bmi, this.weightclass);
        outfile.close();
    }

    // Setters
    public void setName(String name) {
        this.name = name;
    }

    public void setFeet(int feet) {
        this.feet = feet;
    }

    public void setInches(int inches) {
        this.inches = inches;
    }

    public void setWeight(double weight) {
        this.weight = weight;
        calcBMI(feet, inches, weight); 
        calcWeightClass(bmi, bodyfat, sex); 
    }

    public void setBodyfat(int bodyfat) {
        this.bodyfat = bodyfat;
        calcWeightClass(bmi, bodyfat, sex); 
    }

    public void setSex(char sex) {
        this.sex = sex;
        calcWeightClass(bmi, bodyfat, sex); 
    }

    // Getters
    public String getName() {
        return name;
    }

    public int getFeet() {
        return feet;
    }

    public int getInches() {
        return inches;
    }

    public double getWeight() {
        return weight;
    }

    public int getBodyfat() {
        return bodyfat;
    }

    public char getSex() {
        return sex;
    }

    public double getBmi() {
        return bmi;
    }

    public char getWeightclass() {
        return weightclass;
    }
}


