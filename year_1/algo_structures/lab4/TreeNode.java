package com.maxdev.lab4asd;

public class TreeNode {

	private Student value;
	private TreeNode left;
	private TreeNode right;

	public TreeNode(Student value) {
		this.value = value;
		this.left = null;
		this.right = null;
	}

	public int getKey() {
		return (this.value.getId());
	}

	public TreeNode getLeft() {
		return (this.left);
	}

	public TreeNode getRight() {
		return (this.right);
	}

	public void setLeft(TreeNode left) {
		this.left = left;
	}

	public void setRight(TreeNode right) {
		this.right = right;
	}
	
	public Student getStudent() {
		return (this.value);
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
	
	public void removeCriteria(MyList list, int course, double averScore, TreeNode node)
	{
		if (this.value.getGender() == false && 
			this.value.getCourse() == course && 
			this.value.getAverScore() == averScore)
		{
			list.addLast(node);
		}
		// Go through tree, if current node doesn't contain certain student.
		if (this.left != null) {	
			this.removeCriteria(list, course, averScore, left);
		}
		if (this.right != null) {
			this.removeCriteria(list, course, averScore, right);
		}
		// Return, when all nodes will be visited.
		return;
	}
	
	public void print() {
		System.out.println("Student with key " + this.getKey() + ":");
		this.value.print();
	}
	
	public void printKey() {
		System.out.printf("%d ", this.getKey());
	}	

}
