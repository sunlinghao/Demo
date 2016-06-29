#ifndef __SELECTCHECKPOINT_H__
#define __SELECTCHECKPOINT_H__

#include "cocos2d.h"

class SelectCheckpoint : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void backCallback(cocos2d::Ref* pSender);
    
    void FirstCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(SelectCheckpoint);
};

#endif // __SELECTCHECKPOINT_H__
