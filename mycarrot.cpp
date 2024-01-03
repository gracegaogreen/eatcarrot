#include"mycarrot.h"


void mycarrot::addCarrot(Vec2 endPoint)
{//抖动动画功能
    //建立图片帧
    auto frame1 = SpriteFrame::create("carrotshake1.png", Rect(0, 0, 100, 100));//整张图片
    auto frame2 = SpriteFrame::create("carrotshake2.png", Rect(0, 0, 100, 100));
    auto frame3 = SpriteFrame::create("carrotshake3.png", Rect(0, 0, 100, 100));
    auto frame4 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame5 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame6 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame7 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    //用第4帧来创建精灵
    CarrotSprite = Sprite::createWithSpriteFrame(frame4);
    CarrotSprite->setScale(2);//放大2倍
    CarrotSprite->setPosition(Vec2(0, 0));

    this->setPosition(endPoint);//设置在路线终点
    this->addChild(CarrotSprite);
    //保存图片帧
    Vector<SpriteFrame*> array;
    array.pushBack(frame1);
    array.pushBack(frame2);
    array.pushBack(frame3);
    array.pushBack(frame4);
    array.pushBack(frame5);
    array.pushBack(frame6);
    array.pushBack(frame7);
    //利用图片帧完成抖动动画
    auto Shake = Animation::createWithSpriteFrames(array, 0.2f);
    CarrotSprite->runAction(RepeatForever::create(Animate::create(Shake)));//循环播放
    //建立upgrade按钮
    upgradeButton = cocos2d::ui::Button::create("upgrade.png");
    upgradeButton->retain();
    if (upgradeButton == nullptr || upgradeButton->getContentSize().width <= 0 || upgradeButton->getContentSize().height <= 0)
    {
        return;
    }
    else
    {
        //设置按钮大小（按倍数）
        upgradeButton->setScale(1);
        // 设置按钮位置
        upgradeButton->setPosition(Vec2(0, 50));

        // 设置按钮的回调函数
        upgradeButton->addTouchEventListener(CC_CALLBACK_2(mycarrot::upgradeButtonCallback, this));

        // 将按钮添加到场景
        this->addChild(upgradeButton, 80);
    }
    //初始化鼠标监听器
    mouseListener = EventListenerMouse::create();
    //调用回调函数
    mouseListener->onMouseMove = CC_CALLBACK_1(mycarrot::onMouseMove, this);
    //将鼠标事件监听器添加到当前场景
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

int mycarrot::gethealth() {
    return health;
}

void mycarrot::takeDamage()
{
    int count = 0;
    health = health - 1;//减去伤害值
    count++;
    

    switch (count) {
        case 1:
            CarrotSprite->setTexture("carrotbitten1.png");
        case 2:
            CarrotSprite->setTexture("carrotbitten2.png");
        case 3:
            CarrotSprite->setTexture("carrotbitten3.png");
    }
}



void mycarrot::upgradeButtonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:

            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:

            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            CarrotSprite->stopAllActions();
            CarrotSprite->setTexture("newcarrot.png");//升级萝卜
            upgradeButton->setVisible(false);
            //angeMoney(-320);
            break;
        }

        default:
            break;

    }

}

void mycarrot::onMouseMove(Event* event) {
    EventMouse* place = dynamic_cast<EventMouse*>(event);

    // 鼠标坐标
    Vec2 mousePosition = Vec2(place->getCursorX(), place->getCursorY());

    // 定义矩形范围
    Vec2 rectMin = Vec2(1230, 250);  // 矩形左下角坐标
    Vec2 rectMax = Vec2(1330, 350);  // 矩形右上角坐标
    Vec2 rectMin2 = Vec2(1650, 820);  // 矩形左下角坐标
    Vec2 rectMax2 = Vec2(1750, 920);  // 矩形右上角坐标1700 870

    // 检查鼠标是否在矩形范围内
    if ((mousePosition.x >= rectMin.x && mousePosition.x <= rectMax.x &&
        mousePosition.y >= rectMin.y && mousePosition.y <= rectMax.y) || (mousePosition.x >= rectMin2.x && mousePosition.x <= rectMax2.x &&
            mousePosition.y >= rectMin2.y && mousePosition.y <= rectMax2.y)) {
        // 鼠标在范围内
        upgradeButton->setVisible(true);  // 显示升级按钮
    }
    else {
        // 鼠标不在萝卜图标范围内
        upgradeButton->setVisible(false);//不显示升级按钮
    }
}