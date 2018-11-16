// Generated from Matrices.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link MatricesParser}.
 */
public interface MatricesListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by the {@code RootRule}
	 * labeled alternative in {@link MatricesParser#root}.
	 * @param ctx the parse tree
	 */
	void enterRootRule(MatricesParser.RootRuleContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RootRule}
	 * labeled alternative in {@link MatricesParser#root}.
	 * @param ctx the parse tree
	 */
	void exitRootRule(MatricesParser.RootRuleContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToSetVar}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 */
	void enterGoToSetVar(MatricesParser.GoToSetVarContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToSetVar}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 */
	void exitGoToSetVar(MatricesParser.GoToSetVarContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Calculate}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 */
	void enterCalculate(MatricesParser.CalculateContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Calculate}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 */
	void exitCalculate(MatricesParser.CalculateContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SetVariable}
	 * labeled alternative in {@link MatricesParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterSetVariable(MatricesParser.SetVariableContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SetVariable}
	 * labeled alternative in {@link MatricesParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitSetVariable(MatricesParser.SetVariableContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToBrackets}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGoToBrackets(MatricesParser.GoToBracketsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToBrackets}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGoToBrackets(MatricesParser.GoToBracketsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToMatrixMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGoToMatrixMult(MatricesParser.GoToMatrixMultContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToMatrixMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGoToMatrixMult(MatricesParser.GoToMatrixMultContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToVectorMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGoToVectorMult(MatricesParser.GoToVectorMultContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToVectorMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGoToVectorMult(MatricesParser.GoToVectorMultContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToInverse}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterGoToInverse(MatricesParser.GoToInverseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToInverse}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitGoToInverse(MatricesParser.GoToInverseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToVectorMult2}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 */
	void enterGoToVectorMult2(MatricesParser.GoToVectorMult2Context ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToVectorMult2}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 */
	void exitGoToVectorMult2(MatricesParser.GoToVectorMult2Context ctx);
	/**
	 * Enter a parse tree produced by the {@code Brackets}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 */
	void enterBrackets(MatricesParser.BracketsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Brackets}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 */
	void exitBrackets(MatricesParser.BracketsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MatrixMult}
	 * labeled alternative in {@link MatricesParser#matrmult}.
	 * @param ctx the parse tree
	 */
	void enterMatrixMult(MatricesParser.MatrixMultContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MatrixMult}
	 * labeled alternative in {@link MatricesParser#matrmult}.
	 * @param ctx the parse tree
	 */
	void exitMatrixMult(MatricesParser.MatrixMultContext ctx);
	/**
	 * Enter a parse tree produced by the {@code VectorMult}
	 * labeled alternative in {@link MatricesParser#vecmult}.
	 * @param ctx the parse tree
	 */
	void enterVectorMult(MatricesParser.VectorMultContext ctx);
	/**
	 * Exit a parse tree produced by the {@code VectorMult}
	 * labeled alternative in {@link MatricesParser#vecmult}.
	 * @param ctx the parse tree
	 */
	void exitVectorMult(MatricesParser.VectorMultContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Inverse}
	 * labeled alternative in {@link MatricesParser#inv}.
	 * @param ctx the parse tree
	 */
	void enterInverse(MatricesParser.InverseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Inverse}
	 * labeled alternative in {@link MatricesParser#inv}.
	 * @param ctx the parse tree
	 */
	void exitInverse(MatricesParser.InverseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Vector}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void enterVector(MatricesParser.VectorContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Vector}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void exitVector(MatricesParser.VectorContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Matrix}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void enterMatrix(MatricesParser.MatrixContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Matrix}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void exitMatrix(MatricesParser.MatrixContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Variable}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void enterVariable(MatricesParser.VariableContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Variable}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void exitVariable(MatricesParser.VariableContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GoToBrackets2}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void enterGoToBrackets2(MatricesParser.GoToBrackets2Context ctx);
	/**
	 * Exit a parse tree produced by the {@code GoToBrackets2}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 */
	void exitGoToBrackets2(MatricesParser.GoToBrackets2Context ctx);
}