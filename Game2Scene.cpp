#include"Game2Scene.h"

USING_NS_CC;
bool Game2Scene::init() {
    //添加背景图
    addgame2Background();
    //添加路径
    addgame2way();
    //添加暂停按钮
    addStop();
    //添加金钱数字栏
    addmoneyback();
    //添加萝卜
    Carrot = new mycarrot;
    Carrot->addCarrot(Vec2(1745, 880));
    addChild(Carrot, 80);
    //播放音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("homebgm.mp3", true);
    //添加显示钱数的标签
    addLabel();
    //添加实时检测钱数的调度器
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::updatescore), 0.1f);
    //添加实时检测游戏状态的调度器
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus), 0.1f, CC_REPEAT_FOREVER, 34.0f);
    //生成一个此场景钱的实例
    score = new Money;
    //怪物间隔生成，此处调用频率过快会导致加载不出来
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::createMonsterGap), 1.0f);
    GameEnd();
    //给炮塔层传入敌人数组
    scheduleUpdate();
    return true;
}

void Game2Scene::addLabel() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
    scoreLabel->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 70));
    this->addChild(scoreLabel, 3);
}
void Game2Scene::addgame2Background()
{
    // 添加背景图片
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgound3 = Sprite::create("bg3.png");//定义大背景
    if (backgound3 == nullptr) {
        return;
    }
    else {
        backgound3->setScale(1);

        backgound3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(backgound3, 2);
    }
}
void Game2Scene::addgame2way()
{
    // 添加背景图片
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto way2 = Sprite::create("way2.png");
    if (way2 == nullptr) {
        return;
    }
    else {
        way2->setScale(1);

        way2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(way2, 2);
    }
    auto rainbow = Sprite::create("rainbow2.png");
    //添加彩虹
    if (rainbow == nullptr) {
        return;
    }
    else {
        rainbow->setScale(2);

        rainbow->setPosition(Vec2(200, 850));


        this->addChild(rainbow, 3);
    }
    //添加树丛
    auto tree = Sprite::create("tree2.png");
    if (tree == nullptr) {
        return;
    }
    else {
        tree->setScale(1.3);

        tree->setPosition(Vec2(1500, 430));


        this->addChild(tree, 3);
    }
    //添加气球
    auto bollon = Sprite::create("bollon.png");
    if (bollon == nullptr) {
        return;
    }
    else {
        bollon->setScale(1.6);

        bollon->setPosition(Vec2(650, 950));


        this->addChild(bollon, 3);
    }
}
void Game2Scene::StopCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    int count = 0;
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:

            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:

            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED: {
            count++;
            if (!(count % 2)) {
                this->resume();
                StopButton->loadTextures("resume.png", "resume.png");
            }
            if (count % 2) {
                this->pause();
                StopButton->loadTextures("stop.png", "stop.png");
            }
            break;
        }

        default:
            break;

    }
}

void Game2Scene::addStop() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    StopButton = cocos2d::ui::Button::create("stop.png");
    if (StopButton == nullptr || StopButton->getContentSize().width <= 0 || StopButton->getContentSize().height <= 0)
    {
        return;
    }
    else
    {
        // 设置按钮大小（按倍数）
        StopButton->setScale(1.3);
        // 设置按钮位置
        StopButton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 70));  // 调整按钮位置

        // 设置按钮的回调函数
        StopButton->addTouchEventListener(CC_CALLBACK_2(Game2Scene::StopCallback, this));

        // 将按钮添加到场景
        this->addChild(StopButton, 3);
    }
}

