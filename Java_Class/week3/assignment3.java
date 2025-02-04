import java.util.Scanner;

public class Main {

    public static void calculateTheFatness(float bmi, int bodyFatPercent, String sex) {
        if (bmi > 25) {
            if (sex.equals("male") && bodyFatPercent > 24) {
                System.out.println("OVERWEIGHT!!");
                return;
            }
            if (sex.equals("female") && bodyFatPercent > 31) {
                System.out.println("OVERWEIGHT!!");
                return;
            }
            System.out.println("probably not overweight");
            return;
        }
        if (bmi > 18.5) {
            System.out.println("normal weight");
            return;
        }
        System.out.println("underweight");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("please enter your first name");
        String name = scanner.nextLine();

        System.out.println("please enter your height in feet");
        int feet = scanner.nextInt();

        System.out.println("how many inches on top of those feet?");
        int inches = scanner.nextInt();

        System.out.println("please enter how many pounds you are");
        float pounds = scanner.nextFloat();

        System.out.println("please enter your body fat percent");
        int bodyFatPercent = scanner.nextInt();

        System.out.println("male or female?");
        scanner.nextLine(); 
        String sex = scanner.nextLine();

        float bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
        System.out.println("hello " + name + " your bmi is " + bmi);

        calculateTheFatness(bmi, bodyFatPercent, sex);

    }
}