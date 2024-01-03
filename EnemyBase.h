#pragma once
#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"            //ui 血条-Loadingbar组件
#include "SimpleAudioEngine.h"      //音效
#include "Money.h"                  //takeDamage里写死亡爆金币
#include "mycarrot.h"               //update里写接近终点扣萝卜生命值
USING_NS_CC;
using namespace CocosDenshion;      //音效

//EnemyBase是继承自cocos2d中结点类的
class EnemyBase : public cocos2d::Node {
protected:
    Sprite* EnemyAnima;         //动作动画
    Sprite* EnemyDieAnima;      //死亡动画

    float Health;               //血量属性
    float health;               //现有血量
    ui::LoadingBar* healthBar;  //血条

    bool isFly;                 //判断是否是飞行怪
    int value;                  //击败怪物后掉落的钱数

    float speed;                //移动速度
    std::vector<Vec2> wayPoints;//路径点
    int currentWayPointIndex;   //当前路径点索引

    mycarrot* Carrot;           //当前地图的萝卜实例
public:
    //纯虚函数--多态
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) = 0;

    //输出有效报错信息
    static void problemLoading(const char* filename);

    //takeDamage不是一个调度器，每次受到伤害都会调用这个函数，不必每隔一段时间执行
    void takeDamage(float damage, Money* score);

    //默认监听器完成按速度向路径点移动，并判断是否到达终点
    virtual void update(float dt);

    //更新血条位置
    void updateHealthBarPosition();
    template<typename T>

    //死亡特效
    void dieAnima(T* it);

    //死亡掉落特别帧的多态
    virtual SpriteFrame* ExplodeMoney() = 0;

    //返回生命值
    float getHP() const;

    //获取是不是飞行怪
    bool getFly() const;
};

/*---------------------------Enemy1---------------------------------*/
//override用于显式地指示该函数是在派生类中重写（覆盖）了基类中的虚函数
class Enemy1 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy1);//宏函数 生成Enemy1类的create函数
};
/*---------------------------Enemy1---------------------------------*/

/*---------------------------Enemy2---------------------------------*/
class Enemy2 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy2);//宏函数 生成Enemy1类的create函数
};
/*---------------------------Enemy2---------------------------------*/

/*---------------------------Enemy3---------------------------------*/
class Enemy3 : public EnemyBase {
public:
    virtual bool initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) override;

    virtual SpriteFrame* ExplodeMoney() override;

    CREATE_FUNC(Enemy3);//宏函数 生成Enemy1类的create函数
};
/*---------------------------Enemy3---------------------------------*/

#endif // __ENEMY_BASE_H__