import org.junit.experimental.theories.DataPoints;
import org.junit.experimental.theories.Theories;
import org.junit.experimental.theories.Theory;
import org.junit.runner.RunWith;

import static junit.framework.Assert.assertEquals;

@RunWith(Theories.class)
public class TheoriesTest {

    public SwitchFSM thyFSM = new SwitchFSM();
    // public TransTableFSM thyFSM = new TransTableFSM();
    // public StateFSM thyFSM = new StateFSM();

    @DataPoints
    public static Object[][] testData = new Object[][] {

            // Covers an empty string.
            { false, "" },

            // Covers no < sign.
            { false, "+23>" },

            // Covers no > sign.
            { false, "<+23" },

            // Covers > inside of string.
            { false, "<+2>3>" },

            // Covers < inside of string.
            { false, "<+2<3>" },

            // Covers missing + or - sign.
            { false, "<2<3>" },

            // Covers no digits and letters sign.
            { false, "<->" },

            // Covers a normal string with digits.
            { true, "<+1234>" },

            // Covers a normal string with letters.
            { true, "<-zzzz>" },
    };

    @Theory
    public void testRegexp(final Object... testData) {
        final boolean actual = thyFSM.scanString((String)testData[1]);
        assertEquals(testData[0], actual);
    }
}