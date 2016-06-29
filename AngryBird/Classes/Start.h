#ifndef __START_H__
#define __START_H__

#include "cocos2d.h"

class Start : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menu1Callback(Ref* pSender);
    void SelectCheckpointCallback(Ref* pSender);
   // void update(float d);
    // implement the "static create()" method manually
    CREATE_FUNC(Start);
};

#endif // __START_H__
