// Generated from Matrices.g4 by ANTLR 4.7
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class MatricesLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		NUMBER=1, VECTOR=2, MATRIX=3, VAR=4, MULT=5, VECTMULT=6, INV=7, EQUAL=8, 
		LB=9, RB=10, WHITESPACE=11;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"NUMBER", "VECTOR", "MATRIX", "VAR", "MULT", "VECTMULT", "INV", "EQUAL", 
		"LB", "RB", "WHITESPACE"
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


	public MatricesLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Matrices.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\r_\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\3\2\5\2\33\n\2\3\2\6\2\36\n\2\r\2\16\2\37\3\2\6\2#\n\2\r\2"+
		"\16\2$\3\2\3\2\6\2)\n\2\r\2\16\2*\5\2-\n\2\3\3\3\3\3\3\3\3\7\3\63\n\3"+
		"\f\3\16\3\66\13\3\3\3\3\3\3\4\3\4\3\4\3\4\7\4>\n\4\f\4\16\4A\13\4\3\4"+
		"\3\4\3\5\3\5\6\5G\n\5\r\5\16\5H\3\6\3\6\3\7\3\7\3\7\3\b\3\b\3\b\3\t\3"+
		"\t\3\n\3\n\3\13\3\13\3\f\6\fZ\n\f\r\f\16\f[\3\f\3\f\2\2\r\3\3\5\4\7\5"+
		"\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\3\2\5\3\2\62;\3\2C\\\5\2\13\f"+
		"\17\17\"\"\2g\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2"+
		"\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2"+
		"\27\3\2\2\2\3\32\3\2\2\2\5.\3\2\2\2\79\3\2\2\2\tD\3\2\2\2\13J\3\2\2\2"+
		"\rL\3\2\2\2\17O\3\2\2\2\21R\3\2\2\2\23T\3\2\2\2\25V\3\2\2\2\27Y\3\2\2"+
		"\2\31\33\7/\2\2\32\31\3\2\2\2\32\33\3\2\2\2\33,\3\2\2\2\34\36\t\2\2\2"+
		"\35\34\3\2\2\2\36\37\3\2\2\2\37\35\3\2\2\2\37 \3\2\2\2 -\3\2\2\2!#\t\2"+
		"\2\2\"!\3\2\2\2#$\3\2\2\2$\"\3\2\2\2$%\3\2\2\2%&\3\2\2\2&(\7\60\2\2\'"+
		")\t\2\2\2(\'\3\2\2\2)*\3\2\2\2*(\3\2\2\2*+\3\2\2\2+-\3\2\2\2,\35\3\2\2"+
		"\2,\"\3\2\2\2-\4\3\2\2\2./\7]\2\2/\64\5\3\2\2\60\61\7.\2\2\61\63\5\3\2"+
		"\2\62\60\3\2\2\2\63\66\3\2\2\2\64\62\3\2\2\2\64\65\3\2\2\2\65\67\3\2\2"+
		"\2\66\64\3\2\2\2\678\7_\2\28\6\3\2\2\29:\7]\2\2:?\5\5\3\2;<\7=\2\2<>\5"+
		"\5\3\2=;\3\2\2\2>A\3\2\2\2?=\3\2\2\2?@\3\2\2\2@B\3\2\2\2A?\3\2\2\2BC\7"+
		"_\2\2C\b\3\2\2\2DF\t\3\2\2EG\t\2\2\2FE\3\2\2\2GH\3\2\2\2HF\3\2\2\2HI\3"+
		"\2\2\2I\n\3\2\2\2JK\7,\2\2K\f\3\2\2\2LM\7`\2\2MN\7,\2\2N\16\3\2\2\2OP"+
		"\7`\2\2PQ\7\63\2\2Q\20\3\2\2\2RS\7?\2\2S\22\3\2\2\2TU\7*\2\2U\24\3\2\2"+
		"\2VW\7+\2\2W\26\3\2\2\2XZ\t\4\2\2YX\3\2\2\2Z[\3\2\2\2[Y\3\2\2\2[\\\3\2"+
		"\2\2\\]\3\2\2\2]^\b\f\2\2^\30\3\2\2\2\f\2\32\37$*,\64?H[\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}