/*
 * JNICall.h
 *
 *  Created on: 2 Apr 2015
 *      Author: chu
 */

#ifndef JNICALL_H_
#define JNICALL_H_

#include <iostream>
#include "cocos2d.h"
#include "JNISound.h"
#include "MusicPlayerScene.h"

USING_NS_CC;

class JNICall: public Layer {
public:

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(JNICall);

private:

	bool cReturn;

	void button1Callback(Ref* pSender);
	void button2Callback(Ref* pSender);
	void button3Callback(Ref* pSender);
	void button4Callback(Ref* pSender);
	void button5Callback(Ref* pSender);
	void button6Callback(Ref* pSender );
	void button7Callback(Ref* pSender );
	void button8Callback(Ref* pSender );


	void jni_callVoid();
	void jni_callBool();
	void jni_callVoidWithInt(int number);
	void jni_callVoidWithJavaString(const char *cString);
	void jni_callVoidCreateDialog(const char *cTitle , const char *cMessager, const char *cOkName , const char *cCancelName);
	void jni_setVibrationDevice();

	int jni_getCurrentVolumeLevel();
	int jni_getMaxVolumeLevel();

	void jni_getMusicFileDetails();

};
#endif /* JNICALL_H_ */
