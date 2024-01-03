#include"Game2Scene.h"

USING_NS_CC;
bool Game2Scene::init() {
    //��ӱ���ͼ
    addgame2Background();
    //���·��
    addgame2way();
    //�����ͣ��ť
    addStop();
    //��ӽ�Ǯ������
    addmoneyback();
    //����ܲ�
    Carrot = new mycarrot;
    Carrot->addCarrot(Vec2(1745, 880));
    addChild(Carrot, 80);
    //��������
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("homebgm.mp3", true);
    //�����ʾǮ���ı�ǩ
    addLabel();
    //���ʵʱ���Ǯ���ĵ�����
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::updatescore), 0.1f);
    //���ʵʱ�����Ϸ״̬�ĵ�����
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus), 0.1f, CC_REPEAT_FOREVER, 34.0f);
    //����һ���˳���Ǯ��ʵ��
    score = new Money;
    //���������ɣ��˴�����Ƶ�ʹ���ᵼ�¼��ز�����
    schedule(CC_SCHEDULE_SELECTOR(Game2Scene::createMonsterGap), 1.0f);
    GameEnd();
    //�������㴫���������
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
    // ��ӱ���ͼƬ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgound3 = Sprite::create("bg3.png");//����󱳾�
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
    // ��ӱ���ͼƬ
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
    //��Ӳʺ�
    if (rainbow == nullptr) {
        return;
    }
    else {
        rainbow->setScale(2);

        rainbow->setPosition(Vec2(200, 850));


        this->addChild(rainbow, 3);
    }
    //�������
    auto tree = Sprite::create("tree2.png");
    if (tree == nullptr) {
        return;
    }
    else {
        tree->setScale(1.3);

        tree->setPosition(Vec2(1500, 430));


        this->addChild(tree, 3);
    }
    //�������
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
        // ���ð�ť��С����������
        StopButton->setScale(1.3);
        // ���ð�ťλ��
        StopButton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 70));  // ������ťλ��

        // ���ð�ť�Ļص�����
        StopButton->addTouchEventListener(CC_CALLBACK_2(Game2Scene::StopCallback, this));

        // ����ť��ӵ�����
        this->addChild(StopButton, 3);
    }
}

void Game2Scene::addmoneyback() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto moneyback = Sprite::create("moneybg.png");//����󱳾�
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
    // ����һ��������
    auto popupLayer = LayerColor::create(Color4B(0, 0, 0, 150));
    addChild(popupLayer, 110);

    // ������ť
    if (isVictory == true) {
        // ʤ��ʱ���ʤ����ť
        auto victoryButton = ui::Button::create("win.png");
        victoryButton->setScale(1.7);
        victoryButton->setPosition(Vec2(1960 / 2, 1090 / 2));
        victoryButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // �����ť��Ĳ���
                CCLOG("Victory button clicked!");
                // �ӳ�����ջ�е�����ǰ���������ص���һ������
                Director::getInstance()->popScene();
            }
            });
        popupLayer->addChild(victoryButton,100);
    }
    if (isVictory == false) {
        // ʧ��ʱ���ʧ�ܰ�ť
        auto defeatButton = ui::Button::create("lose.png");
        defeatButton->setScale(1.7);
        defeatButton->setPosition(Vec2(1960 / 2, 1090 / 2));
        defeatButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // �����ť��Ĳ���
                CCLOG("Defeat button clicked!");
                // �ӳ�����ջ�е�����ǰ���������ص���һ������
                Director::getInstance()->popScene();
            }
            });
        popupLayer->addChild(defeatButton,100);
    }
}
void Game2Scene::updatescore(float dt) {
    // ���������Ǯ��
    int money = score->Money::getcrntMoney();// ���� getmoney �ǻ�ȡǮ���ĺ���
    scoreLabel->setString(StringUtils::format(" %d", money));
}
void Game2Scene::checkGameStatus(float dt) {
    int status = GameEnd();
    if (status == 1)
    {
        // ��ʾ��ʤ������ť
        showGameResultPopup(true);
        unschedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus));
    }
    if (status == 2)
    {
        // ��ʾʧ�ܵ�����ť
        showGameResultPopup(false);
        unschedule(CC_SCHEDULE_SELECTOR(Game2Scene::checkGameStatus));
    }

}
void Game2Scene::createMonsterGap(float dt) {
    bool haveAlive = 0;             //�ж��ǲ��ǻ��л��ŵĹ�
    GAP += dt;
    if (GAP >= 1.0f) {                       //���һ������һ��������ʵ��
        if (MonsterNum < 30) {              //û�����㹻�Ĺ���
            if (MonsterNum < 10)
                monster = Enemy1::create();
            else if (MonsterNum >= 10 && MonsterNum < 20)
                monster = Enemy2::create();
            else if (MonsterNum >= 20 && MonsterNum < 30)
                monster = Enemy3::create();
            this->addChild(monster, 90);    //100������Ч
            std::vector<Vec2> path;         //����·����
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
            monster->initE(path, Carrot);   //���ɹ���
            enemies.pushBack(monster);      //���ɵĹ����������
            GAP = 0;                        //GAP���³�ʼ��
            MonsterNum++;
            haveAlive = 1;
        }
        else {                               //�����㹻�Ĺ�����
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
        return 0;//�������
    }
    for (auto enemy : enemies) {
        if (enemy->getHP() > 0)
            haveAlive = 1;
    }
    if (!haveAlive) {                 //���û����
        return 1;                     //����ʤ�����
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