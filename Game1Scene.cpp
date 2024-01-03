#include "Game1Scene.h"

Scene* Game1Scene::createScene(){
    return Game1Scene::create();
}
bool Game1Scene::init() {
    //添加背景图
    addgame1Background();
    //添加路径
    addgame1way();
    //添加暂停按钮
    Stop();
    //添加金钱数字栏
    addmoneyback();
    //添加萝卜
    Carrot = new mycarrot;
    Carrot->addCarrot(Vec2(1280, 300));
    addChild(Carrot, 80);
    //播放音乐
    SimpleAudioEngine::getInstance()->playBackgroundMusic("homebgm.mp3", true);
    addLabel();
    schedule(CC_SCHEDULE_SELECTOR(Game1Scene::updatescore), 0.1f);
    schedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus), 0.1f);
    //生成一个此场景钱的实例
    score = new Money;
    //怪物间隔生成，此处调用频率过快会导致加载不出来
    schedule(CC_SCHEDULE_SELECTOR(Game1Scene::createMonsterGap), 1.0f);
    gameEnd();
    return true;
}

void Game1Scene::addLabel() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
    scoreLabel->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 70));
    this->addChild(scoreLabel, 3);
}

void Game1Scene::addgame1Background()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgound2 = Sprite::create("bg2.png");//定义大背景
    if (backgound2 == nullptr) {
        return;
    }
    else {
        backgound2->setScale(1);

        backgound2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(backgound2, 2);
    }
}

void Game1Scene::addgame1way()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //添加路径
    auto way1 = Sprite::create("way1.png");
    if (way1 == nullptr) {
        return;
    }
    else {
        way1->setScale(1);

        way1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


        this->addChild(way1, 3);
    }
    auto rainbow = Sprite::create("rainbow.png");
    //添加彩虹
    if (rainbow == nullptr) {
        return;
    }
    else {
        rainbow->setScale(2);

        rainbow->setPosition(Vec2(250,920));


        this->addChild(rainbow, 3);
    }
    //添加树丛
    auto tree = Sprite::create("tree.png");
    if (tree== nullptr) {
        return;
    }
    else {
        tree->setScale(1.5);

        tree->setPosition(Vec2(1500, 400));


        this->addChild(tree, 3);
    }
    //添加气球
    auto bollon = Sprite::create("bollon.png");
    if (bollon == nullptr) {
        return;
    }
    else {
        bollon->setScale(1.7);

        bollon->setPosition(Vec2(1800, 700));


        this->addChild(bollon, 3);
    }
    //添加箱子
    auto box = Sprite::create("box.png");
    if (box == nullptr) {
        return;
    }
    else {
        box->setScale(1.2);

        box->setPosition(Vec2(200, 600));


        this->addChild(box, 3);
    }
}

void Game1Scene::StopCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    int count = 0;
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:

            break;

        case cocos2d::ui::Widget::TouchEventType::MOVED:
            // 处理触摸移动
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

void Game1Scene::Stop() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    StopButton = cocos2d::ui::Button::create("stop.png");
    if (StopButton == nullptr || StopButton->getContentSize().width <= 0 || StopButton->getContentSize().height <= 0) {
        return;
    }
    else
    {
        // 设置按钮大小（按倍数）
        StopButton->setScale(1.3);

        // 设置按钮位置
        StopButton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 70));  // 调整按钮位置

        // 设置按钮的回调函数
        StopButton->addTouchEventListener(CC_CALLBACK_2(Game1Scene::StopCallback, this));

        // 将按钮添加到场景
        this->addChild(StopButton, 3);
    }
}

void Game1Scene::addmoneyback() {
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

void Game1Scene::showGameResultPopup(bool isVictory)
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

void Game1Scene::updatescore(float dt) {
    int money = score->Money::getcrntMoney(); // 假设 getmoney 是获取钱数的函数
    scoreLabel->setString(StringUtils::format(" %d", money));
}

void Game1Scene::checkGameStatus(float dt) {
    int status = gameEnd();
    if (status == 1)
    {
        // 显示获胜弹窗按钮
        showGameResultPopup(true);
        unschedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus));
    }
    if (status == 2)
    {
        // 显示失败弹窗按钮
        showGameResultPopup(false);
        unschedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus));
    }
}

void Game1Scene::createMonsterGap(float dt) {
    GAP += dt;
    if (GAP >= 1.0f)
    {//间隔一秒生成一个怪物类实例
        if (MonsterNum < 10)
            monster = Enemy1::create();
        else if (MonsterNum >= 10 && MonsterNum < 20)
            monster = Enemy2::create();
        else if (MonsterNum >= 20 && MonsterNum < 30)
            monster = Enemy3::create();
        else
        {
            monster = Enemy1::create();
            MonsterNum = 0;
        }
        this->addChild(monster, 90);    //100死亡特效
        std::vector<Vec2> path;         //创建路径点
        path.push_back(Vec2(750, 1035));
        path.push_back(Vec2(1540, 1035));
        path.push_back(Vec2(1540, 690));
        path.push_back(Vec2(405, 690));
        path.push_back(Vec2(405, 330));
        path.push_back(Vec2(1190, 330));
        monster->initE(path, Carrot);   //生成怪物
        GAP = 0;                        //GAP重新初始化
        MonsterNum++;
    }
}

int Game1Scene::gameEnd() {
    int HP = Carrot->gethealth();
    if (HP <= 0) {
        
        return 0;//死亡结局
    }
}

