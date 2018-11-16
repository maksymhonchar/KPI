package com.maxdev.exampractice;

public class TestingClass {	
	
	public static void main(String[] args) {
		BinaryTree testTree = new BinaryTree();
		int[] valuesSet = { 25, 50, 20, 49, 60, 70, 59, 58, 24, 8 };
		for (int i = 0; i < valuesSet.length; i++)
		{
			testTree.insert(valuesSet[i]);
		}
		// In-order traverse.
		testTree.traverse();
		
		System.out.println("Height of Node with key 50: " + testTree.findHeight(50));
		System.out.println("Height of Node with key 118: " + testTree.findHeight(118));
		System.out.println("Height of Node with key 40: " + testTree.findHeight(40));
		System.out.println("Height of Node with key 16: " + testTree.findHeight(16));
		
	}
}
