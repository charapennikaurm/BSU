package com.bsu;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            List<String> text = readText(scanner);
            for (String str : text) {
                String word = findMinUniqueCharWord(str);
                System.out.println("\"" + str + "\" -> " + word + ": " + countUniqueCharacters(word));
            }
        } catch (Exception exception) {
            System.out.println(exception);
        }
    }

    public static List<String> readText(Scanner scanner) throws IllegalArgumentException {
        String nextLine;
        List<String> text = new ArrayList<>();
        nextLine = scanner.nextLine();
        while (!nextLine.isEmpty()) {
            text.add(nextLine);
            nextLine = scanner.nextLine();
        }
        return text;
    }

    public static int countUniqueCharacters(String word) {
        int numberOfUniqueCharacters = 0;
        for (int i = 0; i < word.length(); ++i) {
            char c = word.charAt(i);
            if (word.indexOf(c) == i) {
                numberOfUniqueCharacters++;
            }
        }
        return numberOfUniqueCharacters;
    }

    public static String findMinUniqueCharWord(String string) {
        String minUniqueCharWord = "";
        int minUniqueCharactersNumber = -1;
        List<String> words = splitStringIntoWords(string);
        for (String word : words) {
            int uniqueCharacters = countUniqueCharacters(word);
            if (uniqueCharacters < minUniqueCharactersNumber || minUniqueCharactersNumber == -1) {
                minUniqueCharWord = word;
                minUniqueCharactersNumber = uniqueCharacters;
            }
        }
        return minUniqueCharWord;
    }

    public static List<String> splitStringIntoWords(String string) {
        List<String> words = new ArrayList<>();
        for (String word : string.split(" |,|\\.")) {
            if (!word.isEmpty()) {
                words.add(word);
            }
        }
        return words;
    }

}
