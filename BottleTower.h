#ifndef __BOTTLE_TOWER_H__
#define __BOTTLE_TOWER_H__

#include "cocos2d.h"
#include "EnemyBase.h"

using namespace std;
USING_NS_CC;

#define CANT_PUT 0//不能放的点位
#define EMPTY 1//空白的可以放的点位
#define PUT 2 //已经放过的点位
#define BLOCK 3//障碍物

class Towers : public cocos2d::Layer {
private:
    Vector<EnemyBase*> enemies;      //装场上所有敌人
public:
    int money = 500;//随便设置的三个物品加起来的钱
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
    //更新敌人集合的函数，被场景调用传入敌人集合
    void getEnemies(Vector<EnemyBase*> _enemies);
    //寻找最近目标攻击的调度器
    virtual void update(float dt);
    //寻找最近的目标攻击
    void selectEnemy();
}; 
#endif // __BOTTLE_TOWER_H__#pragma once
