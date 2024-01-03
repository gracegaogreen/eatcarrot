#include "EnemyBase.h"

void EnemyBase::problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
}

void EnemyBase::takeDamage(float damage, Money* score) {
    Vec2 crntPosition = this->getPosition();//��ȡ����ʵ�������scene��λ��

    health -= damage;//��Ѫ

    /*�ܻ������ֻ���*/
    auto damageRedWord = Label::create();//����Label��ǩ
    damageRedWord->retain();
    damageRedWord->setDimensions(150, 50);//���þ��������x��y
    //damageRedWord->setPosition(Vec2(0, this->getContentSize().height));//����λ��Ϊ����ʵ��ͷ��

    //������ת��Ϊ�ַ���
    std::stringstream ss;
    ss << damage;
    std::string damageString = ss.str();

    damageRedWord->setString(damageString);//�������Ϊ�˺�
    damageRedWord->setTextColor(Color4B(255, 0, 0, 100));//������ɫ��ɫ�����һ����������ɫŨ�ȣ����Ǳ�ǩ͸����
    damageRedWord->setOpacity(0);//�������͸���ȳ�ʼֵ��������Ϊ0
    damageRedWord->setSystemFontSize(30);//���������С
    damageRedWord->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);//���ж���

    //��label��ӽ�����ʵ��
    this->addChild(damageRedWord);
    //���ö���
    auto rWAFadei = FadeIn::create(0.3f);
    auto rWAScale = ScaleBy::create(0.3f, 2.0f);//��һ������:ʱ�� �ڶ�������:����
    auto redWordAinma = Spawn::createWithTwoActions(rWAFadei, rWAScale);
    auto redWordAinmaSeq = Sequence::create(
        redWordAinma,
        redWordAinma->reverse(),//��ת
        nullptr
    );
    damageRedWord->runAction(redWordAinmaSeq);
    /*�ܻ������ֻ���*/

    /*�ܻ���Ч����*/
    //����һ����Ч����
    auto hitted = SimpleAudioEngine::getInstance();
    //������ֵ
    hitted->playEffect("enemy/hitted.mp3", false, 1.0f, 0.0f, 1.0f);//file:��ַ,loop:trueѭ��,pitch:frequency,pan:������(-1left channel),volumn:����
    /*�ܻ���Ч����*/

    if (health <= 0)
    {
        EnemyAnima->removeFromParent();     //���Ƴ���������
        healthBar->removeFromParent();      //��Ѫ��
        dieAnima(this);                     //�ٲ�����������
        score->changeMoney(value);          //���볡������Ǯ��ָ�룬Ȼ�������ֵ
        unscheduleUpdate();                 //ֹͣ������
        //removeFromParent();                 //���ܴӳ������Ƴ�����ʵ��
    }
    else
    {
        // Ѫ���Դ�����ʱ������Ѫ�����ȣ�����Ѫ��/��Ѫ��*100%
        healthBar->setPercent((health / Health) * 100.0f);
    }
}

void EnemyBase::update(float dt) {
    Vec2 currentWayPoint = wayPoints[currentWayPointIndex];//·�������ǹ���ʵ����λ��
    // ������˽ӽ���ǰ·���㣬�л���ǰ·����Ϊ��һ��·����
    float distanceToWayPoint = getPosition().distance(currentWayPoint);//��ȡ����ʵ������ǰ·����ľ���
    if (distanceToWayPoint < 5.0f) {                                   //�ȽϿ��Ƿ񵽴�·����
        if (currentWayPointIndex < wayPoints.size() - 1) {             //�ж����û�����յ�
            currentWayPointIndex++;
            currentWayPoint = wayPoints[currentWayPointIndex];         //������һ��·���㣬����·����
        }
        else {// �Ѿ������յ㣬����ִ����Ӧ�Ĳ���
            Carrot->takeDamage();           //���ܲ�
            unscheduleUpdate();             //ֹͣ������
            removeFromParent();             //�Ƴ����ʵ��
        }
    }
    if (health > 0 && currentWayPointIndex != wayPoints.size() && distanceToWayPoint >= 5.0f)
    {//���û����Ҳû���յ㣬��ǰ·�����ƶ�����ֹ���յ�󶶶�
        Vec2 direction = currentWayPoint - getPosition();      //�������ʵ������ǰ·����ķ���
        direction.normalize();                                 //����λ����
        Vec2 newPosition = getPosition() + direction * speed * dt;
        setPosition(newPosition);                              //ͨ��setPosition���Ƕ�������ʵ���ƶ���set���ǹ���ʵ����λ��

        updateHealthBarPosition();//ֱ���ڸ��¹���λ�ú���ã�ͬ������Ѫ��
    }
}

