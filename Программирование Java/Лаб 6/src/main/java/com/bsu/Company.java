package main.java.com.bsu;

import java.time.LocalDate;
import java.util.Objects;

public class Company {
    private String name; //Наименование
    private String shortName; //Краткое наименование
    private LocalDate actualizationDate; //Дата актуализации
    private String address; //Адрес
    private LocalDate foundationDate; //Дата основания
    private int numberOfEmployee; //Численность
    private String auditor; // Аудитор
    private String phoneNumber; //Телефон
    private String email;
    private String industry; //Отрасль
    private String activityType; //Вид деятельности
    private String websiteAddress; //Интернет-адресс

    public Company(String name, String shortName, LocalDate actDate, String address, LocalDate foundationDate,
                   int numberOfEmployee, String auditor, String phoneNumber, String email, String industry,
                   String activityType, String websiteAddress) {
        this.name = name;
        this.shortName = shortName;
        this.actualizationDate = actDate;
        this.address = address;
        this.foundationDate = foundationDate;
        this.numberOfEmployee = numberOfEmployee;
        this.auditor = auditor;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.industry = industry;
        this.activityType = activityType;
        this.websiteAddress = websiteAddress;
    }

    @Override
    public String toString() {
        return name + ";" + shortName + ";" + actualizationDate.toString() + ";" + address + ";" +
                foundationDate.toString() + ";" + numberOfEmployee + ";" + auditor + ";" + phoneNumber + ";" +
                email + ";" + industry + ";" + activityType + ";" + websiteAddress;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Company o = (Company) obj;
        return Objects.equals(name, o.name) &&
                Objects.equals(shortName, o.shortName) &&
                Objects.equals(actualizationDate, o.actualizationDate) &&
                Objects.equals(address, o.address) &&
                Objects.equals(foundationDate, o.foundationDate) &&
                (numberOfEmployee == o.numberOfEmployee) &&
                Objects.equals(auditor, o.auditor) &&
                Objects.equals(phoneNumber, o.phoneNumber) &&
                Objects.equals(email, o.email) &&
                Objects.equals(industry, o.industry) &&
                Objects.equals(activityType, o.activityType) &&
                Objects.equals(websiteAddress, o.websiteAddress);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, shortName, actualizationDate, address, foundationDate, numberOfEmployee, auditor,
                phoneNumber, email, industry, activityType, websiteAddress);
    }


    public String getShortName() {
        return shortName.toLowerCase();
    }

    public String getIndustry() {
        return industry.toLowerCase();
    }

    public String getActivityType() {
        return activityType.toLowerCase();
    }

    public int getNumberOfEmployee() {
        return numberOfEmployee;
    }

    public LocalDate getFoundationDate() {
        return foundationDate;
    }
}