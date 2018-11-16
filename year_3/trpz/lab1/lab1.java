package lab1;

import java.util.Scanner;
import java.util.InputMismatchException;

public class Main {
	
	// roles of users
	public enum FUNC_OPTIONS {
		MSG_CHECK,
		SEARCH,
        REPORTS_VIEW,
	}
	
	public static void main(String[] args) {
		boolean db_connection = true;
		if (db_connection) {
			while(true) {
                menu_print_administrator();
				int option = select_option();
				
                switch(option) {
                    case MSG_CHECK:
                        // 
                        break;
                    case SEARCH:
                        // 
                        break;
                    case REPORTS_VIEW:
                        //
                        break;
                }
			}
		}
		else {
			System.err.println("Cannot establish the connection to database");
		}
		System.out.println("End of the program.");
	}
	
	// every menu returns the options that it has inside
	public static String[] menu_print_administrator() {
		String[] options = {
			"Check messages",
			"Review created reports",
			"Search for violator",
			"Exit"
		};
		return menu_print(options);
	}
	
	private static String[] menu_print(String[] options) {
		for (int i = 0; i < options.length; i++) {
			System.out.println((i + 1) + ". " + options[i]);
		}
		return options;
	}

    private static int select_option() {
        // TODO: select function
    }
	
	public static void react_on_chosen_option(int option) {
		// TODO: function implementation
	}
}