void EnemyBase::updateHealthBarPosition() {
    //��Ѫ��λ������Ϊ����Ų�
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height));
}

template<typename T>
void EnemyBase::dieAnima(T* it) {
    /*������������*/
    //����ͼƬ֡
    auto frame0 = SpriteFrame::create("enemy/die1.1.png", Rect(0, 0, 160, 160));//����ͼƬ
    auto frame1 = SpriteFrame::create("enemy/die1.2.png", Rect(0, 0, 160, 160));
    auto frame2 = it->ExplodeMoney();                                           //���ö�̬ʵ�ֲ�ͬ��ҵ���
    //�õ�0֡����������
    EnemyDieAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyDieAnima->setLocalZOrder(100);//90����ʵ��
    EnemyDieAnima->setScale(2);//�Ŵ�2��
    EnemyDieAnima->setPosition(Vec2(0, 0));//���������it(������Ĺ���ʵ��)��λ��
    it->addChild(EnemyDieAnima);//��ӽ�it(���������ʵ��)��
    //����ͼƬ֡
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    array.pushBack(frame2);
    //����ͼƬ֡�����Ծ����
    auto Die = Animation::createWithSpriteFrames(array, 0.2f, 1);//֡��ÿ֡��ʾʱ�䣬���д���
    auto dieAnimate = Animate::create(Die);

    // ���һ���ص��������ڶ�����ɺ�ִ���Զ���Ļص�����
    auto removeCallback = CallFunc::create([=]() {
        EnemyDieAnima->removeFromParent(); //�ӹ���ʵ���Ƴ�����
        });

    // ����һ�����ж������Ȳ��Ŷ�����Ȼ��ִ�лص��Ƴ�����
    auto sequence = Sequence::create(
        dieAnimate,
        removeCallback,
        nullptr
    );
    EnemyDieAnima->runAction(sequence);
    /*������������*/
}

bool Enemy1::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*��ʼ������*/
    if (!Node::init())
        return false;
    //��Ա�������̳��Ի��࣬�˴������и�ֵ����
    Health = 150;                   //�������Ѫ��
    health = Health;                //��ʼ������Ѫ��
    speed = 150.0f;                 //��������ٶ�
    isFly = 0;                      //���Ƿ��й�
    value = 50;                     //����ֵ����Ǯ
    wayPoints = _wayPoints;         //����·����Ϣ
    Carrot = _Carrot;               //���뵱ǰ��ͼ�ܲ�ʵ�������ڵ��ÿ��ܲ�
    this->setPosition(wayPoints[0]);//���ù���ʵ����ʼλ��
    currentWayPointIndex = 1;       //��ʼ��·��������Ϊ1����Ϊ0�����
    scheduleUpdate();               //ִ��Ĭ��update������
    /*��ʼ������*/

    /*��Ծ��������*/
    //����ͼƬ֡
    auto frame0 = SpriteFrame::create("enemy/Enemy1.1.png", Rect(0, 0, 76, 76));//����ͼƬ
    auto frame1 = SpriteFrame::create("enemy/Enemy1.2.png", Rect(0, 0, 76, 76));
    //�õ�0֡����������
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//�Ŵ�2��
    EnemyAnima->setPosition(Vec2(0, 0));//��������ڹ���ʵ����λ��
    this->addChild(EnemyAnima);//�����������Ϊthis(����ʵ��)���ӽڵ�
    //����ͼƬ֡
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //����ͼƬ֡�����Ծ����
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//ѭ������
    /*��Ծ��������*/

    /*��ʼ��Ѫ��*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //�����ڹ���ʵ��������
    healthBar->setPercent(100); // ��ʼѪ����ʾΪ100%
    // ���Ѫ��������ʵ����
    this->addChild(healthBar);
    /*��ʼ��Ѫ��*/
    return true;
}

