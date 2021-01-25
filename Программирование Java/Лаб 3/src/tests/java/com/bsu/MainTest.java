package com.bsu;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class MainTest {
    @Test
    public void countUniqueCharacters1() {
        int actual = Main.countUniqueCharacters("123ghgh");
        int expected = 5;
        assertEquals(expected, actual);
    }

    @Test
    public void countUniqueCharactersEmpty() {
        int actual = Main.countUniqueCharacters("");
        int expected = 0;
        assertEquals(expected, actual);
    }

    @Test
    public void findMinUniqueCharWord() {
        String actual = Main.findMinUniqueCharWord("132263 fff dhuhdfu");
        String expected = "fff";
        assertEquals(expected, actual);
    }

    @Test
    public void findMinUniqueCharWordPunct() {
        String actual = Main.findMinUniqueCharWord("111111, jndfjuu oifod");
        String expected = "111111";
        assertEquals(expected, actual);
    }

    @Test
    public void findMinUniqueCharWordEmpty() {
        String actual = Main.findMinUniqueCharWord("");
        String expected = "";
        assertEquals(expected, actual);
    }


}