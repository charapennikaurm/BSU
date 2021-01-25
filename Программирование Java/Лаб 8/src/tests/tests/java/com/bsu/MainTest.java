package tests.java.com.bsu;

import main.java.com.bsu.Main;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static org.junit.jupiter.api.Assertions.assertEquals;

class MainTest {
    String regexp = "\"[^\"]+\"";
    Pattern pattern = Pattern.compile(regexp);

    @Test
    public void singleQuote(){
        String str = "this is string \"with one quote\"";
        Matcher matcher = pattern.matcher(str);
        List<String> actualResult = Main.allQuotes(str,matcher);
        List<String> expectedResult = new ArrayList<>();
        expectedResult.add("\"with one quote\"");
        assertEquals(expectedResult,actualResult);
    }

    @Test
    public void multiQuote(){
        String str = "\"quote1\" not a quote \" quote2!@#\" \"\tquote with tab\"";
        Matcher matcher = pattern.matcher(str);
        List<String> actualResult = Main.allQuotes(str,matcher);
        List<String> expectedResult = new ArrayList<>();
        expectedResult.add("\"quote1\"");
        expectedResult.add("\" quote2!@#\"");
        expectedResult.add("\"\tquote with tab\"");
        assertEquals(expectedResult,actualResult);
    }

    @Test
    public void multilineQuote(){
        String str = "\"this is \n multiline quote \" \" and this is singleline quote\"";
        Matcher matcher = pattern.matcher(str);
        List<String> actualResult = Main.allQuotes(str,matcher);
        List<String> expectedResult = new ArrayList<>();
        expectedResult.add("\"this is \n multiline quote \"");
        expectedResult.add("\" and this is singleline quote\"");
        assertEquals(expectedResult,actualResult);
    }

}