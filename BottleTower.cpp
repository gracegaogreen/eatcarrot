#include "BottleTower.h"
#define BOTTLE_PRICE 100
#define FAN_PRICE 160
#define PLANE_PRICE 220

#define BOTTLE_UPDATE 180
#define FAN_UPDATE 220
#define PLANE_UPDATE 260

#define BOTTLE_DELETE 80
#define FAN_DELETE 128
#define PLANE_DELETE 176

USING_NS_CC;

bool Towers::init()
{
    if (!Layer::init()) {
        return false;
    }
    //启用更新敌人位置的调度器
    //scheduleUpdate();
    //取大小和位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    map1Init();//如果是蓝色地图
    //map2Init();//如果是紫色地图
    object = Vec2(visibleSize.width / 2 + origin.x, 100);
    //贴十字空白位置
    auto blank = Sprite::create("Items.png", Rect(550, 734, 72, 72));
    if (blank == nullptr)
    {
        problemLoading("'Items.png'");
    }
    else
    {
        blank->setScale(2);
        this->addChild(blank, 2);
        blank->setVisible(false);
    }
    //贴选择图标位置
    //瓶子的选择图标
    auto choice1 = Sprite::create("bottle.png", Rect(0, 0, 81, 81));
    if (choice1 == nullptr)
    {
        problemLoading("'bottle.png'");
    }
    else
    {
        // add the sprite as a child to this layer
        this->addChild(choice1, 2);
        choice1->setScale(2);
        choice1->setVisible(false);
    }
    //风扇的选择图标
    auto choice2 = Sprite::create("Fan.png", Rect(0, 89, 81, 81));
    if (choice2 == nullptr)
    {
        problemLoading("'Fan.png'");
    }
    else
    {
        // add the sprite as a child to this layer
        this->addChild(choice2, 2);
        choice2->setScale(2);
        choice2->setVisible(false);
    }
    //飞机的选择图标
    auto choice3 = Sprite::create("plane.png", Rect(0, 1297, 81, 81));
    if (choice3 == nullptr)
    {
        problemLoading("'plane.png'");
    }
    else
    {
        // add the sprite as a child to this layer
        this->addChild(choice3, 2);
        choice3->setRotation(-90.0);
        choice3->setVisible(false);
        choice3->setScale(2);
    }

    //通过点击购买
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [visibleSize, origin, this, blank, choice1, choice2, choice3](Touch* touch, Event* event) {
        Vec2 mousePos = touch->getLocation();
        if (!blank->isVisible() && (Change(mousePos) == EMPTY)) {
            blank->setPosition(Vec2(mousePos.x, mousePos.y));
            choice1->setPosition(Vec2(mousePos.x, mousePos.y + 144)); // 设置精灵位置与鼠标位置一致
            choice2->setPosition(Vec2(mousePos.x - 162, mousePos.y + 144));
            choice3->setPosition(Vec2(mousePos.x + 162, mousePos.y + 144));
            if (getcrntMoney() < BOTTLE_PRICE)
                choice1->setTextureRect(Rect(78, 0, 81, 81));
            else
                choice1->setTextureRect(Rect(0, 0, 81, 81));
            if (getcrntMoney() < FAN_PRICE)
                choice2->setTextureRect(Rect(0, 171, 81, 81));
            else
                choice2->setTextureRect(Rect(0, 89, 81, 81));
            if (getcrntMoney() < PLANE_PRICE)
                choice3->setTextureRect(Rect(0, 1380, 81, 81));
            else
                choice3->setTextureRect(Rect(0, 1297, 81, 81));
            blank->setVisible(true);
            choice1->setVisible(true);
            choice2->setVisible(true);
            choice3->setVisible(true);
        }
        else if (blank->isVisible()) {
            Vec2 choicePos1 = choice1->getPosition();
            Vec2 choicePos2 = choice2->getPosition();
            Vec2 choicePos3 = choice3->getPosition();
            Vec2 blankPos = blank->getPosition();
            Vec2 weaponPosition = blankPos; // 选择武器的位置
            if (getcrntMoney() >= BOTTLE_PRICE && mousePos.x >= choicePos1.x - 80 && mousePos.x <= choicePos1.x + 80 && mousePos.y >= choicePos1.y - 80 && mousePos.y <= choicePos1.y + 80) {
                BuyBottle(weaponPosition);
                changeMoney(-BOTTLE_PRICE);
                blank->setVisible(false);
                choice1->setVisible(false);
                choice2->setVisible(false);
                choice3->setVisible(false);
                int j = weaponPosition.y / 182;
                int i = (weaponPosition.x - 70) / 182;
                type[i][j] = PUT;
            }
            else if (getcrntMoney() >= FAN_PRICE && mousePos.x >= choicePos2.x - 80 && mousePos.x <= choicePos2.x + 80 && mousePos.y >= choicePos2.y - 80 && mousePos.y <= choicePos2.y + 80) {
                BuyFan(weaponPosition);
                changeMoney(-FAN_PRICE);
                blank->setVisible(false);
                choice1->setVisible(false);
                choice2->setVisible(false);
                choice3->setVisible(false);
                int j = weaponPosition.y / 182;
                int i = (weaponPosition.x - 70) / 182;
                type[i][j] = PUT;
            }
            else if (getcrntMoney() >= PLANE_PRICE && mousePos.x >= choicePos3.x - 80 && mousePos.x <= choicePos3.x + 80 && mousePos.y >= choicePos2.y - 80 && mousePos.y <= choicePos2.y + 80) {
                BuyPlane(weaponPosition);
                changeMoney(-PLANE_PRICE);
                blank->setVisible(false);
                choice1->setVisible(false);
                choice2->setVisible(false);
                choice3->setVisible(false);
                int j = weaponPosition.y / 182;
                int i = (weaponPosition.x - 70) / 182;
                type[i][j] = PUT;
            }
            else {
                blank->setVisible(false);
                choice1->setVisible(false);
                choice2->setVisible(false);
                choice3->setVisible(false);
            }
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
void Towers::BuyBottle(Vec2 weaponPosition)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //贴底座
    auto bottom = Sprite::create("bottle.png", Rect(260, 74, 62, 62));
    if (bottom == nullptr)
        problemLoading("'bottle.png'");
    else {
        this->addChild(bottom, 2);
        bottom->setScale(2);
    }
    //贴最小的瓶子
    auto bottle = Sprite::create("bottle.png", Rect(461, 70, 31, 58));
    if (bottle == nullptr)
        problemLoading("'bottle.png'");
    else {
        this->addChild(bottle, 2);
        bottle->setScale(2);
    }
    //贴子弹
    auto bullet = Sprite::create("bottle.png", Rect(0, 83, 29, 36));
    if (bullet == nullptr)
        problemLoading("'bottle.png'");
    else {
        this->addChild(bullet, 2);
        bullet->setScale(2);
    }
    float angle = atan((object.x - weaponPosition.x) / (object.y - weaponPosition.y));
    if (object.y < weaponPosition.y)
        angle += 3.1415926;
    bottom->setPosition(weaponPosition);
    bottom->setVisible(true);
    bottle->setPosition(weaponPosition);
    bottle->setVisible(true);
    bottle->setRotation(angle * 180.0 / 3.1415926);
    bullet->setRotation(angle * 180.0 / 3.1415926);
    bullet->setPosition(Vec2(weaponPosition.x + 92.0 * sin(angle), weaponPosition.y + 92.0 * cos(angle)));
    auto a1 = MoveTo::create(1, object);
    auto resetPosition = MoveTo::create(0, Vec2(weaponPosition.x + 56.0 * sin(angle), weaponPosition.y + 56.0 * cos(angle)));
    auto sequence = Sequence::create(a1, resetPosition, nullptr);
    auto repeat = Repeat::create(sequence, 3.0f);
    bullet->runAction(repeat);
    bullet->setVisible(true);
    //升级
    auto upgrade = Sprite::create("Items.png");
    if (upgrade == nullptr)
        problemLoading("'Items.png'");
    else {
        upgrade->setVisible(false);
        upgrade->setPosition(Vec2(weaponPosition.x, weaponPosition.y + 144));
        this->addChild(upgrade, 2);
        upgrade->setScale(2);
    }
    //删除
    auto deleteTower = Sprite::create("Items.png", Rect(666, 575, 81, 81));
    if (deleteTower == nullptr)
        problemLoading("'Items.png'");
    else {
        deleteTower->setVisible(false);
        deleteTower->setPosition(Vec2(weaponPosition.x, weaponPosition.y - 144));
        this->addChild(deleteTower, 2);
        deleteTower->setScale(2);
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [touchListener, bottom, bottle, bullet, upgrade, deleteTower, this, weaponPosition](Touch* touch, Event* event) {
        Vec2 mousePos = touch->getLocation();
        if (getcrntMoney() >= BOTTLE_UPDATE)
            upgrade->setTextureRect(Rect(423, 71, 81, 81));
        else
            upgrade->setTextureRect(Rect(600, 656, 81, 81));
        if (!upgrade->isVisible() && !deleteTower->isVisible() && mousePos.y< weaponPosition.y + 66 && mousePos.y > weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 66 && mousePos.x > weaponPosition.x - 66) {
            upgrade->setVisible(true);
            deleteTower->setVisible(true);
        }
        else if (upgrade->isVisible() && getcrntMoney() >= BOTTLE_UPDATE && mousePos.y< weaponPosition.y + 244 && mousePos.y > weaponPosition.y + 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(-BOTTLE_UPDATE);
            bottle->setTextureRect(Rect(354, 67, 37, 63));
            bullet->setTextureRect(Rect(203, 76, 28, 55));
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        else if (deleteTower->isVisible() && mousePos.y > weaponPosition.y - 224 && mousePos.y < weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(BOTTLE_DELETE);
            int j = weaponPosition.y / 182;
            int i = (weaponPosition.x - 70) / 182;
            type[i][j] = EMPTY;
            bottle->stopAllActions();
            bottle->getParent()->removeChild(bottle);
            bottom->stopAllActions();
            bottom->getParent()->removeChild(bottom);
            bullet->stopAllActions();
            bullet->getParent()->removeChild(bullet);
            upgrade->stopAllActions();
            upgrade->getParent()->removeChild(upgrade);
            deleteTower->stopAllActions();
            deleteTower->getParent()->removeChild(deleteTower);
            auto dispatcher = Director::getInstance()->getEventDispatcher();  // 获取事件分发器
            dispatcher->removeEventListener(touchListener);  // 取消触摸监听器的注册
        }
        else if (upgrade->isVisible() && deleteTower->isVisible()) {
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Towers::BuyFan(Vec2 weaponPosition)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //贴底座
    auto bottom = Sprite::create("Fan.png", Rect(275, 184, 33, 35));
    if (bottom == nullptr)
        problemLoading("'Fan.png'");
    else {
        this->addChild(bottom, 2);
        bottom->setScale(2);
    }
    //贴扇叶
    auto leaves = Sprite::create("Fan.png", Rect(153, 189, 55, 55));
    if (leaves == nullptr)
        problemLoading("'Fan.png'");
    else {
        this->addChild(leaves, 2);
        leaves->setScale(2);
    }
    // 贴旋转的扇叶
    auto flyFan = Sprite::create("Fan.png", Rect(153, 189, 55, 55));
    if (flyFan == nullptr)
        problemLoading("'Fan.png'");
    else {
        this->addChild(flyFan, 2);
        flyFan->setScale(2);
    }
    bottom->setPosition(weaponPosition);
    bottom->setVisible(true);
    leaves->setPosition(Vec2(weaponPosition.x, weaponPosition.y + 34.0));
    leaves->setVisible(true);
    flyFan->setPosition(Vec2(weaponPosition.x, weaponPosition.y + 34.0));
    float moveDuration = 4.0f; // 移动动画持续时间
    // 创建旋转动画
    float rotateSpeed = 2880.0f; // 旋转速度（度数/秒）
    auto rotateAction = RotateBy::create(moveDuration, rotateSpeed);
    // 创建前进动画
    auto moveAction = MoveTo::create(moveDuration, Vec2(object));
    // 创建组合动作
    auto spawnAction = Spawn::create(rotateAction, moveAction, nullptr);
    // 创建重复动作
    auto repeatAction = RepeatForever::create(spawnAction);
    // 运行动画
    flyFan->runAction(repeatAction);
    /*//打到敌人的“爆炸”效果
    auto bomb = Sprite::create("Fan.png", Rect(240, 0, 62, 62));
    if (bomb == nullptr)
        problemLoading("'Fan.png'");
    else {
        bomb->setVisible(false);
        this->addChild(bomb, 0);
    }*/
    //升级
    auto upgrade = Sprite::create("Items.png");
    if (upgrade == nullptr)
        problemLoading("'Items.png'");
    else {
        upgrade->setVisible(false);
        upgrade->setPosition(Vec2(weaponPosition.x, weaponPosition.y + 166));
        this->addChild(upgrade, 2);
        upgrade->setScale(2);
    }
    //删除
    auto deleteTower = Sprite::create("Items.png", Rect(564, 1083, 81, 80));
    if (deleteTower == nullptr)
        problemLoading("'Items.png'");
    else {
        deleteTower->setVisible(false);
        deleteTower->setPosition(Vec2(weaponPosition.x, weaponPosition.y - 126));
        this->addChild(deleteTower, 2);
        deleteTower->setScale(2);
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [bottom, leaves, flyFan, upgrade, deleteTower, this, weaponPosition, touchListener](Touch* touch, Event* event) {
        Vec2 mousePos = touch->getLocation();
        if (getcrntMoney() >= FAN_UPDATE)
            upgrade->setTextureRect(Rect(522, 655, 81, 81));
        else
            upgrade->setTextureRect(Rect(588, 575, 81, 81));
        if (!upgrade->isVisible() && !deleteTower->isVisible() && mousePos.y< weaponPosition.y + 66 && mousePos.y > weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 66 && mousePos.x > weaponPosition.x - 66) {
            upgrade->setVisible(true);
            deleteTower->setVisible(true);
        }
        else if (upgrade->isVisible() && getcrntMoney() >= BOTTLE_UPDATE && mousePos.y< weaponPosition.y + 224 && mousePos.y > weaponPosition.y + 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(-FAN_UPDATE);
            leaves->setTextureRect(Rect(87, 4, 65, 65));
            flyFan->setTextureRect(Rect(87, 4, 65, 65));
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        else if (deleteTower->isVisible() && mousePos.y > weaponPosition.y - 224 && mousePos.y < weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(FAN_DELETE);
            int j = weaponPosition.y / 182;
            int i = (weaponPosition.x - 70) / 182;
            type[i][j] = EMPTY;
            leaves->stopAllActions();
            leaves->getParent()->removeChild(leaves);
            bottom->stopAllActions();
            bottom->getParent()->removeChild(bottom);
            flyFan->stopAllActions();
            flyFan->getParent()->removeChild(flyFan);
            upgrade->stopAllActions();
            upgrade->getParent()->removeChild(upgrade);
            deleteTower->stopAllActions();
            deleteTower->getParent()->removeChild(deleteTower);
            auto dispatcher = Director::getInstance()->getEventDispatcher();  // 获取事件分发器
            dispatcher->removeEventListener(touchListener);  // 取消触摸监听器的注册
        }
        else if (upgrade->isVisible() && deleteTower->isVisible()) {
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Towers::BuyPlane(Vec2 weaponPosition)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //贴底座
    auto bottom = Sprite::create("plane.png", Rect(2, 1464, 77, 75));
    if (bottom == nullptr)
        problemLoading("'plane.png'");
    else {
        this->addChild(bottom, 2);
        bottom->setScale(2);
    }
    //贴飞机
    auto plane = Sprite::create("plane.png", Rect(81, 1430, 64, 73));
    if (plane == nullptr)
        problemLoading("'plane.png'");
    else {
        this->addChild(plane, 2);
        plane->setScale(2);
    }
    // 贴激光
    auto laser = Sprite::create("plane.png", Rect(145, 0, 37, 1260));
    if (laser == nullptr)
        problemLoading("'plane.png'");
    else {
        laser->setAnchorPoint(Vec2(0.5, 0));
        laser->setVisible(false);
        this->addChild(laser, 2);
        laser->setScale(2);
    }
    float angle = atan((object.x - weaponPosition.x) / (object.y - weaponPosition.y));
    if (object.y < weaponPosition.y)
        angle += 3.1415926;
    bottom->setPosition(weaponPosition);
    bottom->setVisible(true);
    plane->setPosition(weaponPosition);
    plane->setVisible(true);
    plane->setRotation(angle * 180.0 / 3.1415926 - 90.0);
    laser->setRotation(angle * 180.0 / 3.1415926);
    laser->setPosition(Vec2(weaponPosition.x + 56.0 * sin(angle), weaponPosition.y + 56.0 * cos(angle)));
    // 定义出现和消失的延迟时间（单位：秒）
    float appearDelayTime = 1.0f;
    float disappearDelayTime = 0.8f;
    // 创建出现和消失的动作序列
    auto appearAction = Sequence::create(DelayTime::create(appearDelayTime), Show::create(), nullptr);
    auto disappearAction = Sequence::create(DelayTime::create(disappearDelayTime), Hide::create(), nullptr);
    // 创建循环动作
    auto loopAction = RepeatForever::create(Sequence::create(appearAction, disappearAction, nullptr));
    // 执行循环动作
    laser->runAction(loopAction);
    //升级
    auto upgrade = Sprite::create("Items.png");
    if (upgrade == nullptr)
        problemLoading("'Items.png'");
    else {
        upgrade->setPosition(Vec2(weaponPosition.x, weaponPosition.y + 148));
        upgrade->setVisible(false);
        this->addChild(upgrade, 2);
        upgrade->setScale(2);
    }
    //删除
    auto deleteTower = Sprite::create("Items.png", Rect(505, 1246, 81, 81));
    if (deleteTower == nullptr)
        problemLoading("'Items.png'");
    else {
        deleteTower->setVisible(false);
        deleteTower->setPosition(Vec2(weaponPosition.x, weaponPosition.y - 158));
        this->addChild(deleteTower, 2);
        deleteTower->setScale(2);
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [bottom, deleteTower, touchListener, plane, laser, upgrade, this, weaponPosition](Touch* touch, Event* event) {
        Vec2 mousePos = touch->getLocation();
        if (getcrntMoney() >= PLANE_UPDATE)
            upgrade->setTextureRect(Rect(510, 559, 81, 81));
        else
            upgrade->setTextureRect(Rect(498, 403, 81, 81));
        if (!upgrade->isVisible() && !deleteTower->isVisible() && mousePos.y< weaponPosition.y + 66 && mousePos.y > weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 66 && mousePos.x > weaponPosition.x - 66) {
            upgrade->setVisible(true);
            deleteTower->setVisible(true);
        }
        else if (upgrade->isVisible() && getcrntMoney() >= BOTTLE_UPDATE && mousePos.y< weaponPosition.y + 244 && mousePos.y > weaponPosition.y + 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(-PLANE_UPDATE);
            laser->setTextureRect(Rect(0, 0, 73, 1260));
            plane->setTextureRect(Rect(81, 1357, 64, 73));
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        else if (deleteTower->isVisible() && mousePos.y > weaponPosition.y - 224 && mousePos.y < weaponPosition.y - 66 && mousePos.x< weaponPosition.x + 82 && mousePos.x > weaponPosition.x - 82) {
            changeMoney(PLANE_DELETE);
            int j = weaponPosition.y / 182;
            int i = (weaponPosition.x - 70) / 182;
            type[i][j] = EMPTY;
            plane->stopAllActions();
            plane->getParent()->removeChild(plane);
            bottom->stopAllActions();
            bottom->getParent()->removeChild(bottom);
            laser->stopAllActions();
            laser->getParent()->removeChild(laser);
            upgrade->stopAllActions();
            upgrade->getParent()->removeChild(upgrade);
            deleteTower->stopAllActions();
            deleteTower->getParent()->removeChild(deleteTower);
            auto dispatcher = Director::getInstance()->getEventDispatcher();  // 获取事件分发器
            dispatcher->removeEventListener(touchListener);  // 取消触摸监听器的注册
        }
        else if (upgrade->isVisible() && deleteTower->isVisible()) {
            upgrade->setVisible(false);
            deleteTower->setVisible(false);
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Towers::map1Init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == 4 && i != 8)
                type[i][j] = EMPTY;
            else if (j == 2 && i != 1)
                type[i][j] = EMPTY;
            else if (j == 0 && i != 0 && i != 1 && i != 7 && i != 8 || i != 9)
                type[i][j] = BLOCK;
            else if (j == 1 && (i == 7))
                type[i][j] = BLOCK;
            else if (j == 3 && (i == 0 || i == 9))
                type[i][j] = BLOCK;
            else if (j == 5 && (i == 0 || i == 1 || i == 2 || i == 9))
                type[i][j] = BLOCK;
            else
                type[i][j] = CANT_PUT;
        }
    }
}

void Towers::map2Init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == 1 && i <= 5)
                type[i][j] = EMPTY;
            else if (j == 2 && i == 7)
                type[i][j] = EMPTY;
            else if (j == 3 && (i == 0 || i == 2 || i == 3 || i == 5 || i == 8))
                type[i][j] = EMPTY;
            else if (j == 0 && i >= 3 && i <= 7)
                type[i][j] = BLOCK;
            else if (j == 2 && (i == 0 || i == 5 || i == 8))
                type[i][j] = BLOCK;
            else if (j == 4 && (i == 0 || i == 2 || i == 3 || i == 8))
                type[i][j] = BLOCK;
            else if (j == 5)
                type[i][j] = BLOCK;
            else
                type[i][j] = CANT_PUT;
        }
    }
}

int Towers::Change(Vec2& position) {
    int i, j;
    j = position.y / 182;
    i = (position.x - 70) / 182;
    if (i > 9)
        return CANT_PUT;
    position.y = j * 182 + 91;
    position.x = i * 182 + 161;
    return type[i][j];
}

void Towers::getEnemies(Vector<EnemyBase*> _enemies) {
    enemies = _enemies;
}

void Towers::update(float dt) {
    selectEnemy();
}

void Towers::selectEnemy() {
    float minDistance = INT_MAX;            //最近距离
    EnemyBase* minDistanceEnemy = nullptr;  //最近敌人
    for (auto enemy : enemies) {
        if (enemy->getHP() > 0) {
            //离萝卜的距离
            float distanceToTower = enemy->getPosition().distance(Vec2(1745, 880));
            if (distanceToTower < minDistance) {
                minDistance = distanceToTower;  //更新最近距离
                minDistanceEnemy = enemy;       //更新最近敌人
            }
        }
    }
    if (minDistanceEnemy != nullptr)
        object = minDistanceEnemy->getPosition();
}