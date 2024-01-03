/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "MapScene.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:

    std::string bgmFileName;

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void playBackgroundMusic();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::ui::Button* startButton;
    void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        using namespace cocos2d::ui;

        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("choose.mp3");
                // ��������ʼ ��ʼ���ŵ����Ч
                break;

            case cocos2d::ui::Widget::TouchEventType::MOVED:
                // �������ƶ�
                break;

            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                CCLOG("��ť�������");
                //�������Ĳ��� ֹͣ��ǰbgm����ת����
                CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                auto mapScene = MapScene::createScene();//�����µ�mapscene����
                Director::getInstance()->pushScene(mapScene);
                break;
            }
                                                           // ����������


            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                // ������ȡ��
                break;

            default:

                break;
        }
    }
};

#endif // __HELLOWORLD_SCENE_H__
