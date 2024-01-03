#include "EnemyBase.h"

void EnemyBase::problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
}

void EnemyBase::takeDamage(float damage, Money* score) {
    Vec2 crntPosition = this->getPosition();//获取怪物实例相对于scene的位置

    health -= damage;//扣血

    /*受击跳红字机制*/
    auto damageRedWord = Label::create();//创建Label标签
    damageRedWord->retain();
    damageRedWord->setDimensions(150, 50);//设置矩形区域宽x高y
    //damageRedWord->setPosition(Vec2(0, this->getContentSize().height));//设置位置为怪物实例头顶

    //将整数转换为字符串
    std::stringstream ss;
    ss << damage;
    std::string damageString = ss.str();

    damageRedWord->setString(damageString);//添加内容为伤害
    damageRedWord->setTextColor(Color4B(255, 0, 0, 100));//字体颜色红色，最后一个参数是颜色浓度，不是标签透明度
    damageRedWord->setOpacity(0);//淡入操作透明度初始值必须设置为0
    damageRedWord->setSystemFontSize(30);//设置字体大小
    damageRedWord->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);//居中对齐

    //把label添加进怪物实例
    this->addChild(damageRedWord);
    //设置动画
    auto rWAFadei = FadeIn::create(0.3f);
    auto rWAScale = ScaleBy::create(0.3f, 2.0f);//第一个参数:时间 第二个参数:倍数
    auto redWordAinma = Spawn::createWithTwoActions(rWAFadei, rWAScale);
    auto redWordAinmaSeq = Sequence::create(
        redWordAinma,
        redWordAinma->reverse(),//倒转
        nullptr
    );
    damageRedWord->runAction(redWordAinmaSeq);
    /*受击跳红字机制*/

    /*受击音效功能*/
    //创建一个音效对象
    auto hitted = SimpleAudioEngine::getInstance();
    //给对象赋值
    hitted->playEffect("enemy/hitted.mp3", false, 1.0f, 0.0f, 1.0f);//file:地址,loop:true循环,pitch:frequency,pan:立体声(-1left channel),volumn:音量
    /*受击音效功能*/

    if (health <= 0)
    {
        EnemyAnima->removeFromParent();     //先移除动作动画
        healthBar->removeFromParent();      //和血条
        dieAnima(this);                     //再播放死亡动画
        score->changeMoney(value);          //传入场景的总钱数指针，然后更改其值
        unscheduleUpdate();                 //停止调度器
        //removeFromParent();                 //不能从场景中移除怪物实例
    }
    else
    {
        // 血量仍大于零时，更新血条进度：现有血量/总血量*100%
        healthBar->setPercent((health / Health) * 100.0f);
    }
}

void EnemyBase::update(float dt) {
    Vec2 currentWayPoint = wayPoints[currentWayPointIndex];//路径点存的是怪物实例的位置
    // 如果敌人接近当前路径点，切换当前路径点为下一个路径点
    float distanceToWayPoint = getPosition().distance(currentWayPoint);//获取怪物实例到当前路径点的距离
    if (distanceToWayPoint < 5.0f) {                                   //比较看是否到达路径点
        if (currentWayPointIndex < wayPoints.size() - 1) {             //判断如果没到达终点
            currentWayPointIndex++;
            currentWayPoint = wayPoints[currentWayPointIndex];         //还有下一个路径点，更新路径点
        }
        else {// 已经到达终点，可以执行相应的操作
            Carrot->takeDamage();           //啃萝卜
            unscheduleUpdate();             //停止调度器
            removeFromParent();             //移除类的实例
        }
    }
    if (health > 0 && currentWayPointIndex != wayPoints.size() && distanceToWayPoint >= 5.0f)
    {//如果没死，也没到终点，向当前路径点移动，防止到终点后抖动
        Vec2 direction = currentWayPoint - getPosition();      //计算怪物实例朝向当前路径点的方向
        direction.normalize();                                 //化单位向量
        Vec2 newPosition = getPosition() + direction * speed * dt;
        setPosition(newPosition);                              //通过setPosition而非动画队列实现移动，set的是怪物实例的位置

        updateHealthBarPosition();//直接在更新怪物位置后调用，同步更新血条
    }
}

void EnemyBase::updateHealthBarPosition() {
    //将血条位置设置为怪物脚部
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height));
}

template<typename T>
void EnemyBase::dieAnima(T* it) {
    /*死亡动画功能*/
    //建立图片帧
    auto frame0 = SpriteFrame::create("enemy/die1.1.png", Rect(0, 0, 160, 160));//整张图片
    auto frame1 = SpriteFrame::create("enemy/die1.2.png", Rect(0, 0, 160, 160));
    auto frame2 = it->ExplodeMoney();                                           //利用多态实现不同金币掉落
    //用第0帧来创建精灵
    EnemyDieAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyDieAnima->setLocalZOrder(100);//90怪物实例
    EnemyDieAnima->setScale(2);//放大2倍
    EnemyDieAnima->setPosition(Vec2(0, 0));//设置相对于it(派生类的怪物实例)的位置
    it->addChild(EnemyDieAnima);//添加进it(派生类怪物实例)里
    //保存图片帧
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    array.pushBack(frame2);
    //利用图片帧完成跳跃动画
    auto Die = Animation::createWithSpriteFrames(array, 0.2f, 1);//帧，每帧显示时间，运行次数
    auto dieAnimate = Animate::create(Die);

    // 添加一个回调动作，在动画完成后执行自定义的回调函数
    auto removeCallback = CallFunc::create([=]() {
        EnemyDieAnima->removeFromParent(); //从怪物实例移除精灵
        });

    // 创建一个序列动作，先播放动画，然后执行回调移除精灵
    auto sequence = Sequence::create(
        dieAnimate,
        removeCallback,
        nullptr
    );
    EnemyDieAnima->runAction(sequence);
    /*死亡动画功能*/
}

