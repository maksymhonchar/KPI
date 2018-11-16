package com.maxdev;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Paint;
import javafx.scene.shape.*;
import javafx.stage.Stage;

public class Test extends Application {
    public static void main (String args[]) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        // Scene (root, x, y)
        Scene scene = new Scene (root, 800, 800);

		/*
		// creating of red rectangle
		final Rectangle rect1 = new Rectangle(10, 10, 100, 100);
		// arch and arcw
		rect1.setArcHeight(100);
		rect1.setArcWidth(60);
		rect1.setFill(Color.RED);
		root.getChildren().add(rect1);

		Line l = new Line(100, 100, 200, 100); //
		root.getChildren().add(l);
		l.setStroke(Color.RED);

		// Circle (x, y, R)
		Circle circle = new Circle(100,100,50);
		root.getChildren().add(circle);

		// curved line
		Polyline polyline = new Polyline(0, 0.0, 20.0, 10.0, 10.0, 20.0);
		root.getChildren().add(polyline);

		// Ellipse (x, y, Rx, Ry)
		Ellipse ellipse = new Ellipse(50,50,50,25);
		root.getChildren().add(ellipse);
		*/

        // Arc types: ArcType.OPEN, ArcType.CHORD (tied), ArcType.Round (half-rectangle)
        // Arc (x, y, Rx, Ry, start angle (to horizon), length (covered degrees))
        Arc arc = new Arc(300, 300, 200, 300, 0, 190);
        //arc.setType(ArcType.ROUND);
        arc.setType(ArcType.OPEN);
        arc.setStroke(Paint.valueOf("#000000"));
        // arc.setType(ArcType.OPEN);
        arc.setFill(Paint.valueOf("#FFFFFF"));
        root.getChildren().add(arc);

        //Drawing an arc
        Arc arcNew = new Arc();
        arcNew.setType(ArcType.OPEN);
        arcNew.setCenterX(300.0f);
        arcNew.setCenterY(150.0f);
        arcNew.setRadiusX(90.0f);
        arcNew.setRadiusY(90.0f);
        arcNew.setStartAngle(40.0f);
        arcNew.setLength(239.0f);
        root.getChildren().add(arcNew);

        primaryStage.setTitle("Christmas Tree 9000");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
