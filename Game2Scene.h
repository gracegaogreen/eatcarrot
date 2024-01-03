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
    EnemyBase* monster;             //在场景的头部声明成员变量，使其生命周期与场景一致
    Money* score;                   //指向当前关卡的钱的实例的指针
    Vector<EnemyBase*>enemies;      //装场上所有敌人
    float TIME = 0;				    //当前关卡开始时间，用于主计时器
    int GAP = 0;                    //控制间隔出怪
    int MonsterNum = 0;             //控制每种怪物的个数
    mycarrot* Carrot;               //指向一个萝卜实例的指针
    Button* StopButton;             //停止按钮
    Label* scoreLabel;              //当前总钱数显示
    Towers* towerLayer;             //炮塔层
public:
    //自定义初始化函数
    bool init();
    //初始化调用-添加一个标签
    void addLabel();
    //初始化调用-添加背景
    void  addgame2Background();
    //初始化调用-添加路径
    void  addgame2way();
    //调度器-监听
    void  StopCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    //添加暂停按钮
    void  addStop();
    //添加总钱数背景板
    void addmoneyback();
    //添加游戏结束的弹窗
    void showGameResultPopup(bool isVictory);
    // 在这里更新钱数
    void updatescore(float delta);
    //根据游戏是否结束生成对应的弹窗
    void checkGameStatus(float delta);
    //自定义调度器-负责隔1秒出怪
    void createMonsterGap(float dt);
    //创建场景
    //static cocos2d::Scene* createScene();
    //创建Game2Scene类的create宏函数
    CREATE_FUNC(Game2Scene);
    //检测游戏结束的调度器
    int GameEnd();
    //给炮塔传入敌人数组的默认调度器
    virtual void update(float dt);
    //获取当前炮塔层
    void getTowerLayer(Towers* TowersLayer);
    //测试用死亡函数
    void WalkDie();
};

#endif // __GAME2_SCENE_H__

