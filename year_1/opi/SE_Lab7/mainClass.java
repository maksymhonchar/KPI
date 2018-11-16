package mainPackage;

public class mainClass {

	public static void main(String[] args) {
		char[] str = {1, '_', 'a','d',')', '5','z','0','@', '&'};
		BeautifulLine lineObj = new BeautifulLine(str);
		
		lineObj.printMyLine();
		System.out.println(" ");
		lineObj.getLineLength();
		lineObj.shiftRight();
		System.out.println("After shifting : ");
		lineObj.printMyLine();
		lineObj.shiftRight();
	}
}