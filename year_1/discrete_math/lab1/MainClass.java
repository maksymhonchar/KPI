package mainpackage;

public class MainClass {

	public static void main(String[] args) {
		
		MyMatrix matrix = new MyMatrix();
//		int [][] A = {
//				{0,1,0,1,0},
//				{0,0,1,0,0},
//				{1,1,0,0,0},
//				{0,0,0,0,1},
//				{1,0,0,1,0}
//		};
		int [][] A = {
				{0,1,0,1,0,0,0,0,0},
				{0,0,1,0,0,0,0,0,0},
				{0,0,0,1,0,0,0,0,0},
				{0,0,0,0,1,0,0,0,0},
				{0,0,0,0,0,1,0,0,0},
				{0,0,0,0,0,0,1,0,0},
				{0,0,0,0,0,0,0,1,0},
				{0,0,0,0,1,0,0,0,0},
				{0,0,0,0,0,0,0,1,0}
		};
		int [][] D;
		int [][] R;
		int [][] RT;
		System.out.println("---start---");
		System.out.println("---A MATRIX---");
		matrix.printMatrice(A);
		System.out.println("---D MATRIX---");
		D = matrix.calculateDMatrix(A);
		matrix.printMatrice(D);
		System.out.println("---R MATRIX---");
		R = matrix.calculateRMatrix(D);
		matrix.printMatrice(R);
		System.out.println("---WAYS---");
		matrix.calculateAmountWays(D);
		System.out.println("--LOOPS---");
		matrix.calculateAmountLoops(A);
		matrix.calculateLengthLoops(D);
		System.out.println("---KWADRATNA FORMA---");
		RT = matrix.transponateMatrices(R);
		matrix.printMatrice(matrix.multiMatricesByElements(R, RT));
		System.out.println("---end---");
	}
}