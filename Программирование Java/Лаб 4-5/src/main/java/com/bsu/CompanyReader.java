package main.java.com.bsu;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class CompanyReader {
    private String filepath;
    private String dateFormat;

    public CompanyReader(String filepath, String dateFormat) {
        this.filepath = filepath;
        this.dateFormat = dateFormat;
    }

    public List<Company> readAllRecords() throws FileNotFoundException {
        File file = new File(filepath);
        List<Company> records = new ArrayList<>();
        try (Scanner scanner = new Scanner(file);) {
            while (scanner.hasNextLine()) {
                records.add(buildRecord(scanner.nextLine()));
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }

        return records;
    }

    public Company buildRecord(String str) throws IllegalArgumentException {
        String[] fields = str.split(";");
        if (fields.length < 12) {
            throw new IllegalArgumentException("Not enough information to build record");
        }
        String name = fields[0];
        String shortName = fields[1];
        LocalDate actualizationDate;
        String address = fields[3];
        LocalDate foundationDate;
        int numberOfEmployee;
        String auditor = fields[6];
        String phoneNumber = fields[7];
        String email = fields[8];
        String industry = fields[9];
        String activityType = fields[10];
        String websiteAddress = fields[11];

        //считывание даты
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern(dateFormat);
            actualizationDate = LocalDate.parse(fields[2], formatter);
            foundationDate = LocalDate.parse(fields[4], formatter);
            numberOfEmployee = Integer.parseInt(fields[5]);
        } catch (Exception exception){
            throw new IllegalArgumentException("Cant parse data");
        }
        //проверка необходимых полей
        if (shortName.isEmpty()) {
            throw new IllegalArgumentException("Short name should be filled");
        }
        if (industry.isEmpty()) {
            throw new IllegalArgumentException("Industry should be filled");
        }
        if (activityType.isEmpty()) {
            throw new IllegalArgumentException("Activity type should be filled");
        }
        if (fields[5].isEmpty()) {
            throw new IllegalArgumentException("Employee number should be filled");
        }
        if (fields[4].isEmpty()) {
            throw new IllegalArgumentException("Foundation date should be filled");
        }
        return new Company(name, shortName, actualizationDate, address, foundationDate, numberOfEmployee, auditor,
                phoneNumber, email, industry, activityType, websiteAddress);
    }

    public String getDateFormat() {
        return dateFormat;
    }

    public String getFilepath() {
        return filepath;
    }

    public void setDateFormat(String dateFormat) {
        this.dateFormat = dateFormat;
    }

    public void setFilepath(String filepath) {
        this.filepath = filepath;
    }
}
