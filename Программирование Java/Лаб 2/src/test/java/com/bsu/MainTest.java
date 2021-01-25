package test.java.com.bsu;

import main.java.com.bsu.Main;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MainTest {
    @Test
    public void test(){
        int actualResult = Main.findMaxMainDiagonalSum(new int[][]{{1,2},{-7,7}});
        int expectedResult = 8;
        assertEquals(expectedResult,actualResult);
        actualResult = Main.findMaxMainDiagonalSum(new int[][]{{1,18,15},{0,20,7},{8,3,6}});
        expectedResult = 27;
        assertEquals(expectedResult,actualResult);
        actualResult = Main.findMaxMainDiagonalSum(new int[][]{{-3}});
        expectedResult = -3;
        assertEquals(expectedResult,actualResult);
    }

}