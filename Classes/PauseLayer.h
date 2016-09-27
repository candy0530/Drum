/*
 * PauseLayer.h
 *
 *  Created on: 2015/6/25
 *      Author: Wei Shang Chieh
 */

#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class PauseLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void Resume_bt(Ref* pSender);
    void Over_bt(Ref* pSender);

    CREATE_FUNC(PauseLayer);
};


#endif /* PAUSELAYER_H_ */
