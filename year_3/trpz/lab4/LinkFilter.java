package com.maxdev;


import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class LinkFilter implements Filter {

    @Override
    public boolean verifyMessage(String message) {
        return message != null && !message.isEmpty();
    }

    @Override
    public boolean processMessage(String message) {
        return this.verifyMessage(message) && !message.contains(".com") && !message.contains("www.");
    }

    @Override
    public String getResultString(boolean isSuccessful) {
        if (isSuccessful) {
            return "Результат: позитивний. Повідомлення користувача відповідає правилу про веб-посилання.";
        } else {
            return "Результат: негативний. Повідомлення від користувача містить веб-посилання.";
        }
    }
}
