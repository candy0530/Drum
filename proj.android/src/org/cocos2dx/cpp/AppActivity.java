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

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;




public class AppActivity extends Cocos2dxActivity {
	private Cocos2dxGLSurfaceView glSurfaceView;
	
	public static final int SHOW_DIALOG = 0x0001;
	public static final int OPEN_BT = 0x0002;
	public static final int SENT_DATA = 0x0003;
	private BluetoothAdapter btAdapt;

    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState); 
        
        JniHelper.init(mHandler);
		JniHelper.setPackageName(this.getPackageName());
		
		btAdapt = BluetoothAdapter.getDefaultAdapter();
    }

    public Cocos2dxGLSurfaceView onCreateView()
    {
        glSurfaceView = new Cocos2dxGLSurfaceView(this);

        this.hideSystemUI();

        // create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }

    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus)
        {
            this.hideSystemUI();
        }
    }

    private void hideSystemUI()
    {
        // Set the IMMERSIVE flag.
        // Set the content to appear under the system bars so that the content
        // doesn't resize when the system bars hide and show.
        glSurfaceView.setSystemUiVisibility(
                Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_STABLE 
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_FULLSCREEN
                | Cocos2dxGLSurfaceView.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        
    }

    static
    {
        System.loadLibrary("cocos2dcpp");
    }
    
    private Handler mHandler = new Handler()  
    {  
        @Override  
        public void handleMessage(Message msg) {  
            switch(msg.what)  
            {  
            case SHOW_DIALOG:   
//                new AlertDialog.Builder(AppActivity.this)  
//                .setTitle(Var.title)  
//                .setMessage(Var.txt).setNegativeButton("cancle", new DialogInterface.OnClickListener() {  
//                      
//                    @Override  
//                    public void onClick(DialogInterface dialog, int which) {  
//                        dialog.dismiss();  
//                    }  
//                })  
//                .setPositiveButton("Ok",   
//                        new DialogInterface.OnClickListener() {  
//  
//                    @Override  
//                    public void onClick(DialogInterface dialog, int which) {  
//                        dialog.dismiss();  
//                        JniHelper.exit();  
//                    }  
//                })  
//                .create().show();  
                break;
                
            case OPEN_BT:
            	
            	if (!btAdapt.isEnabled()) {			
            		btAdapt.enable();
//            		Connect_BT();
            		Toast.makeText(AppActivity.this,"無法連線裝置",Toast.LENGTH_SHORT).show();
        		}else{
        			Toast.makeText(AppActivity.this,"無法連線裝置",Toast.LENGTH_SHORT).show();
//        			Connect_BT();
        		}
            	break;
            	
            case SENT_DATA:
//            	Sent_Data("1111");
//            	Log.d("JAVA","SHOW:::"+Var.data);
            	break;
            }  
        }  
    };
	
}
