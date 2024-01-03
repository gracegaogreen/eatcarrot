
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
//�ܲ���
class mycarrot :public cocos2d::Node {
public:
    Sprite* CarrotSprite;       //�ܲ���������
    bool isTakingDamage;        //�Ƿ��ڽ��ܹ���
    int health=5;                 //Ѫ��
    Button* upgradeButton;     //����������ť
    EventListenerMouse* mouseListener;//������������
public:
    //���������ĳ��������һ���ܲ�
    void addCarrot(Vec2 endPoint);
    //�ܲ��ܵ������˺�
    void takeDamage();
    //����ܲ��Ƿ��ܵ��˺�
    bool getisTakingDamage();
    //��ȡ�ܲ�����ֵ
    int gethealth();
    //������ť�Ļص�����
    void upgradeButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    //����ƶ����ܲ�λ��ʱ�Ļص�����
    void onMouseMove(Event* event);
};
#endif // __MY_CARROT_H__