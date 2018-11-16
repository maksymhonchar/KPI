package Lab1;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import javafx.scene.shape.*;
import javafx.scene.paint.Color;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("First Lab");
        Group mygroup = new Group();
        Scene scene = new Scene (mygroup, 290, 200);

        Rectangle wall = new Rectangle(20, 20, 260, 150);  //прямокутник
        mygroup.getChildren().add(wall);
        wall.setFill(Color.rgb(128, 0, 0)); //заповнення кольором

        Line line = new Line(22, 60, 278, 60);
        mygroup.getChildren().add(line);
        line.setStroke(Color.YELLOW);
        line.setStrokeWidth(5);

        Line middle_line = new Line(22, 117, 278, 117);
        mygroup.getChildren().add(middle_line);
        middle_line.setStroke(Color.YELLOW);
        middle_line.setStrokeWidth(5);

        Line middle_vert_one = new Line(151, 22, 151, 60);
        mygroup.getChildren().add(middle_vert_one);
        middle_vert_one.setStroke(Color.YELLOW);
        middle_vert_one.setStrokeWidth(5);

        Line middle_vert_two = new Line(151, 117, 151, 168);
        mygroup.getChildren().add(middle_vert_two);
        middle_vert_two.setStroke(Color.YELLOW);
        middle_vert_two.setStrokeWidth(5);

        Line vert_left = new Line(91, 60, 91, 117);
        mygroup.getChildren().add(vert_left);
        vert_left.setStroke(Color.YELLOW);
        vert_left.setStrokeWidth(5);

        Line vert_right = new Line(210, 60, 210, 117);
        mygroup.getChildren().add(vert_right);
        vert_right.setStroke(Color.YELLOW);
        vert_right.setStrokeWidth(5);

        scene.setFill(Color.rgb(128, 128, 0)); //заповнення сцени кольором

        primaryStage.setResizable(false);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

}