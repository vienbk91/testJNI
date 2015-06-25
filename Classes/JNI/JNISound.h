
#ifndef JNISOUND_H_
#define JNISOUND_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::experimental;
using namespace cocos2d::ui;


class JNISound : public Scene
{
public:
	static JNISound* createScene(int volumeLevel , int maxVolume);
	virtual bool init(int volumeLevel, int maxVolume);


	void onEnter();

private:
	MenuItemImage* playBtn;
	MenuItemImage* pauseBtn;
	void playCallback(Ref* pSender);
	void pauseCallback(Ref* pSender);

	void updateVolume(float dt);
	void sliderCallback(Ref* pSender , Slider::EventType type);

	int soundId;
	int _percent;

};


#endif /* JNISOUND_H_ */
