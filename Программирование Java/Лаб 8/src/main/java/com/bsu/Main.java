package main.java.com.bsu;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static void main(String[] args) {
        try(Scanner scanner = new Scanner(System.in)) {
            String regexp = "\"[^\"]+\"";
            Pattern pattern = Pattern.compile(regexp);
            String input = scanner.nextLine();
            Matcher matcher = pattern.matcher(input);
            List<String> quotes = allQuotes(input,matcher);
            for (String quote: quotes){
                System.out.println(quote);
            }
        }catch(Exception ex){
            System.out.println(ex.getMessage());
        }
    }

    public static List<String> allQuotes(String string,Matcher matcher){
        List<String> result = new ArrayList<>();
        while (matcher.find()){
           result.add(string.substring(matcher.start(),matcher.end()));
        }
        return result;
    }
}
