// Generated from Matrices.g4 by ANTLR 4.7
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class MatricesParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		NUMBER=1, VECTOR=2, MATRIX=3, VAR=4, MULT=5, VECTMULT=6, INV=7, EQUAL=8, 
		LB=9, RB=10, WHITESPACE=11;
	public static final int
		RULE_root = 0, RULE_input = 1, RULE_assignment = 2, RULE_expression = 3, 
		RULE_brack = 4, RULE_matrmult = 5, RULE_vecmult = 6, RULE_inv = 7, RULE_atom = 8;
	public static final String[] ruleNames = {
		"root", "input", "assignment", "expression", "brack", "matrmult", "vecmult", 
		"inv", "atom"
	};

	private static final String[] _LITERAL_NAMES = {
		null, null, null, null, null, "'*'", "'^*'", "'^1'", "'='", "'('", "')'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "NUMBER", "VECTOR", "MATRIX", "VAR", "MULT", "VECTMULT", "INV", 
		"EQUAL", "LB", "RB", "WHITESPACE"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Matrices.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public MatricesParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class RootContext extends ParserRuleContext {
		public RootContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root; }
	 
		public RootContext() { }
		public void copyFrom(RootContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class RootRuleContext extends RootContext {
		public InputContext input() {
			return getRuleContext(InputContext.class,0);
		}
		public TerminalNode EOF() { return getToken(MatricesParser.EOF, 0); }
		public RootRuleContext(RootContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterRootRule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitRootRule(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitRootRule(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RootContext root() throws RecognitionException {
		RootContext _localctx = new RootContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_root);
		try {
			_localctx = new RootRuleContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(18);
			input();
			setState(19);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InputContext extends ParserRuleContext {
		public InputContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_input; }
	 
		public InputContext() { }
		public void copyFrom(InputContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class GoToSetVarContext extends InputContext {
		public AssignmentContext assignment() {
			return getRuleContext(AssignmentContext.class,0);
		}
		public GoToSetVarContext(InputContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToSetVar(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToSetVar(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToSetVar(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class CalculateContext extends InputContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public CalculateContext(InputContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterCalculate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitCalculate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitCalculate(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InputContext input() throws RecognitionException {
		InputContext _localctx = new InputContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_input);
		try {
			setState(23);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				_localctx = new GoToSetVarContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(21);
				assignment();
				}
				break;
			case 2:
				_localctx = new CalculateContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(22);
				expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignmentContext extends ParserRuleContext {
		public AssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignment; }
	 
		public AssignmentContext() { }
		public void copyFrom(AssignmentContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class SetVariableContext extends AssignmentContext {
		public TerminalNode VAR() { return getToken(MatricesParser.VAR, 0); }
		public TerminalNode EQUAL() { return getToken(MatricesParser.EQUAL, 0); }
		public InputContext input() {
			return getRuleContext(InputContext.class,0);
		}
		public SetVariableContext(AssignmentContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterSetVariable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitSetVariable(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitSetVariable(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignmentContext assignment() throws RecognitionException {
		AssignmentContext _localctx = new AssignmentContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_assignment);
		try {
			_localctx = new SetVariableContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(25);
			match(VAR);
			setState(26);
			match(EQUAL);
			setState(27);
			input();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	 
		public ExpressionContext() { }
		public void copyFrom(ExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class GoToMatrixMultContext extends ExpressionContext {
		public MatrmultContext matrmult() {
			return getRuleContext(MatrmultContext.class,0);
		}
		public GoToMatrixMultContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToMatrixMult(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToMatrixMult(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToMatrixMult(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GoToVectorMultContext extends ExpressionContext {
		public VecmultContext vecmult() {
			return getRuleContext(VecmultContext.class,0);
		}
		public GoToVectorMultContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToVectorMult(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToVectorMult(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToVectorMult(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GoToInverseContext extends ExpressionContext {
		public InvContext inv() {
			return getRuleContext(InvContext.class,0);
		}
		public GoToInverseContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToInverse(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToInverse(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToInverse(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GoToBracketsContext extends ExpressionContext {
		public BrackContext brack() {
			return getRuleContext(BrackContext.class,0);
		}
		public GoToBracketsContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToBrackets(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToBrackets(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToBrackets(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_expression);
		try {
			setState(33);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				_localctx = new GoToBracketsContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(29);
				brack();
				}
				break;
			case 2:
				_localctx = new GoToMatrixMultContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(30);
				matrmult();
				}
				break;
			case 3:
				_localctx = new GoToVectorMultContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(31);
				vecmult();
				}
				break;
			case 4:
				_localctx = new GoToInverseContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(32);
				inv();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BrackContext extends ParserRuleContext {
		public BrackContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_brack; }
	 
		public BrackContext() { }
		public void copyFrom(BrackContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class BracketsContext extends BrackContext {
		public TerminalNode LB() { return getToken(MatricesParser.LB, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RB() { return getToken(MatricesParser.RB, 0); }
		public BracketsContext(BrackContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterBrackets(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitBrackets(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitBrackets(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GoToVectorMult2Context extends BrackContext {
		public TerminalNode LB() { return getToken(MatricesParser.LB, 0); }
		public VecmultContext vecmult() {
			return getRuleContext(VecmultContext.class,0);
		}
		public TerminalNode RB() { return getToken(MatricesParser.RB, 0); }
		public GoToVectorMult2Context(BrackContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToVectorMult2(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToVectorMult2(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToVectorMult2(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BrackContext brack() throws RecognitionException {
		BrackContext _localctx = new BrackContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_brack);
		try {
			setState(43);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				_localctx = new GoToVectorMult2Context(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(35);
				match(LB);
				setState(36);
				vecmult();
				setState(37);
				match(RB);
				}
				break;
			case 2:
				_localctx = new BracketsContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(39);
				match(LB);
				setState(40);
				expression();
				setState(41);
				match(RB);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MatrmultContext extends ParserRuleContext {
		public MatrmultContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_matrmult; }
	 
		public MatrmultContext() { }
		public void copyFrom(MatrmultContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class MatrixMultContext extends MatrmultContext {
		public BrackContext brack() {
			return getRuleContext(BrackContext.class,0);
		}
		public TerminalNode MULT() { return getToken(MatricesParser.MULT, 0); }
		public InvContext inv() {
			return getRuleContext(InvContext.class,0);
		}
		public MatrixMultContext(MatrmultContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterMatrixMult(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitMatrixMult(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitMatrixMult(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MatrmultContext matrmult() throws RecognitionException {
		MatrmultContext _localctx = new MatrmultContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_matrmult);
		try {
			_localctx = new MatrixMultContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(45);
			brack();
			setState(46);
			match(MULT);
			setState(47);
			inv();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VecmultContext extends ParserRuleContext {
		public VecmultContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_vecmult; }
	 
		public VecmultContext() { }
		public void copyFrom(VecmultContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class VectorMultContext extends VecmultContext {
		public List<AtomContext> atom() {
			return getRuleContexts(AtomContext.class);
		}
		public AtomContext atom(int i) {
			return getRuleContext(AtomContext.class,i);
		}
		public TerminalNode VECTMULT() { return getToken(MatricesParser.VECTMULT, 0); }
		public VectorMultContext(VecmultContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterVectorMult(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitVectorMult(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitVectorMult(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VecmultContext vecmult() throws RecognitionException {
		VecmultContext _localctx = new VecmultContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_vecmult);
		try {
			_localctx = new VectorMultContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			atom();
			setState(50);
			match(VECTMULT);
			setState(51);
			atom();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InvContext extends ParserRuleContext {
		public InvContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inv; }
	 
		public InvContext() { }
		public void copyFrom(InvContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class InverseContext extends InvContext {
		public AtomContext atom() {
			return getRuleContext(AtomContext.class,0);
		}
		public TerminalNode INV() { return getToken(MatricesParser.INV, 0); }
		public InverseContext(InvContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterInverse(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitInverse(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitInverse(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InvContext inv() throws RecognitionException {
		InvContext _localctx = new InvContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_inv);
		int _la;
		try {
			_localctx = new InverseContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(53);
			atom();
			setState(55);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==INV) {
				{
				setState(54);
				match(INV);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AtomContext extends ParserRuleContext {
		public AtomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_atom; }
	 
		public AtomContext() { }
		public void copyFrom(AtomContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class MatrixContext extends AtomContext {
		public TerminalNode MATRIX() { return getToken(MatricesParser.MATRIX, 0); }
		public MatrixContext(AtomContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterMatrix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitMatrix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitMatrix(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class VariableContext extends AtomContext {
		public TerminalNode VAR() { return getToken(MatricesParser.VAR, 0); }
		public VariableContext(AtomContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterVariable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitVariable(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitVariable(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class VectorContext extends AtomContext {
		public TerminalNode VECTOR() { return getToken(MatricesParser.VECTOR, 0); }
		public VectorContext(AtomContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterVector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitVector(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitVector(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class GoToBrackets2Context extends AtomContext {
		public BrackContext brack() {
			return getRuleContext(BrackContext.class,0);
		}
		public GoToBrackets2Context(AtomContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).enterGoToBrackets2(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MatricesListener ) ((MatricesListener)listener).exitGoToBrackets2(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof MatricesVisitor ) return ((MatricesVisitor<? extends T>)visitor).visitGoToBrackets2(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AtomContext atom() throws RecognitionException {
		AtomContext _localctx = new AtomContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_atom);
		try {
			setState(61);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case VECTOR:
				_localctx = new VectorContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(57);
				match(VECTOR);
				}
				break;
			case MATRIX:
				_localctx = new MatrixContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(58);
				match(MATRIX);
				}
				break;
			case VAR:
				_localctx = new VariableContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(59);
				match(VAR);
				}
				break;
			case LB:
				_localctx = new GoToBrackets2Context(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(60);
				brack();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\rB\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\3\2\3\2\3\2"+
		"\3\3\3\3\5\3\32\n\3\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\5\5$\n\5\3\6\3\6\3"+
		"\6\3\6\3\6\3\6\3\6\3\6\5\6.\n\6\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\t\3"+
		"\t\5\t:\n\t\3\n\3\n\3\n\3\n\5\n@\n\n\3\n\2\2\13\2\4\6\b\n\f\16\20\22\2"+
		"\2\2A\2\24\3\2\2\2\4\31\3\2\2\2\6\33\3\2\2\2\b#\3\2\2\2\n-\3\2\2\2\f/"+
		"\3\2\2\2\16\63\3\2\2\2\20\67\3\2\2\2\22?\3\2\2\2\24\25\5\4\3\2\25\26\7"+
		"\2\2\3\26\3\3\2\2\2\27\32\5\6\4\2\30\32\5\b\5\2\31\27\3\2\2\2\31\30\3"+
		"\2\2\2\32\5\3\2\2\2\33\34\7\6\2\2\34\35\7\n\2\2\35\36\5\4\3\2\36\7\3\2"+
		"\2\2\37$\5\n\6\2 $\5\f\7\2!$\5\16\b\2\"$\5\20\t\2#\37\3\2\2\2# \3\2\2"+
		"\2#!\3\2\2\2#\"\3\2\2\2$\t\3\2\2\2%&\7\13\2\2&\'\5\16\b\2\'(\7\f\2\2("+
		".\3\2\2\2)*\7\13\2\2*+\5\b\5\2+,\7\f\2\2,.\3\2\2\2-%\3\2\2\2-)\3\2\2\2"+
		".\13\3\2\2\2/\60\5\n\6\2\60\61\7\7\2\2\61\62\5\20\t\2\62\r\3\2\2\2\63"+
		"\64\5\22\n\2\64\65\7\b\2\2\65\66\5\22\n\2\66\17\3\2\2\2\679\5\22\n\28"+
		":\7\t\2\298\3\2\2\29:\3\2\2\2:\21\3\2\2\2;@\7\4\2\2<@\7\5\2\2=@\7\6\2"+
		"\2>@\5\n\6\2?;\3\2\2\2?<\3\2\2\2?=\3\2\2\2?>\3\2\2\2@\23\3\2\2\2\7\31"+
		"#-9?";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}