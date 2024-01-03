#ifndef __BOTTLE_TOWER_H__
#define __BOTTLE_TOWER_H__

#include "cocos2d.h"
#include "EnemyBase.h"

using namespace std;
USING_NS_CC;

#define CANT_PUT 0//���ܷŵĵ�λ
#define EMPTY 1//�հ׵Ŀ��Էŵĵ�λ
#define PUT 2 //�Ѿ��Ź��ĵ�λ
#define BLOCK 3//�ϰ���

class Towers : public cocos2d::Layer {
private:
    Vector<EnemyBase*> enemies;      //װ�������е���
public:
    int money = 500;//������õ�������Ʒ��������Ǯ
   static void problemLoading(const char* filename)
    {
        printf("Error while loading: %s\n", filename);
        printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
    }
    void BuyBottle(Vec2 weaponPosition);
    void BuyFan(Vec2 weaponPosition);
    void BuyPlane(Vec2 weaponPosition);
    int getcrntMoney() { return money; }
    void changeMoney(int tempMoney) { money += tempMoney; }
    Vec2 object;
    virtual bool init();
    int type[10][6];
    void map1Init();
    void map2Init();
    int Change(Vec2& position);
    CREATE_FUNC(Towers);
    //���µ��˼��ϵĺ��������������ô�����˼���
    void getEnemies(Vector<EnemyBase*> _enemies);
    //Ѱ�����Ŀ�깥���ĵ�����
    virtual void update(float dt);
    //Ѱ�������Ŀ�깥��
    void selectEnemy();
}; 
#endif // __BOTTLE_TOWER_H__#pragma once
