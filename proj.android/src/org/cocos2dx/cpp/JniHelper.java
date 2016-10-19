package org.cocos2dx.cpp;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class JniHelper {
    
    private static Handler handler;
    
    public static void init(Handler handler){
        JniHelper.handler = handler;
    }
    
    public static native void setPackageName(String packagename);
    
    public static native void exit();

    public static void showDialog(String title , String txt){
        Message msg = handler.obtainMessage();
        msg.what = AppActivity.SHOW_DIALOG;
        Var.title = title;
        Var.txt = txt;
        msg.sendToTarget();
    }

    public static void openBT(){
        Log.d("JAVA","open bt");
        
        Message msg = handler.obtainMessage();
        msg.what = AppActivity.OPEN_BT;
        msg.sendToTarget();
    }

    public static void sent_data(String data){
        Log.d("JAVA","send data to bt");
        
        Message msg = handler.obtainMessage();
        msg.what = AppActivity.SEND_DATA;
        Var.data = data;
        msg.sendToTarget();
    }
    public static String receive_data(){
        return Var.receivemsg;
    }

    public static boolean get_bluetooth_status(){
        return Var.bluetooth_status;
    }
}
