package main.java.com.bsu;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(new File("input.txt"));
             FileWriter fileWriter1 = new FileWriter("output1.txt");
             FileWriter fileWriter2 = new FileWriter("output2.txt");) {
            String regexp = "<[^<>]+>";
            String input = readFile(scanner);
            Pattern pattern = Pattern.compile(regexp);
            Matcher matcher = pattern.matcher(input);
            List<String> tags = allTags(matcher, input);
            for (String s : tags) {
                fileWriter1.write(s + System.lineSeparator());
            }

            tags.stream().map(s-> s.toLowerCase()).distinct().sorted((s1, s2) -> s2.length() - s1.length()).forEach(s -> {
                try {
                    fileWriter2.write(s + System.lineSeparator());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    public static String readFile(Scanner scanner) {
        String result = new String("");
        while (scanner.hasNext()) {
            result += scanner.nextLine();
        }
        return result;
    }

    public static List<String> allTags(Matcher matcher, String str) {
        List<String> result = new ArrayList<>();
        while (matcher.find()) {
            result.add(str.substring(matcher.start(), matcher.end()));
        }
        return result;
    }


}
