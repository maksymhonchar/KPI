package mainpackage;

public class MyMatrix {

	private final int[][] EMPTY_MATRIX = {};
	private final int EMPTY_ITEM = -777;

	/**
	 * This method multiplies two matrices A and B. <br/>
	 * If matrices are not related - print a message error and return. <br/>
	 * 
	 * @param A
	 *            First matrix.
	 * @param B
	 *            Second matrix.
	 * @return Result=A*B
	 */
	public int[][] multiplyMatrices(int A[][], int B[][]) {
		// Standart fields convenience
		int aRows = A.length;
		int aCols = A[0].length;
		int bRows = B.length;
		int bCols = B[0].length;
		// Check if we can multiply matrices
		if (aCols != bRows) {
			System.out.println("Cannot multiply this matrix: ACols!=BRows");
			return (EMPTY_MATRIX);
		}
		// Multiply the matrices
		int[][] result = new int[aRows][bCols];
		for (int i = 0; i < aRows; i++) { // aRow
			for (int j = 0; j < bCols; j++) { // bColumn
				for (int k = 0; k < aCols; k++) {// aColumn
					result[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return (result);
	}

	public int[][] multiMatricesByElements(int A[][], int B[][]) {
		// Standart fields convenience
		int aRows = A.length;
		int aCols = A[0].length;
		int bRows = B.length;
		int bCols = B[0].length;
		// Check if we can multiply matrices
		if (aRows != bRows || aCols != bCols) {
			System.out.println("Cannot multiply this matrix: ACols!=BRows");
			return (EMPTY_MATRIX);
		}
		//Calculate matrix
		int[][] result = new int[aRows][bCols];
		for (int i = 0; i < aRows; i++) { // aRow
			for (int j = 0; j < bCols; j++) { // bColumn
				result[i][j] = A[i][j] * B[i][j];
			}
		}
		return (result);
	}

	/**
	 * This function transponates matrix A
	 * 
	 * @param A
	 *            Matrix to transponate
	 * @return transponated matrix
	 */
	public int[][] transponateMatrices(int A[][]) {
		int[][] result = new int[A.length][A[0].length];
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[0].length; j++) {
				result[i][j] = A[j][i];
			}
		}
		return (result);
	}

	/**
	 * This method prints the matrix out. <br/>
	 * 
	 * @param A
	 *            Matrix to print out.
	 */
	public void printMatrice(int A[][]) {
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[0].length; j++) {
				if (A[i][j] == EMPTY_ITEM) {
					System.out.printf("%5c", '_');
					continue;
				}
				System.out.printf("%5d", A[i][j]);
			}
			System.out.println("");
		}
	}

	/**
	 * This method calculates the distancy matrix from the adjacency matrix.
	 * <br/>
	 * Then distancy matrix D is printed out. <br/>
	 * 
	 * @param A
	 *            Adjacency matrix
	 * @return Distancy matrix
	 */
	public int[][] calculateDMatrix(int A[][]) {
		// The distancy matrix.
		int[][] D = new int[A.length][A[0].length];
		// Fill the D array with empty fields.
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A.length; j++) {
				D[i][j] = EMPTY_ITEM;
			}
		}
		// Copy the main diagonal from A to D.
		// It can be either zero`s or other elements - so be careful!
		for (int i = 0; i < A.length; i++)
			D[i][i] = A[i][i];
		// Main algo
		int tempA[][] = A;
		for (int stepen = 0; stepen < A.length; stepen++) {
			// first step - for A^1.
			if (stepen == 0) {
				for (int i = 0; i < A.length; i++) {
					for (int j = 0; j < A.length; j++) {
						if (A[i][j] != 0 && D[i][j] == EMPTY_ITEM)
							D[i][j] = stepen + 1;
					}
				}
				continue;
			}
			// next steps - for A^(n-1)
			tempA = multiplyMatrices(tempA, A);
			for (int i = 0; i < A.length; i++) {
				for (int j = 0; j < A.length; j++) {
					if (tempA[i][j] != 0 && D[i][j] == EMPTY_ITEM)
						D[i][j] = stepen + 1;
				}
			}
		}
		return (D);
	}

	/**
	 * This method finds amount of ways with length 1 to (n-1) with help of
	 * distance matrix. <br/>
	 * 
	 * @param D
	 *            Distance matrix
	 */
	public void calculateAmountWays(int D[][]) {
		int amount = 0;
		// Count empty fields
		for (int i = 0; i < D.length; i++) {
			for (int j = 0; j < D.length; j++) {
				if (D[i][j] == EMPTY_ITEM)
					amount++;
			}
		}
		System.out.printf("Empty items: %d\n", amount);
		// Count lenghtes of ways
		for (int wayCount = 1; wayCount < D.length; wayCount++) {
			amount = 0;
			for (int i = 0; i < D.length; i++) {
				for (int j = 0; j < D.length; j++) {
					if (D[i][j] == wayCount)
						amount++;
				}
			}
			System.out.printf("Ways with length %d: %d\n", wayCount, amount);
		}
	}

	/**
	 * This method calculates the reach matrix R and returns it<br/>
	 * 
	 * @param D
	 *            Distance matrix
	 * @return Reach matrix
	 */
	public int[][] calculateRMatrix(int[][] D) {
		int[][] R = new int[D.length][D.length];
		// Calculate items of reach matrix
		for (int i = 0; i < R.length; i++) {
			for (int j = 0; j < R.length; j++) {
				if (D[i][j] == EMPTY_ITEM)
					R[i][j] = 0;
				else
					R[i][j] = 1;
			}
		}
		return (R);
	}

	public void calculateAmountLoops(int[][] A) {
		int amount = 0;
		// First, check if D has nonzero elements on the main diagonal.
		for (int i = 0; i < A.length; i++) {
			if (A[i][i] != 0)
				amount++;
		}
		// print the message, that there are no loops here:
		if (amount == 0) {
			System.out.println("There are no loops in this graph");
			return;
		}
		// Print message what length has each loop
		for (int i = 0; i < A.length; i++) {
			if (A[i][i] != 0) {
				System.out.printf("%d vertex has %d loops\n", i + 1, A[i][i]);
			}
		}
	}

	public void calculateLengthLoops(int[][] D) {
		int amount = 0;
		// First, check if D has nonzero elements on the main diagonal.
		for (int i = 0; i < D.length; i++) {
			if (D[i][i] != 0)
				amount++;
		}
		// print the message, that there are no loops here:
		if (amount == 0) {
			System.out.println("There are no loops in this graph");
			return;
		}
		// Print message what length has each loop
		for (int i = 0; i < D.length; i++) {
			if (D[i][i] != 0) {
				System.out.printf("Length of loop on %d vertex is %d\n", i + 1, D[i][i]);
			}
		}
	}
}