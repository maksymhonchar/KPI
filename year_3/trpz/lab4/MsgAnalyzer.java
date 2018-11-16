package com.maxdev;


import java.util.ArrayList;
import java.util.List;

public class MsgAnalyzer {

    private LinkFilter _linkFilter;
    private ContainsFilter _containsFilter;

    MsgAnalyzer() {
        this._linkFilter = new LinkFilter();
        this._containsFilter = new ContainsFilter();
        this.fillUpContainsFilter();
    }

    private void fillUpContainsFilter() {
        List<String> _swearWords = new ArrayList<String>() {{
            add("arse");
            add("ass");
            add("asshole");
            add("bastard");
            add("bitch");
            add("bollocks");
            add("child-fucker");
            add("Christ on a bike");
            add("Christ on a cracker");
            add("crap");
            add("cunt");
            add("damn");
            add("frigger");
            add("fuck");
            add("fuck");
            add("goddamn");
            add("godsdamn");
            add("hell");
            add("holy shit");
            add("motherfucker");
            add("nigga");
            add("nigger");
            add("shit");
            add("shit ass");
            add("shitass");
            add("son of a bitch");
            add("son of a motherless goat");
            add("son of a whore");
            add("sweet Jesus");
            add("twat");
        }};
        for (String swearWord: _swearWords) {
            this._containsFilter.addBannedWord(swearWord);
        }
    }

    public String checkMessageLink(String message) {
        System.out.println("Перевірка " + message);
        boolean isSuccessful = this._linkFilter.processMessage(message);
        return this._linkFilter.getResultString(isSuccessful);
    }

    public String checkMessageContains(String message) {
        System.out.println("Перевірка " + message);
        boolean isSuccessful =  this._containsFilter.processMessage(message);
        return this._containsFilter.getResultString(isSuccessful);
    }

}
