package com.maxdev.lab4asd;

public class MainClass {

	private static BinaryTree prepBinaryTree() {
		// Binary tree for tests.
		BinaryTree testTree = new BinaryTree();
		// Prepare testing set for tree testing.
		int[] idSet = { 50, 45, 20, 48, 60, 55, 70, 65, 68, 67, 69, 20, 18, 5, 19 };
		Student[] studentSet = new Student[idSet.length];
		for (int i = 0; i < studentSet.length; i++) {
			//boolean curGender = (i % 2 == 0) ? true : false;
			boolean curGender = false;
			studentSet[i] = new Student("testName", "testSurname", i, idSet[i], (double)5, curGender);
		}
		// Add students set to the tree.
		for (int i = 0; i < studentSet.length; i++) {
			testTree.insert(studentSet[i]);
		}
		return (testTree);
	}

	private static void test1(BinaryTree testTree) {
		System.out.println("----------------------------->>> Binary tree test 1 <<<-----------------------------");

		System.out.println("Size of the tree: " + testTree.size());
		System.out.println("");

		testTree.traverse();
		System.out.println("");

		Student testStudent = new Student("hello", "world", 123, 69, 5, true);
		testTree.insert(testStudent);
		System.out.println("");

		Student deletedStudent = testTree.remove(69);
		if (deletedStudent != null) {
			System.out.println("This student was deleted:");
			deletedStudent.print();
		}
		System.out.println("");

		System.out.println("Size of the tree: " + testTree.size());
		testTree.traverse();
		System.out.println("");

		Student delSt2 = testTree.remove(60);
		if (delSt2 != null) {
			System.out.println("This student was deleted:");
			delSt2.print();
		}
		System.out.println("");

		testTree.traverse();
		System.out.println("");

		Student delSt3 = testTree.remove(20);
		if (delSt3 != null) {
			System.out.println("This student was deleted:");
			delSt3.print();
		}
		System.out.println("");

		testTree.traverse();
		System.out.println("");

		System.out
				.println("----------------------------->>> End of binary tree test 1 <<<-----------------------------");
	}

	private static void test2(BinaryTree testTree) {

		System.out.println("----------------------------->>> Binary tree test 2 <<<-----------------------------");

		System.out.println("Size of the tree is " + testTree.size());
		testTree.traverse();
		System.out.println("");

		System.out.println("deleting items...");

		int itemsDeleted = testTree.removeByCriteria(5, 5);

		System.out.println("");
		System.out.println("Items, that were deleted: " + itemsDeleted);
		System.out.println("");

		System.out.println("Size of the tree is " + testTree.size());
		testTree.traverse();
		System.out.println("");

		System.out
				.println("----------------------------->>> End of binary tree test 2 <<<-----------------------------");
	}

	public static void main(String[] args) {

		BinaryTree testTree = prepBinaryTree();
		//test1(testTree);
		 test2(testTree);
	}
}
