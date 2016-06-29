#include "Loading.h"
#include "SelectCheckpoint.h"
#include "Start.h"

USING_NS_CC;

Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(Start::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("startbg.png");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    
    sprite->setScale(800/x, 600/y);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto normal = Sprite::create("start.png");
    
    auto selected = Sprite::create("start.png");

    selected -> setScale(1.1);
    
    //selected->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto mItem1 = MenuItemSprite::create(normal, selected,CC_CALLBACK_1(Start::menu1Callback, this));
    
    auto mItem2 = MenuItemImage::create("angrybird.png","angrybird.png");
    auto menu = Menu::create(mItem2,mItem1,NULL);
    //menu->setAnchorPoint(ccp(selected->getContentSize().width/2 , selected->getContentSize().width/2 ));
    //menu->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    menu->alignItemsVertically();
    this->addChild(menu, 1);
    
    
    
    return true;
}

void Start::menu1Callback(Ref* pSender){
  //  auto select = SelectCheckpoint::createScene();
    //auto trans = TransitionTurnOffTiles::create(2, select);
    auto trans = TransitionTurnOffTiles::create(2, SelectCheckpoint::createScene());
    
        Director::getInstance()->pushScene(trans);

}


