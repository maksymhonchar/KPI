package com.maxdev.lab3asd;

import java.awt.Point;

public class Circle {

	private Point center;
	private double radius;

	public Circle() {
		this.center = new Point(0, 0);
		this.radius = 0.0;
	}

	public Circle(Point center, double radius) {
		this.center = new Point(center);
		this.radius = radius <= 0.0 ? 0.0 : radius;
	}

	public double getArea() {
		return (Math.PI * Math.pow(this.radius, 2));
	}

	public double getPerimeter() {
		return (2 * Math.PI * this.radius);
	}

	public void print() {
		System.out.printf("Center:(%.2f;%.2f). Radius:%.2f\n",
				this.center.getX(), this.center.getY(),
				this.radius);
	}
}
