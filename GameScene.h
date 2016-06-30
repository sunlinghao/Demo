#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initword(float d);
    void update(float d);
    void updateAlphabet(float d);
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    cocos2d::SpriteBatchNode* batchNode;
    cocos2d::EventListenerKeyboard* keyListener = cocos2d::EventListenerKeyboard::create();
    std::vector<cocos2d::Sprite*> v;
    cocos2d::Map<int,cocos2d::Sprite*  >container;
     int count = 0;
    float grade = 1;
};

#endif // __GAME_SCENE_H__
