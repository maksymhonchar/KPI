package com.maxdev;

import javafx.scene.text.Text;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.scene.shape.QuadCurveTo;
import javafx.stage.Stage;

public class SimpleExample extends Application {
    public static void main(String[] args) {
        Application.launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Shapes");
        Group root = new Group();
        Scene scene = new Scene(root, 300, 300, Color.WHITE);

        Path path = new Path();

        QuadCurveTo quadCurveTo = new QuadCurveTo();
        quadCurveTo.setX(50);
        quadCurveTo.setY(50);
        quadCurveTo.setControlX(10);
        quadCurveTo.setControlY(50);

        LineTo lineTo1 = new LineTo();
        lineTo1.setX(150);
        lineTo1.setY(150);

        LineTo lineTo2 = new LineTo();
        lineTo2.setX(100);
        lineTo2.setY(200);

        LineTo lineTo3 = new LineTo();
        lineTo3.setX(350);
        lineTo3.setY(150);

        MoveTo moveTo = new MoveTo();
        moveTo.setX(50);
        moveTo.setY(150);

        Text text = new Text("1");
        text.setX(50);
        text.setY(150);

        Text text2 = new Text("2");
        text2.setX(10);
        text2.setY(50);

        path.getElements().add(moveTo);
        path.getElements().add(quadCurveTo);
        path.getElements().add(lineTo1);
        path.getElements().add(lineTo2);
        path.getElements().add(lineTo3);
        path.setTranslateY(30);
        path.setStrokeWidth(3);
        path.setStroke(Color.BLACK);

        root.getChildren().add(path);
        root.getChildren().add(text);
        root.getChildren().add(text2);

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
