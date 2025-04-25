import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Assignment12 {
    public static void main(String[] args) throws IOException {
        Person personOne = new Person("Keith", 5, 5, 150, 20, 'm');
        
        List<String> lines = new ArrayList<>();
        List<Person> people = new ArrayList<>();

        BufferedReader br = new BufferedReader(new FileReader("datafile.csv"));
        String line;
        while ((line = br.readLine()) != null) {
            lines.add(line);
        }
        br.close();

        for (String l : lines) {
            String[] parts = l.split(",");
            if (parts.length >= 6) {
                String name = parts[0].trim();
                int feet = Integer.parseInt(parts[1].trim());
                int inches = Integer.parseInt(parts[2].trim());
                double weight = Double.parseDouble(parts[3].trim());
                int bodyfat = Integer.parseInt(parts[4].trim());
                char sex = parts[5].trim().charAt(0);
                
                Person person = new Person(name, feet, inches, weight, bodyfat, sex);
                people.add(person);
            }
        }

        for (Person person : people) {
            person.appendPersonToFile("output.txt");
        }
    }
}
