#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__
#include "ui/CocosGUI.h"
#include "Game1Scene.h"
#include "Game2Scene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "BottleTower.h"
using namespace CocosDenshion;


class MapScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    //第一个地图的按钮
    cocos2d::ui::Button* map1;
    //第二个地图的按钮
    cocos2d::ui::Button* map2;
    //返回按钮
    cocos2d::ui::Button* backButton;

    virtual bool init();

    CREATE_FUNC(MapScene);

private:
    void addBackground();

    //此处试图建一个函数可以按照传入参数的不同图片名显示不同的按钮 然失败
    //添加第一个背景缩略图
    void addMap();
    //添加第二个背景缩略图
    void addMap2();
    //添加返回上一个界面按钮
    void addBackButton();
    //三个按钮的回调函数
    void MapCallback1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void MapCallback2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void backButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    Towers* towerLayer;         //炮塔层
};


#endif // __MAP_SCENE_H__