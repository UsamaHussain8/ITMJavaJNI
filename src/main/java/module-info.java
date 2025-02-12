module com.itm.callitm {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.itm.callitm to javafx.fxml;
    exports com.itm.callitm;
}