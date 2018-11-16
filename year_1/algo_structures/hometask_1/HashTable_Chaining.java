package com.maxdev.hometask;

public class HashTable_Chaining {
	private final int TABLE_SIZE = 100;
	LinkedHashEntry[] table;

	public HashTable_Chaining() {
		this.table = new LinkedHashEntry[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			this.table[i] = null;
		}
	}

	public int get(int key) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] == null)
			return -1;
		else {
			LinkedHashEntry entry = table[hash];
			while (entry != null && entry.getKey() != key)
				entry = entry.getNext();
			if (entry == null)
				return -1;
			else
				return entry.getValue();
		}
	}

	public void put(int key, int value) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] == null)
			table[hash] = new LinkedHashEntry(key, value);
		else {
			LinkedHashEntry entry = table[hash];
			while (entry.getNext() != null && entry.getKey() != key)
				entry = entry.getNext();
			if (entry.getKey() == key)
				entry.setValue(value);
			else
				entry.setNext(new LinkedHashEntry(key, value));
		}
	}

	public int remove(int key) {
		int hash = (key % TABLE_SIZE);
		if (table[hash] != null) {
			LinkedHashEntry prevEntry = null;
			LinkedHashEntry entry = table[hash];
			while (entry.getNext() != null && entry.getKey() != key) {
				prevEntry = entry;
				entry = entry.getNext();
			}
			if (entry.getKey() == key) {
				if (prevEntry == null) {
					int toRet = entry.getValue();
					table[hash] = entry.getNext();
					return toRet;
				} else {
					int toRet = entry.getValue();
					prevEntry.setNext(entry.getNext());
					return toRet;
				}
			}
		}
		return 0;
	}
}
