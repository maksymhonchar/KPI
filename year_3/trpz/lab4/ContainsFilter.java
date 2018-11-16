package com.maxdev;


import java.util.ArrayList;
import java.util.List;

public class ContainsFilter implements Filter{

    private List<String> _bannedWords;

    ContainsFilter() {
        this._bannedWords = new ArrayList<>();
    }

    void addBannedWord(String message) {
        if (message != null) {
            this._bannedWords.add(message.toLowerCase());
        }
    }

    @Override
    public boolean verifyMessage(String message) {
        return message != null && !message.isEmpty();
    }

    @Override
    public boolean processMessage(String message) {
        if (!this.verifyMessage(message)) {
            return false;
        }
        String[] splittedSentence = message.split("\\s+");
        for (String word: splittedSentence) {
            if (this._bannedWords.contains(word)) {
                return false;
            }
        }
        return true;
    }

    @Override
    public String getResultString(boolean isSuccessful) {
        if (isSuccessful) {
            return "Результат: позитивний. Повідомлення користувача не містить заборонених фраз.";
        } else {
            return "Результат: негативний. Повідомлення від користувача містить заборонені фрази.";
        }
    }
}
