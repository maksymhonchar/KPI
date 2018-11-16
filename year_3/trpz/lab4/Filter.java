package com.maxdev;


public interface Filter {
    boolean verifyMessage(String message);
    boolean processMessage(String message);
    String getResultString(boolean isSuccessful);
}