bool Enemy1::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*初始化区域*/
    if (!Node::init())
        return false;
    //成员变量均继承自基类，此处仅进行赋值操作
    Health = 150;                   //这类怪物血量
    health = Health;                //初始化现有血量
    speed = 150.0f;                 //这类怪物速度
    isFly = 0;                      //不是飞行怪
    value = 50;                     //怪物值多少钱
    wayPoints = _wayPoints;         //传入路径信息
    Carrot = _Carrot;               //传入当前地图萝卜实例，用于调用啃萝卜
    this->setPosition(wayPoints[0]);//设置怪物实例初始位置
    currentWayPointIndex = 1;       //初始化路径点索引为1，因为0是起点
    scheduleUpdate();               //执行默认update调度器
    /*初始化区域*/

    /*跳跃动画功能*/
    //建立图片帧
    auto frame0 = SpriteFrame::create("enemy/Enemy1.1.png", Rect(0, 0, 76, 76));//整张图片
    auto frame1 = SpriteFrame::create("enemy/Enemy1.2.png", Rect(0, 0, 76, 76));
    //用第0帧来创建精灵
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//放大2倍
    EnemyAnima->setPosition(Vec2(0, 0));//设置相对于怪物实例的位置
    this->addChild(EnemyAnima);//所有组件都作为this(怪物实例)的子节点
    //保存图片帧
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //利用图片帧完成跳跃动画
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//循环播放
    /*跳跃动画功能*/

    /*初始化血条*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //设置在怪物实例的下面
    healthBar->setPercent(100); // 初始血条显示为100%
    // 添加血条到怪物实例中
    this->addChild(healthBar);
    /*初始化血条*/
    return true;
}

bool Enemy2::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*初始化区域*/
    if (!Node::init())
        return false;
    //成员变量均继承自基类，此处仅进行赋值操作
    Health = 80;                   //这类怪物血量
    health = Health;                //初始化现有血量
    speed = 300.0f;                 //这类怪物速度
    isFly = 0;                      //不是飞行怪
    value = 75;                     //怪物值多少钱
    wayPoints = _wayPoints;         //传入路径信息
    Carrot = _Carrot;               //传入当前地图萝卜实例，用于调用啃萝卜
    this->setPosition(wayPoints[0]);//设置怪物实例初始位置
    currentWayPointIndex = 1;       //初始化路径点索引为1，因为0是起点
    scheduleUpdate();               //执行默认update调度器
    /*初始化区域*/

    /*跳跃动画功能*/
    //建立图片帧
    auto frame0 = SpriteFrame::create("enemy/Enemy2.1.png", Rect(0, 0, 70, 60));//整张图片
    auto frame1 = SpriteFrame::create("enemy/Enemy2.2.png", Rect(0, 0, 70, 60));
    //用第0帧来创建精灵
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//放大2倍
    EnemyAnima->setPosition(Vec2(0, 0));//设置相对于怪物实例的位置
    this->addChild(EnemyAnima);//所有组件都作为this(怪物实例)的子节点
    //保存图片帧
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //利用图片帧完成跳跃动画
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//循环播放
    /*跳跃动画功能*/

    /*初始化血条*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //设置在怪物实例的下面
    healthBar->setPercent(100); // 初始血条显示为100%
    // 添加血条到怪物实例中
    this->addChild(healthBar);
    /*初始化血条*/

    return true;
}

bool Enemy3::initE(std::vector<Vec2> _wayPoints, mycarrot* _Carrot) {
    /*初始化区域*/
    if (!Node::init())
        return false;
    //成员变量均继承自基类，此处仅进行赋值操作
    Health = 100;                   //这类怪物血量
    health = Health;                //初始化现有血量
    speed = 200.0f;                 //这类怪物速度
    isFly = 1;                      //是飞行怪
    value = 85;                     //怪物值多少钱
    wayPoints = _wayPoints;         //传入路径信息
    Carrot = _Carrot;               //传入当前地图萝卜实例，用于调用啃萝卜
    this->setPosition(wayPoints[0]);//设置怪物实例初始位置
    currentWayPointIndex = 1;       //初始化路径点索引为1，因为0是起点
    scheduleUpdate();               //执行默认update调度器
    /*初始化区域*/

    /*跳跃动画功能*/
    //建立图片帧
    auto frame0 = SpriteFrame::create("enemy/Enemy3.1.png", Rect(0, 0, 100, 70));//整张图片
    auto frame1 = SpriteFrame::create("enemy/Enemy3.2.png", Rect(0, 0, 100, 70));
    //用第0帧来创建精灵
    EnemyAnima = Sprite::createWithSpriteFrame(frame0);
    EnemyAnima->setScale(2);//放大2倍
    EnemyAnima->setPosition(Vec2(0, 0));//设置相对于怪物实例的位置
    this->addChild(EnemyAnima);//所有组件都作为this(怪物实例)的子节点
    //保存图片帧
    Vector<SpriteFrame*> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    //利用图片帧完成跳跃动画
    auto Jump = Animation::createWithSpriteFrames(array, 0.2f);
    EnemyAnima->runAction(RepeatForever::create(Animate::create(Jump)));//循环播放
    /*跳跃动画功能*/

    /*初始化血条*/
    healthBar = ui::LoadingBar::create("enemy/healthBar.png");
    healthBar->setPosition(Vec2(0, -EnemyAnima->getContentSize().height)); //设置在怪物实例的下面
    healthBar->setPercent(100); // 初始血条显示为100%
    // 添加血条到怪物实例中
    this->addChild(healthBar);
    /*初始化血条*/
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