package com.maxdev.lab4asd;

public class Student {

	private String name;
	private String surname;
	private int course;
	private int id;
	private double averScore;
	// 'True' means male and 'False' means female.
	private boolean gender;

	public Student(String name, String surname, int course, int id, double averScore, boolean gender) {
		this.name = name;
		this.surname = surname;
		this.course = course;
		this.id = (id <= 0) ? 0 : id;
		this.averScore = averScore;
		this.gender = gender;
	}

	public int getId() {
		return (this.id);
	}

	public void setId(int newId) {
		if (newId <= 0) {
			return;
		}
		this.id = newId;
	}

	public boolean getGender() {
		return (this.gender);
	}

	public double getAverScore() {
		return (this.averScore);
	}

	public int getCourse() {
		return (this.course);
	}

	public void print() {
		System.out.println(this.name + " " + this.surname + " gender:" + (this.gender ? "male" : "female") + " course:"
				+ this.course + " id:" + this.id + " averScore:" + this.averScore);
	}

}
