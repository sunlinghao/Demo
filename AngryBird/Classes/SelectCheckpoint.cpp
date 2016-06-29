#include "SelectCheckpoint.h"
#include "First.h"

USING_NS_CC;

Scene* SelectCheckpoint::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectCheckpoint::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectCheckpoint::init()
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
    auto backItem = MenuItemImage::create(
                                           "backarrow.png",
                                           "backarrow.png",
                                           CC_CALLBACK_1(SelectCheckpoint::backCallback, this));
   
    backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width/2 ,
                               origin.y + backItem->getContentSize().height/2));
    auto first = MenuItemImage::create("bird1.png","bird1.png",CC_CALLBACK_1(SelectCheckpoint::FirstCallback,this));
    first->setPosition(Vec2(origin.x + visibleSize.width/4 ,
                               origin.y + visibleSize.height/1.3));
    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(SelectCheckpoint::menuCloseCallback, this));
    
    	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                    origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem,first,closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("bj2.png");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    sprite->setScale(800/x, 600/y);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}
void SelectCheckpoint::FirstCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(First::createScene());
}

void SelectCheckpoint::backCallback(Ref* pSender)
{
    Director::getInstance()->popScene();

}
void SelectCheckpoint::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
}
