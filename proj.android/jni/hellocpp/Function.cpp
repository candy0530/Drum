/*
 * Function.cpp
 *
 *  Created on: 2015/3/18
 *      Author: Wei Shang Chieh
 */

#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "Function.h"
#include "JniEv.h"

#define CLASS_NAME "org/cocos2dx/cpp/JniHelper"

using namespace cocos2d;

extern "C"
{
    void showDialog(const char *title, const char *msg)
    {
        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V"))
        {
            jstring jTitle = t.env->NewStringUTF(title);
            jstring jMsg = t.env->NewStringUTF(msg);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle, jMsg);
            t.env->DeleteLocalRef(jTitle);
            t.env->DeleteLocalRef(jMsg);
        }
    }

    void Java_org_cocos2dx_cpp_JniHelper_setPackageName(JNIEnv *env, jobject thiz, jstring packageName)
    {
        const char *pkgName = env->GetStringUTFChars(packageName, NULL);
        setPackageName(pkgName);
        env->ReleaseStringUTFChars(packageName, pkgName);
    }

    void Java_org_cocos2dx_cpp_JniHelper_exit(JNIEnv *env, jobject thiz)
    {
        exit();
    }

    void openBT(){
        log("open bt 2");

        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openBT", "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    void sent_data(const char *data){
        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sent_data", "(Ljava/lang/String;)V"))
        {
            jstring jdata = t.env->NewStringUTF(data);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jdata);
            t.env->DeleteLocalRef(jdata);
        }
    }

    jboolean get_bluetooth_status(){
        JniMethodInfo info;
        if(JniHelper::getStaticMethodInfo(info,CLASS_NAME,"get_bluetooth_status","()Z"))  
        {  
            log("Call function succeed");  
            return info.env->CallStaticBooleanMethod(info.classID, info.methodID);  
        }
    }

    jstring receive_data() {
        JniMethodInfo info;
        if(JniHelper::getStaticMethodInfo(info,CLASS_NAME,"receive_data","()Ljava/lang/String;"))  
        {  
            log("Call function succeed");  
            return (jstring)info.env->CallStaticObjectMethod(info.classID, info.methodID);  
        }
    }
}
