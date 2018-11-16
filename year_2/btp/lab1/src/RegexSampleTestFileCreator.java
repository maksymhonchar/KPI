import java.util.ArrayList;
import java.util.List;
import java.io.PrintWriter;

public class RegexSampleTestFileCreator {

    private String _writeFilePath = "";

    public RegexSampleTestFileCreator(String writeFilePath) {
        _writeFilePath = writeFilePath;
    }

    public boolean createCustomTestingFile(List<String> dataSet, boolean avoidNewLines) {
        final String ENCODING = "UTF-8";

        try {
            PrintWriter pw = new PrintWriter(_writeFilePath, ENCODING);
            for (String line : dataSet) {
                if (avoidNewLines) {
                    pw.print(line);
                }
                else {
                    pw.println(line);
                }
            }
            pw.close();
        } catch (Exception e) {
            System.out.println("Error catched while writing a dataset to file.\n" + e.getMessage());
            return false;
        }
        return true;
    }

    public List<String> createCustomTestingDataSet(int linesCnt) {
        RandUtils rndUtils = new RandUtils();
        StringBuilder sb = new StringBuilder();
        List<String> dataSet = new ArrayList<>();

        // Create lines for a data set.
        for (int i = 0; i < linesCnt; i++) {
            // Clear a stringBuilder at the beginning.
            sb.setLength(0);

            // 80% of a '+' character.
            if (rndUtils.getRndChance(80)) {
                sb.append('+');
            }

            // 80% to add [0:10] digits.
            if (rndUtils.getRndChance(80)) {
                for (int j = 0; j < rndUtils.getRndAmount(10); j++) {
                    sb.append(rndUtils.getRndNumber());
                }
            }

            // Add either digits or characters in uppercase.
            for (int j = 0; j < rndUtils.getRndAmount(10) + 1; j++) {
                if (rndUtils.getRndChance(70)) { // 80% chance to add a letter.
                    sb.append(rndUtils.getRndLetter());
                } else if (rndUtils.getRndChance(70)) { // 80% chance to add a digit.
                    sb.append(rndUtils.getRndNumber());
                } else { // Screw up a string.
                    sb.append('_');
                }
            }

            // Add a line to resulting data set.
            dataSet.add(sb.toString());
        }

        return dataSet;
    }
}
