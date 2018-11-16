package com.maxdev;

public class Main {

    public static void main(String[] args) {
        mainBehavior();
    }

    private static void mainBehavior() {
        MsgAnalyzer msgAnalyzer = new MsgAnalyzer();

        // Get incoming messages.
        String firstMsg = "hello man";
        String secondMsg = "get the fuck out man!";
        String thirdMsd = "i love google.com";

        // Initialize and use containsFilter.
        System.out.println(msgAnalyzer.checkMessageContains(firstMsg) + '\n');
        System.out.println(msgAnalyzer.checkMessageContains(secondMsg) + '\n');
        System.out.println(msgAnalyzer.checkMessageContains(thirdMsd) + '\n');

        // Initialize and use linkFilter.
        System.out.println(msgAnalyzer.checkMessageLink(firstMsg) + '\n');
        System.out.println(msgAnalyzer.checkMessageLink(secondMsg) + '\n');
        System.out.println(msgAnalyzer.checkMessageLink(thirdMsd) + '\n');
    }
}
