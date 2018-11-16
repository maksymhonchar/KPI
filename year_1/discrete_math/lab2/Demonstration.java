package mainpackage;

public class Demonstration {

	public static void main(String[] args) {

		int[][] matrix = { 
				{ 0, 5, 8, 7, 18, 0 }, 
				{ 0, 0, 11, 0, 0, 0 }, 
				{ 0, 0, 0, 0, 0, 17 }, 
				{ 0, 10, 12, 0, 6, 0 },
				{ 0, 7, 8, 0, 0, 11 }, 
				{ 0, 0, 0, 0, 0, 0 } 
		};
		int dimension = matrix[0].length;
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if (matrix[i][j] == 0)
					matrix[i][j] = 1000;
			}
		}

		// Algorithms algoHelper = new Algorithms();
		// algoHelper.EnterMatrix();

		System.out.println("Start of the program.\n");
		Algorithms algoHelper = new Algorithms(matrix, dimension);
		algoHelper.PrintMainMatrix();
		algoHelper.DijkstraAlgorithm();
		algoHelper.PrintMinDistances();
		algoHelper.PrintMinPaths();
		algoHelper.FulkersonAlgorithm();
		algoHelper.PrintMaxDistances();
		System.out.println("End of the program.");
	}
}
