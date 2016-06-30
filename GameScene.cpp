#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
        
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
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto sprite = Sprite::createWithSpriteFrameName("background.jpg");
    float x = sprite->getContentSize().width;
    float y = sprite->getContentSize().height;
    sprite->setScale(800/x, 600/y);
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(sprite, 0);
    
    
    keyListener->onKeyPressed = [this](EventKeyboard::KeyCode key, Event*e){
      // auto temp = batchNode->getChildByTag((int)key -124);
        batchNode->removeChildByTag((int)key -124);
        
        
        CCLOG("keypress %d",key);
        
    };
    auto dispatch = Director::getInstance()->getEventDispatcher();
    dispatch->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    this->addChild(batchNode,2);
    
    //创建字母
    this->schedule(CC_SCHEDULE_SELECTOR(Game::initword), grade);
    //掉落字母
    this->schedule(CC_SCHEDULE_SELECTOR(Game::updateAlphabet),grade);
    this->scheduleUpdate();
   
    
    return true;
}

void Game::initword(float d){

    
   // srand(time(NULL));
    int x = visibleSize.width-20;
   // float y = visibleSize.height;
   
    int randomNUM = rand()%x;
    int randalp = rand()%25;
    Sprite*alphabet;
    switch(randalp)
    {
        
        case 0:
     alphabet = Sprite::createWithSpriteFrameName("a.png");
            break;
        case 1:
      alphabet = Sprite::createWithSpriteFrameName("b.png");
            break;
        case 2:
     alphabet = Sprite::createWithSpriteFrameName("c.png");
            break;
        case 3:
     alphabet = Sprite::createWithSpriteFrameName("d.png");
            break;
        case 4:
      alphabet = Sprite::createWithSpriteFrameName("e.png");
            break;
        case 5:
     alphabet = Sprite::createWithSpriteFrameName("f.png");
            break;
        case 6:
      alphabet = Sprite::createWithSpriteFrameName("g.png");
            break;
        case 7:
       alphabet = Sprite::createWithSpriteFrameName("h.png");
            break;
        case 8:
      alphabet = Sprite::createWithSpriteFrameName("i.png");
            break;
        case 9:
        alphabet = Sprite::createWithSpriteFrameName("j.png");
            break;
        case 10:
        alphabet = Sprite::createWithSpriteFrameName("k.png");
            break;
        case 11:
        alphabet = Sprite::createWithSpriteFrameName("l.png");
            break;
        case 12:
        alphabet = Sprite::createWithSpriteFrameName("m.png");
            break;
        case 13:
      alphabet = Sprite::createWithSpriteFrameName("n.png");
            break;
        case 14:
        alphabet = Sprite::createWithSpriteFrameName("o.png");
            break;
        case 15:
      alphabet = Sprite::createWithSpriteFrameName("p.png");
            break;
        case 16:
       alphabet = Sprite::createWithSpriteFrameName("q.png");
            break;
        case 17:
      alphabet = Sprite::createWithSpriteFrameName("r.png");
            break;
        case 18:
     alphabet = Sprite::createWithSpriteFrameName("s.png");
            break;
        case 19:
      alphabet = Sprite::createWithSpriteFrameName("t.png");
            break;
        case 20:
       alphabet = Sprite::createWithSpriteFrameName("u.png");
            break;
        case 21:
      alphabet = Sprite::createWithSpriteFrameName("v.png");
            break;
        case 22:
        alphabet = Sprite::createWithSpriteFrameName("w.png");
            break;
        case 23:
      alphabet = Sprite::createWithSpriteFrameName("x.png");
            break;
        case 24:
     alphabet = Sprite::createWithSpriteFrameName("y.png");
            break;
        case 25:
     alphabet = Sprite::createWithSpriteFrameName("z.png");
            break;
    }
    //alphabet->setTag(randalp);
    alphabet->setPosition(randomNUM+10, visibleSize.height+alphabet->getContentSize().height);
    
   // v.push_back(alphabet);
    container.insert(randalp,alphabet);
    batchNode->addChild(alphabet,1,randalp);
   
    
    //this->addChild(batchNode,1);
}
void Game::updateAlphabet(float d){
    this->removeChildByTag(200);
    
    auto randomAlphabet = batchNode->getChildren().getRandomObject();
    if (randomAlphabet&&randomAlphabet->getNumberOfRunningActions() == 0)
    {
        auto move = MoveTo::create(3, Vec2(randomAlphabet->getPosition().x,-randomAlphabet->getContentSize().height));
        randomAlphabet->runAction(move);
         count++;
    }
    //将int转换成ccstring
    CCString* ns=CCString::createWithFormat("%d",count);
    const char*s = ns->getCString();
    auto lab= Label::createWithTTF(s, "fonts/Marker Felt.ttf", 40);
    lab->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height- lab->getContentSize().height));
    this->addChild(lab,2,200);

    
    
}
void Game::update(float d)
{

    auto vec = batchNode->getDescendants();
    int index = v.size();
    if(batchNode->getChildren().getRandomObject()!=NULL)
    {
        
    auto temp = batchNode->getChildren().getRandomObject();
    float y = temp->getPositionY();
        if(y<0)
        {      //停止判断
            CCLOG("stop");
            this->unscheduleUpdate();
            //停止更新
            this->unschedule(CC_SCHEDULE_SELECTOR(Game::updateAlphabet));
            //停止所有监听器
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeEventListener(keyListener);
            //停止所有动作
            this->stopAllActions();
            auto over = Label::createWithTTF("Game over", "fonts/Marker Felt.ttf", 100);
            
            over->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2+over->getContentSize().height/2));
            this->addChild(over,2);
            
            //            auto backItem =  MenuItemImage::create("backarrow.png","backarrow.png",CC_CALLBACK_1(First::gameover, this));
            //            auto menu = Menu::create(backItem ,NULL);
            //            menu->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2.5-backItem->getContentSize().height));
            //            this->addChild(menu,2);
            //Director::getInstance()->popScene();
        }
    }

//    for(int i = 0;i<index;i++){
//        Sprite* temp = v[i];
//        float x = temp->getPositionY();
//        if(x<0)
//        {      //停止判断
//            CCLOG("stop");
//            this->unscheduleUpdate();
//            //停止更新
//            this->unschedule(CC_SCHEDULE_SELECTOR(Game::updateAlphabet));
//            //停止所有监听器
//            auto dispatcher = Director::getInstance()->getEventDispatcher();
//            dispatcher->removeEventListener(keyListener);
//            //停止所有动作
//            this->stopAllActions();
//            auto over = Label::createWithTTF("Game over", "fonts/Marker Felt.ttf", 100);
//
//            over->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2+over->getContentSize().height/2));
//            this->addChild(over,2);
//            
////            auto backItem =  MenuItemImage::create("backarrow.png","backarrow.png",CC_CALLBACK_1(First::gameover, this));
////            auto menu = Menu::create(backItem ,NULL);
////            menu->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y +visibleSize.height/2.5-backItem->getContentSize().height));
////            this->addChild(menu,2);
//            //Director::getInstance()->popScene();
//        }
    
//    }
}


void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
