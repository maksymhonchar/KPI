package com.maxdev.hometask;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

/**
 * <b> Class with main function. </b> <br />
 * Illustrates benchmarking of several experiments: <br />
 * - Quicksort sorting algorithm (experiment1, experiment2). <br />
 * - Deleting from dictionary with different inner build (experiment3). <br />
 * To view result of any experiment, uncomment certain line in main function.
 * 
 * @author MaxGonchar
 *
 */
public class TestingClass {

	final static int maxBound = 1_000_000;

	private static void writeResults(String filename, String content) throws IOException {
		try {
			FileWriter fw = new FileWriter(filename, true);
			fw.write("\r\n" + content);
			fw.close();
		} catch (IOException ioe) {
			System.err.println("IOException: " + ioe.getMessage());
		}
	}

	static void experiment1() throws IOException {
		DataGenerator generator = new DataGenerator(maxBound);
		long startTime = 0, endTime = 0;
		double estTime = 0.0;

		for (int i = 1; i < 10; i++) {
			// Array with random numbers.
			int[] averageTestSet = generator.generateAverageCase(i * 100000);
			QuickSorter sorter = new QuickSorter(averageTestSet);
			// Array with best pivot placement.
			int[] bestTestSet = generator.generateBestCase(i * 100000);
			QuickSorter sorter2 = new QuickSorter(bestTestSet);
			// Array with worst pivot placement.
			int[] worstTestSet = generator.generateWorstCase(10000);
			QuickSorter sorter3 = new QuickSorter(worstTestSet);

			System.out.println("Sorting random set of numbers - average case.");
			writeResults("exp1_averCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter.quicksort(0, averageTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp1_averCase.txt", Double.toString(estTime) + "s\n");
			System.out.println("Estimated time for average case: " + estTime + "\n");

			System.out.println("Sorting sequence with best pivot placement.");
			writeResults("exp1_bestCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter2.quicksort(0, bestTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp1_bestCase.txt", Double.toString(estTime) + "s\n");
			System.out.println("Estimated time for best case: " + estTime + "\n");

			System.out.println("Sorting sequence with worst pivot placement.");
			writeResults("exp1_worstCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter3.quicksort(0, worstTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp1_worstCase.txt", Double.toString(estTime) + "s\n");
			System.out.println("Estimated time for worst case: " + estTime + "\n");
		}
	}

	static void experiment2() throws IOException {
		DataGenerator generator = new DataGenerator(maxBound);
		long startTime = 0, endTime = 0;
		double estTime = 0.0;

		for (int i = 1; i < 10; i++) {
			// Array with random numbers.
			int[] averageTestSet = generator.generateAverageCase(i * 100000);
			QuickSorter sorter = new QuickSorter(averageTestSet.clone());
			// Array with best pivot placement.
			int[] bestTestSet = generator.generateBestCase(i * 100000);
			QuickSorter sorter2 = new QuickSorter(bestTestSet.clone());
			// Array with worst pivot placement.
			int[] worstTestSet = generator.generateWorstCase(10000);
			QuickSorter sorter3 = new QuickSorter(worstTestSet.clone());

			System.out.println("Sorting random set of numbers - average case.");
			writeResults("exp2_averageCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter.quicksort(0, averageTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_averageCase.txt", "Lomuto: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time: " + estTime);
			startTime = System.nanoTime();
			Arrays.sort(averageTestSet);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_averageCase.txt", "Default: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time with basic sort: " + estTime + "\n");

			System.out.println("Sorting sequence with best pivot placement.");
			writeResults("exp2_bestCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter2.quicksort(0, bestTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_bestCase.txt", "Lomuto: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time: " + estTime);
			startTime = System.nanoTime();
			Arrays.sort(bestTestSet);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_bestCase.txt", "Default: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time with basic sort: " + estTime + "\n");

			System.out.println("Sorting sequence with worst pivot placement.");
			writeResults("exp2_worstCase.txt", Integer.toString(i * 100000) + " items:");
			startTime = System.nanoTime();
			sorter3.quicksort(0, worstTestSet.length - 1);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_worstCase.txt", "Lomuto: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time: " + estTime);
			startTime = System.nanoTime();
			Arrays.sort(worstTestSet);
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp2_worstCase.txt", "Default: " + Double.toString(estTime) + "s\n");
			System.out.println("Estimated time with basic sort: " + estTime + "\n");

		}
	}

	static void experiment3() throws IOException {
		DataGenerator generator = new DataGenerator(maxBound);
		long startTime = 0, endTime = 0;
		double estTime = 0.0;

		for (int j = 1; j < 10; j++)
		{
			// Lists for two sub-experiments.
			SingleLinkedList list1 = generator.generateUnsortedLinkedList(100000 + 10000 * j);
			// Chaining hash tables for two sub-experiments.
			HashTable_Chaining bestCaseHT = generator.generateBestAverCaseChainingTable(100000 + 10000 * j);
			HashTable_Chaining worstCaseHT = generator.generateWorstCaseChainingTable(100000 + 10000 * j);
			writeResults("exp3_HashTableDeletion_AverCase.txt", "Items in hashtable: " + Integer.toString(100000 + 10000 * j));
			writeResults("exp3_HashTableDeletion_WorstCase.txt", "Items in hashtable: " + Integer.toString(100000 + 10000 * j));
			writeResults("exp3_RandomLinkedListDeletion_AverCase.txt", "Items in list: " + Integer.toString(100000 + 10000 * j) + "\n");

			System.out.println("Average case - deleting random elements from hashtable.");
			startTime = System.nanoTime();
			writeResults("exp3_HashTableDeletion_AverCase.txt", Integer.toString(j * 10000) + " items:");
			for (int i = 0; i < j * 10000; i++) {
				bestCaseHT.remove(i);
			}
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp3_HashTableDeletion_AverCase.txt", Double.toString(estTime) + "s");
			System.out.println("Estimated time for average case: " + estTime + "\n");

			System.out.println("Worst case - deleting random elements from hashtable.");
			writeResults("exp3_HashTableDeletion_WorstCase.txt", Integer.toString(j * 10000) + " items:");
			startTime = System.nanoTime();
			for (int i = 0; i < j * 10000; i++) {
				worstCaseHT.remove(i);
			}
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp3_HashTableDeletion_WorstCase.txt", Double.toString(estTime) + "s");
			System.out.println("Estimated time for average case: " + estTime + "\n");

			System.out.println("Deleting random elements from list with random elements.");
			writeResults("exp3_RandomLinkedListDeletion_AverCase.txt", Integer.toString(j * 10000) + " items:");
			startTime = System.nanoTime();
			for (int i = 0; i < j * 10000; i++) {
				list1.deleteIndex(i + 500);
			}
			endTime = System.nanoTime();
			estTime = (endTime - startTime) / 1000000000.0;
			writeResults("exp3_RandomLinkedListDeletion_AverCase.txt", Double.toString(estTime) + "s");
			System.out.println("Estimated time: " + estTime + "\n");
		}		
	}

	public static void main(String[] args) throws IOException {
		// experiment1();
		// experiment2();
		experiment3();
	}
}
