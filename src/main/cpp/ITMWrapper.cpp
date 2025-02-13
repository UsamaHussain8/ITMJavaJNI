//#include <jni.h>
#include "com_itm_callitm_ITMWrapper.h"
#include "itm.h" // Make sure this file exists

JNIEXPORT jint JNICALL Java_com_itm_callitm_ITMWrapper_ITM_1P2P_1TLS_1Ex(
    JNIEnv *env, jobject obj, jdouble h_tx, jdouble h_rx, jdoubleArray pfl,
    jint climate, jdouble N_0, jdouble f_mhz, jint pol, jdouble epsilon,
    jdouble sigma, jint mdvar, jdouble time, jdouble location, jdouble situation,
    jdoubleArray A_db, jlongArray warnings, jobject interValuesObj) {

    // Convert Java double array to C array
    jsize pfl_length = env->GetArrayLength(pfl);
    double *pfl_c = env->GetDoubleArrayElements(pfl, NULL);

    // For outputs, we assume one result value (modify if needed)
    double *A_db_c = env->GetDoubleArrayElements(A_db, NULL);
    long *warnings_c = env->GetLongArrayElements(warnings, NULL);

    // Prepare IntermediateValues struct
    IntermediateValues interValues_c;

    // Retrieve Java class of IntermediateValues
    jclass interValuesClass = env->GetObjectClass(interValuesObj);
    jfieldID fid_A_fs_db = env->GetFieldID(interValuesClass, "A_fs_db", "D");

    // Call the native ITM function once with the full profile array
    int result = ITM_P2P_TLS_Ex(h_tx, h_rx, pfl_c, climate, N_0, f_mhz, pol,
                                epsilon, sigma, mdvar, time, location, situation,
                                &A_db_c[0], &warnings_c[0], &interValues_c);

    // Copy back the results to Java arrays
    env->ReleaseDoubleArrayElements(A_db, A_db_c, 0);
    env->ReleaseLongArrayElements(warnings, warnings_c, 0);
    env->ReleaseDoubleArrayElements(pfl, pfl_c, 0);

    // Update the Java IntermediateValues object with updated A_fs_db value
    env->SetDoubleField(interValuesObj, fid_A_fs_db, interValues_c.A_fs__db);

    return result;
}


//JNIEXPORT jint JNICALL Java_com_itm_callitm_ITMWrapper_ITM_1P2P_1TLS_1Ex(
//    JNIEnv *env, jobject obj, jdouble h_tx, jdouble h_rx, jdoubleArray pfl,
//    jint climate, jdouble N_0, jdouble f_mhz, jint pol, jdouble epsilon,
//    jdouble sigma, jint mdvar, jdouble time, jdouble location, jdouble situation,
//    jdoubleArray A_db, jlongArray warnings, jobject interValuesObj) {
//
//    // Convert Java double array to C array
//    jsize pfl_length = env->GetArrayLength(pfl);
//    double *pfl_c = env->GetDoubleArrayElements(pfl, NULL);
//
//    // Convert Java arrays to C++ arrays for storing results
//    double *A_db_c = env->GetDoubleArrayElements(A_db, NULL);
//    long *warnings_c = env->GetLongArrayElements(warnings, NULL);
//
//    // Prepare IntermediateValues struct
//    IntermediateValues interValues_c;
//
//    // Retrieve Java class of IntermediateValues
//    jclass interValuesClass = env->GetObjectClass(interValuesObj);
//    jfieldID fid_A_fs_db = env->GetFieldID(interValuesClass, "A_fs_db", "D");
//
//    // Loop through all PFL points
//    for (int i = 0; i < pfl_length; i++) {
//        double A_db_result;
//        long warnings_result;
//
//        // Call the ITM function for each point
//        int result = ITM_P2P_TLS_Ex(h_tx, h_rx, &pfl_c[i], climate, N_0, f_mhz, pol,
//                                    epsilon, sigma, mdvar, time, location, situation,
//                                    &A_db_result, &warnings_result, &interValues_c);
//
//        // Store results in C++ arrays
//        A_db_c[i] = A_db_result;
//        warnings_c[i] = warnings_result;
//    }
//
//    // Copy back the results to Java arrays
//    env->ReleaseDoubleArrayElements(A_db, A_db_c, 0);
//    env->ReleaseLongArrayElements(warnings, warnings_c, 0);
//    env->ReleaseDoubleArrayElements(pfl, pfl_c, 0);
//
//    return 0; // Return success
//}



//JNIEXPORT jint JNICALL Java_com_itm_callitm_ITMWrapper_ITM_1P2P_1TLS_1Ex(
//    JNIEnv *env, jobject obj, jdouble h_tx, jdouble h_rx, jdoubleArray pfl,
//    jint climate, jdouble N_0, jdouble f_mhz, jint pol, jdouble epsilon,
//    jdouble sigma, jint mdvar, jdouble time, jdouble location, jdouble situation,
//    jdoubleArray A_db, jlongArray warnings, jobject interValuesObj) {
//
//    // Convert Java double array to C array
//    jsize pfl_length = env->GetArrayLength(pfl);
//    double *pfl_c = env->GetDoubleArrayElements(pfl, NULL);
//
//    // Prepare output variables
//    double A_db_result;
//    long warnings_result;
//    IntermediateValues interValues_c;  // ✅ We create a local C++ struct
//
//    // Retrieve Java class of IntermediateValues
//    jclass interValuesClass = env->GetObjectClass(interValuesObj);
//
//    // Extract the field "A_fs_db" from Java object and store in C++ struct
//    jfieldID fid_A_fs_db = env->GetFieldID(interValuesClass, "A_fs_db", "D");
//    interValues_c.A_fs__db = env->GetDoubleField(interValuesObj, fid_A_fs_db);
//
//    // Call the actual ITM function
//    int result = ITM_P2P_TLS_Ex(h_tx, h_rx, pfl_c, climate, N_0, f_mhz, pol,
//                                epsilon, sigma, mdvar, time, location, situation,
//                                &A_db_result, &warnings_result, &interValues_c);
//
//    // Store results in Java objects
//    env->SetDoubleArrayRegion(A_db, 0, 1, &A_db_result);
//    env->SetLongArrayRegion(warnings, 0, 1, &warnings_result);
//
//    // Update the Java IntermediateValues object with updated A_fs_db value
//    env->SetDoubleField(interValuesObj, fid_A_fs_db, interValues_c.A_fs__db);
//
//    // Release memory
//    env->ReleaseDoubleArrayElements(pfl, pfl_c, 0);
//
//    return result;
//}
