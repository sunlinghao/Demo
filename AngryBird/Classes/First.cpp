#include "First.h"
#include "SelectCheckpoint.h"
#include<iostream>
#include <sstream>
#include<string>

Scene* First::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = First::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool First::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //添加所有图片
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mySprite.plist");
    auto texture = Director::getInstance()->getTextureCache()->addImage("mySprite.pvr.ccz");
    batchNode = SpriteBatchNode::createWithTexture(texture);

    //背景
    auto sprite = Sprite::createWithSpriteFrameName("background.jpg");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    sprite->setScale(800/x, 600/y);
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(sprite, 0);
        

       //父节点
    auto  birds = Sprite::create();
    //子节点
    auto bird = Sprite::createWithSpriteFrameName("bird1.png");
    bird->setAnchorPoint(Vec2(0,0));
    //粒子特效
    auto particle = ParticleSystemQuad::create("bird.plist");
    particle->setPosition(35,32);
    //父节点添加子节点
    birds->addChild(bird,1,11);
    birds->addChild(particle,0);
    //设置父节点大小
    birds->setContentSize(bird->getContentSize());
    //设置父节点位置
    birds->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/1.3 + origin.y));
    this->addChild(birds,1,10);
    
    listener->onTouchBegan = CC_CALLBACK_2(First::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(First::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(First::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, birds);
 
    
    
    this->initUFO();
    this->schedule(CC_SCHEDULE_SELECTOR(First::updateUFO), 0.1f);
    this->scheduleUpdate();


    return true;
}



bool First::onTouchBegan(Touch* t, Event* e)
{
    auto birds = this->getChildByTag(10);
    auto bird = birds->getChildByTag(11);
    auto pos= bird->getBoundingBox();
    auto location = t->getLocation();
    auto truet = birds-> convertToNodeSpace(location);
    if(pos.containsPoint(truet))
    {
        birds->setPosition(location);
        return true;
    }
    else
    {
        return false;
    }

}
void First::onTouchMoved(Touch* t, Event* e)
{
    auto birds = this->getChildByTag(10);
   // auto bird = birds->getChildByTag(11);
    
//    auto loca =bird ->getPosition();
    //
   // CCLOG("  true.x = %f,true.y = %f",loca.x,loca.y,trueLoca.x,trueLoca.y);
   // auto pos= bird->getBoundingBox();
    
 //   float a = pos.getMaxX();
 //   CCLOG("a = %f",a);
    
    auto location = t->getLocation();
    auto truet = birds-> convertToNodeSpace(location);
    if(0<location.x&&location.x<800 && 0<location.y&&location.y<600)
    {
        
        birds->setPosition(location);

    }
    //CCLOG("loca.x = %f,loca.y = %f",location.x,location.y);
    
}
void First::onTouchEnded(Touch* t, Event* e)
{
    
}

void First::initUFO(){
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mySprite.plist");
    auto texture = Director::getInstance()->getTextureCache()->addImage("mySprite.pvr.ccz");
     batchNode = SpriteBatchNode::createWithTexture(texture);
    
    auto tempStar = Sprite::createWithSpriteFrameName("ufo.png");
    float imageHeight = tempStar->getContentSize().height/4;
    UFOCount = visibleSize.height/(imageHeight+39);
    
    for(int i = 0;i <UFOCount;i++)
    {
        auto ufo = Sprite::createWithSpriteFrameName("ufo.png");
        ufo->setScale(0.25);
        ufo->setPosition( origin.x+ visibleSize.width-100 ,
                          (imageHeight+39)* i + imageHeight/2.0f);
        batchNode->addChild(ufo,0,i);
        
    }
    this->addChild(batchNode,1);
}
void First::updateUFO(float d){
    this->removeChildByTag(20);

    auto randomUFO = batchNode->getChildren().getRandomObject();
    if (randomUFO&&randomUFO->getNumberOfRunningActions() == 0)
    {
        auto move = MoveTo::create(3, Vec2(-randomUFO->getContentSize().width,randomUFO->getPosition().y));
        auto place = Place::create(Vec2(visibleSize.width + randomUFO->getContentSize().width,randomUFO->getPosition().y ));
        auto sequence = Sequence::create(move,place, NULL);
        randomUFO->runAction(sequence);
        grade++;
    }
    //将int转换成ccstring
    CCString* ns=CCString::createWithFormat("%d",grade);
    const char*s = ns->getCString();
    auto lab= Label::createWithTTF(s, "fonts/Marker Felt.ttf", 40);
    lab->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height- lab->getContentSize().height));
    this->addChild(lab,2,20);
    

}

void First::update(float d)
{
    auto rect = this->getChildByTag(10)->getBoundingBox();
    auto vec = batchNode->getDescendants();

    for(int i = 0;i<UFOCount;i++){
        auto temp = batchNode->getChildByTag(i)->getBoundingBox();
        if(rect.intersectsRect(temp))
        {
            //停止所有ufo
            for(int j = 0;j<UFOCount;j++)
            {
                auto ntemp = batchNode->getChildByTag(j);
                ntemp->stopAllActions();
            }
            //停止判断
            this->unscheduleUpdate();
            //停止更新ufo
            this->unschedule(CC_SCHEDULE_SELECTOR(First::updateUFO));
            //停止所有监听器
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeEventListener(listener);
            
            auto over = Label::createWithBMFont("fonts/myFont.fnt", "Game Over");
            over->setBMFontSize(100);
            over->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2+over->getContentSize().height/2));
            this->addChild(over,2);
            
            auto backItem =  MenuItemImage::create("backarrow.png","backarrow.png",CC_CALLBACK_1(First::gameover, this));
            auto menu = Menu::create(backItem ,NULL);
            menu->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2.5-backItem->getContentSize().height));
            this->addChild(menu,2);
            //Director::getInstance()->popScene();
        }
    }
}
void First::gameover(Ref* pSender)
{

    Director::getInstance()->popScene();
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

