import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in); 


        System.out.println("Please enter your name:");
        String name = s.nextLine();

        System.out.println("Enter your height in feet:");
        int feet = Integer.parseInt(s.nextLine());

        System.out.println("Enter your height in inches:");
        int inches = Integer.parseInt(s.nextLine());

        System.out.println("Enter your weight in pounds:");
        float pounds = Float.parseFloat(s.nextLine());

        float heightInInches = feet * 12 + inches;
        float bmi = pounds / (heightInInches * heightInInches) * 703;

        System.out.println("Hello " + name + ", your BMI is " + bmi);

    }
}