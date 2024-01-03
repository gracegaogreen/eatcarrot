#include "Game1Scene.h"

Scene* Game1Scene::createScene(){
    return Game1Scene::create();
}
bool Game1Scene::init() {
    //��ӱ���ͼ
    addgame1Background();
    //���·��
    addgame1way();
    //�����ͣ��ť
    Stop();
    //��ӽ�Ǯ������
    addmoneyback();
    //����ܲ�
    Carrot = new mycarrot;
    Carrot->addCarrot(Vec2(1280, 300));
    addChild(Carrot, 80);
    //��������
    SimpleAudioEngine::getInstance()->playBackgroundMusic("homebgm.mp3", true);
    addLabel();
    schedule(CC_SCHEDULE_SELECTOR(Game1Scene::updatescore), 0.1f);
    schedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus), 0.1f);
    //����һ���˳���Ǯ��ʵ��
    score = new Money;
    //���������ɣ��˴�����Ƶ�ʹ���ᵼ�¼��ز�����
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
    auto backgound2 = Sprite::create("bg2.png");//����󱳾�
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
    //���·��
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
    //��Ӳʺ�
    if (rainbow == nullptr) {
        return;
    }
    else {
        rainbow->setScale(2);

        rainbow->setPosition(Vec2(250,920));


        this->addChild(rainbow, 3);
    }
    //�������
    auto tree = Sprite::create("tree.png");
    if (tree== nullptr) {
        return;
    }
    else {
        tree->setScale(1.5);

        tree->setPosition(Vec2(1500, 400));


        this->addChild(tree, 3);
    }
    //�������
    auto bollon = Sprite::create("bollon.png");
    if (bollon == nullptr) {
        return;
    }
    else {
        bollon->setScale(1.7);

        bollon->setPosition(Vec2(1800, 700));


        this->addChild(bollon, 3);
    }
    //�������
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
            // �������ƶ�
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
        // ���ð�ť��С����������
        StopButton->setScale(1.3);

        // ���ð�ťλ��
        StopButton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 70));  // ������ťλ��

        // ���ð�ť�Ļص�����
        StopButton->addTouchEventListener(CC_CALLBACK_2(Game1Scene::StopCallback, this));

        // ����ť��ӵ�����
        this->addChild(StopButton, 3);
    }
}

void Game1Scene::addmoneyback() {
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

void Game1Scene::showGameResultPopup(bool isVictory)
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

void Game1Scene::updatescore(float dt) {
    int money = score->Money::getcrntMoney(); // ���� getmoney �ǻ�ȡǮ���ĺ���
    scoreLabel->setString(StringUtils::format(" %d", money));
}

void Game1Scene::checkGameStatus(float dt) {
    int status = gameEnd();
    if (status == 1)
    {
        // ��ʾ��ʤ������ť
        showGameResultPopup(true);
        unschedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus));
    }
    if (status == 2)
    {
        // ��ʾʧ�ܵ�����ť
        showGameResultPopup(false);
        unschedule(CC_SCHEDULE_SELECTOR(Game1Scene::checkGameStatus));
    }
}

void Game1Scene::createMonsterGap(float dt) {
    GAP += dt;
    if (GAP >= 1.0f)
    {//���һ������һ��������ʵ��
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
        this->addChild(monster, 90);    //100������Ч
        std::vector<Vec2> path;         //����·����
        path.push_back(Vec2(750, 1035));
        path.push_back(Vec2(1540, 1035));
        path.push_back(Vec2(1540, 690));
        path.push_back(Vec2(405, 690));
        path.push_back(Vec2(405, 330));
        path.push_back(Vec2(1190, 330));
        monster->initE(path, Carrot);   //���ɹ���
        GAP = 0;                        //GAP���³�ʼ��
        MonsterNum++;
    }
}

int Game1Scene::gameEnd() {
    int HP = Carrot->gethealth();
    if (HP <= 0) {
        
        return 0;//�������
    }
}

