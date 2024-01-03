#ifndef __GAME2_SCENE_H__
#define __GAME2_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "mycarrot.h"
#include "EnemyBase.h"
#include "Money.h"
#include "BottleTower.h"
USING_NS_CC;
using namespace cocos2d::ui;
#define DAMAGE 1

class Game2Scene : public Scene {
protected:
    EnemyBase* monster;             //�ڳ�����ͷ��������Ա������ʹ�����������볡��һ��
    Money* score;                   //ָ��ǰ�ؿ���Ǯ��ʵ����ָ��
    Vector<EnemyBase*>enemies;      //װ�������е���
    float TIME = 0;				    //��ǰ�ؿ���ʼʱ�䣬��������ʱ��
    int GAP = 0;                    //���Ƽ������
    int MonsterNum = 0;             //����ÿ�ֹ���ĸ���
    mycarrot* Carrot;               //ָ��һ���ܲ�ʵ����ָ��
    Button* StopButton;             //ֹͣ��ť
    Label* scoreLabel;              //��ǰ��Ǯ����ʾ
    Towers* towerLayer;             //������
public:
    //�Զ����ʼ������
    bool init();
    //��ʼ������-���һ����ǩ
    void addLabel();
    //��ʼ������-��ӱ���
    void  addgame2Background();
    //��ʼ������-���·��
    void  addgame2way();
    //������-����
    void  StopCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    //�����ͣ��ť
    void  addStop();
    //�����Ǯ��������
    void addmoneyback();
    //�����Ϸ�����ĵ���
    void showGameResultPopup(bool isVictory);
    // ���������Ǯ��
    void updatescore(float delta);
    //������Ϸ�Ƿ�������ɶ�Ӧ�ĵ���
    void checkGameStatus(float delta);
    //�Զ��������-�����1�����
    void createMonsterGap(float dt);
    //��������
    //static cocos2d::Scene* createScene();
    //����Game2Scene���create�꺯��
    CREATE_FUNC(Game2Scene);
    //�����Ϸ�����ĵ�����
    int GameEnd();
    //������������������Ĭ�ϵ�����
    virtual void update(float dt);
    //��ȡ��ǰ������
    void getTowerLayer(Towers* TowersLayer);
    //��������������
    void WalkDie();
};

#endif // __GAME2_SCENE_H__

