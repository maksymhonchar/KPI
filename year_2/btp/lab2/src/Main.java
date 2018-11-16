import java.util.NoSuchElementException;
import java.util.Scanner;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

import Jama.*;

public class Main {

	@SuppressWarnings("deprecation")
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		Analyzer treeVisitor = new Analyzer();
		
		System.out.println("Type your vars or an expression.");
		// todo: more text about rules, data formats
		
		while (true) {
			System.out.print("> ");;
			String input = scanner.nextLine();
			
			// handler for exiting from endless loop
			if (input.isEmpty()) {
				continue;
			} else if (input.equals("exit")) {
				scanner.close();
				break;
			}
			
			// handler for user input.
			ANTLRInputStream antlrInput = new ANTLRInputStream(input);
			MatricesLexer lexer = new MatricesLexer(antlrInput);
			CommonTokenStream tokens = new CommonTokenStream(lexer);
			MatricesParser parser = new MatricesParser(tokens);
			
			// error handler to prevent parsing incorrect input.
			parser.setErrorHandler(new DefaultErrorStrategy() {
				@Override
				public Token recoverInline(Parser recognizer) {
					throw new IllegalArgumentException("Invalid input according to \"Matrices\" grammar (recoverInLine)");
				}
				
				@Override
				public void reportError(Parser recognizer, RecognitionException e) {
					throw new IllegalArgumentException("Invalid input according to \"Matrices\" grammar (reportError)");
				}
			});
			
			// work on user input.
			try {
				// handle error in input.
				ParseTree tree = parser.root();
				// illegal argument exception, or npe.
				Matrix result = treeVisitor.visit(tree);
				// print result.
				result.print(1, 2);
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}			
		}
		
	}
}
