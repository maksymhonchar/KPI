import org.junit.Test;

import static junit.framework.TestCase.assertEquals;

public class FSMTest {

    public SwitchFSM instFSM = new SwitchFSM();

    // Covers an empty string.
    @Test
    public void testEmptyString() {
        assertEquals(false, instFSM.scanString(""));
    }

    // Covers no < sign.
    @Test
    public void testNoFirstSign() {
        assertEquals(false, instFSM.scanString("+23>"));
    }

    // Covers no > sign.
    @Test
    public void testNoLastSign() {
        assertEquals(false, instFSM.scanString("<+23"));
    }

    // Covers > inside of string.
    @Test
    public void testMoreSignInsideOfStr() {
        assertEquals(false, instFSM.scanString("<+2>3>"));
    }

    // Covers < inside of string.
    @Test
    public void testLessSignInsideOfStr() {
        assertEquals(false, instFSM.scanString("<+2<3>"));
    }

    // Covers missing + or - sign.
    @Test
    public void testMissingPlusOrMinusSign() {
        assertEquals(false, instFSM.scanString("<2<3>"));
    }

    // Covers no digits and letters sign.
    @Test
    public void testNoLettersNoDigits() {
        assertEquals(false, instFSM.scanString("<->"));
    }

    // Covers a normal string with digits.
    @Test
    public void testNormalStringDigits() {
        assertEquals(true, instFSM.scanString("<+1234>"));
    }

    // Covers a normal string with letters.
    @Test
    public void testNormalStringLetters() {
        assertEquals(true, instFSM.scanString("<-zzzz>"));
    }
}
