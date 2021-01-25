package com.tests;

import com.bsu.Main;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MainTest {
    @Test
    public void test(){
        double x = 0.0;
        double eps =10E-6;
        double expectedResult = Math.cosh(x);
        double actualResult = Main.calculateTaylorSeries(x,eps);
        assertEquals(expectedResult, actualResult, 5E-4);
        x=9.0;
        expectedResult = Math.cosh(x);
        actualResult = Main.calculateTaylorSeries(x,eps);
        assertEquals(expectedResult,actualResult,5E-4);
        x = -0.5;
        expectedResult = Math.cosh(x);
        actualResult = Main.calculateTaylorSeries(x,eps);
        assertEquals(expectedResult,actualResult,5E-4);
    }

}