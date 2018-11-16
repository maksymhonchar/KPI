import org.omg.CORBA.Environment;

public class LabLauncher {

    private static final String DATASET_WITH_LINES = "testDataSet1.txt";
    private static final String DATASET_CHECKED_WITH_REGEX = "dataSet1Matches.txt";
    private static final String DATASET_PLAIN_TEXT = "testDataSet2.txt";
    private static final String DATASET_CHECKED_WITH_REGEX_2 = "dataSet2Matches.txt";

    public static void main(String[] args) {
        // firstTask();

        secondTask();
    }

    private static void firstTask() {
        // Task 1.1
        RegexSample rs = new RegexSample("^\\+(\\d+)(\\d|[A-Z])+$");
        RegexSampleTestFileCreator creator = new RegexSampleTestFileCreator(DATASET_WITH_LINES);
        // create a data set.
        boolean testingFileCreated = creator.createCustomTestingFile(
                creator.createCustomTestingDataSet(100), false );
        if (!testingFileCreated) {
            System.out.println("Error in 1.1(1)");
            return;
        }
        // check a data set.
        boolean matchesFileWritten = rs.writeMatchedWordsToFile(
                rs.readDataSetFromFile(DATASET_WITH_LINES), DATASET_CHECKED_WITH_REGEX );
        if (!matchesFileWritten) {
            System.out.println("Error in 1.1(2)");
            return;
        }

        // Task 1.2
        rs = new RegexSample("\\+(\\d+)(\\d|[A-Z])+");
        // create a data set.
        creator = new RegexSampleTestFileCreator(DATASET_PLAIN_TEXT);
        testingFileCreated = creator.createCustomTestingFile(
                creator.createCustomTestingDataSet(50), true );
        if (!testingFileCreated) {
            System.out.println("Error in 1.2(1)");
            return;
        }
        // check a data set.
        matchesFileWritten = rs.writeMatchedWordsToFile(
                rs.readDataSetFromFile(DATASET_PLAIN_TEXT), DATASET_CHECKED_WITH_REGEX_2 );
        if (!matchesFileWritten) {
            System.out.println("Error in 1.2(2)");
            // return;
        }
    }

    private static void secondTask() {
        String[] testCases = {
                "<+05>",
                "<-zzz>",
                "<+02szsz>"
        };

        // Task 2.1. Switch FSM.
        System.out.println("Switch FSM");
        SwitchFSM switchFSM = new SwitchFSM();
        for (int i = 0; i < testCases.length; i++) {
            System.out.print("Test case: " + testCases[i]);
            System.out.println("\tResult: " + switchFSM.scanString(testCases[i]));
        }
        System.out.println("");

        // Task 2.2. Transition table SFM.
        System.out.println("Transition table SFM");
        TransTableFSM transTableFSM = new TransTableFSM();
        for (int i = 0; i < testCases.length; i++) {
            System.out.print("Test case: " + testCases[i]);
            System.out.println("\tResult: " + transTableFSM.scanString(testCases[i]));
        }
        System.out.println("");

        // Task 2.3. State SFM.
        System.out.println("State FSM");
        StateFSM stateFSM = new StateFSM();
        for (int i = 0; i < testCases.length; i++) {
            System.out.print("Test case: " + testCases[i]);
            System.out.println("\tResult: " + stateFSM.scanString(testCases[i]));
            stateFSM.start();
        }
    }
}
