package main.java.com.bsu;

import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            writeToLogFile(Calendar.getInstance().getTime().toString() + " Program Started");
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        String dateFormat = "dd.MM.yyyy";
        String filePath = ".\\src\\input_output_files\\";
        if (args.length == 2) {
            dateFormat = args[0];
            filePath = args[1];
        }
        String inputFile = "data.csv";
        try (Scanner scanner = new Scanner(System.in)) {
            CompanyReader reader = new CompanyReader(filePath + inputFile, dateFormat);
            List<Company> companies = reader.readAllRecords();
            int req;
            showAvailableRequests();
            req = scanner.nextInt();
            while(req!= 0){
                workWithRequests(scanner,companies,req);
                showAvailableRequests();
                req = scanner.nextInt();
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public static void showAvailableRequests() {
        System.out.println("Available Requests:");
        System.out.println("1)Find company by short name");
        System.out.println("2)Find companies by industry");
        System.out.println("3)Find companies by activity type");
        System.out.println("4)Find companies by foundation date");
        System.out.println("5)Find companies by number of employees");
        System.out.println("Enter appropriate number to make request or 0 to exit");
    }

    public static void workWithRequests(Scanner scanner, List<Company> companies,int key){
        String requestInfo = Calendar.getInstance().getTime().toString();
        scanner.nextLine();
        List<Company> result = new ArrayList<>();
        switch (RequestProcessor.Request.getRequestFromInt(key)){
            case SHORT_NAME:
                System.out.println("Enter short name: ");
                requestInfo += " find company by short name: ";
                String shortName = scanner.nextLine();
                requestInfo += shortName;
                result = RequestProcessor.findByShortName(companies, shortName);
                break;
            case INDUSTRY:
                System.out.println("Enter industry:");
                requestInfo += " find company by industry: ";
                String industry = scanner.nextLine();
                requestInfo += industry;
                result = RequestProcessor.findByIndustry(companies, industry);
                break;
            case ACTIVITY_TYPE:
                System.out.println("Enter activity type");
                requestInfo += " find company by activity type: ";
                String activityType = scanner.nextLine();
                requestInfo += activityType;
                result = RequestProcessor.findByActivityType(companies, activityType);
                break;
            case FOUNDATION_DATE:
                requestInfo += " find company by foundation date: ";
                System.out.println("Enter lower bound of foundation date(dd.MM.yyyy)");
                String lbString = scanner.nextLine();
                System.out.println("Enter upper bound of foundation date(dd.MM.yyyy)");
                String ubString = scanner.nextLine();
                requestInfo += lbString +" - " + ubString;
                try{
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy");
                    LocalDate lb = LocalDate.parse(lbString, formatter);
                    LocalDate ub = LocalDate.parse(ubString, formatter);
                    result = RequestProcessor.findByFoundationDate(companies,lb,ub);
                }catch (Exception exception){
                    System.out.println("Can't parse expression");
                }
                break;
            case EMPLOYEES:
                requestInfo += " find company by number of employees: ";
                System.out.println("Enter lower bound of number of employees");
                String lbstr = scanner.nextLine();
                System.out.println("Enter upper bound of number of employees");
                String ubstr = scanner.nextLine();
                requestInfo += lbstr +" - " + ubstr;
                try{
                    int lb = Integer.parseInt(lbstr);
                    int ub = Integer.parseInt(ubstr);
                    result = RequestProcessor.findByNumberOfEmployee(companies,lb,ub);
                }catch (Exception exception){
                    System.out.println("Can't parse expression");
                }
                break;
            case DEFAULT:
                requestInfo += "Unknown request";
                System.out.println("Unknown request, try again");
                break;
        }
        //вывод результатов и запись в файлы логов
        requestInfo += ", number of results: " + result.size();
        if(result.size() == 0){
            System.out.println("Nothing found");
        }else{
            System.out.println("Results:");
            result.forEach(System.out::println);
        }
        try {
            writeToLogFile(requestInfo);
        }catch (Exception exception){
            System.out.println(exception.getMessage());
        }
    }

    public static void writeToLogFile(String str) throws IOException {
        FileWriter writer = new FileWriter(".\\src\\input_output_files\\logfile.txt", true);
        writer.write(str + System.lineSeparator());
        writer.close();
    }
}