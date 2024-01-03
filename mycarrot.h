
#ifndef __MY_CARROT_H__
#define __MY_CARROT_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Money.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;

#define DAMAGE 1
//萝卜类
class mycarrot :public cocos2d::Node {
public:
    Sprite* CarrotSprite;       //萝卜抖动动画
    bool isTakingDamage;        //是否在接受攻击
    int health=5;                 //血条
    Button* upgradeButton;     //创建升级按钮
    EventListenerMouse* mouseListener;//创建鼠标监听器
public:
    //往调用它的场景里添加一个萝卜
    void addCarrot(Vec2 endPoint);
    //萝卜受到怪物伤害
    void takeDamage();
    //检测萝卜是否受到伤害
    bool getisTakingDamage();
    //获取萝卜生命值
    int gethealth();
    //升级按钮的回调函数
    void upgradeButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    //鼠标移动到萝卜位置时的回调函数
    void onMouseMove(Event* event);
};
#endif // __MY_CARROT_H__