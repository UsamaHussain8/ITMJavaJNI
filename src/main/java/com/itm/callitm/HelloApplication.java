package com.itm.callitm;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();

        ITMWrapper itm = new ITMWrapper();
        ITMWrapper.IntermediateValues interValues = new ITMWrapper.IntermediateValues();

        double[] pfl = new double[100]; // Example: 100 profile points
        for (int i = 0; i < pfl.length; i++) {
            pfl[i] = 100.0 + i * 10; // Example altitude values
        }

        double[] A_db = new double[1];  // Only one result is returned
        long[] warnings = new long[1];

        int result = itm.ITM_P2P_TLS_Ex(10.0, 50.0, pfl, 5, 301.0, 200, 0,
                15.0, 0.005, 2, 50, 50, 50, A_db, warnings, interValues);

        System.out.println("Result: " + result);
        System.out.println("Attenuation: " + A_db[0]);
        System.out.println("Free Space Loss: " + interValues.A_fs_db);

//        ITMWrapper itm = new ITMWrapper();
//        ITMWrapper.IntermediateValues interValues = new ITMWrapper.IntermediateValues();
//
//        double[] pfl = new double[100]; // Example: 1000 terrain profile points
//        double[] A_db = new double[pfl.length];
//        long[] warnings = new long[pfl.length];
//        for (int i = 0; i < pfl.length; i++) {
//            pfl[i] = 1000.0 + i * 10; // Example altitude values
//            int result = itm.ITM_P2P_TLS_Ex(10.0, 50.0, pfl, 5, 301.0, 200, 0,
//                    15.0, 0.005, 2, 50, 50, 50, A_db, warnings, interValues);
//        }
//
//        // Print results
//        for (int i = 0; i < pfl.length; i++) {
//            System.out.println("Point " + i + ": A_db=" + A_db[i] + ", Warnings=" + warnings[i]);
//        }

    }

    public static void main(String[] args) {
        launch();
    }
}