package main.java.com.bsu;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Enter matrix size: ");
            int n = scanner.nextInt();
            if (n <= 0) {
                throw new IllegalArgumentException("N should be greater than 0");
            }
            int[][] matrix = new int[n][n];
            fillMatrix(matrix);
            System.out.println("Inputted matrix:");
            printMatrix(matrix);
            System.out.println("Result: " + findMaxMainDiagonalSum(matrix));
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }

    }

    public static void fillMatrix(int[][] matrix) throws InputMismatchException {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < matrix.length; ++i) {
            for (int j = 0; j < matrix[i].length; ++j) {
                matrix[i][j] = scanner.nextInt();
            }
        }
        scanner.close();
    }

    public static void printMatrix(int[][] matrix) {
        for (int[] ints : matrix) {
            for (int anInt : ints) {
                System.out.print(anInt + " ");
            }
            System.out.println("");
        }
    }

    public static int findMaxMainDiagonalSum(int[][] matrix) throws IllegalArgumentException {
        if (matrix.length != matrix[0].length) {
            throw new IllegalArgumentException("Matrix should be square");
        }
        int n = matrix.length;
        int maxSum = matrix[n - 1][0];
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            int i1 = i;//temporary for i
            //lower diagonal sum
            for (int j = 0; j < n && i1 < n; ++j) {
                sum += matrix[i1++][j];
            }
            if (sum > maxSum) {
                maxSum = sum;
            }
            sum = 0;
            i1 = i;
            //upper diagonal sum
            for (int j = 0; j < n && i1 < n; ++j) {
                sum += matrix[j][i1++];
            }
            if (sum > maxSum) {
                maxSum = sum;
            }
        }

        return maxSum;
    }

}
