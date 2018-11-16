package com.maxdev;

import javafx.animation.*;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.stage.Stage;
import javafx.util.Duration;

public class SnowMan extends Application {

    private static double X (double originalX){
        return originalX + 300;
    }
    private static double Y (double originalY){
        return originalY + 250;
    }

    public static void main(String args[]) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        Scene scene = new Scene(root, 1200, 600);

        // Bottom part
        Arc bottomPart = new Arc(X(40), Y(80), 50, 50, 150, 280);
        bottomPart.setStrokeWidth(4);
        bottomPart.setStroke(Color.BLACK);
        bottomPart.setFill(Color.WHITE);
        root.getChildren().add(bottomPart);

        // Middle part1
        MoveTo moveTo1 = new MoveTo(X(50), Y(45));
        QuadCurveTo curve1 = new QuadCurveTo(X(75), Y(35), X(62), Y(-10));
        Path middle_right_side = new Path();
        middle_right_side.setStrokeWidth(4);
        middle_right_side.setStroke(Color.BLACK);
        middle_right_side.setFill(Color.WHITE);
        middle_right_side.getElements().addAll(moveTo1, curve1);
        root.getChildren().add(middle_right_side);

        // Middle part2
        MoveTo moveTo2 = new MoveTo(X(-3), Y(55));
        QuadCurveTo curve2 = new QuadCurveTo(X(-30), Y(18), X(0), Y(-10));
        Path middle_left_side = new Path();
        middle_left_side.setStrokeWidth(4);
        middle_left_side.setStroke(Color.BLACK);
        middle_left_side.setFill(Color.WHITE);
        middle_left_side.getElements().addAll(moveTo2, curve2);
        root.getChildren().add(middle_left_side);

        // Top part
        Arc topPart = new Arc(X(32), Y(-35), 40, 36, -38, 295);
        topPart.setStrokeWidth(4);
        topPart.setStroke(Color.BLACK);
        topPart.setFill(Color.WHITE);
        root.getChildren().add(topPart);

        // Jacket
        Ellipse j1 = new Ellipse(X(45), Y(16), 2, 2);
        j1.setStroke(Color.BROWN);
        j1.setStrokeWidth(4);
        root.getChildren().add(j1);
        Ellipse j2 = new Ellipse(X(50), Y(28), 2, 2);
        j2.setStroke(Color.BROWN);
        j2.setStrokeWidth(4);
        root.getChildren().add(j2);
        Ellipse j3 = new Ellipse(X(43), Y(40), 2, 2);
        j3.setStroke(Color.BROWN);
        j3.setStrokeWidth(4);
        root.getChildren().add(j3);

        // Left hand
        MoveTo mt1 = new MoveTo(X(-3), Y(20));
        QuadCurveTo qc1 = new QuadCurveTo(X(10), Y(20), X(8), Y(13));
        QuadCurveTo qc2 = new QuadCurveTo(X(-40), Y(-15), X(-35), Y(-10));
        QuadCurveTo qc3 = new QuadCurveTo(X(-15), Y(-35), X(-45), Y(-15));
        QuadCurveTo qc4 = new QuadCurveTo(X(-65), Y(-45), X(-55), Y(-12));
        QuadCurveTo qc5 = new QuadCurveTo(X(-85), Y(-25), X(-57), Y(-2));
        QuadCurveTo qc6 = new QuadCurveTo(X(-85), Y(15), X(-45), Y(2));
        QuadCurveTo qc7 = new QuadCurveTo(X(-20), Y(11), X(-3), Y(20));
        Path left_hand = new Path();
        left_hand.setStrokeWidth(4);
        left_hand.setStroke(Color.BLACK);
        left_hand.setFill(Color.BROWN);
        left_hand.getElements().addAll(mt1, qc1, qc2, qc3, qc4, qc5, qc6, qc7);
        root.getChildren().add(left_hand);

        // Right hand
        MoveTo mt2 = new MoveTo(X(68), Y(18));
        QuadCurveTo qc8 = new QuadCurveTo(X(85), Y(12), X(100), Y(8));
        QuadCurveTo qc9 = new QuadCurveTo(X(135), Y(32), X(110), Y(0));
        QuadCurveTo qc10 = new QuadCurveTo(X(150), Y(-20), X(104), Y(-11));
        QuadCurveTo qc11 = new QuadCurveTo(X(135), Y(-35), X(95), Y(-15));
        QuadCurveTo qc12 = new QuadCurveTo(X(85), Y(-50), X(90), Y(-5));
        QuadCurveTo qc13 = new QuadCurveTo(X(75), Y(0), X(68), Y(3));
        Path right_hand = new Path();
        right_hand.setStrokeWidth(4);
        right_hand.setStroke(Color.BLACK);
        right_hand.setFill(Color.BROWN);
        right_hand.getElements().addAll(mt2, qc8, qc9, qc10, qc11, qc12, qc13);
        root.getChildren().add(right_hand);

