/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;


public class AppActivity extends Cocos2dxActivity {

    /**
     * Cocos JNI
     */
    
    public static final int SHOW_DIALOG = 0x0001;
    public static final int OPEN_BT = 0x0002;
    public static final int SEND_DATA = 0x0003;
    
    /**
     * Bluetooth 
     */
    
    static final String SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";
    static final UUID uuid = UUID.fromString(SPP_UUID);
    private BluetoothSocket btSocket;
    private BluetoothAdapter btAdapt;
    InputStream btIn = null;
    OutputStream btOut;
    SppServer sppServer;
    boolean sppConnected = false;
    private BluetoothServerSocket btServerSocket;
    private String device_address = "2C:F7:F1:81:05:4A";
    private String msg="";

    /**
     * 
     * Cocos
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        
        JniHelper.init(mHandler);
        JniHelper.setPackageName(this.getPackageName());
        
        btAdapt = BluetoothAdapter.getDefaultAdapter();
        
    }
    
    public Cocos2dxGLSurfaceView onCreateView(){
        
        Cocos2dxGLSurfaceView glsv = new Cocos2dxGLSurfaceView(AppActivity.this);
        glsv.setEGLConfigChooser(5,6,5,0,16,8);
        
        return glsv;
    }
    
    static {
        System.loadLibrary("cocos2dcpp");
    }
    
    private Handler mHandler = new Handler()  
    {  
        @Override  
        public void handleMessage(Message msg) {  
            switch(msg.what)  
            {  
                case SHOW_DIALOG:
                    new AlertDialog.Builder(AppActivity.this).setTitle(Var.title).setMessage(Var.txt).setNegativeButton("cancel", new DialogInterface.OnClickListener() {  
                          
                        @Override  
                        public void onClick(DialogInterface dialog, int which) {  
                            dialog.dismiss();  
                        }  
                    }).setPositiveButton("Ok",
                            new DialogInterface.OnClickListener() {  
      
                        @Override  
                        public void onClick(DialogInterface dialog, int which) {  
                            dialog.dismiss();
                            JniHelper.exit();
                        }  
                    }).create().show();
                    break;
                    
                case OPEN_BT:
                    
                    if (!btAdapt.isEnabled()) {
                        btAdapt.enable();
                        Connect_BT();
                    }else{
                        Connect_BT();
                    }
                    break;

                case SEND_DATA:
                    sent_data(Var.data);
                    break;
            }

        }
    };

    /**
     * Bluetooth connect
     */
    // Connect Bluetooth 
    public void Connect_BT(){
        if(sppConnected || device_address == null){
            Toast.makeText(AppActivity.this,"Bluetooth already Connected or Nor found.",Toast.LENGTH_SHORT).show();
            return;
        }
        try{
            btSocket = btAdapt.getRemoteDevice(device_address).createRfcommSocketToServiceRecord(uuid);
            btSocket.connect();
            
            Log.d("JAVA","BT connect");
            
            synchronized (AppActivity.this){
                if(sppConnected)return;
                // btServerSocket.close();
                btIn = btSocket.getInputStream();
                btOut = btSocket.getOutputStream();
                connected();
            }

        }catch(IOException e){
            e.printStackTrace();
            sppConnected = false;
            try{
                btSocket.close();
            }catch (IOException e1){
                e1.printStackTrace();
            }
            btSocket = null;

        }
    }
    //SppServer
    private class SppServer extends Thread{
        public SppServer(){
            try{
                btServerSocket = btAdapt.listenUsingInsecureRfcommWithServiceRecord("SPP", uuid);
            } catch(IOException e){
                e.printStackTrace();
                btServerSocket=null;
            }
        }
        public void run(){
            BluetoothSocket bs=null;
            if(btServerSocket==null){
                Log.e("JAVA", "ServerSocket null");
                return;
            }
            try{
                bs = btServerSocket.accept();
                synchronized(AppActivity.class){
                    if(sppConnected)return;
                    btServerSocket.close();
                    btIn = btSocket.getInputStream();
                    btOut = btSocket.getOutputStream();
                    connected();
                }
            }catch(IOException e){
                e.printStackTrace();
                Log.d("JAVA","ServerSocket accept failed");
            }
            Log.i("JAVA", "End Bluetooth SPP Server");
        }
        public void cancel(){
            if(btServerSocket==null){
                return;
            }
            try{
                btServerSocket.close();
            }catch(IOException e){
                e.printStackTrace();
                Log.e("JAVA", "close serversocket failed");
            }
        }
    }
    //Connected
    private void connected(){
        sppConnected = true;
        new SppReceiver(btIn).start();
        sppServer =null;
        Toast.makeText(AppActivity.this,"Bluetooth Connected",Toast.LENGTH_SHORT).show();
        Log.e("JAVA", "connected");
    }
    //Disconnect
    private void disconnect(){
        sppConnected = false;
        btIn = null;
        btOut = null;
        sppServer = new SppServer();
        sppServer.start();
        Log.e("JAVA", "disconnect");
    }
    //Data receiver
    private class SppReceiver extends Thread{
        private InputStream input =null;
        public SppReceiver(InputStream in){
            input = in;
        }
        public void run(){
            byte[] data =new byte[1024];
            int length=0;
            if(input==null){
                return;
            }
            while(true){
                try{
                    length = input.read(data);
                    if(length>0){
                        Var.receivemsg = new String(data);
                        Log.d("JAVA","Receiver_Msg:"+length);
                        Var.receivemsg = Var.receivemsg.substring(0,1);
                        Log.d("JAVA","Receiver_Msg:"+Var.receivemsg);
                    }
                }catch(IOException e){
                    Log.e("JAVA", "SppR_disconnected");
                    disconnect();
                }
            }
        }
    }

    public String receive_data(){
        return Var.receivemsg;
    }

    public boolean get_bluetooth_status(){
        return sppConnected;
    }
    /**
     * 
     * Sent Data to BT
     * 
     * Not used
     * 
     * @param data
     */
    public void sent_data(String data){
        
        try {
            btOut.write(data.toString().getBytes());
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
    }
    
    
    
}
