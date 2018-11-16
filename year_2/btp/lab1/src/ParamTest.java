import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;


@RunWith(Parameterized.class)
public class ParamTest {

    public SwitchFSM fsmInstance = new SwitchFSM();

    @Parameter(value = 0)
    public boolean result;
    @Parameter(value = 1)
    public String reg_exp;

    @Parameters(name = "{1}")
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {

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
                { true, "<-zzzz>" }
        });

    }

    @Test
    public void testRegexp() {
        assertEquals(result, fsmInstance.scanString(reg_exp));
    }
}