        // Nose
        MoveTo mt3 = new MoveTo(X(50), Y(-25));
        QuadCurveTo qcn1 = new QuadCurveTo(X(35), Y(-32), X(40), Y(-35));
        QuadCurveTo qcn2 = new QuadCurveTo(X(140), Y(-60), X(50), Y(-25));
        Path nose = new Path();
        nose.setStrokeWidth(2);
        nose.setStroke(Color.BLACK);
        nose.setFill(Color.ORANGE);
        nose.getElements().addAll(mt3, qcn1, qcn2);
        root.getChildren().add(nose);

        // Left eye
        Ellipse leTop = new Ellipse(X(33), Y(-42), 5, 6);
        leTop.setStroke(Color.BLACK);
        leTop.setStrokeWidth(2);
        leTop.setFill(Color.WHITE);
        root.getChildren().add(leTop);
        Ellipse leBot = new Ellipse(X(35), Y(-45), 2, 2);
        leBot.setStroke(Color.BLACK);
        leBot.setStrokeWidth(2);
        leBot.setFill(Color.BLACK);
        root.getChildren().add(leBot);

        // Right eye
        Ellipse reTop = new Ellipse(X(43), Y(-43), 4, 5);
        reTop.setStroke(Color.BLACK);
        reTop.setStrokeWidth(2);
        reTop.setFill(Color.WHITE);
        root.getChildren().add(reTop);
        Ellipse reBot = new Ellipse(X(44), Y(-45), 1.5, 1.5);
        reBot.setStroke(Color.BLACK);
        reBot.setStrokeWidth(2);
        reBot.setFill(Color.BLACK);
        root.getChildren().add(reBot);

        // Mouth
        MoveTo mt4 = new MoveTo(X(18), Y(-30));
        QuadCurveTo mqc = new QuadCurveTo(X(25), Y(-14), X(45), Y(-15));
        Path mouth = new Path();
        mouth.setStrokeWidth(1);
        mouth.setStroke(Color.BLACK);
        mouth.setFill(Color.WHITE);
        mouth.getElements().addAll(mt4, mqc);
        root.getChildren().add(mouth);

        // Small thing on the left of mouth
        MoveTo mt5 = new MoveTo(X(13), Y(-30));
        QuadCurveTo smqc = new QuadCurveTo(X(15), Y(-27), X(19), Y(-27));
        Path smallThing = new Path();
        smallThing.setStrokeWidth(1);
        smallThing.setStroke(Color.BLACK);
        smallThing.setFill(Color.WHITE);
        smallThing.getElements().addAll(mt5, smqc);
        root.getChildren().add(smallThing);

        // Tongue
        Arc mouthArc = new Arc(X(26), Y(-19), 10, 5, 115, 210);
        mouthArc.setStrokeWidth(1);
        mouthArc.setStroke(Color.BLACK);
        mouthArc.setFill(Color.RED);
        root.getChildren().add(mouthArc);

        // Animation
        int cycleCount = 2;
        int time = 2000;

        ScaleTransition scaleTransition = new ScaleTransition(Duration.millis(time), root);
        scaleTransition.setToX(2);
        scaleTransition.setToY(2);
        scaleTransition.setAutoReverse(true);

        RotateTransition rotateTransition = new RotateTransition(Duration.millis(time), root);
        rotateTransition.setByAngle(360f);
        rotateTransition.setCycleCount(cycleCount);
        rotateTransition.setAutoReverse(true);

        TranslateTransition translateTransition = new TranslateTransition(Duration.millis(time), root);
        translateTransition.setFromX(150);
        translateTransition.setToX(50);
        translateTransition.setCycleCount(cycleCount+1);
        translateTransition.setAutoReverse(true);

        TranslateTransition translateTransition2 = new TranslateTransition(Duration.millis(time), root);
        translateTransition2.setFromX(50);
        translateTransition2.setToX(150);
        translateTransition2.setCycleCount(cycleCount+1);
        translateTransition2.setAutoReverse(true);

        ScaleTransition scaleTransition2 = new ScaleTransition(Duration.millis(time), root);
        scaleTransition2.setToX(0.1);
        scaleTransition2.setToY(0.1);
        scaleTransition2.setCycleCount(cycleCount);
        scaleTransition2.setAutoReverse(true);

        ParallelTransition parallelTransition = new ParallelTransition();
        parallelTransition.getChildren().addAll(
                rotateTransition,
                scaleTransition,
                scaleTransition2,
                translateTransition
        );
        parallelTransition.setCycleCount(Timeline.INDEFINITE);
        parallelTransition.play();
        // End of animation

        primaryStage.setResizable(false);
        primaryStage.setTitle("Lab 3");
        primaryStage.setScene(scene);
        primaryStage.show();

    }

}
