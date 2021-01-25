package main.java.com.bsu;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private static final Logger LOGGER = Logger.getLogger(Main.class.getName());
    private static final String logFileName = ".\\src\\files\\logfile.txt";
    private static final String companiesFile = ".\\src\\files\\input.csv";
    private static final String requestsFile = ".\\src\\files\\requests.txt";
    private static final String dateFormat = "dd.MM.yyyy";

    public static void main(String[] args) {
        try (Scanner requestsScanner = new Scanner(new File(requestsFile))) {
            {
                LOGGER.setLevel(Level.FINE);
                FileHandler fileHandler = new FileHandler(logFileName, true);
                fileHandler.setLevel(Level.FINE);
                fileHandler.setFormatter(new SimpleFormatter());
                LOGGER.addHandler(fileHandler);
                LOGGER.fine("Programm Started" + System.lineSeparator());
            }
            CompanyReader companyReader = new CompanyReader(companiesFile, dateFormat);
            List<Company> companies = companyReader.readAllRecords();
            int requestNumber = 1;
            String request;
            while (requestsScanner.hasNextLine()) {
                FileWriter writer = new FileWriter(".\\src\\files\\request" + (requestNumber++) + ".txt");
                request = requestsScanner.nextLine().toLowerCase();
                processRequest(companies, request, writer);
                writer.close();
            }
        } catch (Exception exception) {
            LOGGER.fine("Error" + exception + ": " + exception.getMessage());
        }
    }

    public static void processRequest(List<Company> companies, String request, FileWriter writer)
            throws IllegalArgumentException, IOException {
        String[] words = request.split("[ ]+");
        Pattern pattern = Pattern.compile("\"[^\"]+\"");
        Matcher matcher = pattern.matcher(request);
        List<Company> result = new ArrayList<>();
        if (words.length >= 4 && words[0].equals(SQLRequests.SELECT)
                && words[1].equals("*") && words[2].equals(SQLRequests.FROM)) {
            if (words[3].equals(SQLRequests.TABLE_NAME)) {
                if (words[4].equals(SQLRequests.WHERE)) {
                    switch (words[5]) {
                        case SQLRequests.SHORTNAME:
                            if (!matcher.find()) {
                                throw new IllegalArgumentException("Can't find shortname command argument!");
                            }
                            result = RequestProcessor.findByShortName(companies, request.substring(matcher.start() + 1, matcher.end() - 1));
                            break;
                        case SQLRequests.ACTIVITY_TYPE:
                            if (!matcher.find()) {
                                throw new IllegalArgumentException("Can't find activity_type command argument!");
                            }
                            result = RequestProcessor.findByActivityType(companies, request.substring(matcher.start() + 1, matcher.end() - 1));
                            break;
                        case SQLRequests.EMPLOYEE_NUMBER:
                            if (words[6].equals(SQLRequests.BETWEEN) && words[8].equals(SQLRequests.AND) && words.length >= 10) {
                                int lb = Integer.parseInt(words[7]);
                                int ub = Integer.parseInt(words[9]);
                                result = RequestProcessor.findByNumberOfEmployee(companies, lb, ub);
                            } else {
                                throw new IllegalArgumentException("Wrong employee_number command format");
                            }
                            break;
                        default:
                            throw new IllegalArgumentException("Unknown command");
                    }
                }
                LOGGER.fine("SQL Request: " + request + System.lineSeparator() +
                        "\t\tNumber of results: " + result.size());
                writeToFile(result, writer);
            } else {
                throw new IllegalArgumentException("Unknown table");
            }

        } else {
            throw new IllegalArgumentException("Unknown Command");
        }
    }

    public static void writeToFile(List<Company> companies, FileWriter writer) throws IOException {
        if (companies.isEmpty()) {
            writer.write("Nothing found");
        }
        for (Company company : companies) {
            writer.write(company + System.lineSeparator());
        }
    }
}
