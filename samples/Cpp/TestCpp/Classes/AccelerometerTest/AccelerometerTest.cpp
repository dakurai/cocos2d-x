#include "AccelerometerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

//------------------------------------------------------------------
//
// AccelerometerTest
//
//------------------------------------------------------------------
AccelerometerTest::AccelerometerTest(void)
: _lastTime(0.0)
{
}

AccelerometerTest::~AccelerometerTest(void)
{
    _ball->release();
}

std::string AccelerometerTest::title()
{
    return "AccelerometerTest";
}

void AccelerometerTest::onEnter()
{
    Layer::onEnter();

    setAccelerometerEnabled(true);


    auto label = LabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y-50) );

    _ball = Sprite::create("Images/ball.png");
    _ball->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y));
    addChild(_ball);

    _ball->retain();
}

void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (_lastTime > 0.0)
//     {
//         auto ptNow = convertToUI
//     }
// 
//     _lastTime = fNow;

    auto pDir = Director::getInstance();

    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    if ( _ball == NULL ) {
        return;
    }

    auto ballSize  = _ball->getContentSize();

    auto ptNow  = _ball->getPosition();  

    ptNow.x -= acc->x ;
    ptNow.y -= acc->y ;

    FIX_POS(ptNow.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
    FIX_POS(ptNow.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
    _ball->setPosition(ptNow);
}

//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
void AccelerometerTestScene::runThisTest()
{
    auto layer = new AccelerometerTest();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
