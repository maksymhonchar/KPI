package com.maxdev.lab3asd;

public class HashTable_2 {

	private final int defaultSize = 10;
	private final double A = (Math.sqrt(5) - 1) / 2; // 0.6180339887...
	private static final Entry DELL = new Entry();

	public Entry[] table;
	private int size = 0;
	private double loadFactor = 0.8;

	public HashTable_2() {
		this.table = new Entry[this.defaultSize];
	}

	public HashTable_2(int capacity) {
		this.table = new Entry[capacity];
	}

	public HashTable_2(int capacity, double loadFactor) {
		this.table = new Entry[capacity];
		this.loadFactor = loadFactor;
	}

	public boolean isEmpty() {
		return (this.size == 0);
	}

	public int size() {
		return (this.size);
	}

	public boolean contains(int key) {
		// Go through hash table by quadratic probing method.
		int probe = 0, hashIndex = this.hash(key);
		while (probe != this.table.length) {
			int i = (int) (hashIndex + Math.pow(probe, 2)) % this.table.length;
			if (this.table[i] == null)
				return (false);
			else if (this.table[i].getKey() == key)
				return (true);
			// If current cell is DELL - go to the next step.
			probe++;
		}
		// If method reached end of table and didn't found a key.
		return (false);
	}

	public Circle get(int key) {
		// Go through hash table by quadratic probing method.
		int probe = 0, i = this.hash(key);
		while (probe != this.table.length) {
			i = (int) (i + Math.pow(probe, 2)) % this.table.length;
			if (this.table[i] == null)
				return (null);
			else if (this.table[i].getKey() == key)
				return (this.table[i].getValue());
			// If current cell is DELL - reset counter to primary.
			i = this.hash(key);
			probe++;
		}
		// If method reached end of table and didn't found a key.
		return (null);
	}

	public Circle put(Circle value) {
		int key = (int) value.getPerimeter();
		return (this.put(key, value));
	}

	public Circle put(int key, Circle value) {
		// Check if key is correct.
		if ((int) value.getPerimeter() != key) {
			System.err.println("Incorrect key fatal error.");
			return (null);
		}
		if (((this.size + 1) / (double) this.table.length) >= this.loadFactor) {
			int prevSize = this.table.length;
			this.rehash();
			int nextSize = this.table.length;
			System.out.printf("Hash table was rehashed: [%d] to [%d]. Elems in HT now: [%d].\n", prevSize, nextSize,
					this.size());
		}
		// Go through hash table by quadratic probing method.
		int probe = 0, i = this.hash(key);
		while (probe != this.table.length) {
			i = (int) (i + Math.pow(probe, 2)) % this.table.length;
			if (this.table[i] == null || this.table[i] == DELL) {
				this.table[i] = new Entry(value);
				this.size++;
				return (null);
			}
			else if (this.table[i].getKey() == key)
			{
				Circle toRet = this.table[i].getValue();
				// this.table[i] = new Entry(value);
				this.table[i].setValue(value);
				return (toRet);
			}
			System.out.println("Collision detected! Collision on cell " + i);
			System.out.println("Circle, that was under collision:");
			value.print();
			// Reset counter to primary.
			i = this.hash(key);
			probe++;
		}
		return (null);
	}

	public Circle remove(int key) {
		// Go through hash table by quadratic probing method.
		int probe = 0, i = this.hash(key);
		while (probe != this.table.length) {
			i = (int) (i + Math.pow(probe, 2)) % this.table.length;
			if (this.table[i] == null)
				return (null);
			else if (this.table[i].getKey() == key) {
				Circle toRet = this.table[i].getValue();
				this.table[i] = DELL;
				this.size--;
				return (toRet);
			}
			// Reset counter to primary.
			i = this.hash(key);
			probe++;
		}
		return (null);
	}

	public void print() {
		System.out.printf("Hash table capacity: %2d\nHash table size: %-2d\n", this.table.length, this.size);
		for (int i = 0; i < this.table.length; i++) {
			if (this.table[i] == null) {
				System.out.printf("%2d) Empty.\n", i);
				continue;
			} else if (this.table[i] == DELL) {
				System.out.printf("%2d) Key: %3d. This Circle was deleted.\n", i, this.table[i].getKey());
				continue;
			}
			System.out.printf("%2d) Key: %3d. ", i, this.table[i].getKey());
			this.table[i].getValue().print();
		}

	}

	private int hash(int key) {
		return ((int) (this.table.length * ((key * this.A) % 1)));
	}

	private void rehash() {
		Entry[] oldTable = this.table;
		int newSize = (int) (oldTable.length / this.loadFactor);
		this.table = new Entry[newSize];
		this.size = 0;
		for (int i = 0; i < oldTable.length; i++) {
			if (oldTable[i] != null) {
				this.put(oldTable[i].getKey(), oldTable[i].getValue());
			}
		}
	}

}
