package main.java.com.bsu;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {


    public static void main(String[] args) {
        try {
            Stream<Integer> integerStream = Stream.of(1, 17, 43, 28, 59, 87);
            Stream<String> fileLines = Files.lines(Paths.get(".\\src\\input.txt"));
            // вычисление факториала при помощи stream
            System.out.println(IntStream.rangeClosed(2, 10).reduce((a, b) -> a * b).getAsInt());
            integerStream.map(i -> i % 2).forEach(System.out::println);
            Map<String, Integer> linesMap = fileLines.filter(s -> s.length() > 10).
                    collect(Collectors.toMap(s -> s, String::length));
            linesMap.forEach((key, val) -> System.out.println(key + ";length = " + val));
            List<Person> persons = Arrays.asList(new Person("Павел", 23, "M"),
                    new Person("Анатолий", 13, "M"), new Person("Маша", 15, "F"),
                    new Person("Кристина", 19, "F"), new Person("Андрей", 7, "M"));
            Map<String, Long> personMap =
                    persons.stream().collect(Collectors.groupingBy(Person::getSex, Collectors.counting()));
            personMap.forEach((s, l) -> System.out.println(s + ": " + l));
            Stream<Double> doubleStream = Stream.of(10.3, 11.7,-3.5,-4.6, 4.0);
            System.out.println(doubleStream.filter(d -> d < 0.0 ).findAny().orElse(0.0));
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }

    }
}

class Person {
    String name;
    int age;
    String sex;

    Person(String name, int age, String sex) {
        this.age = age;
        this.name = name;
        this.sex = sex;
    }

    String getSex() {
        return sex;
    }
}
