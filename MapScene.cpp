#include "MapScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

USING_NS_CC;

Scene* MapScene::createScene() {
    return MapScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool MapScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //播放选择地图的bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("mapbgm.mp3", true);
    //添加背景图
    addBackground();
    //添加第一个地图缩略图
    addMap();
    //添加第二个地图缩略图
    addMap2();
    //添加返回按钮
    addBackButton();

    return true;
}

void MapScene::addBackground()
{
    // 添加背景图片
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgound1 = Sprite::create("bg1.png");//定义大背景
    if (backgound1 == nullptr) {
        problemLoading("'bg1.png'");
    }
    else {
        backgound1->setScale(1);
        //放置在屏幕左侧
        backgound1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //贴图
        this->addChild(backgound1, 1);//后面一个参数是显示优先级
    }
}
void MapScene::addMap() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    map1 = cocos2d::ui::Button::create("buttongame1.png");
    if (map1 == nullptr || map1->getContentSize().width <= 0 || map1->getContentSize().height <= 0)
    {
        problemLoading("按钮图片");
    }
    else
    {
        //设置按钮大小（按倍数）
        map1->setScale(1.3);

        // 设置按钮位置
        map1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));

        // 设置按钮的回调函数
        map1->addTouchEventListener(CC_CALLBACK_2(MapScene::MapCallback1, this));

        // 将按钮添加到场景
        this->addChild(map1, 1);
    }
}
void MapScene::addMap2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    map2 = cocos2d::ui::Button::create("buttongame2.png");
    if (map2 == nullptr || map2->getContentSize().width <= 0 || map2->getContentSize().height <= 0)
    {
        problemLoading("按钮图片");
    }
    else
    {
        //设置按钮大小（按倍数）
        map2->setScale(1.3);

        // 设置按钮位置
        map2->setPosition(Vec2((visibleSize.width / 3) * 2, visibleSize.height / 2));

        // 设置按钮的回调函数
        map2->addTouchEventListener(CC_CALLBACK_2(MapScene::MapCallback2, this));

        // 将按钮添加到场景
        this->addChild(map2, 1);
    }
}


void MapScene::addBackButton() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    backButton = cocos2d::ui::Button::create("homebutton.png");
    if (backButton == nullptr || backButton->getContentSize().width <= 0 || backButton->getContentSize().height <= 0)
    {
        problemLoading("返回按钮图片");
    }
    else
    {
        // 设置按钮大小（按倍数）
        backButton->setScale(1.5);

        // 设置按钮位置
        backButton->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 100));  // 调整按钮位置

        // 设置按钮的回调函数
        backButton->addTouchEventListener(CC_CALLBACK_2(MapScene::backButtonCallback, this));

        // 将按钮添加到场景
        this->addChild(backButton, 1);
    }
}


void MapScene::MapCallback1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    using namespace cocos2d::ui;

    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("choose.mp3");
            // 处理触摸开始 开始播放按钮音效
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // 处理触摸移动
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("按钮被点击！");
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            auto game1Scene = Game1Scene::createScene();//跳转到第一个游戏界面
            //加入炮塔层
            auto towerLayer = Towers::create();
            towerLayer->retain();
            game1Scene->addChild(towerLayer, 50);
            Director::getInstance()->replaceScene(game1Scene);
            break;
        }



        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            // 处理触摸取消
            break;

        default:

            break;
    }
}
void MapScene::MapCallback2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    using namespace cocos2d::ui;

    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("choose.mp3");
            // 处理触摸开始
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // 处理触摸移动
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("按钮被点击！");
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Game2Scene* game2Scene = Game2Scene::create();//跳转到第一个游戏界面
            //加入炮塔层
            towerLayer = Towers::create();
            towerLayer->retain();
            game2Scene->addChild(towerLayer, 50);
            Director::getInstance()->replaceScene(game2Scene);
            game2Scene->getTowerLayer(towerLayer);
            break;
        }



        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            // 处理触摸取消
            break;

        default:

            break;
    }
}
void MapScene::backButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("choose.mp3");
            // 处理触摸开始
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // 处理触摸移动
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("返回按钮被点击！");
            // 从场景堆栈中弹出当前场景，返回到上一个场景
            Director::getInstance()->popScene();
            break;


            break;
        }

        default:
            break;
    }
}