package com.maxdev.lab3asd;

public class Entry {

	private int key;
	private Circle value;

	public Entry() {
		this.key = -1;
		this.value = null;
	}

	public Entry(Circle circle) {
		this.key = (int) circle.getPerimeter();
		this.value = circle;
	}

	public Entry(int key, Circle circle) {
		this.key = key;
		this.value = circle;
	}

	public void setKey(int key) {
		this.key = key;
	}

	public int getKey() {
		return (this.key);
	}

	public void setValue(Circle value) {
		this.value = value;
	}

	public Circle getValue() {
		return (this.value);
	}
}
