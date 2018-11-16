package com.maxdev;

import javafx.animation.*;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.stage.Stage;
import javafx.util.Duration;

public class Apple extends Application {

    public static double X (double originalX){
        return originalX + 300;
    }
    public static double Y (double originalY){
        return originalY + 250;
    }

    public static void main(String args[]) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        Scene scene = new Scene(root, 1200, 600);

        //Support Arc
        Arc support1 = new Arc(X(79), Y(61), 11, 11, 150, 220);
        support1.setStroke(Color.BLACK);
        support1.setStrokeWidth(2);
        support1.setFill(Color.WHITE);
        root.getChildren().add(support1);

        //Support Rectangles
        Rectangle support2 = new Rectangle(X(52), Y(70), 55, 5);
        support2.setStroke(Color.BLACK);
        support2.setStrokeWidth(2);
        support2.setFill(Color.WHITE);
        root.getChildren().add(support2);
        Rectangle support3 = new Rectangle(X(36), Y(73), 83, 19);
        support3.setStroke(Color.BLACK);
        support3.setStrokeWidth(2);
        support3.setFill(Color.LIGHTBLUE);
        root.getChildren().add(support3);

        //Buttons
        Rectangle button1 = new Rectangle(X(93), Y(80), 10, 3);
        button1.setStroke(Color.BLACK);
        button1.setStrokeWidth(1);
        button1.setFill(Color.WHITE);
        root.getChildren().add(button1);
        Rectangle button2 = new Rectangle(X(106), Y(80), 10, 3);
        button2.setStroke(Color.BLACK);
        button2.setStrokeWidth(1);
        button2.setFill(Color.WHITE);
        root.getChildren().add(button2);

        // White Border of a Laptop
        Path whiteBorder = new Path();
        whiteBorder.setStrokeWidth(2);
        MoveTo moveTo_11 = new MoveTo(X(40), Y(10));
        QuadCurveTo curve_11 = new QuadCurveTo(X(71), Y(4), X(104), Y(2));
        QuadCurveTo curve_12 = new QuadCurveTo(X(106), Y(28), X(112), Y(59));
        QuadCurveTo curve_13 = new QuadCurveTo(X(79), Y(62), X(46), Y(67));
        QuadCurveTo curve_14 = new QuadCurveTo(X(45), Y(38), X(40), Y(10));
        whiteBorder.getElements().addAll(moveTo_11, curve_11, curve_12, curve_13, curve_14);
        whiteBorder.setFill(Color.WHITE);
        root.getChildren().add(whiteBorder);

        // Blue Screen
        Path bluescreen = new Path();
        bluescreen.setStrokeWidth(2);
        MoveTo moveTo_21 = new MoveTo(X(49), Y(16));
        QuadCurveTo curve_21 = new QuadCurveTo(X(72), Y(10), X(97), Y(9));
        QuadCurveTo curve_22 = new QuadCurveTo(X(101), Y(29), X(102), Y(51));
        QuadCurveTo curve_23 = new QuadCurveTo(X(79), Y(57), X(55), Y(58));
        QuadCurveTo curve_24 = new QuadCurveTo(X(49), Y(34), X(49), Y(16));
        bluescreen.getElements().addAll(moveTo_21, curve_21, curve_22, curve_23, curve_24);
        bluescreen.setFill(Color.LIGHTBLUE);
        root.getChildren().add(bluescreen);

        //Eyes
        Ellipse eye1 = new Ellipse(X(66), Y(27), 2, 5);
        eye1.setStroke(Color.BLACK);
        eye1.setStrokeWidth(1);
        eye1.setFill(Color.WHITE);
        root.getChildren().add(eye1);
        Ellipse eye2 = new Ellipse(X(83), Y(25), 2, 5);
        eye2.setStroke(Color.BLACK);
        eye2.setStrokeWidth(1);
        eye2.setFill(Color.WHITE);
        root.getChildren().add(eye2);
        Ellipse eyeApple1 = new Ellipse(X(66), Y(27), 1, 1);
        eyeApple1.setFill(Color.BLACK);
        root.getChildren().add(eyeApple1);
        Ellipse eyeApple2 = new Ellipse(X(83), Y(25), 1, 1);
        eyeApple2.setFill(Color.BLACK);
        root.getChildren().add(eyeApple2);

        //Mouth
        Path smile = new Path();
        MoveTo moveTo_31 = new MoveTo(X(57), Y(35));
        smile.setStrokeWidth(1);
        QuadCurveTo curve_31 = new QuadCurveTo(X(66), Y(44), X(80), Y(41));
        QuadCurveTo curve_32 = new QuadCurveTo(X(77), Y(48), X(71), Y(41.8));
        smile.getElements().addAll(moveTo_31, curve_31, curve_32);
        smile.setFill(Color.WHITE);
        root.getChildren().add(smile);
        Path mouth = new Path();
        MoveTo moveTo_32 = new MoveTo(X(80), Y(41));
        QuadCurveTo curve_33 = new QuadCurveTo(X(88), Y(37), X(93), Y(31));
        mouth.setStrokeWidth(1);
        mouth.getElements().addAll(moveTo_32, curve_33);
        root.getChildren().add(mouth);

        //Arms
        Line arm1 = new Line(X(45.5), Y(50), X(28), Y(60));
        arm1.setStroke(Color.BLACK);
        arm1.setStrokeLineCap(StrokeLineCap.ROUND);
        arm1.setStrokeWidth(3);
        root.getChildren().add(arm1);
        Line arm2 = new Line(X(108.5), Y(43), X(131), Y(49));
        arm2.setStroke(Color.BLACK);
        arm2.setStrokeLineCap(StrokeLineCap.ROUND);
        arm2.setStrokeWidth(3);
        root.getChildren().add(arm2);


//        int cycleCount = 2; //animation
//        int time = 3000;
//
//        ScaleTransition scaleTransition = new ScaleTransition(Duration.millis(time), root);
//        scaleTransition.setToX(2);
//        scaleTransition.setToY(2);
//        scaleTransition.setAutoReverse(true);
//
//        RotateTransition rotateTransition = new RotateTransition(Duration.millis(time), root);
//        rotateTransition.setByAngle(360f);
//        rotateTransition.setCycleCount(cycleCount);
//        rotateTransition.setAutoReverse(true);
//
//
//        TranslateTransition translateTransition = new TranslateTransition(Duration.millis(time), root);
//        translateTransition.setFromX(150);
//        translateTransition.setToX(50);
//        translateTransition.setCycleCount(cycleCount+1);
//        translateTransition.setAutoReverse(true);
//
//
//        ScaleTransition scaleTransition2 = new ScaleTransition(Duration.millis(time), root);
//        scaleTransition2.setToX(0.1);
//        scaleTransition2.setToY(0.1);
//        scaleTransition2.setCycleCount(cycleCount);
//        scaleTransition2.setAutoReverse(true);
//
//        ParallelTransition parallelTransition = new ParallelTransition();
//        parallelTransition.getChildren().addAll(
//
//                rotateTransition,
//                scaleTransition,
//                scaleTransition2,
//                translateTransition
//        );
//
//        parallelTransition.setCycleCount(Timeline.INDEFINITE);
//        parallelTransition.play();

        primaryStage.setResizable(false);
        primaryStage.setTitle("Apple");
        primaryStage.setScene(scene);
        primaryStage.show();

    }

}
