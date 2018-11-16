package com.maxdev.hometask;

public class LinkedHashEntry {
	private int key;
	private int value;
	private LinkedHashEntry next;
	
	public LinkedHashEntry(int key, int value) {
		this.key = key;
		this.value = value;
		this.next = null;
	}
	
	public int getValue() {
		return value;
	}
	
	public void setValue(int value) {
		this.value = value;
	}
	
	public int getKey() {
		return this.key;
	}
	
	public LinkedHashEntry getNext() {
		return this.next;
	}
	
	public void setNext(LinkedHashEntry next) {
		this.next = next;
	}
}
