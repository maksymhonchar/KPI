package com.maxdev.lab4asd;

public class BinaryTree {

	private TreeNode root;

	public BinaryTree() {
		this.root = null;
	}

	public int size() {
		if (this.root != null) {
			return (this.root.getSize());
		}
		return (0);
	}

	public int getMin() {
		TreeNode focusNode = this.root;
		if (focusNode != null) {
			while (focusNode.getLeft() != null) {
				focusNode = focusNode.getLeft();
			}
			return (focusNode.getKey());
		} else {
			return (-1);
		}
	}

	public int getMax() {
		TreeNode focusNode = this.root;
		if (focusNode != null) {
			while (focusNode.getRight() != null) {
				focusNode = focusNode.getRight();
			}
			return (focusNode.getKey());
		} else {
			return (-1);
		}
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

	public void insert(Student value) {
		// Check if value for adding is valid.
		if (value == null) {
			return;
		}
		// Check if there student already contains in tree.
		if (this.get(value.getId()) != null) {
			System.out.println("Error: Student with key [" + value.getId() + "] already exists in tree.");
			return;
		}
		this.insertAt(value.getId(), value);
	}

	public void insertAt(int key, Student value) {
		if (value == null) {
			return;
		}
		if (key <= 0 || value.getId() != key) {
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

	public Student remove(int key) {
		// Check the key if it's valid.
		if (key <= 0) {
			return null;
		}
		if (this.root == null) {
			return null;
		}

		// Node to go through the tree.
		TreeNode focusNode = this.root;
		// Node to save previous entity of each step.
		TreeNode parent = this.root;
		// Boolean to check, if node to delete is a left, or a right child for parent. 
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
				return (null);
			}
		}
		
		// Save data in node to delete.
		Student studentToDelete = focusNode.getStudent(); 
		
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
		return (studentToDelete);
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
	
	public int removeByCriteria(int course, double averScore) {
		if (this.root == null) {
			System.out.println("Tree is empty.");
			return (0);
		}
		MyList treeNodes = new MyList();
		System.out.println("");
		this.root.removeCriteria(treeNodes, course, averScore, this.root);
		for (int i = 0; i < treeNodes.getSize(); i++) {
			int curKey = treeNodes.getFromIndex(i).getKey(); 
			this.remove(curKey);
		}
		return (treeNodes.getSize());
	}

	private void inorderTraverseTree(TreeNode root) {
		if (root != null) {
			inorderTraverseTree(root.getLeft());
			root.printKey();
			inorderTraverseTree(root.getRight());
		}
	}
}
