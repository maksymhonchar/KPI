import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexSample {
    public static final String RESULTS_FILE_PATH = "matcherResult.txt";
    private Pattern _ptrn = null;

    public RegexSample(String regex) {
        try {
            _ptrn = Pattern.compile(regex, Pattern.MULTILINE);
        } catch (NullPointerException e) {
            System.out.println(e + " in RegexSample constructor.");
        }
    }

    public Map<Integer, String> readDataSetFromFile(String dataSetFilePath) {
        Map<Integer, String> dataSet = new HashMap<>();
        Matcher mtchr;
        String fileContent = "";

        try {
            fileContent = new String(Files.readAllBytes(Paths.get(dataSetFilePath)));
        } catch (IOException e) {
            System.out.println("Error catched while reading data set file content.");
            e.printStackTrace();
        }

        mtchr = _ptrn.matcher(fileContent);
        while(mtchr.find()) {
            dataSet.put(mtchr.start(), fileContent.substring(mtchr.start(), mtchr.end()));
        }

        return dataSet;
    }

    public boolean writeMatchedWordsToFile(Map<Integer, String> dataSetAsMap, String dataSetFilePath) {

        RegexSampleTestFileCreator creator = new RegexSampleTestFileCreator(dataSetFilePath);
        List<String> dataSetAsList = new ArrayList<>();
        Map<Integer, String> sortedMap = new TreeMap<>(dataSetAsMap);

        for (Map.Entry<Integer, String> entry : sortedMap.entrySet()) {
            String hmEntryToString = String.format(
                    "%1$s - %2$d position\r\n", entry.getValue().trim(), entry.getKey());
            dataSetAsList.add(hmEntryToString);
        }

        boolean fileWritten = creator.createCustomTestingFile(dataSetAsList, true);
        return fileWritten;
    }
}
