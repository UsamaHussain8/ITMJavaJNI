package com.itm.callitm;

public class ITMWrapper {
    public static class IntermediateValues {
        public double[] theta_hzn_rad = new double[2];
        public double[] d_hzn_meter = new double[2];
        public double[] h_e_meter = new double[2];
        public double N_s;
        public double delta_h_meter;
        public double A_ref_db;
        public double A_fs_db;
        public double d_km;
        public int Mode;
    }

//    static {
//        String libraryPath = System.getProperty("java.library.path"); // Get existing paths
//        String customPath = "/usr/local/lib/"; // Your library directory
//        System.setProperty("java.library.path", libraryPath + ":" + customPath); // Add yours
//        System.loadLibrary("ITMWrapper"); // Load after setting path
//    }

//    static {
//        String libPath = System.getProperty("java.library.path");
//        String myLibDir = "/usr/local/lib";
//
//        // Check if the path is already included (avoid duplicates)
//        if (!libPath.contains(myLibDir)) {
//            System.setProperty("java.library.path", libPath + ":" + myLibDir);
//        }
//
//        try {
//            System.loadLibrary("ITMWrapper");
//        } catch (UnsatisfiedLinkError e) {
//            System.err.println("Error loading library:");
//            //e.printStackTrace(); // Print the full error details
//            // Check ldd output and other dependencies
//        }
//    }

    static {
        try {
            System.load("/usr/local/lib/libITMWrapper.so");
            System.out.println("Library loaded successfully");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load libITMWrapper.so");
            e.printStackTrace();
        }
    }


    public native int ITM_P2P_TLS_Ex(
            double h_tx, double h_rx, double[] pfl, int climate,
            double N_0, double f_mhz, int pol, double epsilon,
            double sigma, int mdvar, double time, double location,
            double situation, double[] A_db, long[] warnings, IntermediateValues interValues
    );
}
