#pragma once
#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"            //ui Ѫ��-Loadingbar���
#include "SimpleAudioEngine.h"      //��Ч
#include "Money.h"                  //takeDamage��д���������
#include "mycarrot.h"               //update��д�ӽ��յ���ܲ�����ֵ
USING_NS_CC;
using namespace CocosDenshion;      //��Ч

//EnemyBase�Ǽ̳���cocos2d�н�����
class EnemyBase : public cocos2d::Node {
protected:
    Sprite* EnemyAnima;         //��������
    Sprite* EnemyDieAnima;      //��������

    float Health;               //Ѫ������
    float health;               //����Ѫ��
    ui::LoadingBar* healthBar;  //Ѫ��

    bool isFly;                 //�ж��Ƿ��Ƿ��й�
    int value;                  //���ܹ��������Ǯ��

    float speed;                //�ƶ��ٶ�
    std::vector<Vec2> wayPoints;//·����
    int currentWayPointIndex;   //��ǰ·��������

    mycarrot* Carrot;           //��ǰ��ͼ���ܲ�ʵ��
public:
    //���麯��--��̬
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) = 0;

    //�����Ч������Ϣ
    static void problemLoading(const char* filename);

    //takeDamage����һ����������ÿ���ܵ��˺���������������������ÿ��һ��ʱ��ִ��
    void takeDamage(float damage, Money* score);

    //Ĭ�ϼ�������ɰ��ٶ���·�����ƶ������ж��Ƿ񵽴��յ�
    virtual void update(float dt);

    //����Ѫ��λ��
    void updateHealthBarPosition();
    template<typename T>

    //������Ч
    void dieAnima(T* it);

    //���������ر�֡�Ķ�̬
    virtual SpriteFrame* ExplodeMoney() = 0;

    //��������ֵ
    float getHP() const;

    //��ȡ�ǲ��Ƿ��й�
    bool getFly() const;
};

/*---------------------------Enemy1---------------------------------*/
//override������ʽ��ָʾ�ú�����������������д�����ǣ��˻����е��麯��
class Enemy1 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy1);//�꺯�� ����Enemy1���create����
};
/*---------------------------Enemy1---------------------------------*/

/*---------------------------Enemy2---------------------------------*/
class Enemy2 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy2);//�꺯�� ����Enemy1���create����
};
/*---------------------------Enemy2---------------------------------*/

/*---------------------------Enemy3---------------------------------*/
class Enemy3 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy3);//�꺯�� ����Enemy1���create����
};
/*---------------------------Enemy3---------------------------------*/

#endif // __ENEMY_BASE_H__