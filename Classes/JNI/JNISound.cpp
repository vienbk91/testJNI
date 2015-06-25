#include "JNISound.h"

USING_NS_CC;
using namespace cocos2d::experimental;
using namespace cocos2d::ui;


JNISound* JNISound::createScene(int volumeLevel , int maxVolume) {
	/////////////////////////////////////////////////////////
	// Change design resolution
	/////////////////////////////////////////////////////////

	JNISound* layer = new JNISound();
	if (layer && layer->init(volumeLevel , maxVolume)) {
		layer->autorelease();
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool JNISound::init(int volumeLevel , int maxVolume) {
	if (!Scene::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	onEnter();

	// Load sound using cocos2dx
	// Effect and music
	soundId = AudioEngine::play2d("sound/bkcn.mp3", true);

	// Create slideBer

	Slider* slider = Slider::create();
	slider->loadBarTexture("image/sliderTrack.png");
	slider->loadSlidBallTextures("image/sliderThumb.png",
			"image/sliderThumb.png", "");
	slider->loadProgressBarTexture("image/sliderProgress.png");
	slider->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	slider->addEventListener(CC_CALLBACK_2(JNISound::sliderCallback , this));
	slider->setScaleX(2.0f);
	slider->setScaleY(2.0f);
	addChild(slider);

	log("Volume currnet: %d" , volumeLevel);
	log("Volume Max: %d" , maxVolume);

	float percent = (float)volumeLevel/maxVolume*100.0;
	log("%f" , percent);
	log("%d" , int(roundf(percent)));
	slider->setPercent(int(roundf(percent)));

	AudioEngine::setVolume(soundId, (float)volumeLevel / maxVolume);

	return true;
}

void JNISound::onEnter() {
	Scene::onEnter();

	// Create Play Button
	Size visibleSize = Director::getInstance()->getVisibleSize();

	playBtn = MenuItemImage::create("image/play_icon.png",
			"image/play_icon1.png", CC_CALLBACK_1(JNISound::playCallback, this));
	playBtn->setScale(1.5f);
	playBtn->setPosition(
			Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 - 50));

	// Create Pause Button
	pauseBtn = MenuItemImage::create("image/pause_icon.png",
			"image/pause_icon1.png",
			CC_CALLBACK_1(JNISound::pauseCallback, this));
	pauseBtn->setScale(1.5f);
	pauseBtn->setPosition(
			Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 50));

	auto menu = Menu::create(playBtn, pauseBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

}

void JNISound::sliderCallback(Ref* pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(pSender);
		_percent = slider->getPercent();
		log("Percent: %f", (float) _percent);
		AudioEngine::setVolume(soundId, (float) _percent / 100);
	}
}

void JNISound::playCallback(Ref* pSender) {

	AudioEngine::pause(soundId);
	log("Pause Sound");
}

void JNISound::pauseCallback(Ref* pSender) {

	AudioEngine::resume(soundId);
	log("Resume Sound");

}


