package com.maxdev.exampractice;

import java.math.BigDecimal;

public class BinaryTree {

	public class TreeNode {
		private int value;
		private int key;
		private TreeNode left;
		private TreeNode right;

		public TreeNode(int value) {
			this.value = value;
			this.key = Math.abs(this.value * 2);
			this.left = null;
			this.right = null;
		}

		public TreeNode getLeft() {
			return this.left;
		}

		public TreeNode getRight() {
			return this.right;
		}

		public void setLeft(TreeNode left) {
			this.left = left;
		}

		public void setRight(TreeNode right) {
			this.right = right;
		}

		public int getValue() {
			return this.value;
		}

		public int getKey() {
			return this.key;
		}

		public int getHeight() {
			if (this.left == null && this.right == null)
				return 0;
			else if (this.left == null) {
				return (1 + this.right.getHeight());
			} else if (this.right == null) {
				return (1 + this.left.getHeight());
			} else {
				return (1 + Math.max(this.right.getHeight(), this.left.getHeight()));
			}
		}

		public int getSize() {
			int result = 0;
			if (this.left != null) {
				result += this.left.getSize();
			}
			if (this.right != null) {
				result += this.right.getSize();
			}
			return (result += 1);
		}

		public void print() {
			System.out.println("Value: " + this.value);
		}
	}

	private TreeNode root;

	public BinaryTree() {
		this.root = null;
	}

	public int size() {
		if (this.root != null) {
			return this.root.getSize();
		}
		return 0;
	}

	public TreeNode get(int key) {
		if (this.root == null) {
			return (null);
		}
		// Start searching from the root.
		TreeNode focusNode = this.root;
		while (focusNode.getKey() != key) {
			// Choose path to go on.
			if (key < focusNode.getKey())
				focusNode = focusNode.getLeft();
			else
				focusNode = focusNode.getRight();
			// If search reached the end and node isn't found yet.
			if (focusNode == null)
				return (null);
		}
		return (focusNode);
	}

	public boolean contains(int key) {
		if (this.root == null) {
			return (false);
		}
		// Start searching from the root.
		TreeNode focusNode = this.root;
		while (focusNode.getKey() != key) {
			// Choose path to go on.
			if (key < focusNode.getKey()) {
				focusNode = focusNode.getLeft();
			} else
				focusNode = focusNode.getRight();
			// If search reached the end and node isn't found yet.
			if (focusNode == null)
				return (false);
		}
		return (true);
	}

	public void insert(int value) {
		this.insertAt(Math.abs(value * 2), value);
	}

	public void insertAt(int key, int value) {
		if (key <= 0 || Math.abs(value * 2) != key) {
			return;
		}
		// Start adding a new node to tree.
		TreeNode nodeToAdd = new TreeNode(value);
		// If there is no root in tree.
		if (this.root == null) {
			this.root = nodeToAdd;
		}
		// If tree isn't empty.
		else {
			// Node to go through the tree.
			TreeNode focusNode = this.root;
			// Node that will be a future parent for nodeToAdd.
			TreeNode futureParent = null;
			while (true) {
				// Parent is the node, from which we came before.
				futureParent = focusNode;
				// Choose which side to go on.
				if (key < focusNode.getKey()) {
					focusNode = focusNode.getLeft();
					// If search reached the end - paste the node.
					if (focusNode == null) {
						futureParent.setLeft(nodeToAdd);
						return;
					}
				} else {
					focusNode = focusNode.getRight();
					// If search reached the end - paste the node.
					if (focusNode == null) {
						futureParent.setRight(nodeToAdd);
						return;
					}
				}
			}
		}
	}

	public int remove(int key) {
		// Check the key if it's valid.
		if (key <= 0) {
			return -1;
		}
		if (this.root == null) {
			return -1;
		}

		// Node to go through the tree.
		TreeNode focusNode = this.root;
		// Node to save previous entity of each step.
		TreeNode parent = this.root;
		// Boolean to check, if node to delete is a left, or a right child for
		// parent.
		boolean isItALeftChild = false;

		// Find node by key to delete.
		while (focusNode.getKey() != key) {
			parent = focusNode;
			if (key < focusNode.getKey()) {
				isItALeftChild = true;
				focusNode = focusNode.getLeft();
			} else {
				isItALeftChild = false;
				focusNode = focusNode.getRight();
			}
			if (focusNode == null) {
				return (-1);
			}
		}

		// Save data in node to delete.
		int valueToDelete = focusNode.getKey();

		// Start removing a node.
		// If node does not have any children.
		if (focusNode.getLeft() == null && focusNode.getRight() == null) {
			if (focusNode == this.root) {
				this.root = null;
			} else if (isItALeftChild) {
				parent.setLeft(null);
			} else {
				parent.setRight(null);
			}
		}
		// Situation, when node has a single child.
		// When this child is a left child.
		else if (focusNode.getRight() == null) {
			if (focusNode == this.root) {
				this.root = focusNode.getLeft();
			} else if (isItALeftChild) {
				parent.setLeft(focusNode.getLeft());
			} else {
				parent.setRight(focusNode.getLeft());
			}
		}
		// When this child is a right child.
		else if (focusNode.getLeft() == null) {
			if (focusNode == this.root) {
				this.root = focusNode.getRight();
			} else if (isItALeftChild) {
				parent.setLeft(focusNode.getRight());
			} else {
				parent.setRight(focusNode.getRight());
			}
		}
		// Situation, when there are two or more children.
		else {
			TreeNode successor = this.getSuccessor(focusNode);
			if (focusNode == this.root) {
				this.root = successor;
			} else if (isItALeftChild) {
				parent.setLeft(successor);
			} else {
				parent.setRight(successor);
			}
			successor.setLeft(focusNode.getLeft());
		}
		return (valueToDelete);
	}

	private TreeNode getSuccessor(TreeNode replacedNode) {
		TreeNode replacementParent = replacedNode;
		TreeNode replacement = replacedNode;
		TreeNode focusNode = replacedNode.getRight();
		while (focusNode != null) {
			replacementParent = replacement;
			replacement = focusNode;
			focusNode = focusNode.getLeft();
		}
		if (replacement != replacedNode.getRight()) {
			replacementParent.setLeft(replacement.getRight());
			replacement.setRight(replacedNode.getRight());
		}
		return (replacement);
	}

	public void traverse() {
		System.out.println("In-order traversal: ");
		if (this.root != null) {
			this.inorderTraverseTree(this.root);
			System.out.println("");
			return;
		}
		System.out.println("Tree is empty.");
		return;
	}

	public int findHeight(int key) {
		// Node to go through the tree.
		TreeNode focusNode = this.root;
		// Find node by key to delete.
		while (focusNode.getKey() != key) {
			if (key < focusNode.getKey()) {
				focusNode = focusNode.getLeft();
			} else {
				focusNode = focusNode.getRight();
			}
			if (focusNode == null) {
				return (-1);
			}
		}
		
		return focusNode.getHeight();
	}

	private void inorderTraverseTree(TreeNode root) {
		if (root != null) {
			inorderTraverseTree(root.getLeft());
			System.out.print(root.getKey() + " ");
			inorderTraverseTree(root.getRight());
		}
	}

}
