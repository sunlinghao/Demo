#ifndef __FIRST_H__
#define __FIRST_H__

#include "cocos2d.h"
USING_NS_CC;
class First : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    bool onTouchBegan(Touch* t, Event* e);
    void onTouchMoved(Touch* t, Event* e);
    void onTouchEnded(Touch* t, Event* e);
    
    
    void initUFO();
    void updateUFO(float d);
    void update(float d);
    void gameover(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(First);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    cocos2d::Sprite* player;
    cocos2d::Label*lbl;
    SpriteBatchNode*batchNode;
    int UFOCount = 0;
    int grade = 0;

};

#endif // __FIRST_H__
