package com.maxdev.hometask;

import java.util.Random;

/**
 * Generate different test sets, filled with integer numbers.
 * 
 * @author MaxGonchar
 *
 */
public class DataGenerator {

	/**
	 * Random generator to get random numbers set.
	 */
	private Random rnd;

	/**
	 * Maximal bound of number, that can be placed into array. Is set in
	 * constructor.
	 */
	private int maxBound;

	/**
	 * Initialize random numbers generator and maximal bound value.
	 * 
	 * @param maxBound
	 *            Maximal bound of number in array.
	 */
	public DataGenerator(int maxBound) {
		this.rnd = new Random();
		this.maxBound = maxBound;
	}

	/**
	 * Generate average case for quicksort sorting algorithm. <br />
	 * In this case, array will be filled with random numbers.
	 * 
	 * @param arrSize
	 *            Amount of elements in array.
	 * @return Array, filled with random numbers.
	 */
	public int[] generateAverageCase(int arrSize) {
		int[] arr = new int[arrSize];
		for (int i = 0; i < arr.length; i++) {
			arr[i] = this.rnd.nextInt(this.maxBound);
		}
		return arr;
	}

	/**
	 * Generate worst case for quicksort sorting algorithm. <br />
	 * In this case, array will be filled with ascending sorted sequence. That
	 * means, that pivot placement will be the worst and algorithm will sort
	 * array of integers for time O(n^2). <br />
	 * This test set may cause StackOverflowError, because recursion depth will
	 * reach O(n) value.
	 * 
	 * @param arrSize
	 *            Amount of elements in array.
	 * @return Array, filled with random numbers.
	 */
	public int[] generateWorstCase(int arrSize) {
		int[] arr = new int[arrSize];
		for (int i = 0; i < arr.length; i++) {
			arr[i] = i + 1;
		}
		return arr;
	}

	/**
	 * Generate best case for quicksort sorting algorithm. <br />
	 * In this case, array will be filled with random numbers and there will be
	 * a special pivot, which will match the best placement and value: <br />
	 * - It will be placed in the middle of array <br />
	 * - It will have average value <br />
	 * As a result, after partition method, algorithm will be divided in two
	 * equally sorted parts.
	 * 
	 * @param arrSize
	 *            Amount of elements in array.
	 * @return Array, filled with random numbers.
	 */
	public int[] generateBestCase(int arrSize) {
		int[] arr = this.generateAverageCase(arrSize);
		arr[arr.length / 2] = this.maxBound / 2;
		return arr;
	}
	
	/**
	 * Generate chaining hash table, filled with random sequence of integer numbers. <br />
	 * Table is prepared as table for deleting element for average/best time.  
	 * 
	 * @param elementsAmount Amount of elements to fill into hash table.
	 * @return Hash table, filled with integers.
	 */
	public HashTable_Chaining generateBestAverCaseChainingTable(int elementsAmount) {
		HashTable_Chaining table = new HashTable_Chaining();
		for (int i = 0; i < elementsAmount; i++) {
			// Value doesn't matter. In this case it equals 1000.
			table.put(i, 1000);
		}
		return table;
	}

	/**
	 * Generate chaining hash table, filled with certain sequence of integer numbers. <br />
	 * All values will fill the first cell of hash table - this will cause deleting element
	 * in this hash table for worst time.
	 * 
	 * @param elementsAmount Amount of elements to fill into hash table.
	 * @return Hash table, filled with integers.
	 */
	public HashTable_Chaining generateWorstCaseChainingTable(int elementsAmount) {
		HashTable_Chaining table = new HashTable_Chaining();
		for (int i = 0, counter = 1; i < elementsAmount; i++, counter += 100) {
			// Value doesn't matter. In this case it equals 1000.
			table.put(counter, 1000);
		}
		return table;
	}

	/**
	 * Generate list, filled with random sequence of integer numbers.
	 * 
	 * @param elementsAmount Amount of elements to fill into list.
	 * @return List, filled with random numbers.
	 */
	public SingleLinkedList generateUnsortedLinkedList(int elementsAmount) {
		SingleLinkedList list = new SingleLinkedList();
		for (int i = 0; i < elementsAmount; i++) {
			list.addLast(this.rnd.nextInt(this.maxBound));
		}
		return list;
	}
}
