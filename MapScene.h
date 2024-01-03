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
    //��һ����ͼ�İ�ť
    cocos2d::ui::Button* map1;
    //�ڶ�����ͼ�İ�ť
    cocos2d::ui::Button* map2;
    //���ذ�ť
    cocos2d::ui::Button* backButton;

    virtual bool init();

    CREATE_FUNC(MapScene);

private:
    void addBackground();

    //�˴���ͼ��һ���������԰��մ�������Ĳ�ͬͼƬ����ʾ��ͬ�İ�ť Ȼʧ��
    //��ӵ�һ����������ͼ
    void addMap();
    //��ӵڶ�����������ͼ
    void addMap2();
    //��ӷ�����һ�����水ť
    void addBackButton();
    //������ť�Ļص�����
    void MapCallback1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void MapCallback2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void backButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    Towers* towerLayer;         //������
};


#endif // __MAP_SCENE_H__