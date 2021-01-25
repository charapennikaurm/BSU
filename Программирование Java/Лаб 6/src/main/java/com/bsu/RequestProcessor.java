package main.java.com.bsu;


import java.util.ArrayList;
import java.util.List;

public class RequestProcessor {
    enum Request {
        SHORT_NAME(1),
        ACTIVITY_TYPE(2),
        EMPLOYEES(3),
        DEFAULT(0);

        private int value;

        Request(int val) {
            this.value = val;
        }

        public int getValue() {
            return value;
        }

        public static Request getRequestFromInt(int val) {
            for (Request req : values()) {
                if (req.value == val) return req;
            }
            return Request.DEFAULT;
        }

    }

    static List<Company> findByShortName(List<Company> companies, String shortName) {
        List<Company> result = new ArrayList<>();
        for (Company company : companies) {
            if (company.getShortName().equalsIgnoreCase(shortName)) {
                result.add(company);
            }
        }
        return result;
    }

    static List<Company> findByActivityType(List<Company> companies, String actType) {
        List<Company> result = new ArrayList<>();
        for (Company company : companies) {
            if (company.getActivityType().equalsIgnoreCase(actType)) {
                result.add(company);
            }
        }
        return result;
    }

    static List<Company> findByNumberOfEmployee(List<Company> companies, int lb, int ub) {
        List<Company> result = new ArrayList<>();
        for (Company company : companies) {
            if (ub >= company.getNumberOfEmployee() && company.getNumberOfEmployee() >= lb) {
                result.add(company);
            }
        }
        return result;
    }
}