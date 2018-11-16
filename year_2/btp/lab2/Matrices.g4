grammar Matrices;

/*
 * Grammar for expression (V1 ^* V2) * A^1
 * 	where:
 * 		V1, V2 - vectors.
 * 		A - matrix.
 * 		^* - multiplying two vectors.
 * 		* - multiplying matrices/vectors.
 * 		^1 - matrix inversion.
 */
 
/*
 * PARSER RULES
 */
 
root :
 	input EOF						# RootRule
 	;
 	
input :
	assignment						# GoToSetVar
	| expression					# Calculate
	;
	
assignment :
	VAR EQUAL input					# SetVariable
	;
	
expression :
	brack							# GoToBrackets
	| matrmult						# GoToMatrixMult
	| vecmult						# GoToVectorMult
	| inv							# GoToInverse
	;
	
brack :
	LB vecmult RB					# GoToVectorMult2
	| LB expression RB				# Brackets
	;

matrmult :
	brack MULT inv					# MatrixMult
	;

vecmult :
	atom VECTMULT atom				# VectorMult
	;
	
inv :
	atom (INV)?						# Inverse
	;
	
atom :
	VECTOR							# Vector
	| MATRIX						# Matrix
	| VAR							# Variable
	| brack							# GoToBrackets2
	;
 
/*
 * LEXER RULES
 */
    
// Data types.
NUMBER : '-'?([0-9]+ | [0-9]+'.'[0-9]+) ;
VECTOR : '['NUMBER(','NUMBER)*']' ;
MATRIX : '['VECTOR(';'VECTOR)*']' ;
// Variables.
VAR : [A-Z][0-9]+ ;
// Math operators.
MULT : '*' ;
VECTMULT : '^*' ;
INV : '^1' ;
// Different characters.
EQUAL : '=';
LB : '(' ;
RB : ')' ;
// To skip.
WHITESPACE : [ \n\t\r]+ -> skip;
