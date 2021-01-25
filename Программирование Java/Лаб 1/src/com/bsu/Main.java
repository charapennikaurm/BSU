package com.bsu;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        int k;
        double x;
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Enter k:");
            k = scanner.nextInt();
            if (k < 0) {
                throw new IllegalArgumentException("K should be >= 0");
            }
            System.out.println("Enter x:");
            x = scanner.nextDouble();
            double eps = Math.pow(10, -k);
            double actualResult = calculateTaylorSeries(x, eps);
            double expectedResult = Math.cosh(x);
            System.out.println("Actual result: " + formatValue(actualResult));
            System.out.println("Expected result: " + formatValue(expectedResult));
        } catch (Exception exception) {
            System.out.println(exception);
        }
    }

    public static double calculateTaylorSeries(double x, double eps) {
        double taylorSeriesSum = 0.0;
        double nextTerm = 1.0;
        int i = 0;
        while (nextTerm >= eps) {
            taylorSeriesSum += nextTerm;
            i += 2;
            nextTerm = nextTerm * x * x / (i * (i - 1));
        }
        return taylorSeriesSum;
    }

    private static String formatValue(double value) {
        return String.format("%.3f", value);
    }

}

