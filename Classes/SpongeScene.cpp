#include "TeachScene.h"
#include "GameScene.h"
#include "SpongeScene.h"
#include "SimpleAudioEngine.h"
#include "PauseLayer.h"
#include <math.h>
USING_NS_CC;

using namespace CocosDenshion;

int count  = 0;
int count2  = 0;
int count3  = 0;
int count4  = 0;
int count5  = 0;

CCSprite *target1;
CCSprite *target2;
CCSprite *target3;
CCSprite *target4;
CCSprite *target5;

CCSprite *target_enemy;

int music_w = 150;
int music_d = 200;
int Array_size = 300;

int mu1[300];
int mu2[300];
int mu3[300];
int mu4[300];
int mu5[300];

float Song_delay;
float Song_speed;
float level;
float range = 300;

int target1_status = 0;
int target2_status = 0;
int target3_status = 0;
int target4_status = 0;
int target5_status = 0;

ImageView* rope;
float rope_x = -5 ;

int click_status1 = 0;
int click_status2 = 0;
int click_status3 = 0;
int click_status4 = 0;
int click_status5 = 0;

extern int data_mode;
extern int data_stage;

const char *song ;
const char *pic ;

int end_flag = 0;

float hit = 0;
float hit_e =0;
float total_hit = 0;

int delay_buff = 0;
int delay_buff_flag = 0;
int zero_flag = 0;

int delay_buff2 = 0;
int delay_buff_flag2 = 0;
int zero_flag2 = 0;

int delay_buff3 = 0;
int delay_buff_flag3 = 0;
int zero_flag3 = 0;

int delay_buff4 = 0;
int delay_buff_flag4 = 0;
int zero_flag4 = 0;

int delay_buff5 = 0;
int delay_buff_flag5 = 0;
int zero_flag5 = 0;

extern int data_pause;

int page = 0;

int music_flag = 0;

Scene* SpongeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = SpongeScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SpongeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Readdata();

    CocosDenshion::SimpleAudioEngine::getInstance()->end();
    log("music start");
//    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(song,false);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Game_bk.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto layout1 = Layout::create();
    layout1->setSize(windowSize);
    layout1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto eny = ImageView::create(pic);
    eny->setPosition(Vec2(0,745));

    rope = ImageView::create("Game_rope.png");
    rope->setPosition(Vec2(rope_x,-225));

    auto button1 = Button::create("Game_touch_obj1.png");
    button1->setPosition(Vec2(-400,-825));
    button1->addTouchEventListener(CC_CALLBACK_1(SpongeScene::Touch_bt1, this));

    auto button2 = Button::create("Game_touch_obj2.png");
    button2->setPosition(Vec2(-200,-825));
    button2->addTouchEventListener(CC_CALLBACK_1(SpongeScene::Touch_bt2, this));

    auto button3 = Button::create("Game_touch_obj3.png");
    button3->setPosition(Vec2(0,-825));
    button3->addTouchEventListener(CC_CALLBACK_1(SpongeScene::Touch_bt3, this));

    auto button4 = Button::create("Game_touch_obj4.png");
    button4->setPosition(Vec2(200,-825));
    button4->addTouchEventListener(CC_CALLBACK_1(SpongeScene::Touch_bt4, this));

    auto button5 = Button::create("Game_touch_obj5.png");
    button5->setPosition(Vec2(400,-825));
    button5->addTouchEventListener(CC_CALLBACK_1(SpongeScene::Touch_bt5, this));

    auto button_menu = Button::create("Game_Pause.png");
    button_menu->setPosition(Vec2(475,900));
    button_menu->addClickEventListener(CC_CALLBACK_1(SpongeScene::Menu, this));


    layout1->addChild(eny);
    layout1->addChild(rope);
    layout1->addChild(button1);
    layout1->addChild(button2);
    layout1->addChild(button3);
    layout1->addChild(button4);
    layout1->addChild(button5);
    layout1->addChild(button_menu);

    sprite->addChild(layout1);

    this->addChild(sprite, 0);
