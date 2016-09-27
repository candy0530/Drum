/*
 * JniEv.h
 *
 *  Created on: 2015/3/18
 *      Author: Wei Shang Chieh
 */

#ifndef JNIEV_H_
#define JNIEV_H_

#include "cocos2d.h"

using namespace cocos2d;

void setPackageName(const char *a){

    CCLog("packageName:%s",a);
}

void exit(){

    CCDirector::sharedDirector()->end();
}

#endif /* JNIEV_H_ */
