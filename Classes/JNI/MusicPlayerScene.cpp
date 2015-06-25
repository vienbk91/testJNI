/*
 * MusicPlayerScene.cpp
 *
 *  Created on: 7 Apr 2015
 *      Author: chu
 */

#include "MusicPlayerScene.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "jni.h" // Thu vien can thiet
#include "jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;
using namespace std;

Scene* MusicPlayer::createScene() {
	auto scene = Scene::create();
	auto layer = MusicPlayer::create();

	scene->addChild(layer);

	return scene;
}

bool MusicPlayer::init() {
	if (!Layer::init()) {
		return false;
	}

	onEnter();
	loadMusic();
	createSlider();

	// Thiet lap am luong hien tai bang voi am luong cua thiet bi
	_currentVolume = getCurrentVolume();
	_maxVolume = getMaxVolume();
	float percent = (float) _currentVolume / _maxVolume * 100.0;
	_sliderVolume->setPercent(int(roundf(percent)));
	AudioEngine::setVolume(_currentSoundId,
			(float) _currentVolume / _maxVolume);

	return true;
}

void MusicPlayer::onEnter() {
	Layer::onEnter();
	createContent();
}

void MusicPlayer::loadMusic() {
	// Doc file mp3 tu android device
	_currentSoundId = AudioEngine::play2d("/mnt/sdcard/Music/BaKeConNghe.mp3",
			false);

}

void MusicPlayer::createContent() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float baseNavigationY = visibleSize.height / 2 - 100;

	/////////////////////////////////////////////////////////////
	// NAVIGATIN MENU
	/////////////////////////////////////////////////////////////

	/////////////////////// MIDDLE

	_playBtn = MenuItemImage::create("image/128x128/m_play.png",
			"image/128x128/m_play.png",
			CC_CALLBACK_1(MusicPlayer::pauseCallback, this));
	_playBtn->setPosition(Vec2(visibleSize.width / 2, baseNavigationY));
	_playBtn->setVisible(true);

	_pauseBtn = MenuItemImage::create("image/128x128/m_pause1.png",
			"image/128x128/m_pause1.png",
			CC_CALLBACK_1(MusicPlayer::playCallback, this));
	_pauseBtn->setPosition(Vec2(visibleSize.width / 2, baseNavigationY));
	_pauseBtn->setVisible(false);

	////////////////////// RIGHT
	_loopNextBtn = MenuItemImage::create("image/128x128/m_ffw.png",
			"image/128x128/m_ffw1.png",
			CC_CALLBACK_1(MusicPlayer::loopNextCallback, this));
	_loopNextBtn->setPosition(
			Vec2(
					_pauseBtn->getPositionX()
							+ _pauseBtn->getContentSize().width / 2 + 5
							+ _loopNextBtn->getContentSize().width / 2,
					baseNavigationY));

	_nextBtn = MenuItemImage::create("image/128x128/m_last.png",
			"image/128x128/m_last1.png",
			CC_CALLBACK_1(MusicPlayer::nextCallback, this));
	_nextBtn->setPosition(
			Vec2(
					_loopNextBtn->getPositionX()
							+ _loopNextBtn->getContentSize().width / 2 + 5
							+ _nextBtn->getContentSize().width / 2,
					baseNavigationY));

	/////////////////////LEFT
	_loopPreviousBtn = MenuItemImage::create("image/128x128/m_rew.png",
			"image/128x128/m_rew1.png",
			CC_CALLBACK_1(MusicPlayer::loopPreviousCallback , this));
	_loopPreviousBtn->setPosition(
			Vec2(
					_pauseBtn->getPositionX()
							- _pauseBtn->getContentSize().width / 2 - 5
							- _loopPreviousBtn->getContentSize().width / 2,
					baseNavigationY));

	_previousBtn = MenuItemImage::create("image/128x128/m_first.png",
			"image/128x128/m_first1.png",
			CC_CALLBACK_1(MusicPlayer::previousCallback, this));
	_previousBtn->setPosition(
			Vec2(
					_loopPreviousBtn->getPositionX()
							- _loopPreviousBtn->getContentSize().width / 2 - 5
							- _previousBtn->getContentSize().width / 2,
					baseNavigationY));

	////////////////////TOP
	_foderBtn = MenuItemImage::create("image/128x128/m_folder.png",
			"image/128x128/m_folder1.png",
			CC_CALLBACK_1(MusicPlayer::foderCallback, this));
	_foderBtn->setPosition(
			Vec2(20 + _foderBtn->getContentSize().width / 2,
					visibleSize.height - 20
							- _foderBtn->getContentSize().height / 2));

	_systemBtn = MenuItemImage::create("image/128x128/m_power.png",
			"image/128x128/m_power1.png",
			CC_CALLBACK_1(MusicPlayer::systemCallback, this));
	_systemBtn->setPosition(
			Vec2(
					visibleSize.width - 10
							- _systemBtn->getContentSize().width / 2,
					visibleSize.height - 20
							- _systemBtn->getContentSize().height / 2));

	_infoBtn = MenuItemImage::create("image/128x128/m_info.png",
			"image/128x128/m_info1.png",
			CC_CALLBACK_1(MusicPlayer::infoCallback, this));
	_infoBtn->setPosition(
			Vec2(
					_systemBtn->getPositionX()
							- _systemBtn->getContentSize().width / 2 - 10
							- _infoBtn->getContentSize().width / 2,
					visibleSize.height - 20
							- _infoBtn->getContentSize().height / 2));

	Menu* menu = Menu::create(_playBtn, _pauseBtn, _loopNextBtn, _nextBtn,
			_loopPreviousBtn, _previousBtn, _foderBtn, _systemBtn, _infoBtn,
			NULL);
	menu->setPosition(Vec2::ZERO);

	addChild(menu);

	/////////////////////////////////////////////////////////////
	// TEXT LABEL
	/////////////////////////////////////////////////////////////

	_songName = Label::createWithTTF("fonts/arial.ttf", "Song Name",
			TextHAlignment::CENTER, 200);
	_songName->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	_songName->setSystemFontSize(80);

	addChild(_songName);

}

