// Generated from Matrices.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link MatricesParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface MatricesVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by the {@code RootRule}
	 * labeled alternative in {@link MatricesParser#root}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRootRule(MatricesParser.RootRuleContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToSetVar}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToSetVar(MatricesParser.GoToSetVarContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Calculate}
	 * labeled alternative in {@link MatricesParser#input}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCalculate(MatricesParser.CalculateContext ctx);
	/**
	 * Visit a parse tree produced by the {@code SetVariable}
	 * labeled alternative in {@link MatricesParser#assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSetVariable(MatricesParser.SetVariableContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToBrackets}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToBrackets(MatricesParser.GoToBracketsContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToMatrixMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToMatrixMult(MatricesParser.GoToMatrixMultContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToVectorMult}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToVectorMult(MatricesParser.GoToVectorMultContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToInverse}
	 * labeled alternative in {@link MatricesParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToInverse(MatricesParser.GoToInverseContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToVectorMult2}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToVectorMult2(MatricesParser.GoToVectorMult2Context ctx);
	/**
	 * Visit a parse tree produced by the {@code Brackets}
	 * labeled alternative in {@link MatricesParser#brack}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBrackets(MatricesParser.BracketsContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MatrixMult}
	 * labeled alternative in {@link MatricesParser#matrmult}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMatrixMult(MatricesParser.MatrixMultContext ctx);
	/**
	 * Visit a parse tree produced by the {@code VectorMult}
	 * labeled alternative in {@link MatricesParser#vecmult}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVectorMult(MatricesParser.VectorMultContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Inverse}
	 * labeled alternative in {@link MatricesParser#inv}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInverse(MatricesParser.InverseContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Vector}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVector(MatricesParser.VectorContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Matrix}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMatrix(MatricesParser.MatrixContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Variable}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVariable(MatricesParser.VariableContext ctx);
	/**
	 * Visit a parse tree produced by the {@code GoToBrackets2}
	 * labeled alternative in {@link MatricesParser#atom}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGoToBrackets2(MatricesParser.GoToBrackets2Context ctx);
}