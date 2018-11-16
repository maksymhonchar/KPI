package com.maxdev.lab3asd;

public class HashTable_1 {

	private final int defaultSize = 10;
	private final double A = (Math.sqrt(5) - 1) / 2;

	public Entry[] table;
	private int size = 0;

	public HashTable_1() {
		this.table = new Entry[this.defaultSize];
	}

	public HashTable_1(int capacity) {
		this.table = new Entry[capacity];
	}

	public boolean isEmpty() {
		return (this.size == 0);
	}

	public int size() {
		return (this.size);
	}

	public boolean contains(int key) {
		int currentHash = this.hash(key);
		return (this.table[currentHash] != null && this.table[currentHash].getKey() == key);
	}

	public Circle get(int key) {
		int hashKey = this.hash(key);
		if (this.table[hashKey] != null && this.table[hashKey].getKey() == key) {
			return (this.table[hashKey].getValue());
		} else {
			return (null);
		}
	}

	public Circle put(Circle value) {
		int key = (int) value.getPerimeter();
		return (this.put(key, value));
	}

	public Circle put(int key, Circle value) {
		// Check if key is correct.
		if ((int) value.getPerimeter() != key) {
			System.err.println("Incorrect key fatal error.");
			// TODO: incorrect argument 'key' exception.
			return (null);
		}
		// If certain cell in hash table is full - refill it with value.
		int currentHash = this.hash(key);
		if (this.table[currentHash] != null) {
			Circle toRet = this.table[currentHash].getValue();
			this.table[currentHash] = new Entry(value);
			return (toRet);
		}
		// If certain hash table cell is empty - fill it with value.
		this.table[currentHash] = new Entry(value);
		this.size++;
		return (null);
	}

	public Circle remove(int key) {
		int index = this.hash(key);
		int oldKey = this.table[index].getKey();
		if (key != oldKey) {
			return (null);
		}
		// Remove Circle at certain index.
		Circle toRet = this.table[index].getValue();
		this.table[index] = null;
		this.size--;
		return (toRet);
	}

	public void print() {
		System.out.printf("Hash table capacity: %2d\nHash table size: %-2d\n", this.table.length, this.size);
		for (int i = 0; i < this.table.length; i++) {
			if (this.table[i] == null) {
				System.out.printf("%2d) Empty.\n", i);
				continue;
			}
			System.out.printf("%2d) Key: %3d. ", i, this.table[i].getKey());
			this.table[i].getValue().print();
		}

	}

	private int hash(int key) {
		return ((int) (this.table.length * ((key * this.A) % 1)));
	}
}
