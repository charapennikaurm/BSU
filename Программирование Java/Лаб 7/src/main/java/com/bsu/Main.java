package main.java.com.bsu;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;
import java.util.Scanner;


class Sort implements Runnable {
    private Integer[] arr;
    private Comparator<Integer> cmp;

    public Sort(Integer[] arr, Comparator<Integer> cmp) {
        this.arr = arr;
        this.cmp = cmp;
    }


    public Integer[] getArray() {
        return arr;
    }

    @Override
    public void run() {
        try {
            Arrays.sort(arr, cmp);
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }
}


public class Main {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Введите размер массива: ");
            int n = scanner.nextInt();
            Integer[] arr = new Integer[n];
            Random randGenerator = new Random();
            for (int i = 0; i < n; ++i) {
                arr[i] = randGenerator.nextInt() % 10000000;
            }
            System.out.println(Arrays.toString(arr));
            System.out.println("Выберите тип сортировки:");
            System.out.println("1)По возрастанию чисел");
            System.out.println("2)По убыванию чисел");
            System.out.println("3)По возрастанию длины чисел");
            System.out.println("4)По убыванию длины чисел");
            int sortType = scanner.nextInt();
            Comparator<Integer> cmp;
            switch (sortType) {
                case 1:
                    cmp = Integer::compareTo;
                    break;
                case 2:
                    cmp = Comparator.reverseOrder();
                    break;
                case 3:
                    cmp = Comparator.comparingInt(Main::numberOfDigits);
                    break;
                case 4:
                    cmp = (o1, o2) -> numberOfDigits(o2) - numberOfDigits(o1);
                    break;
                default:
                    throw new IllegalArgumentException("Неизвестный тип сортировки");
            }
            Sort sort = new Sort(arr, cmp);
            Thread thread = new Thread(sort);
            thread.start();
            thread.join();
            Integer[] sortedArray = sort.getArray();
            System.out.println("Отсортированный массив:");
            System.out.println(Arrays.toString(sortedArray));
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }

    }


    public static int numberOfDigits(Integer n) {
        int numberOfDigits = 0;
        int tmp = n;
        while (tmp != 0) {
            tmp /= 10;
            ++numberOfDigits;
        }
        return numberOfDigits;
    }
}
