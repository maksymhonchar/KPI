package com.maxdev.hometask;

public class SingleLinkedList {

	private class Node {
		public int data;
		public Node next;

		public Node(int data) {
			this.data = data;
			this.next = null;
		}
	}

	private int size;
	private Node head;

	public SingleLinkedList() {
		this.size = 0;
		this.head = null;
	}

	public void addFirst(int data) {
		Node newNode = new Node(data);
		if (size != 0) {
			newNode.next = head;
		}
		head = newNode;
		size++;
	}

	void addLast(int data) {
		Node newNode = new Node(data);
		if (size == 0) {
			head = newNode;
		} else {
			Node tail = head;
			while (tail.next != null) {
				tail = tail.next;
			}
			tail.next = newNode;
		}
		size++;
	}

	void addIndex(int data, int index) {
		if (index < 0 || index > size) {
			System.out.println("Invalid index");
			return;
		}
		if (index == 0) {
			addFirst(data);
			return;
		}
		if (index == size) {
			addLast(data);
			return;
		}
		Node current = head;
		for (int i = 0; i < index; i++) {
			current = current.next;
		}
		Node newNode = new Node(data);
		newNode.next = current.next;
		current.next = newNode;
		size++;
	}

	void print() {
		if (size == 0) {
			System.out.println("My linked list is empty");
			return;
		}
		Node current = head;
		System.out.println("Items in linked list:");
		while (current != null) {
			System.out.print(current.data + " ");
			current = current.next;
		}
		System.out.println("");
	}

	int deleteFirst() {
		if (size == 0) {
			return 0;
		}
		int toDelete = head.data;
		head = head.next;
		size--;
		return toDelete;
	}

	int deleteIndex(int index) {
		if (index < 0 || index >= size) {
			System.out.println("Invalid index");
			return 0;
		}
		if (index == 0) {
			return deleteFirst();
		} else if (index == size - 1) {
			return deleteLast();
		}
		Node current = head;
		for (int i = 1; i < index; i++) {
			current = current.next;
		}
		Node deleteNode = current.next;
		current.next = deleteNode.next;
		size--;
		return deleteNode.data;
	}

	int deleteLast() {
		return deleteIndex(size - 1);
	}

	int getSize() {
		return size;
	}

	int getFromIndex(int index) {
		if (index < 0 || index >= size) {
			System.out.println("Invalid index");
			return -1;
		}
		if (index == 0) {
			return head.data;
		}
		Node current = head;
		for (int i = 0; i < index; i++) {
			current = current.next;
		}
		return current.data;
	}

	boolean isEmpty() {
		return size == 0;
	}
}
