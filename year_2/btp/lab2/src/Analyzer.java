import java.util.HashMap;
import java.util.NoSuchElementException;

import Jama.*;

public class Analyzer extends MatricesBaseVisitor<Matrix> {
	private HashMap<String, Matrix> _variables = new HashMap<String, Matrix>();
	
	@Override
	public Matrix visitRootRule(MatricesParser.RootRuleContext ctx) {
		System.out.println("visit root rule");;
		return visit(ctx.input());
	}
	
	@Override
	public Matrix visitGoToSetVar(MatricesParser.GoToSetVarContext ctx) {
		System.out.println("visit gotosetvar rule");
		return visit(ctx.assignment());
	}
	
	@Override
	public Matrix visitCalculate(MatricesParser.CalculateContext ctx) {
		System.out.println("visit calculate rule");
		return visit(ctx.expression());
	}
	
	@Override
	public Matrix visitSetVariable(MatricesParser.SetVariableContext ctx) {
		System.out.println("visit setvariable rule");
		Matrix value = visit(ctx.input());
		if (value != null) {
			_variables.put(ctx.VAR().getText(), value);
		} else {
			String throwMsg = "\nAn Refused an attempt to assign null value to variable.";
			throw new IllegalArgumentException(throwMsg);
		}
		return value;
	}
	
	@Override
	public Matrix visitGoToBrackets(MatricesParser.GoToBracketsContext ctx) {
		System.out.println("visit gotobrackets rule");
		return visit(ctx.brack());
	}
	
	@Override
	public Matrix visitGoToMatrixMult(MatricesParser.GoToMatrixMultContext ctx) {
		System.out.println("visit gotovecmatrmultcontext rule");
		return visit(ctx.matrmult());
	}
	
	@Override
	public Matrix visitGoToVectorMult(MatricesParser.GoToVectorMultContext ctx) {
		System.out.println("visit gotovectormult rule");
		return visit(ctx.vecmult());
	}
	
	@Override
	public Matrix visitGoToInverse(MatricesParser.GoToInverseContext ctx) {
		System.out.println("visit gotoinverse rule");
		return visit(ctx.inv());
	}
	
	@Override
	public Matrix visitGoToVectorMult2(MatricesParser.GoToVectorMult2Context ctx) {
		System.out.println("visit gotovectormult2 rule");
		return visit(ctx.vecmult());
	}
	
	@Override
	public Matrix visitBrackets(MatricesParser.BracketsContext ctx) {
		System.out.println("visit braces rule");
		return visit(ctx.expression());
	}
	
	@Override
	public Matrix visitMatrixMult(MatricesParser.MatrixMultContext ctx) {
		System.out.println("visit matrixmult rule");
		try {
			Matrix firstMatrix = visit(ctx.brack());
			Matrix secondMatrix = visit(ctx.inv());
			return firstMatrix.times(secondMatrix);
		} catch (IllegalArgumentException e) {
			String throwMsg = "\nInvalid dimensions while performing \"*\" operation.";
			throw new IllegalArgumentException(throwMsg);
		}
	}
	
	@Override
	public Matrix visitVectorMult(MatricesParser.VectorMultContext ctx) {
		System.out.println("visit vectormult rule");
		try {
			Matrix firstMatrix = visit(ctx.atom(0));
			Matrix secondMatrix = visit(ctx.atom(1));
			// multiply two vectors.
			return firstMatrix.arrayTimes(secondMatrix);			
		} catch (IllegalArgumentException e) {
			String throwMsg = "\nInvalid dimensions while performing \"^*\" operation.";
			throw new IllegalArgumentException(throwMsg);
		}
	}
	
	@Override
	public Matrix visitInverse(MatricesParser.InverseContext ctx) {
		System.out.println("visit inverse rule");
		try {
			if (ctx.INV() != null) {
				return visit(ctx.atom()).inverse();
			}
		} catch (IllegalArgumentException e) {
			String throwMsg = "\nInvalid dimensions while performing \"^1\" operation.";
			throw new IllegalArgumentException(throwMsg);
		}
		return visit(ctx.atom());
	}
	
	@Override
	public Matrix visitVector(MatricesParser.VectorContext ctx) {
		System.out.println("visit vector rule");
		String vectorAsString = ctx.getText();
		vectorAsString = vectorAsString.replace("[", "").replace("]", "");
		
		String[] vectorValuesArr = vectorAsString.split(",");
		double[] arr = new double[vectorValuesArr.length];
		
		for (int i = 0; i < arr.length; i++) {
			arr[i] = Double.valueOf(vectorValuesArr[i]);
		}
		
		try {
			Matrix toReturn = new Matrix(arr, 1); // 1 for 1 dimension as vector.
			return toReturn;
		} catch (IllegalArgumentException e) {
			String throwMsg = "\nInvalid dimensions while creating a Vector";
			throw new IllegalArgumentException(throwMsg);
		}		
	}
	
	@Override
	public Matrix visitMatrix(MatricesParser.MatrixContext ctx) {
		System.out.println("visit matrix rule");
		String matrixAsString = ctx.getText();
		matrixAsString = matrixAsString.replace("[", "").replace("]", "");
		
		String[] vectorArr = matrixAsString.split(";");
		double[][] arr = new double[vectorArr.length][];
		
		for (int i = 0; i < vectorArr.length; i++) {
			String[] numbers = vectorArr[i].split(",");
			arr[i] = new double[numbers.length];
			for (int j = 0; j < numbers.length; j++) {
				arr[i][j] = Double.valueOf(numbers[j]);
			}
		}
		
		try {
			Matrix toReturn = new Matrix(arr);
			return toReturn;
		} catch (IllegalArgumentException e) {
			String throwMsg = "\nInvalid dimensions while creating a Matrix";
			throw new IllegalArgumentException(throwMsg);
		}
	}
	
	@Override
	public Matrix visitVariable(MatricesParser.VariableContext ctx) {
		System.out.println("visit variable rule");
		if (_variables.containsKey(ctx.VAR().getText())) {
			return _variables.get(ctx.VAR().getText());
		} else {
			String throwMsg = String.format("\nThere is not such variable \"%s\" in the HashMap.");
			throw new NoSuchElementException(throwMsg);
		}
	}
	
	@Override
	public Matrix visitGoToBrackets2(MatricesParser.GoToBrackets2Context ctx) {
		System.out.println("visit gotobrackets2 rule");
		return visit(ctx.brack());
	}
}
