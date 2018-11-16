import java.io.*;
import java.util.*;
import java.util.logging.ConsoleHandler;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Department {
    public final static Logger logger = Logger.getLogger(Department.class.getName());
    private String phoneNumber;
    private String website;
    private List<RepairOrder> ordersList;
    private Map<Equipment, Integer> equipmentDamageMap;

    public Department(String fileLocation){
        try {
            ConsoleHandler consoleHandler = new ConsoleHandler();
            FileHandler fileHandler = new FileHandler("logs/Department.log", true);
            logger.addHandler(fileHandler);
            logger.addHandler(consoleHandler);
            logger.setUseParentHandlers(false);
        } catch (IOException e) {
            System.out.println("Can't add a handler on logger.");
            logger.log(Level.SEVERE, "Error, while adding handler to the logger. Reason: IOException");
        }
        phoneNumber = "0448521414";
        website = "our.legal.website.com";
        ordersList = new LinkedList<RepairOrder>();
        String[] orders = fileRead(fileLocation).split("\n");
        String[] orderFields;
        for(String s : orders){
            orderFields = s.split("%");
            try{
                ordersList.add(new RepairOrder(Equipment.valueOf(orderFields[0]), orderFields[1], Integer.parseInt(orderFields[2])));
            }catch (IllegalArgumentException e){
                try{
                    throw new MismatchTypeEquipment();
                }catch (MismatchTypeEquipment me){
                    System.out.println("There is no such type of equipment that is pointed in the file.");
                    logger.log(Level.SEVERE, "Error, while reading from file. Reason: MismatchTypeEquipment.");
                }
            }
        }
    }

    public void print(){
        for(RepairOrder order : ordersList){
            System.out.println(order.toString());
        }
    }

    public String findWorstProducer(){
        int index = 0;
        String name = ordersList.get(index).getProducer();
        int maxAmount = ordersList.get(index).getDamages();
        for(RepairOrder ord : ordersList){
            if(ord.getDamages() > maxAmount)
                name = ord.getProducer();
        }
        return "The worst producer is: " + name;
    }

    public void equipmentDamageRelation(){
        equipmentDamageMap = new TreeMap<Equipment, Integer>();
        for (RepairOrder ord : ordersList)
            equipmentDamageMap.put(ord.getEquipment(), ord.getDamages());
        //output
        System.out.println("Ordered list of 'Equipment' - 'Damages'.");
        for (Map.Entry unit : equipmentDamageMap.entrySet())
            System.out.println(unit.getKey().toString() + " - " + unit.getValue().toString());
    }

    public void writeMap(){
        if (equipmentDamageMap != null) {
            write((TreeMap<Equipment, Integer>) equipmentDamageMap);
            System.out.println("Data is written to the file.");
        } else {
            System.out.println("The TreeMap is empty!!!");
        }
    }

    private String fileRead(String fileLocation) {
        String returnValue = "";
        FileReader file = null;
        String line ;
        try {
            file = new FileReader(fileLocation);
            BufferedReader reader = new BufferedReader(file);
            while ((line = reader.readLine()) != null) {
                returnValue += line + "\n";
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found.");
            logger.log(Level.SEVERE, "Error, while opening the file.Reason: FileNotFoundException");
        } catch (IOException e) {
            System.out.println("Some problems with reading from file.");
            logger.log(Level.SEVERE, "Error, while reading from the file.Reason: IOException");
        } finally {
            if (file != null) {
                try {
                    file.close();
                } catch (IOException e) {
                    System.out.println("Problem with closing file.");
                    logger.log(Level.SEVERE, "Error, while closing the file.Reason: IOException");
                }
            }
        }
        return returnValue;
    }

    private void write(TreeMap<Equipment,Integer> myMap) {
        File file = new File("mapContent.txt");

        try {
            if(!file.exists()){
                file.createNewFile();
            }

            PrintWriter out = new PrintWriter(file.getAbsoluteFile());

            try {
                for(Map.Entry entry : myMap.entrySet()) {
                    out.print(entry.getKey().toString() + " has " + entry.getValue().toString() + " damages.\n");
                }
            } finally {
                out.close();
            }
        } catch(IOException e) {
            System.out.println("Problem while writing to the file.");
            logger.log(Level.SEVERE, "Error, while writing to the file. Reason: IOException");
        }
    }
}
