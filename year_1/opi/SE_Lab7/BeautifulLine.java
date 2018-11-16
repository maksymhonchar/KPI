package mainPackage;

public class BeautifulLine {

	private char[] myString;

	public BeautifulLine(char[] line) {
		int counter = 0;
		for (int i = 0; i < line.length; i++) {
			if (!Character.isLetterOrDigit(line[i])) {
				counter++;
			}
		}
		myString = new char[counter];
		int j = 0;
		for (int i = 0; i < line.length; i++) {
			if (!Character.isLetterOrDigit(line[i])) {
				myString[j] = line[i];
				j++;
			}
		}
	}

	public void getLineLength() {
		int len = myString.length;
		System.out.println("Length of line is " + len);
	}

	public void shiftRight() {
		int len = myString.length;
		char temp = myString[len - 1];
		for (int i = len - 1; i > 0; i--) {
			myString[i] = myString[i - 1];
		}
		myString[0] = temp;
	}

	public void printMyLine() {
		System.out.println("MyLine consists of such symbols: ");
		for (int i = 0; i < myString.length; i++) {
			System.out.printf(myString[i] + " ");
		}
	}
}
