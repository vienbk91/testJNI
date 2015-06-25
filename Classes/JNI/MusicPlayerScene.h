/*
 * MusicPlayerScene.h
 *
 *  Created on: 7 Apr 2015
 *      Author: chu
 */

#ifndef MUSICPLAYERSCENE_H_
#define MUSICPLAYERSCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace cocos2d::experimental;
using namespace cocos2d::ui;


class MusicPlayer : public Layer
{
public:
	//////////////////////////////////////////////////////
	// Khoi tao Scene MusicPlayer
	//////////////////////////////////////////////////////
	static Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(MusicPlayer);

private:
	int _currentSoundId;
	int _currentVolume;
	int _maxVolume;
	int _percent;
	int _currentTimeSong;
	

	//////////////////////////MIDDLE
	MenuItemImage* _playBtn;
	MenuItemImage* _pauseBtn;
	/////////////////////////RIGHT
	MenuItemImage* _nextBtn;
	MenuItemImage* _loopNextBtn;
	/////////////////////////LEFT
	MenuItemImage* _previousBtn;
	MenuItemImage* _loopPreviousBtn;
	///////////////////////////TOP
	MenuItemImage* _foderBtn;
	MenuItemImage* _systemBtn;
	MenuItemImage* _infoBtn;
	//////////////////////////BOTTOM
	Slider* _sliderSong;
	Slider* _sliderVolume;
	//////////////////////////TEXT
	Label* _songName;
	Label* _songTime;

	void createContent();
	void createSlider();
	int getCurrentVolume();
	int getMaxVolume();
	void sliderSongCallback(Ref* pSender, Slider::EventType type);
	void sliderVolumeCallback(Ref* pSender, Slider::EventType type);


	void playCallback(Ref* pSender);
	void pauseCallback(Ref* pSender);
	void loopNextCallback(Ref* pSender);
	void nextCallback(Ref* pSender);
	void loopPreviousCallback(Ref* pSender);
	void previousCallback(Ref* pSender);
	void foderCallback(Ref* pSender);
	void systemCallback(Ref* pSender);
	void infoCallback(Ref* pSender);

	void loadMusic();

};


#endif /* MUSICPLAYERSCENE_H_ */
