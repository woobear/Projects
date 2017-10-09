
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.util.Stack;


public class Gomoku extends Application {
    int turnCount = 0;
    Stack<Circle> stack = new Stack<Circle>();
    BorderPane border = new BorderPane();
    VBox vb = new VBox();
    Label goesFirst = new Label("P L A Y E R  1    G O E S    F I R S T ");
    Label pl1 = new Label("R E A D Y  P L A Y E R   1 ");
    Label pl2 = new Label("R E A D Y  P L A Y E R   2 ");
    IGotGame gamelog = new IGotGame();
    Stage dialogStage = new Stage();
    @Override
    public void start(Stage primaryStage) throws Exception {

        border.setPrefSize(600,600);

        MenuBar menu = makeMenu(border);
        HBox bbox = makeBox();
        border.setTop(menu);
        border.setBottom(bbox);
        GridPane grid = makeGrid();
        goesFirst.setWrapText(true);
        pl1.setWrapText(true);
        pl2.setWrapText(true);
        border.setCenter(grid);
        VBox vb = new VBox();
        vb.getChildren().add(goesFirst);
        vb.setPrefWidth(0);
        border.setLeft(vb);
        border.setOnMousePressed(new EventHandler<MouseEvent>() {
            public void handle (MouseEvent mouseEvent) {
                System.out.println("X: " + mouseEvent.getX() + " Y: " + mouseEvent.getY());
                if (turnCount % 2 == 0) {
                    Circle crcle1 = new Circle();
                    if (gamelog.insert(mouseEvent.getX(), mouseEvent.getY(), 1)) {
                        crcle1.setCenterX(getXvalue(mouseEvent.getX()));
                        crcle1.setCenterY(getYvalue(mouseEvent.getY()));
                        crcle1.setRadius(10);
                        border.getChildren().add(stack.push(crcle1));
                        turnCount++;
                        vb.getChildren().clear();
                        vb.getChildren().add(pl2);
                        vb.setPrefWidth(0);
                        border.setLeft(vb);
                        if (gamelog.winner(1)) {

                            System.out.println("player 1 wins");
                            VBox vbox = new VBox(new Text("PLAYER 1 WINS!"), quitButton(),restButton());
                            vbox.setAlignment(Pos.CENTER);
                            vbox.setPadding(new Insets(15));
                            dialogStage.setScene(new Scene(vbox));
                            dialogStage.show();
                            Stage dialogStage = new Stage();
                        }
                        if (gamelog.gameTie()){
                            VBox vbox = new VBox(new Text("TIE GAME!"), quitButton(),restButton());
                            vbox.setAlignment(Pos.CENTER);
                            vbox.setPadding(new Insets(15));
                            dialogStage.setScene(new Scene(vbox));
                            dialogStage.show();
                            Stage dialogStage = new Stage();
                        }
                    }
                    else return;

                }else {
                    Circle crcle2 = new Circle();
                    if(gamelog.insert(mouseEvent.getX(), mouseEvent.getY(), 2)){
                        crcle2.setFill(Color.WHITE);
                        crcle2.setCenterX(getXvalue(mouseEvent.getX()));
                        crcle2.setCenterY(getYvalue(mouseEvent.getY()));
                        crcle2.setRadius(10);
                        border.getChildren().add(stack.push(crcle2));
                        turnCount++;
                        vb.getChildren().clear();
                        vb.getChildren().add(pl1);
                        vb.setPrefWidth(0);
                        border.setLeft(vb);
                        if (gamelog.winner(2)) {
                            System.out.println("player 2 wins");
                            VBox vbox = new VBox(new Text("PLAYER 2 WINS!"), quitButton(),restButton());
                            vbox.setAlignment(Pos.CENTER);
                            vbox.setPadding(new Insets(15));
                            dialogStage.setScene(new Scene(vbox));
                            dialogStage.show();
                            Stage dialogStage = new Stage();

                        }
                        if (gamelog.gameTie()){
                            VBox vbox = new VBox(new Text("TIE GAME!"), quitButton(),restButton());
                            vbox.setAlignment(Pos.CENTER);
                            vbox.setPadding(new Insets(15));
                            dialogStage.setScene(new Scene(vbox));
                            dialogStage.show();
                            Stage dialogStage = new Stage();
                        }
                    }
                    else return;


                }
                System.out.println(turnCount);

                }


        });


        Scene scene = new Scene(border);
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();


    }