void Game2Scene::addmoneyback() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto moneyback = Sprite::create("moneybg.png");//定义大背景
    if (moneyback == nullptr) {
        return;
    }
    else {
        moneyback->setScale(0.18);

        moneyback->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 70));

        this->addChild(moneyback, 3);
    }
}
void Game2Scene::showGameResultPopup(bool isVictory)
{
    // 创建一个弹窗层
    auto popupLayer = LayerColor::create(Color4B(0, 0, 0, 150));
    addChild(popupLayer, 110);

    // 创建按钮
    if (isVictory == true) {
        // 胜利时添加胜利按钮
        auto victoryButton = ui::Button::create("win.png");
        victoryButton->setScale(1.7);
        victoryButton->setPosition(Vec2(1960 / 2, 1090 / 2));
        victoryButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 点击按钮后的操作
                CCLOG("Victory button clicked!");
                // 从场景堆栈中弹出当前场景，返回到上一个场景
                Director::getInstance()->popScene();
            }
            });
        popupLayer->addChild(victoryButton,100);
    }
    if (isVictory == false) {
        // 失败时添加失败按钮
        auto defeatButton = ui::Button::create("lose.png");
        defeatButton->setScale(1.7);
        defeatButton->setPosition(Vec2(1960 / 2, 1090 / 2));
        defeatButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 点击按钮后的操作
                CCLOG("Defeat button clicked!");
                // 从场景堆栈中弹出当前场景，返回到上一个场景
                Director::getInstance()->popScene();
            }
            });
        popupLayer->addChild(defeatButton,100);
    }
}
void Game2Scene::updatescore(float dt) {
    // 在这里更新钱数
    int money = score->Money::getcrntMoney();// 假设 getmoney 是获取钱数的函数
    scoreLabel->setString(StringUtils::format(" %d", money));
}
void Game2Scene::checkGameStatus(float dt) {
    int status = GameEnd();
    if (status == 1)
    {
        // 显示获胜弹窗按钮
        showGameResultPopup(true);
        unschedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus));
    }
    if (status == 2)
    {
        // 显示失败弹窗按钮
        showGameResultPopup(false);
        unschedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus));
    }

}
void Game2Scene::createMonsterGap(float dt) {
    bool haveAlive = 0;             //判断是不是还有活着的怪
    GAP += dt;
    if (GAP >= 1.0f) {                       //间隔一秒生成一个怪物类实例
        if (MonsterNum < 30) {              //没生成足够的怪物
            if (MonsterNum < 10)
                monster = Enemy1::create();
            else if (MonsterNum >= 10 && MonsterNum < 20)
                monster = Enemy2::create();
            else if (MonsterNum >= 20 && MonsterNum < 30)
                monster = Enemy3::create();
            this->addChild(monster, 90);    //100死亡特效
            std::vector<Vec2> path;         //创建路径点
            path.push_back(Vec2(400, 870));
            path.push_back(Vec2(400, 440));
            path.push_back(Vec2(880, 440));
            path.push_back(Vec2(880, 880));
            path.push_back(Vec2(1385, 880));
            path.push_back(Vec2(1385, 560));
            path.push_back(Vec2(1230, 560));
            path.push_back(Vec2(1230, 250));
            path.push_back(Vec2(1700, 250));
            path.push_back(Vec2(1700, 870));
            monster->initE(path, Carrot);   //生成怪物
            enemies.pushBack(monster);      //生成的怪物加入容器
            GAP = 0;                        //GAP重新初始化
            MonsterNum++;
            haveAlive = 1;
        }
        else {                               //生成足够的怪物了
            for (auto enemy : enemies) {
                if (enemy->getHP() > 0)
                    haveAlive = 1;
            }
        }
        if(haveAlive)
            WalkDie();
    }
}
int Game2Scene::GameEnd() {
    bool haveAlive = 0;
    int HP = Carrot->gethealth();
    if (HP <= 0) {
        return 0;//死亡结局
    }
    for (auto enemy : enemies) {
        if (enemy->getHP() > 0)
            haveAlive = 1;
    }
    if (!haveAlive) {                 //如果没有了
        return 1;                     //传入胜利结局
    }
}

void Game2Scene::WalkDie() {
    for (auto enemy : enemies) {
        if (enemy->getHP() > 0)
            enemy->takeDamage(20, score);
    }
}

void Game2Scene::update(float dt) {
    towerLayer->getEnemies(enemies);
}

void Game2Scene::getTowerLayer(Towers* TowersLayer) {
    towerLayer = TowersLayer;
}