import java.util.Arrays;
import java.util.NoSuchElementException;

import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.junit.Test;
import static org.junit.Assert.assertEquals;

import Jama.Matrix;

public class Tests {
	Analyzer visitorAnalyzer;
	@SuppressWarnings("deprecation")
	ANTLRInputStream input;
	MatricesLexer lexer;
	CommonTokenStream tokens;
	MatricesParser parser;
	ParseTree tree;
	
	private double[][] prepareToTest(String stringToAnalyze) {
		visitorAnalyzer = new Analyzer();
 	    input = new ANTLRInputStream(stringToAnalyze);
 	    lexer = new MatricesLexer(input);
 	    tokens = new CommonTokenStream(lexer);
 	    parser = new MatricesParser(tokens);
 	    tree = parser.root();
 	    
 	    Matrix toCompare = null;
 	    
 	    try {
			toCompare = visitorAnalyzer.visit(tree);
			return toCompare.getArrayCopy();
		} catch (IllegalArgumentException | NoSuchElementException e) {
 	    	throw e;
 	    } catch (NullPointerException e) {
 	    	throw e;
 	    }
	}
	
	@Test(expected = NullPointerException.class)
	public void testWhiteSpaces() {
		double[][] toCompare = { { 4.0, 10.0, 18.0 } };
		String antlrInputString = "[1, 2, 3] ^* [4, 5, 6]";
		assertEquals(true, Arrays.deepEquals(prepareToTest(antlrInputString), toCompare));
	}
	
	public void twoWhitespaces() {
		double[][] toCompare = { { 4.0, 10.0, 18.0 } };
		String antlrInputString = "A1=  [1,2,3]  ^*  [4,5,6]  ";
		assertEquals(true, Arrays.deepEquals(prepareToTest(antlrInputString), toCompare));
	}
		
	@Test
	public void testVectorMult() {
		double[][] toCompare = { { 4.0, 10.0, 18.0 } };
		String antlrInputString = "[1,2,3] ^* [4,5,6]";
		assertEquals(true, Arrays.deepEquals(prepareToTest(antlrInputString), toCompare));
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidDimensionsMultMatrices() {
		prepareToTest("([1,2]^*[1,2,3])*[[1,2,3];[1,2,3]]");
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidDimensionsMultVectors() {
		prepareToTest("([1,2]^*[1,2,3])");
	}
	
	@Test
	public void testDefaultInput() {
		double[][] toCompare = { { 6.00, -1.00 } };		
		String antlrInputString = "([1,2]^*[3,4])*[[1,2];[3,4]]^1";
		double[][] result = prepareToTest(antlrInputString);
		for (double[] ds : result) {
			for (int i = 0; i < ds.length; i++) {
				ds[i] = (int)Math.round(ds[i]);
			}
		}		
		assertEquals(true, Arrays.deepEquals(result, toCompare));
	}
	
	@Test (expected = NullPointerException.class)
	public void testInvalidVariableFormatNoDigits() {
		prepareToTest("A");
	}
	
	@Test (expected = NullPointerException.class)
	public void testInvalidVariableFormatLowercase() {
		prepareToTest("a11");
	}
	
	@Test (expected = NullPointerException.class)
	public void testCatchUndeclaredVariable() {
		prepareToTest("a");
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testCatchInvalidMatrix() {
		prepareToTest("[[1,2,3,4,5];[1,2,3,4]]");
	}
	
	@Test (expected = NullPointerException.class)
	public void testCatchInvalidVector() {
		prepareToTest("[1,  2,3  ,4,5]");
	}
	
	@Test (expected = RuntimeException.class)
	public void testInvalidInverseCauseOfDeterminantEqualsToZero() {
		prepareToTest("A1 = [[1,2,3];[4,5,6];[7,8,9]]^1");
	}
	
	@Test
	public void testManyBrackets() {
		double[][] toCompare = { {2.0, 4.0} };
		String antlrInputString = "(((([1,2]^*[2,2]))))";
		assertEquals(true, Arrays.deepEquals(prepareToTest(antlrInputString), toCompare));		
	}
}