    public GridPane makeGrid() {
        GridPane grid = new GridPane();
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                Tile tile = new Tile();
                tile.setTranslateX((j * 30) + 46);//+ 58 without labels
                tile.setTranslateY((i * 30) + 25);
                grid.getChildren().add(tile);
            }
        }
        return grid;
    }

    public Button restButton() {
        Button restButton = new Button("Restart");
        restButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.out.println("RESTART!!!!");
                if (stack.empty()) {
                    return;
                }
                while(!stack.empty()) {
                    border.getChildren().remove(stack.pop());
                    gamelog.delete();
                }
                vb.getChildren().clear();
                vb.getChildren().add(goesFirst);
                goesFirst.setWrapText(true);
                vb.setPrefWidth(0);
                border.setLeft(vb);
                turnCount = 0;
                dialogStage.close();
            }
        });
        return restButton;
    }

    public Button quitButton() {
        Button quitButton = new Button("Quit");
        quitButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.exit(0);
            }
        });
        return quitButton;

    }

    public Button backButton(){
        Button backButton = new Button("Back");
        backButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.out.println("Stepping Back!");
                if (stack.empty()) {
                    return;
                }
                border.getChildren().remove(stack.pop());
                gamelog.delete();
                if (turnCount % 2 == 0) {
                    vb.getChildren().clear();
                    vb.getChildren().add(pl2);
                    pl2.setWrapText(true);
                    vb.setPrefWidth(0);
                    border.setLeft(vb);
                    turnCount--;

                }else {
                    vb.getChildren().clear();
                    vb.getChildren().add(pl1);
                    pl1.setWrapText(true);
                    vb.setPrefWidth(0);
                    border.setLeft(vb);
                    turnCount--;
                }
                dialogStage.close();



            }
        });
        return backButton;

    }


    public MenuBar makeMenu(BorderPane root) {
        Image image1 = new Image("fenShui.jpg");
        Image image2 = new Image("Adventure.jpg");
        Image image3 = new Image("ooh_wee.jpg");
        BackgroundSize bSize = new BackgroundSize(BackgroundSize.AUTO, BackgroundSize.AUTO, false, false, true, false);
        Background adventure = new Background(new BackgroundImage(image2,
                BackgroundRepeat.NO_REPEAT.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                bSize));
        Background fenshui = new Background(new BackgroundImage(image1,
                BackgroundRepeat.NO_REPEAT.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                bSize));


        Background ohh_wee = new Background(new BackgroundImage(image3,
                BackgroundRepeat.NO_REPEAT.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                bSize));

        root.setBackground(fenshui);

        MenuBar menu = new MenuBar();
        Menu menuFile = new Menu("File");
        MenuItem nextImage = new MenuItem("Next Image");

        nextImage.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                if( root.getBackground().equals(fenshui)){
                    root.setBackground(adventure);

                }
                else if( root.getBackground().equals(adventure)){
                    root.setBackground(ohh_wee);
                }
                else{
                    root.setBackground(fenshui);
                }
            }
        });

        MenuItem exit = new MenuItem("Quit");
        exit.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.exit(0);
            }
        });
        menuFile.getItems().addAll(nextImage, exit);
        menu.getMenus().add(menuFile);

        return menu;
    }

    public HBox makeBox() {




        HBox hBox = new HBox();
        hBox.setPadding(new Insets(12, 12, 15, 212.5));
        hBox.setSpacing(10);
        hBox.getChildren().addAll(restButton(),quitButton(),backButton());

        return hBox;

    }

    public double getXvalue(double xValue){
        double x = 0;
        if(xValue < (78)){
            x = 88;
            return x;
        }
        for(int i = 0; i < 15; i++){
            x = 88.0 + (i * 30);
            if(xValue >= (x-15) && xValue <= (x+15)){
                return x;
            }

        }

        return x;
    }

    public double getYvalue(double yValue){
        double y = 0;
        if(yValue < (75)){
            y = 85;
            return y;
        }
        for(int i = 0; i < 15; i++){
            y = 85.0 + (i * 30);
            if(yValue >= (y-15) && yValue <= (y+15)){
                return y;
            }


        }
        return y;
    }

    private class Tile extends StackPane {
        public Tile() {
            Rectangle border = new Rectangle(30, 30);
            border.setFill(null);
            border.setStroke(Color.BLACK);

            setAlignment(Pos.CENTER);
            getChildren().addAll(border);
        }
    }

    private class IGotGame {
        int grid[][] = new int[15][15];
        Stack<int[]> turns = new Stack<>();

        public Boolean insert (double x, double y, int player){ //player should be a 1 or 2
            int turn[] = new int[2];
            int[] indices = index(getXvalue(x), getYvalue(y));
            int realX = indices[0];
            int realY = indices[1];
            if(grid[realX][realY] != 0){
                return false;
            }
            turn[0] = realX;
            turn[1] = realY;
            grid[realX][realY] = player;
            turns.push(turn);
            System.out.println("x:" + turn[0] +   "y:" + turn[1]);
            return true;
        }
        public Boolean gameTie() {
            for (int i = 0; i < 15 ; i++) {
                for (int j = 0; j < 15; j++) {
                    if(grid[i][j] == 0) {
                        return false;
                    }

                }
            }
            return true;
        }

        public void delete (){ //this function will only delete the latest move
            int[] oldTurn = turns.pop();
            int x = oldTurn[0];
            int y = oldTurn[1];
            grid[x][y] = 0;
        }

        public Boolean winner (int player){
            // left and right
            for (int i = 0; i < 11 ; i++) {
                for (int j = 0; j < 15; j++) {
                    if (grid[i][j] == player &&
                            grid[i + 1][j] == player &&
                            grid[i + 2][j] == player &&
                            grid[i + 3][j] == player &&
                            grid[i + 4][j] == player) {

                        return true;

                    }
                }
            }
                    //up and down
            for (int i = 0; i < 15 ; i++) {
                for (int j = 0; j < 11; j++) {
                    if (grid[i][j] == player &&
                            grid[i][j + 1] == player &&
                            grid[i][j + 2] == player &&
                            grid[i][j + 3] == player &&
                            grid[i][j + 4] == player) {

                        return true;

                    }
                }
            }
                    // dag '\'
            for (int i = 0; i < 11 ; i++) {
                for (int j = 0; j < 11; j++) {
                    if (grid[i][j] == player &&
                            grid[i+1][j + 1] == player &&
                            grid[i+2][j + 2] == player &&
                            grid[i+3][j + 3] == player &&
                            grid[i+4][j + 4] == player) {

                        return true;

                    }
                }
            }
                    // dag '/'
            for (int i = 4; i < 15 ; i++) {
                for (int j = 0; j < 11; j++) {
                    if (grid[i][j] == player &&
                            grid[i-1][j + 1] == player &&
                            grid[i-2][j + 2] == player &&
                            grid[i-3][j + 3] == player &&
                            grid[i-4][j + 4] == player) {

                        return true;

                    }
                }
            }

            return false;
        }



        public int[] index(double x, double y){ //The arguments are gonna be getXvalue and getYvalue
            int[] indexArray = new int[2];
            for(int i = 0; i < 15; i++){
                if(x == 88 + (i * 30)){
                    indexArray[0] = i;
                }
            }
            for( int j = 0; j < 15; j++){
                if(y == 85 + (j * 30)){
                    indexArray[1] = j;
                }
            }
            return indexArray;
        }

    }

    public static void main(String[] args) {
        launch(args);
    }
}
