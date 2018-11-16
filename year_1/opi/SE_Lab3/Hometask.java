import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.logging.ConsoleHandler;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Hometask {
    public final static Logger logger = Logger.getLogger(Hometask.class.getName());
    static {
        try {
            ConsoleHandler consoleHandler = new ConsoleHandler();
            FileHandler fileHandler = new FileHandler("logs/HomeTask.log", true);
            logger.addHandler(fileHandler);
            logger.addHandler(consoleHandler);
            logger.setUseParentHandlers(false);
        } catch (IOException e) {
            System.out.println("Can't add a handler on logger.");
            logger.log(Level.SEVERE, "Error, while adding handler to the logger. \nReason: IOException");
        }
    }
    public static void main(String[] args){
        Department myDepartment = null;
        String fileLocation;
        Scanner scanner = new Scanner(System.in);
        boolean condition = true;
        int choice = 1;
        while(condition){
            System.out.println("1 - Read orders from file and output them.");
            System.out.println("2 - Find the worst producer.");
            System.out.println("3 - Create TreeMap and output it.");
            System.out.println("4 - Write TreeMap to file.");
            System.out.println("5 - Exit.");
            try{
                choice = scanner.nextInt();
            } catch(InputMismatchException e){
                System.out.println("You've printed wrong data.");
                logger.log(Level.SEVERE, "Error, while input of data. \\nReason: InputMismatchException.");
            }
            switch (choice){
                case 1:{
                    System.out.print("Please, enter the file location: ");
                    fileLocation = scanner.next();
                    myDepartment = new Department(fileLocation);
                    System.out.println("The list of orders:");
                    myDepartment.print();
                    break;
                }
                case 2:{
                    try{
                        System.out.println(myDepartment.findWorstProducer());
                    }catch (NullPointerException e){
                        System.out.println("Please, read data from file at first.");
                        logger.log(Level.SEVERE, "Error, while searching for the worst producer. \\nReason: NullPointerException.");
                    }
                    break;
                }
                case 3:{
                    try {
                        myDepartment.equipmentDamageRelation();
                    }catch(NullPointerException e){
                        System.out.println("Please, read data from file at first.");
                        logger.log(Level.SEVERE, "Error, while creating TreeMap. \\nReason: NullPointerException.");
                    }
                    break;
                }
                case 4:{
                    try{
                        myDepartment.writeMap();
                    }catch (NullPointerException e){
                        System.out.println("Please, create TreeMap at first.");
                        logger.log(Level.SEVERE, "Error, while writing TreeMap data into file. \\nReason: NullPointerException.");
                    }
                    break;
                }
                case 5:{
                    condition = false;
                    break;
                }
                default:{
                    System.out.println("Wrong input!!!");
                    break;
                }
            }
        }
    }
}
