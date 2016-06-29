#include "Loading.h"
#include "Start.h"

USING_NS_CC;

Scene* Loading::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Loading::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto label = Label::createWithTTF("Loading", "fonts/Marker Felt.ttf", 36);
    this->str = "Loading";
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width-label->getContentSize().width/2-50,
                            origin.y +label->getContentSize().height/2 ));

    // add the label as a child to this layer
    this->addChild(label, 1,100);
    

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("loading.png");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    sprite->setScale(800/x, 600/y);
    

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    this ->schedule(schedule_selector(Loading::LoadingChangeCallback),0.8,3,0 );
    return true;
}


void Loading::LoadingChangeCallback(float d)
{
    this->count++;
    if(this->count<=3)
    {
        str=this->str+".";
       auto lab =(Label*)this->getChildByTag(100);
        lab->setString(str);
      
    }else
    {
        auto trans = TransitionProgressRadialCCW::create(1,Start::createScene());
                
        Director::getInstance()->replaceScene(trans);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