//    log("Start:%d",++page);

    float bpm_delay;

    if(Song_delay-1*(60/Song_speed)>0){

        bpm_delay = Song_delay-18/8*(60/Song_speed);
//        bpm_delay = (60/Song_speed)*8;
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(song,false);
        music_flag = 1;

    }else{
        bpm_delay = 2;
    }

    log("Song delay:%f , bpm_delay:%f",Song_delay,bpm_delay);

    DelayTime *delayAction = DelayTime::create(bpm_delay);
    CallFunc *callSelectorAction = CallFunc::create(this, callfunc_selector(SpongeScene::Run));
    this->runAction(Sequence::create(delayAction, callSelectorAction, NULL));

    return true;
}
void SpongeScene::Run(){
    log("Running");

    if(music_flag == 0){

        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(song,false);

        music_flag = 1;
    }

    this->schedule(schedule_selector(SpongeScene::GameLogic),(60/Song_speed)/8);
    this->scheduleUpdate();
}

void SpongeScene::Readdata(){

    count  = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    count5 = 0;

    music_flag = 0;

    rope_x = -5;

    end_flag = 0;

    hit = 0;
    hit_e =0;
    total_hit = 0;

    delay_buff = 0;
    delay_buff_flag = 0;
    zero_flag = 0;

    delay_buff2 = 0;
    delay_buff_flag2 = 0;
    zero_flag2 = 0;

    delay_buff3 = 0;
    delay_buff_flag3 = 0;
    zero_flag3 = 0;

    delay_buff4 = 0;
    delay_buff_flag4 = 0;
    zero_flag4 = 0;

    delay_buff5 = 0;
    delay_buff_flag5 = 0;
    zero_flag5 = 0;

//    log("mode:%d,stage:%d",data_mode,data_stage);

    switch(data_mode){
    case 0:
        switch(data_stage){
        case 3:{
            //fly
            pic = "enemy.png";
            song = "fly.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

//            int h[300] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//            int s[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//            int f[300] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
//            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

            int h[300] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
            int s[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int f[300] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));

            break;
        }
        case 4:{
            //dara
            pic = "Storyb_c3.png";
            song = "fly.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

//            int h[300] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//            int s[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//            int f[300] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
//            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

            int h[300] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
            int s[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int f[300] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));

            break;
        }
        case 5:{
            //dora
            pic = "enemy.png";
            song = "dora.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

            int h[300] = {1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
            int s[300] = {0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0};
            int f[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));

            break;
        }
        case 6:{
            //bridge
            pic = "Storyb_c4.png";
            song = "bridge.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

            int h[300] = {1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
            int s[300] = {0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0};
            int f[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));
            break;
        }
        case 7:{
            //bridge
            pic = "enemy.png";
            song = "bridge.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

            int h[300] = {1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
            int s[300] = {0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0};
            int f[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));

            break;
        }
        case 8:{
            //land
            pic = "Storyb_c5.png";
            song = "bridge.wav";

            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

            int h[300] = {1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,-2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
            int s[300] = {0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0};
            int f[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));
            break;
        }
        case 9:{
            //land
            pic = "enemy.png";
            song = "land.wav";
            Song_delay = 0;
            Song_speed = 120;
            level = 0.2;

            int h[300] = {0,0,0,0,0,0,0,0,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,1,0,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,2,2,0,0,2,2,2,2,0,0,0,0,0};
            int s[300] = {0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,0,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,2,2,2,2,1,0,1,0,0,0,2,2,2,2,0,0,0};
            int f[300] = {1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1};
            int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int c[300] = {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

            memcpy(mu1,h,sizeof(h));
            memcpy(mu2,s,sizeof(s));
            memcpy(mu3,f,sizeof(f));
            memcpy(mu4,t,sizeof(t));
            memcpy(mu5,c,sizeof(c));

            break;
        }

        }
        break;
        case 1:
            switch(data_stage){
            case 1:{

                pic = "Gameb_c2.png";
                song = "SpongeTheme.mp3";

                Song_delay = 4.13;
                Song_speed = 122;
                level = 0.2;

                int h[300] = {1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int s[300] = {0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,0,0,0};
                int f[300] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int t[300] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};

                memcpy(mu1,h,sizeof(h));
                memcpy(mu2,s,sizeof(s));
                memcpy(mu3,f,sizeof(f));
                memcpy(mu4,t,sizeof(t));
                memcpy(mu5,c,sizeof(c));

                break;
            }
            case 2:{

                pic = "Gameb_c5.png";
                song = "Immortals.mp3";

                Song_delay = 3.05;
                Song_speed = 109;
                level = 0.3;

                int h[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,2,3,3,2,2,2,2,2,3,3,2,3,3,2,2,2,2,2,3,3,2,3,3,2,2,2,2,2,3,3,2,3,3,2,2,2,2,2,3,3,2,3,3,2,2,2,2,2,3,3,2,3,3,2,2,2,2,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2};
                int s[300] = {-2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int f[300] = {1,0,0,0,0,0,0,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,0,2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2,2,3,3,2,2,-2,2,-2,2};
                int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int c[300] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

                memcpy(mu1,h,sizeof(h));
                memcpy(mu2,s,sizeof(s));
                memcpy(mu3,f,sizeof(f));
                memcpy(mu4,t,sizeof(t));
                memcpy(mu5,c,sizeof(c));

                break;
            }
            case 3:{
                pic = "Gameb_c4.png";
                song = "drum.mp3";

                Song_delay = 5.98;
                Song_speed = 59;
                level = 0.4;

                int h[300] = {0,0,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-2,0,0,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-2,0,0,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-2,0,0,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-3,3,3,4,4,3,3,-3,3,-2,0,0};
                int s[300] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int f[300] = {0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0};
                int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int c[300] = {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};

                memcpy(mu1,h,sizeof(h));
                memcpy(mu2,s,sizeof(s));
                memcpy(mu3,f,sizeof(f));
                memcpy(mu4,t,sizeof(t));
                memcpy(mu5,c,sizeof(c));
                break;
            }
            case 4:{
                pic = "Gameb_c3.png";
                song = "Mayday.mp3";

                log("Mayday");

                Song_delay = 0.68;
                Song_speed = 120;
                level = 0.5;

                int h[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0};
                int s[300] = {1,0,0,0,2,2,0,0,0,1,0,0,0,2,2,0,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,3,3,2,2,-2,2,1,2,3,3,2,2,-2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0};
                int f[300] = {1,0,0,0,2,2,0,0,0,1,0,0,0,2,2,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,1,2,2,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
                int t[300] = {1,0,0,0,2,2,0,0,0,1,0,0,0,2,2,0,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,2,2,-2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

                memcpy(mu1,h,sizeof(h));
                memcpy(mu2,s,sizeof(s));
                memcpy(mu3,f,sizeof(f));
                memcpy(mu4,t,sizeof(t));
                memcpy(mu5,c,sizeof(c));
                break;
            }
            case 5:{
                pic = "Gameb_c1.png";
                song = "Re_make.mp3";

                Song_delay = 2.06;
                Song_speed = 173;
                level = 0.6;

                int h[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0};
                int s[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,3,3,3,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,3,3,3,0,0,0,0,};
                int f[300] = {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,2,2,1,1,1,1,1,1,1,2,2,1,1,1,2,2,1,1,1,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int t[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int c[300] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,};

                memcpy(mu1,h,sizeof(h));
                memcpy(mu2,s,sizeof(s));
                memcpy(mu3,f,sizeof(f));
                memcpy(mu4,t,sizeof(t));
                memcpy(mu5,c,sizeof(c));
                break;
            }
            }
            break;
    }

    //    int h[200] = {1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //    int s[200] = {0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,0,0,0};
    //    int f[200] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //    int t[200] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //    int c[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};


}
void SpongeScene::Menu(Ref* pSender){

    data_pause = 1;

    RenderTexture *renderTexture = RenderTexture::create(1080,1920);
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();

//    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->pushScene(PauseLayer::createScene(renderTexture));

    //    Director::getInstance()->pause();

}

void SpongeScene::Touch_bt1(Ref* pSender){

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Hihat.wav");

    log("BT1 click::%d",target1_status);
    if(target1_status == 1){

        float dist1 = target1->getPositionY();
        log("dist1::%f",dist1);
        if(dist1-250<range){
            log("Click OK");
            hit++;
            click_status1 = 1;
        }else{
            log("NO Click");
            click_status1 = 0;
        }
    }
        //        log("target1 is null");
//    }
}
void SpongeScene::Touch_bt2(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SnareDrum.wav");
    if(target2_status == 1){

        float dist2 = target2->getPositionY();
        log("dist2::%f",dist2);
        if(dist2-250<range){
            log("Click OK");
            click_status2 = 1;
        }else{
            log("NO Click");
            click_status2 = 0;
        }
    }

}
void SpongeScene::Touch_bt3(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FloorTom_V3.wav");
    if(target3_status == 1){

        float dist3 = target3->getPositionY();
        log("dist3::%f",dist3);
        if(dist3-250<range){
            log("Click OK");
            click_status3 = 1;
        }else{
            log("NO Click");
            click_status3 = 0;
        }
    }

}
void SpongeScene::Touch_bt4(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Tom_12.wav");
    if(target4_status == 1){

        float dist4 = target4->getPositionY();
        log("dist4::%f",dist4);
        if(dist4-250<range){
            log("Click OK");
            click_status4 = 1;
        }else{
            log("NO Click");
            click_status4 = 0;
        }
    }

}
void SpongeScene::Touch_bt5(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Crash.wav");
    if(target5_status == 1){

        float dist5 = target5->getPositionY();
        log("dist5::%f",dist5);
        if(dist5-250<range){
            log("Click OK");
            click_status5 = 1;
        }else{
            log("NO Click");
            click_status5 = 0;
        }
    }

}

void SpongeScene::GameLogic(float dt){

    if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){

        //        log("Playing");
//        log("MU:%d ,delay_buff:%d ,delay_buff_flag:%d",mu1[count],delay_buff,delay_buff_flag);

        if(mu1[count]>0 && zero_flag==0){
            zero_flag = 1;
        }
        if(mu1[count]==0 && delay_buff ==0 && delay_buff_flag==0 && zero_flag==0){
            delay_buff = 7;
            delay_buff_flag=1;
            zero_flag = 1;
//            log("1 X");
        }else if(mu1[count]==-2 && delay_buff==0 && delay_buff_flag==0 && zero_flag==0){
            delay_buff = 3;
            delay_buff_flag=1;
            zero_flag = 1;
        }else if(mu1[count]==-3 && delay_buff==0 && delay_buff_flag==0 && zero_flag==0){
            delay_buff = 1;
            delay_buff_flag=1;
            zero_flag = 1;
        }else if(mu1[count]==-4 && delay_buff==0 && delay_buff_flag==0 && zero_flag==0){
            delay_buff = 0;
            delay_buff_flag=1;
            zero_flag = 1;
        }else if(delay_buff ==0 && delay_buff_flag==0 && zero_flag==1){
//            log("1 O");
            create_obj1(mu1[count]);
            delay_buff_flag = 0;
            zero_flag = 0;
            if(mu1[count] == 1){
                delay_buff = 7;
            }else if(mu1[count] == 2){
                delay_buff = 3;
            }else if(mu1[count] == 3){
                delay_buff = 1;
            }else if(mu1[count] == 4){
                count++;
                delay_buff = 0;
            }
        }else{
//            log("1 X");
            delay_buff--;
            if(delay_buff==0){
                count++;
                zero_flag = 0;
                delay_buff_flag = 0;
            }
        }

//        log("MU2:%d ,delay_buff:%d ,delay_buff_flag:%d",mu2[count2],delay_buff2,delay_buff_flag2);
        // obj2
        if(mu2[count2]>0 && zero_flag2==0){
            zero_flag2 = 1;
        }
        if(mu2[count2]==0 && delay_buff2 ==0 && delay_buff_flag2==0 && zero_flag2==0){
            delay_buff2 = 7;
            delay_buff_flag2=1;
            zero_flag2 = 1;
//            log("2 X");
        }else if(mu2[count2]==-2 && delay_buff2==0 && delay_buff_flag2==0 && zero_flag2==0){
            delay_buff2 = 3;
            delay_buff_flag2 =1;
            zero_flag2 = 1;
        }else if(mu2[count2]==-3 && delay_buff2==0 && delay_buff_flag2==0 && zero_flag2==0){
            delay_buff2 = 1;
            delay_buff_flag2=1;
            zero_flag2 = 1;
        }else if(mu2[count2]==-4 && delay_buff2==0 && delay_buff_flag2==0 && zero_flag2==0){
            delay_buff2 = 0;
            delay_buff_flag2=1;
            zero_flag2 = 1;
        }else if(delay_buff2 ==0 && delay_buff_flag2==0 && zero_flag2==1){
//            log("2 O");
            create_obj2(mu2[count2]);
            delay_buff_flag2 = 0;
            zero_flag2 = 0;
            if(mu2[count2] == 1){
                delay_buff2 = 7;
            }else if(mu2[count2] == 2){
                delay_buff2 = 3;
            }else if(mu2[count2] == 3){
                delay_buff2 = 1;
            }else if(mu2[count2] == 4){
                delay_buff2 = 0;
                count2++;
            }
        }else{
//            log("2 X");
            delay_buff2--;
            if(delay_buff2==0){
                count2++;
                zero_flag2 = 0;
                delay_buff_flag2 = 0;
            }
        }

        //obj3

        if(mu3[count3]>0 && zero_flag3==0){
            zero_flag3 = 1;
        }
        if(mu3[count3]==0 && delay_buff3 ==0 && delay_buff_flag3==0 && zero_flag3==0){
            delay_buff3 = 7;
            delay_buff_flag3=1;
            zero_flag3 = 1;
//            log("3 X");
        }else if(mu3[count3]==-2 && delay_buff3==0 && delay_buff_flag3==0 && zero_flag3==0){
            delay_buff3 = 3;
            delay_buff_flag3=1;
            zero_flag3 = 1;
        }else if(mu3[count3]==-3 && delay_buff3==0 && delay_buff_flag3==0 && zero_flag3==0){
            delay_buff3 = 1;
            delay_buff_flag3=1;
            zero_flag3 = 1;
        }else if(mu3[count3]==-4 && delay_buff3==0 && delay_buff_flag3==0 && zero_flag3==0){
            delay_buff3 = 0;
            delay_buff_flag3=1;
            zero_flag3 = 1;
        }else if(delay_buff3 ==0 && delay_buff_flag3==0 && zero_flag3==1){
//            log("3 O");
            create_obj3(mu3[count3]);
            delay_buff_flag3 = 0;
            zero_flag3 = 0;
            if(mu3[count3] == 1){
                delay_buff3 = 7;
            }else if(mu3[count3] == 2){
                delay_buff3 = 3;
            }else if(mu3[count3] == 3){
                delay_buff3 = 1;
            }else if(mu3[count3] == 4){
                delay_buff3 = 0;
                count3++;
            }
        }else{
            delay_buff3--;
            if(delay_buff3==0){
                count3++;
                zero_flag3 = 0;
                delay_buff_flag3 = 0;
            }
        }

        //obj4

        if(mu4[count4]>0 && zero_flag4==0){
            zero_flag4 = 1;
        }
        if(mu4[count4]==0 && delay_buff4 ==0 && delay_buff_flag4==0 && zero_flag4==0){
            delay_buff4 = 7;
            delay_buff_flag4=1;
            zero_flag4 = 1;
        }else if(mu4[count4]==-2 && delay_buff4 ==0 && delay_buff_flag4==0 && zero_flag4==0){
            delay_buff4 = 3;
            delay_buff_flag4=1;
            zero_flag4 = 1;
        }else if(mu4[count4]==-3 && delay_buff4 ==0 && delay_buff_flag4==0 && zero_flag4==0){
            delay_buff4 = 1;
            delay_buff_flag4=1;
            zero_flag4 = 1;
        }else if(mu4[count4]==-4 && delay_buff4 ==0 && delay_buff_flag4==0 && zero_flag4==0){
            delay_buff4 = 0;
            delay_buff_flag4=1;
            zero_flag4 = 1;
        }else if(delay_buff4 ==0 && delay_buff_flag4==0 && zero_flag4==1){
            create_obj4(mu4[count4]);
            delay_buff_flag4 = 0;
            zero_flag4 = 0;
            if(mu4[count4] == 1){
                delay_buff4 = 7;
            }else if(mu4[count4] == 2){
                delay_buff4 = 3;
            }else if(mu4[count4] == 3){
                delay_buff4 = 1;
            }else if(mu4[count4] == 4){
                delay_buff4 = 0;
                count4++;
            }
        }else{
            delay_buff4--;
            if(delay_buff4==0){
                delay_buff_flag4 = 0;
                count4++;
                zero_flag4 = 0;
            }
        }
        if(mu5[count5]>0 && zero_flag5==0){
            zero_flag5 = 1;
        }
        if(mu5[count5]==0 && delay_buff5 ==0 && delay_buff_flag5==0 && zero_flag5==0){
            delay_buff5 = 7;
            delay_buff_flag5=1;
            zero_flag5 = 1;
        }else if(mu5[count5]==-2 && delay_buff5 ==0 && delay_buff_flag5==0 && zero_flag5==0){
            delay_buff5 = 3;
            delay_buff_flag5=1;
            zero_flag5 = 1;
        }else if(mu5[count5]==-3 && delay_buff5 ==0 && delay_buff_flag5==0 && zero_flag5==0){
            delay_buff5 = 1;
            delay_buff_flag5=1;
            zero_flag5 = 1;
        }else if(mu5[count5]==-4 && delay_buff5 ==0 && delay_buff_flag5==0 && zero_flag5==0){
            delay_buff5 = 0;
            delay_buff_flag5=1;
            zero_flag5 = 1;
        }else if(delay_buff5 ==0 && delay_buff_flag5==0 && zero_flag5==1){
            create_obj5(mu5[count5]);
            delay_buff_flag5 = 0;
            zero_flag5 = 0;
            if(mu5[count5] == 1){
                delay_buff5 = 7;
            }else if(mu5[count5] == 2){
                delay_buff5 = 3;
            }else if(mu5[count5] == 3){
                delay_buff5 = 1;
            }else if(mu5[count5] == 4){
                delay_buff5 = 0;
                count5++;
            }
        }else{
            delay_buff5--;
            if(delay_buff5==0){
                delay_buff_flag5 = 0;
                count5++;
                zero_flag5 = 0;
            }
        }


        //        create_obj1(mu1[count]);
        //        create_obj2(mu2[count]);
        //        create_obj3(mu3[count]);
        //        create_obj4(mu4[count]);
        //        create_obj5(mu5[count]);

        //        count++;

    }else{
        //        log("No Playing");
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->end();

        if(end_flag==0 && data_pause==0){
            log("music end");
            showEnd();
            end_flag = 1;
        }
    }
}

void SpongeScene::create_obj1(int data){

    log("create first obj");
    if(data>0){

        target1_status = 1;

        const char * visable_pic;

        if(data<0){
            visable_pic = "delay.png";
        }else{
            visable_pic = "Game_music.png";
        }

        total_hit++;

//        ImageView* line = ImageView::create("line.png");
//        line->setPosition(Vec2(music_w+0*music_d,250));
//
//        ImageView* line2 = ImageView::create("line.png");
//        line2->setPosition(Vec2(music_w+0*music_d,270+range));

        target1=CCSprite::create(visable_pic);
        target1->setPosition(Vec2(music_w+0*music_d,750));

        target_enemy = CCSprite::create(visable_pic);
        target_enemy->setPosition(Vec2(music_w+0*music_d,750));

//        this->addChild(line,0,1);
//        this->addChild(line2,0,1);
        this->addChild(target1,0,1);
        this->addChild(target_enemy,0,1);

        float run_ime = 0.0;

        //        if(data == 1){
        //            run_ime = 60/Song_speed;
        //        }else if(data == 2){
        //            run_ime = 60/Song_speed/2;
        //        }else if(data == 3){
        //            run_ime = 60/Song_speed/4;
        //        }else if(data == 4){
        //            run_ime = 60/Song_speed/8;
        //        }else if(data == -2){
        //            run_ime = 60/Song_speed/2;
        //        }else if(data == -3){
        //            run_ime = 60/Song_speed/4;
        //        }else if(data == -4){
        //            run_ime = 60/Song_speed/8;
        //        }

//      log("data::%d",data);
        run_ime = 60/Song_speed;

        //        if(data == 1){
        //            run_ime = 60/Song_speed;
        //        }else if(data == 2){
        //            run_ime = 60/Song_speed/2;
        //        }else if(data == 3){
        //            run_ime = 60/Song_speed/4;
        //        }else if(data == 4){
        //            run_ime = 60/Song_speed/8;
        //        }

        CCFiniteTimeAction *actionMove=CCMoveTo::create(run_ime*5/8, Vec2(music_w+0*music_d,270));
        CCFiniteTimeAction *actionMove2=CCMoveTo::create(run_ime*5/8, Vec2(music_w+0*music_d,1920-500));
        CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(SpongeScene::create_dis1));
        target1->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
        target_enemy->runAction(CCSequence::create(actionMove2,actionMoveDone,NULL));

    }
}
void SpongeScene::create_obj2(int data){

    if(data!=0){

        target2_status = 1;

        target2=CCSprite::create("Game_music.png");
        target2->setPosition(Vec2(music_w+1*music_d,750));

        target_enemy = CCSprite::create("Game_music.png");
        target_enemy->setPosition(Vec2(music_w+1*music_d,750));

        float run_ime2 = 0.0;

        run_ime2 = 60/Song_speed;

//        if(data == 1){
//            run_ime2 = 60/Song_speed;
//        }else if(data == 2){
//            run_ime2 = 60/Song_speed/2;
//        }else if(data == 3){
//            run_ime2 = 60/Song_speed/4;
//        }else if(data == 4){
//            run_ime2 = 60/Song_speed/8;
//        }else if(data == -2){
//            run_ime2 = 60/Song_speed/2*3;
//        }else if(data == -3){
//            run_ime2 = 60/Song_speed/4*5;
//        }else if(data == -4){
//            run_ime2 = 60/Song_speed/8*9;
//        }

        this->addChild(target2,0,1);
        this->addChild(target_enemy,0,1);

        FiniteTimeAction *actionMove=CCMoveTo::create(run_ime2*5/8, Vec2(music_w+1*music_d,270));
        CCFiniteTimeAction *actionMove2=CCMoveTo::create(run_ime2*5/8, Vec2(music_w+1*music_d,1920-500));
        FiniteTimeAction *actionMoveDone = CallFuncN::create(this,callfuncN_selector(SpongeScene::create_dis2));
        target2->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
        target_enemy->runAction(CCSequence::create(actionMove2,actionMoveDone,NULL));

    }
}
void SpongeScene::create_obj3(int data){

    if(data!=0){

        target3_status = 1;

        target3=CCSprite::create("Game_music.png");
        target3->setPosition(Vec2(music_w+2*music_d,750));

        target_enemy = CCSprite::create("Game_music.png");
        target_enemy->setPosition(Vec2(music_w+2*music_d,750));


        float run_ime3 = 0.0;

//        if(data == 1){
//            run_ime3 = 60/Song_speed;
//        }else if(data == 2){
//            run_ime3 = 60/Song_speed/2;
//        }else if(data == 3){
//            run_ime3 = 60/Song_speed/4;
//        }else if(data == 4){
//            run_ime3 = 60/Song_speed/8;
//        }else if(data == -2){
//            run_ime3 = 60/Song_speed/2*3;
//        }else if(data == -3){
//            run_ime3 = 60/Song_speed/4*5;
//        }else if(data == -4){
//            run_ime3 = 60/Song_speed/8*9;
//        }

        run_ime3 = 60/Song_speed;

        this->addChild(target3,0,1);
        this->addChild(target_enemy,0,1);

        CCFiniteTimeAction *actionMove=CCMoveTo::create(run_ime3*5/8, Vec2(music_w+2*music_d,270));
        CCFiniteTimeAction *actionMove2=CCMoveTo::create(run_ime3*5/8, Vec2(music_w+2*music_d,1920-500));
        CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(SpongeScene::create_dis3));
        target3->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
        target_enemy->runAction(CCSequence::create(actionMove2,actionMoveDone,NULL));

    }
}
void SpongeScene::create_obj4(int data){

    if(data!=0){

        target4_status = 1;

        target4=CCSprite::create("Game_music.png");
        target4->setPosition(Vec2(music_w+3*music_d,750));

        target_enemy = CCSprite::create("Game_music.png");
        target_enemy->setPosition(Vec2(music_w+3*music_d,750));


        float run_ime4 = 0.0;
        run_ime4 = 60/Song_speed;

//        if(data == 1){
//            run_ime4 = 60/Song_speed;
//        }else if(data == 2){
//            run_ime4 = 60/Song_speed/2;
//        }else if(data == 3){
//            run_ime4 = 60/Song_speed/4;
//        }else if(data == 4){
//            run_ime4 = 60/Song_speed/8;
//        }else if(data == -2){
//            run_ime4 = 60/Song_speed/2*3;
//        }else if(data == -3){
//            run_ime4 = 60/Song_speed/4*5;
//        }else if(data == -4){
//            run_ime4 = 60/Song_speed/8*9;
//        }

        this->addChild(target4,0,1);
        this->addChild(target_enemy,0,1);
        CCFiniteTimeAction *actionMove=CCMoveTo::create(run_ime4*5/8, Vec2(music_w+3*music_d,270));
        CCFiniteTimeAction *actionMove2=CCMoveTo::create(run_ime4*5/8, Vec2(music_w+3*music_d,1920-500));
        CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(SpongeScene::create_dis4));
        target4->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
        target_enemy->runAction(CCSequence::create(actionMove2,actionMoveDone,NULL));

    }
}
void SpongeScene::create_obj5(int data){

    if(data!=0){

        target5_status = 1;

        target5=CCSprite::create("Game_music.png");
        target5->setPosition(Vec2(music_w+4*music_d,750));

        target_enemy = CCSprite::create("Game_music.png");
        target_enemy->setPosition(Vec2(music_w+4*music_d,750));


        float run_ime5 = 0.0;
        run_ime5 = 60/Song_speed;

//        if(data == 1){
//            run_ime5 = 60/Song_speed;
//        }else if(data == 2){
//            run_ime5 = 60/Song_speed/2;
//        }else if(data == 3){
//            run_ime5 = 60/Song_speed/4;
//        }else if(data == 4){
//            run_ime5 = 60/Song_speed/8;
//        }else if(data == -2){
//            run_ime5 = 60/Song_speed/2*3;
//        }else if(data == -3){
//            run_ime5 = 60/Song_speed/4*5;
//        }else if(data == -4){
//            run_ime5 = 60/Song_speed/8*9;
//        }

        this->addChild(target5,0,1);
        this->addChild(target_enemy,0,1);
        CCFiniteTimeAction *actionMove=CCMoveTo::create(run_ime5*5/8, Vec2(music_w+4*music_d,270));
        CCFiniteTimeAction *actionMove2=CCMoveTo::create(run_ime5*5/8, Vec2(music_w+4*music_d,1920-500));
        CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(SpongeScene::create_dis5));
        target5->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
        target_enemy->runAction(CCSequence::create(actionMove2,actionMoveDone,NULL));

    }
}
void SpongeScene::create_dis1(CCNode* sender){

    target1_status = 0;
//    log("end:%d",target1_status);
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    Ai(click_status1);
    click_status1 =0;
}
void SpongeScene::create_dis2(CCNode* sender){
    target2_status = 0;
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    Ai(click_status2);
    click_status2 =0;
}
void SpongeScene::create_dis3(CCNode* sender){
    target3_status = 0;
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    Ai(click_status3);
    click_status3 =0;
}
void SpongeScene::create_dis4(CCNode* sender){
    target4_status = 0;
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    Ai(click_status4);
    click_status4 =0;
}
void SpongeScene::create_dis5(CCNode* sender){
    target5_status = 0;
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
    Ai(click_status5);
    click_status5 =0;
}
void SpongeScene::showEnd(){

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    auto layout2 = Layout::create();
    layout2->setSize(windowSize);
    layout2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    if(rope_x>-5){
        auto end = ImageView::create("Dialog_lose_v2.png");
        end->setPosition(Vec2(0,0));
        layout2->addChild(end);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lose.mp3",false);
    }else{
        auto end = ImageView::create("Dialog_success_v2.png");
        end->setPosition(Vec2(0,0));
        layout2->addChild(end);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("success.mp3",false);
    }
    log("hit = %f",hit*100/total_hit);
    log("hit-e = %f",hit_e);
    log("hit-to = %f",total_hit);
    log("hit_e = %f",hit_e*100/total_hit);

    auto ok = Button::create("Button_OK_v2.png");
    ok->setPosition(Vec2(0,-200));
    ok->addClickEventListener(CC_CALLBACK_1(SpongeScene::endSence, this));

    layout2->addChild(ok);

    this->addChild(layout2);
}

void SpongeScene::endSence(Ref* pSender){

    end_flag = 0;

    auto scene = Scene::create();
    if(data_mode==0){
        scene->addChild(TeachScene::create());
    }else{
        scene->addChild(GameScene::create());
    }
    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);
}

void SpongeScene::Ai(int click){

    float random = CCRANDOM_0_1();
    int ai_click ;

    if(random<=level){
        ai_click = 1;
        hit_e++;
    }else{
        ai_click = 0;
    }

    //    log("Me:%d , Enemy:%d",click,ai_click);

    if(click>ai_click){
        Rope(1);
    }else if(click<ai_click){
        Rope(0);
    }

}
void SpongeScene::Rope(int left){
    float bounce = 10;
    float Max = -325;
    float Min = 325;

    if(left==1){
        if(rope_x>=Max){
            rope_x = rope_x-10;
            rope->setPosition(Vec2(rope_x,-225));
        }
    }else{
        if(rope_x<=Min){
            rope_x = rope_x+10;
            rope->setPosition(Vec2(rope_x,-225));
        }
    }
}

void SpongeScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
