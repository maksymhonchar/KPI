package com.maxdev.lab3asd;

import java.awt.Point;

public class MainLab3 {

	
	@SuppressWarnings("unused")
	private static void task1() {
		System.out.println("------------------->>> First task <<<-------------------\n");

		HashTable_1 testHT = new HashTable_1(10);
		Circle[] testSet = new Circle[5];

		// Fill hash table with test Circles set.
		for (int i = 0; i < testSet.length; i++) {
			Point tmpPoint = new Point(i, i);
			testSet[i] = new Circle(tmpPoint, i + 0.5);
			testHT.put(testSet[i]);
		}
		// Print filled hash table.
		testHT.print();

		System.out.println();

		// Check if some keys contained in hash table.
		int key1 = (int) testSet[0].getPerimeter();
		int key2 = 20;
		if (testHT.contains(key1)) {
			System.out.println("Element with key [" + key1 + "] contains in hash table.");
		}
		if (testHT.contains(key2)) {
			System.out.println("Element with key [" + key2 + "] contains in hash table.");
		}

		System.out.println();

		// Put an element to hash table cell, that is already full.
		Point tmpPoint = new Point(1, 1);
		Circle toPutCircle = new Circle(tmpPoint, 1.5);
		System.out.println("Trying to put this circle: ");
		toPutCircle.print();
		Circle refilledCircle = testHT.put((int) toPutCircle.getPerimeter(), toPutCircle);
		if (refilledCircle != null) {
			System.out.println("Hash table cell was refilled! Refilled value:");
			refilledCircle.print();
		} else {
			System.out.println("No cells from hash table were not refilled.");
		}

		System.out.println();

		// Get information about certain circle.
		Circle testCircle = testHT.get(key1);
		if (testCircle != null) {
			System.out.printf("Info about circle with key [%d]:\n", key1);
			testCircle.print();
		}

		System.out.println();

		// Remove an element by key.
		Circle deletedCircle = testHT.remove(key1);
		if (deletedCircle != null) {
			System.out.printf("Info about deleted circle with key [%d]:\n", key1);
			deletedCircle.print();
		}
		System.out.println();
		// Print hash table after deletion.
		System.out.println("Hash table after deletion:");
		testHT.print();

		System.out.println("\n------------------->>> End of the first task <<<-------------------");
	}

	private static void task2_3() {
		System.out.println("------------------->>> Second task <<<-------------------\n");

		HashTable_2 testHT = new HashTable_2(11);
		
		// Points for collision testing.
		Point testPoint = new Point(15, 15);
		Circle c1 = new Circle(testPoint, 10.5); // [1]
		Circle c2 = new Circle(testPoint, 20.5); // [1]
		Circle c3 = new Circle(testPoint, 22.5); // [1] 
		Circle c4 = new Circle(testPoint, 12.5); // [2]
		Circle c5 = new Circle(testPoint, 14.5); // [2]
		
		// Test #3
		// testHT.put(c4);
		
		// Test #1
		testHT.put(c1);
		testHT.put(c2);
		testHT.put(c3);
		
		// Test #2
		testHT.put(c4);		
		
		System.out.println("");
		
		// Print filled hash table.
		testHT.print();
		
		//
		// Deleting things.
		//
		System.out.println("");
		
		int key1 = (int) c1.getPerimeter();
		int key2 = (int) c2.getPerimeter();
		int key3 = (int) c3.getPerimeter();
		System.out.printf("Delete elements with keys:\n1)%d\n2)%d\n3)%d\n", key1, key2, key3);		
		testHT.remove(key1);
		testHT.remove(key2);
		testHT.remove(key3);
		
		System.out.println("");
		
		testHT.print();
		
		System.out.println("");
		
		//
		// Adding things on deleted cells.
		//
		
		testHT.put(c5);
		
		testHT.print();

		System.out.println("\n------------------->>> End of the second task <<<-------------------");
	}

	public static void main(String[] args) {
		// task1();
		task2_3();
	}
}
