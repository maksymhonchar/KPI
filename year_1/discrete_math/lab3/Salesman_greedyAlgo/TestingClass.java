package mainpackage;

public class TestingClass {

	public static void main(String[] args) {
		final int N = 1000;
		int[][] adjacencyMatrix = {
				{N,8,6,2,5},
				{1,N,3,4,6},
				{5,7,N,7,2},
				{9,2,3,N,4},
				{8,4,6,1,N}				
		};
		
		GreedyAlgoHelper greedyHelper = new GreedyAlgoHelper(adjacencyMatrix);
		
		System.out.println("Adjacenct matrix:");
		greedyHelper.printMatrix();
		
		System.out.println("Doing greedy algorithm...");
		int minLength = greedyHelper.algorithm();
		
		System.out.print("Path: ");
		greedyHelper.printPath();
		
		System.out.print("Weight on each step: ");
		greedyHelper.printStepsWeight();
		
		System.out.println("Min length by greedy algorithm: " + minLength);
		
	}
	
}
