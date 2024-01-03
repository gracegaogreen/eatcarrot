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
    //����ѡ���ͼ��bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("mapbgm.mp3", true);
    //��ӱ���ͼ
    addBackground();
    //��ӵ�һ����ͼ����ͼ
    addMap();
    //��ӵڶ�����ͼ����ͼ
    addMap2();
    //��ӷ��ذ�ť
    addBackButton();

    return true;
}

void MapScene::addBackground()
{
    // ��ӱ���ͼƬ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgound1 = Sprite::create("bg1.png");//����󱳾�
    if (backgound1 == nullptr) {
        problemLoading("'bg1.png'");
    }
    else {
        backgound1->setScale(1);
        //��������Ļ���
        backgound1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //��ͼ
        this->addChild(backgound1, 1);//����һ����������ʾ���ȼ�
    }
}
void MapScene::addMap() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    map1 = cocos2d::ui::Button::create("buttongame1.png");
    if (map1 == nullptr || map1->getContentSize().width <= 0 || map1->getContentSize().height <= 0)
    {
        problemLoading("��ťͼƬ");
    }
    else
    {
        //���ð�ť��С����������
        map1->setScale(1.3);

        // ���ð�ťλ��
        map1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));

        // ���ð�ť�Ļص�����
        map1->addTouchEventListener(CC_CALLBACK_2(MapScene::MapCallback1, this));

        // ����ť��ӵ�����
        this->addChild(map1, 1);
    }
}
void MapScene::addMap2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    map2 = cocos2d::ui::Button::create("buttongame2.png");
    if (map2 == nullptr || map2->getContentSize().width <= 0 || map2->getContentSize().height <= 0)
    {
        problemLoading("��ťͼƬ");
    }
    else
    {
        //���ð�ť��С����������
        map2->setScale(1.3);

        // ���ð�ťλ��
        map2->setPosition(Vec2((visibleSize.width / 3) * 2, visibleSize.height / 2));

        // ���ð�ť�Ļص�����
        map2->addTouchEventListener(CC_CALLBACK_2(MapScene::MapCallback2, this));

        // ����ť��ӵ�����
        this->addChild(map2, 1);
    }
}


void MapScene::addBackButton() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    backButton = cocos2d::ui::Button::create("homebutton.png");
    if (backButton == nullptr || backButton->getContentSize().width <= 0 || backButton->getContentSize().height <= 0)
    {
        problemLoading("���ذ�ťͼƬ");
    }
    else
    {
        // ���ð�ť��С����������
        backButton->setScale(1.5);

        // ���ð�ťλ��
        backButton->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 100));  // ������ťλ��

        // ���ð�ť�Ļص�����
        backButton->addTouchEventListener(CC_CALLBACK_2(MapScene::backButtonCallback, this));

        // ����ť��ӵ�����
        this->addChild(backButton, 1);
    }
}


void MapScene::MapCallback1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    using namespace cocos2d::ui;

    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("choose.mp3");
            // ��������ʼ ��ʼ���Ű�ť��Ч
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // �������ƶ�
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("��ť�������");
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            auto game1Scene = Game1Scene::createScene();//��ת����һ����Ϸ����
            //����������
            auto towerLayer = Towers::create();
            towerLayer->retain();
            game1Scene->addChild(towerLayer, 50);
            Director::getInstance()->replaceScene(game1Scene);
            break;
        }



        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            // ������ȡ��
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
            // ��������ʼ
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // �������ƶ�
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("��ť�������");
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Game2Scene* game2Scene = Game2Scene::create();//��ת����һ����Ϸ����
            //����������
            towerLayer = Towers::create();
            towerLayer->retain();
            game2Scene->addChild(towerLayer, 50);
            Director::getInstance()->replaceScene(game2Scene);
            game2Scene->getTowerLayer(towerLayer);
            break;
        }



        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            // ������ȡ��
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
            // ��������ʼ
            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // �������ƶ�
            break;

        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CCLOG("���ذ�ť�������");
            // �ӳ�����ջ�е�����ǰ���������ص���һ������
            Director::getInstance()->popScene();
            break;


            break;
        }

        default:
            break;
    }
}