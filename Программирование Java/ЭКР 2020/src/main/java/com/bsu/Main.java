package main.java.com.bsu;

import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try (Scanner input1 = new Scanner(new File("input1.txt"));
             Scanner input2 = new Scanner(new File("input2.txt"))) {
            int throughput = input1.nextInt();
            String messageText = readMessageText(input2);
            int numberOfFiles = (int) Math.ceil(messageText.length() / (double) throughput);
            writeNumberOfFiles(numberOfFiles);
            splitMessage(messageText, numberOfFiles,throughput);
            writeOutputFileNames(numberOfFiles);
            restoreMessage(numberOfFiles);

        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public static String readMessageText(Scanner input) {
        String result = "";
        while (input.hasNextLine()) {
            result += (input.nextLine() + System.lineSeparator());
        }
        return result.substring(0, result.length() - 1);
    }

    public static void writeOutputFileNames(int numberOfFiles) {
        try (FileWriter writer = new FileWriter("output2.txt")) {
            for (int i = numberOfFiles; i > 0; --i) {
                if (i != 1) {
                    writer.write(i + "#input2.txt" + System.lineSeparator());
                } else {
                    writer.write(i + "#input2.txt");
                }

            }
        } catch (Exception exception) {
            exception.getMessage();
        }
    }

    public static void writeNumberOfFiles(Integer numberOfFiles) {
        try (FileWriter writer = new FileWriter("output1.txt")) {
            writer.write(numberOfFiles.toString());
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public static void splitMessage(String messageText, int numberOfFiles,int throughput) {
        for (int i = 1; i <= numberOfFiles; ++i) {
            String fileName = i + "#input2.txt";
            try (FileWriter messageWriter = new FileWriter(fileName)) {
                if (i != numberOfFiles) {
                    messageWriter.write(messageText.substring((i - 1) * throughput, (i - 1) * throughput + throughput));
                } else {
                    messageWriter.write(messageText.substring((i - 1) * throughput, messageText.length() - 1));
                }

            } catch (Exception exception) {
                System.out.println(exception.getMessage());
            }
        }
    }

    public static void restoreMessage(int numberOfFiles) {
        try (FileWriter writer = new FileWriter("%input2.txt")) {
            for (int i = 1; i <= numberOfFiles; ++i) {
                Scanner scanner = new Scanner(new File(i + "#input2.txt"));
                String str = readMessageText(scanner);
                str = str.substring(0, str.length() - 1);
                writer.write(str);
                scanner.close();
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }
}