bool Enemy2::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*��ʼ������*/
    if (!Node::init())
        return false;
    //��Ա�������̳��Ի��࣬�˴������и�ֵ����
    Health = 80;                   //�������Ѫ��
    health = Health;                //��ʼ������Ѫ��
    speed = 300.0f;                 //��������ٶ�
    isFly = 0;                      //���Ƿ��й�
    value = 75;                     //����ֵ����Ǯ
    wayPoints = _wayPoints;         //����·����Ϣ
    Carrot = _Carrot;               //���뵱ǰ��ͼ�ܲ�ʵ�������ڵ��ÿ��ܲ�
    this->setPosition(wayPoints[0]);//���ù���ʵ����ʼλ��
    currentWayPointIndex = 1;       //��ʼ��·��������Ϊ1����Ϊ0�����
    scheduleUpdate();               //ִ��Ĭ��update������
    /*��ʼ������*/

    /*��Ծ��������*/
    //����ͼƬ֡
    auto frame0 = SpriteFrame::create("enemy/Enemy2.1.png", Rect(0, 0, 70, 60));//����ͼƬ
    auto frame1 = SpriteFrame::create("enemy/Enemy2.2.png", Rect(0, 0, 70, 60));
    //�õ�0֡����������
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//�Ŵ�2��
    EnemyAnima->setPosition(Vec2(0, 0));//��������ڹ���ʵ����λ��
    this->addChild(EnemyAnima);//�����������Ϊthis(����ʵ��)���ӽڵ�
    //����ͼƬ֡
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //����ͼƬ֡�����Ծ����
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//ѭ������
    /*��Ծ��������*/

    /*��ʼ��Ѫ��*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //�����ڹ���ʵ��������
    healthBar->setPercent(100); // ��ʼѪ����ʾΪ100%
    // ���Ѫ��������ʵ����
    this->addChild(healthBar);
    /*��ʼ��Ѫ��*/

    return true;
}

bool Enemy3::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*��ʼ������*/
    if (!Node::init())
        return false;
    //��Ա�������̳��Ի��࣬�˴������и�ֵ����
    Health = 100;                   //�������Ѫ��
    health = Health;                //��ʼ������Ѫ��
    speed = 200.0f;                 //��������ٶ�
    isFly = 1;                      //�Ƿ��й�
    value = 85;                     //����ֵ����Ǯ
    wayPoints = _wayPoints;         //����·����Ϣ
    Carrot = _Carrot;               //���뵱ǰ��ͼ�ܲ�ʵ�������ڵ��ÿ��ܲ�
    this->setPosition(wayPoints[0]);//���ù���ʵ����ʼλ��
    currentWayPointIndex = 1;       //��ʼ��·��������Ϊ1����Ϊ0�����
    scheduleUpdate();               //ִ��Ĭ��update������
    /*��ʼ������*/

    /*��Ծ��������*/
    //����ͼƬ֡
    auto frame0 = SpriteFrame::create("enemy/Enemy3.1.png", Rect(0, 0, 100, 70));//����ͼƬ
    auto frame1 = SpriteFrame::create("enemy/Enemy3.2.png", Rect(0, 0, 100, 70));
    //�õ�0֡����������
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//�Ŵ�2��
    EnemyAnima->setPosition(Vec2(0, 0));//��������ڹ���ʵ����λ��
    this->addChild(EnemyAnima);//�����������Ϊthis(����ʵ��)���ӽڵ�
    //����ͼƬ֡
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //����ͼƬ֡�����Ծ����
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//ѭ������
    /*��Ծ��������*/

    /*��ʼ��Ѫ��*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //�����ڹ���ʵ��������
    healthBar->setPercent(100); // ��ʼѪ����ʾΪ100%
    // ���Ѫ��������ʵ����
    this->addChild(healthBar);
    /*��ʼ��Ѫ��*/
    return true;
}

SpriteFrame* Enemy1::ExplodeMoney() {
    return SpriteFrame::create("enemy/bjb+50.png", Rect(0, 0, 140, 100));
}

SpriteFrame* Enemy2::ExplodeMoney() {
    return SpriteFrame::create("enemy/bjb+75.png", Rect(0, 0, 140, 100));
}

SpriteFrame* Enemy3::ExplodeMoney() {
    return SpriteFrame::create("enemy/bjb+85.png", Rect(0, 0, 140, 100));
}

float EnemyBase::getHP() const {
    return health;
}

bool EnemyBase::getFly() const {
    return isFly;
}