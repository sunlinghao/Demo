#include "HelloWorldScene.h"
#include "GameScene.h"
#include "UI/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mySprite.plist");
    auto texture = Director::getInstance()->getTextureCache()->addImage("mySprite.pvr.ccz");
    batchNode = SpriteBatchNode::createWithTexture(texture);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("TypeGame", "fonts/Marker Felt.ttf", 48);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    //label->
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto sprite = Sprite::createWithSpriteFrameName("background.jpg");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    sprite->setScale(800/x, 600/y);
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(sprite, 0);
    
     
    //UIbutton
    auto btn =cocos2d::ui::Button::create();
    btn->cocos2d::Node::setScale(0.5);
    btn->setTitleText("Start");
    btn->setTitleFontSize(60);
    btn->setTitleColor(Color3B::BLUE);
    btn->addClickEventListener([](Ref*){
        auto game = Game::createScene();
        Director::getInstance()->pushScene(game);

    });
    btn->cocos2d::Node::setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-50));
    this->addChild(btn,1);
    return true;
}

void HelloWorld::startGame(Ref* pSender)
{
    auto game = Game::createScene();
    Director::getInstance()->pushScene(game);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
