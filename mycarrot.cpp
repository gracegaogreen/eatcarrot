#include"mycarrot.h"


void mycarrot::addCarrot(Vec2 endPoint)
{//������������
    //����ͼƬ֡
    auto frame1 = SpriteFrame::create("carrotshake1.png", Rect(0, 0, 100, 100));//����ͼƬ
    auto frame2 = SpriteFrame::create("carrotshake2.png", Rect(0, 0, 100, 100));
    auto frame3 = SpriteFrame::create("carrotshake3.png", Rect(0, 0, 100, 100));
    auto frame4 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame5 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame6 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    auto frame7 = SpriteFrame::create("carrotshake4.png", Rect(0, 0, 100, 100));
    //�õ�4֡����������
    CarrotSprite = Sprite::createWithSpriteFrame(frame4);
    CarrotSprite->setScale(2);//�Ŵ�2��
    CarrotSprite->setPosition(Vec2(0, 0));

    this->setPosition(endPoint);//������·���յ�
    this->addChild(CarrotSprite);
    //����ͼƬ֡
    Vector<SpriteFrame*> array;
    array.pushBack(frame1);
    array.pushBack(frame2);
    array.pushBack(frame3);
    array.pushBack(frame4);
    array.pushBack(frame5);
    array.pushBack(frame6);
    array.pushBack(frame7);
    //����ͼƬ֡��ɶ�������
    auto Shake = Animation::createWithSpriteFrames(array, 0.2f);
    CarrotSprite->runAction(RepeatForever::create(Animate::create(Shake)));//ѭ������
    //����upgrade��ť
    upgradeButton = cocos2d::ui::Button::create("upgrade.png");
    upgradeButton->retain();
    if (upgradeButton == nullptr || upgradeButton->getContentSize().width <= 0 || upgradeButton->getContentSize().height <= 0)
    {
        return;
    }
    else
    {
        //���ð�ť��С����������
        upgradeButton->setScale(1);
        // ���ð�ťλ��
        upgradeButton->setPosition(Vec2(0, 50));

        // ���ð�ť�Ļص�����
        upgradeButton->addTouchEventListener(CC_CALLBACK_2(mycarrot::upgradeButtonCallback, this));

        // ����ť��ӵ�����
        this->addChild(upgradeButton, 80);
    }
    //��ʼ����������
    mouseListener = EventListenerMouse::create();
    //���ûص�����
    mouseListener->onMouseMove = CC_CALLBACK_1(mycarrot::onMouseMove, this);
    //������¼���������ӵ���ǰ����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

int mycarrot::gethealth() {
    return health;
}

void mycarrot::takeDamage()
{
    int count = 0;
    health = health - 1;//��ȥ�˺�ֵ
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
            CarrotSprite->setTexture("newcarrot.png");//�����ܲ�
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

    // �������
    Vec2 mousePosition = Vec2(place->getCursorX(), place->getCursorY());

    // ������η�Χ
    Vec2 rectMin = Vec2(1230, 250);  // �������½�����
    Vec2 rectMax = Vec2(1330, 350);  // �������Ͻ�����
    Vec2 rectMin2 = Vec2(1650, 820);  // �������½�����
    Vec2 rectMax2 = Vec2(1750, 920);  // �������Ͻ�����1700 870

    // �������Ƿ��ھ��η�Χ��
    if ((mousePosition.x >= rectMin.x && mousePosition.x <= rectMax.x &&
        mousePosition.y >= rectMin.y && mousePosition.y <= rectMax.y) || (mousePosition.x >= rectMin2.x && mousePosition.x <= rectMax2.x &&
            mousePosition.y >= rectMin2.y && mousePosition.y <= rectMax2.y)) {
        // ����ڷ�Χ��
        upgradeButton->setVisible(true);  // ��ʾ������ť
    }
    else {
        // ��겻���ܲ�ͼ�귶Χ��
        upgradeButton->setVisible(false);//����ʾ������ť
    }
}