void MusicPlayer::createSlider() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// Create slideBar Song

	_sliderSong = Slider::create();
	_sliderSong->loadBarTexture("image/sliderTrack.png");
	_sliderSong->loadProgressBarTexture("image/sliderProgress.png");
	_sliderSong->loadSlidBallTextures("image/sliderThumb.png",
			"image/sliderThumb.png", "");
	_sliderSong->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
	_sliderSong->addEventListener(
			CC_CALLBACK_2(MusicPlayer::sliderSongCallback, this));
	_sliderSong->setScaleX(2.0f);
	_sliderSong->setScaleY(2.0f);
	addChild(_sliderSong);

	// Create slider bar time

	_sliderVolume = Slider::create();
	_sliderVolume->loadBarTexture("image/sliderTrack.png");
	_sliderVolume->loadProgressBarTexture("image/sliderProgress.png");
	_sliderVolume->loadSlidBallTextures("image/sliderThumb.png",
			"image/sliderThumb.png", "");
	_sliderVolume->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2 - 400));
	_sliderVolume->addEventListener(
			CC_CALLBACK_2(MusicPlayer::sliderVolumeCallback, this));
	_sliderVolume->setScaleX(2.0f);
	_sliderVolume->setScaleY(2.0f);
	addChild(_sliderVolume);

}

void MusicPlayer::playCallback(Ref* pSender) {

	log("Current Song(Play): %d ", _currentSoundId);
	AudioEngine::resume(_currentSoundId);

	_pauseBtn->setVisible(false);
	_playBtn->setVisible(true);

	log("Resume Song");
}

void MusicPlayer::pauseCallback(Ref* psender) {
	log("Current Song(Pause): %d ", _currentSoundId);
	AudioEngine::pause(_currentSoundId);

	_playBtn->setVisible(false);
	_pauseBtn->setVisible(true);

	log("Pause Song");
}

void MusicPlayer::loopNextCallback(Ref* pSender) {
	_currentTimeSong = AudioEngine::getCurrentTime(_currentSoundId);
	AudioEngine::setCurrentTime(_currentSoundId, _currentTimeSong + 50);

}

void MusicPlayer::loopPreviousCallback(Ref* pSender) {
	_currentTimeSong = AudioEngine::getCurrentTime(_currentSoundId);
	if(_currentTimeSong >= 50){
		AudioEngine::setCurrentTime(_currentSoundId, _currentTimeSong - 50);
	}

}

void MusicPlayer::nextCallback(Ref* pSender) {
}


void MusicPlayer::previousCallback(Ref* pSender) {

}

void MusicPlayer::foderCallback(Ref* pSender) {
}

void MusicPlayer::systemCallback(Ref* pSender) {
}

void MusicPlayer::infoCallback(Ref* pSender) {
}

void MusicPlayer::sliderSongCallback(Ref* pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
	}
}

void MusicPlayer::sliderVolumeCallback(Ref* pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		//Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = _sliderVolume->getPercent();
		log("Percent: %f", (float) percent);
		AudioEngine::setVolume(_currentSoundId, (float) percent / 100);
	}
}

int MusicPlayer::getCurrentVolume() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int currentVolume;
	JniMethodInfo getVolumeMethod;
	if (!JniHelper::getStaticMethodInfo(
					getVolumeMethod,
					"org/cocos2dx/cpp/SongManager"
					, "getCurrentVolumeLevel",
					"()I")) {
		log("Call Java Function Fail");
		return 0;
	}

	jint volume = (jint)getVolumeMethod.env->CallIntMethod(getVolumeMethod.classID , getVolumeMethod.methodID);
	currentVolume = (int)volume;
	getVolumeMethod.env->DeleteLocalRef(getVolumeMethod.classID);

	return currentVolume;
#endif

	return 0;
}

int MusicPlayer::getMaxVolume() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int maxVolume;
	JniMethodInfo getVolumeMethod;
	if (!JniHelper::getStaticMethodInfo(
					getVolumeMethod,
					"org/cocos2dx/cpp/JavaClass"
					, "getMaxVolumeLevel",
					"()I")) {
		log("Call Java Function Fail");
		return 0;
	}

	jint volume = (jint)getVolumeMethod.env->CallIntMethod(getVolumeMethod.classID, getVolumeMethod.methodID);
	maxVolume = (int)volume;
	getVolumeMethod.env->DeleteLocalRef(getVolumeMethod.classID);

	return maxVolume;
#endif

	return 0;
}

