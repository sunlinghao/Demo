#ifndef __LOADING_H__
#define __LOADING_H__

#include "cocos2d.h"

class Loading : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void LoadingChangeCallback(float d);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Loading);
    int count=0;
    std::string str;
};

#endif // __LOADING_H__
