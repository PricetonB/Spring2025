import java.util.*;

class Person {
    private String sex;
    private String firstName;
    private int weightClassId; // overweight = 0, probably not overweight = 1, normal weight = 2, underweight = 3
    private int heightFeet;
    private int heightInches;
    private int bodyFatPercent;
    private int id;
    private float weightPounds;
    private float bmi;

    private void calculateBmi(int feet, int inches, float pounds) {
        this.bmi = pounds / ((feet * 12 + inches) * (feet * 12 + inches)) * 703;
    }

    private void calculateFatness(float bmi, int bodyFatPercent, String sex) {
        if (bmi > 25) {
            if (sex.equals("male") && bodyFatPercent > 24) {
                this.weightClassId = 0;
                return;
            }
            if (sex.equals("female") && bodyFatPercent > 31) {
                this.weightClassId = 0;
                return;
            }
            this.weightClassId = 1;
            return;
        }
        if (bmi > 18.5) {
            this.weightClassId = 2;
            return;
        }
        this.weightClassId = 3;
    }

    public Person(String name, int heightInches, int heightFeet, String sex, float pounds, int fatPercent, int id) {
        this.firstName = name;
        this.heightInches = heightInches;
        this.heightFeet = heightFeet;
        this.sex = sex;
        this.weightPounds = pounds;
        this.bodyFatPercent = fatPercent;
        this.id = id;
        calculateBmi(this.heightFeet, this.heightInches, this.weightPounds);
        calculateFatness(this.bmi, this.bodyFatPercent, this.sex);
    }

    public String getSex() {
        return sex;
    }

    public String getFirstName() {
        return firstName;
    }

    public int getHeightFeet() {
        return heightFeet;
    }

    public int getHeightInches() {
        return heightInches;
    }

    public int getBodyFatPercent() {
        return bodyFatPercent;
    }

    public int getPersonId() {
        return id;
    }

    public float getWeight() {
        return weightPounds;
    }

    public float getBmi() {
        return bmi;
    }

    public int getWeightClassId() {
        return weightClassId;
    }
}

class Group {
    private int groupCount;
    private int maleCount;
    private int femaleCount;
    private float groupBmiAvg;
    private float maleBmiAvg;
    private float femaleBmiAvg;
    private List<Person> people = new ArrayList<>();
    private Map<Integer, Integer> weightClassCounts = new HashMap<>();
    private String[] weightClassNames = {"overweight", "probably not overweight", "normal", "underweight"};

    public Group() {
        groupCount = 0;
        maleCount = 0;
        femaleCount = 0;
        maleBmiAvg = 0;
        femaleBmiAvg = 0;
        groupBmiAvg = 0;
        weightClassCounts.put(0, 0);
        weightClassCounts.put(1, 0);
        weightClassCounts.put(2, 0);
        weightClassCounts.put(3, 0);
    }

    private void printWeightClassPercentages() {
        if (groupCount != 0) {
            for (int i = 0; i < 4; i++) {
                int count = weightClassCounts.get(i);
                if (count != 0) {
                    System.out.println(weightClassNames[i] + " members: " + ((float) count / groupCount) * 100 + "%");
                } else {
                    System.out.println(weightClassNames[i] + " members: 0%");
                }
            }
        } else {
            System.out.println("Group count is zero. Cannot calculate percentages.");
        }
    }

    private void printPersonInfo(Person person) {
        System.out.println("Name: " + person.getFirstName());
        System.out.println("Height: " + person.getHeightFeet() + "," + person.getHeightInches());
        System.out.println("Weight: " + person.getWeight());
        System.out.println("Body Fat Percentage: " + person.getBodyFatPercent());
        System.out.println("Sex: " + person.getSex());
        System.out.println("BMI: " + person.getBmi());
        System.out.println("Weight Class: " + weightClassNames[person.getWeightClassId()]);
    }

    private void calculateGroupBmiAvg() {
        if (groupCount == 0) {
            groupBmiAvg = 0;
            return;
        }

        float totalBmi = 0;
        for (Person person : people) {
            totalBmi += person.getBmi();
        }

        groupBmiAvg = totalBmi / groupCount;
    }

    private void calculateMaleBmiAvg() {
        if (maleCount == 0) {
            maleBmiAvg = 0;
            return;
        }

        float totalBmiMales = 0;
        for (Person person : people) {
            if (person.getSex().equals("male")) {
                totalBmiMales += person.getBmi();
            }
        }

        maleBmiAvg = totalBmiMales / maleCount;
    }

    private void calculateFemaleBmiAvg() {
        if (femaleCount == 0) {
            femaleBmiAvg = 0;
            return;
        }

        float totalBmiFemales = 0;
        for (Person person : people) {
            if (person.getSex().equals("female")) {
                totalBmiFemales += person.getBmi();
            }
        }

        femaleBmiAvg = totalBmiFemales / femaleCount;
    }
  
    public void printGroupBMIfor4a() {
      System.out.println("Average BMI for group: " + groupBmiAvg);
    }
  
  
    public void printWeightClassPercentageFor4a() {
      printWeightClassPercentages();
    }


    public void printGroupInfo() {
        if (groupCount == 0) {
            System.out.println("There are no people in the group.");
            return;
        }

        System.out.println("Number of people in group: " + groupCount);
        System.out.println("Group BMI average: " + groupBmiAvg);
        System.out.println("Male BMI average: " + maleBmiAvg);
        System.out.println("Female BMI average: " + femaleBmiAvg);
        printWeightClassPercentages();
    }

    public void printPersonInfo(int personId) {
        if (personId > groupCount - 1) {
            System.out.println("UNABLE TO FIND PERSON ID " + personId);
            return;
        }
        printPersonInfo(people.get(personId));
    }

    public void addPerson() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter your first name:");
        String name = scanner.nextLine();

        System.out.println("Please enter your height in feet:");
        int feet = scanner.nextInt();

        System.out.println("How many inches on top of those feet?");
        int inches = scanner.nextInt();

        System.out.println("Please enter how many pounds you are:");
        float pounds = scanner.nextFloat();

        System.out.println("Please enter your body fat percent:");
        int bodyFatPercent = scanner.nextInt();

        System.out.println("Male or female?");
        String sex = scanner.next();

        while (!sex.equals("male") && !sex.equals("female")) {
            System.out.println("Try again. Type male or female all lowercase and press enter.");
            sex = scanner.next();
        }

        int personId = groupCount;

        Person personToAdd = new Person(name, inches, feet, sex, pounds, bodyFatPercent, personId);
        people.add(personToAdd);
        weightClassCounts.put(personToAdd.getWeightClassId(), weightClassCounts.get(personToAdd.getWeightClassId()) + 1);

        groupCount += 1;
        if (sex.equals("male")) {
            maleCount += 1;
            calculateMaleBmiAvg();
        }
        if (sex.equals("female")) {
            femaleCount += 1;
            calculateFemaleBmiAvg();
        }
        calculateGroupBmiAvg();

        System.out.println("PERSON CREATED! PERSON ID IS " + personId);
    }
}

public class Assignment4a {
    public static void main(String[] args) {
        Group group = new Group();
        Scanner scanner = new Scanner(System.in);
        boolean running = true;
        for (int i=0; i < 5; i++ ) {
          group.addPerson();
        }
        group.printGroupBMIfor4a();
        group.printWeightClassPercentageFor4a();
      
    }
}
