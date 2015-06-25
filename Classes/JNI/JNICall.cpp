/*
 * JNICall.cpp
 *
 *  Created on: 2 Apr 2015
 *      Author: chu
 */

#include "JNICall.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "jni.h" // Thu vien can thiet
#include "jni/JniHelper.h"
#include <android/log.h>

#endif

Scene* JNICall::createScene() {
	auto scene = Scene::create();
	auto layer = JNICall::create();

	scene->addChild(layer);

	return scene;
}

bool JNICall::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* button1 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button1Callback , this));
	button1->setScale(3);
	button1->setPosition(
			Vec2(visibleSize.width / 2 - 300, visibleSize.height / 2 + 100));

	MenuItemImage* button2 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button2Callback , this));
	button2->setScale(3);
	button2->setPosition(
			Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 100));

	MenuItemImage* button3 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button3Callback , this));
	button3->setScale(3);
	button3->setPosition(
			Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 100));

	MenuItemImage* button4 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button4Callback , this));
	button4->setScale(3);
	button4->setPosition(
			Vec2(visibleSize.width / 2 + 300, visibleSize.height / 2 + 100));

	MenuItemImage* button5 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button5Callback , this));
	button5->setScale(3);
	button5->setPosition(
			Vec2(visibleSize.width / 2 - 300, visibleSize.height / 2 - 200));

	MenuItemImage* button6 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button6Callback , this));
	button6->setScale(3);
	button6->setPosition(
			Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 200));

	MenuItemImage* button7 = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", CC_CALLBACK_1(JNICall::button7Callback , this));
	button7->setScale(3);
	button7->setPosition(
			Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 200));

	MenuItemImage* button8 = MenuItemImage::create("CloseNormal.png",
				"CloseSelected.png", CC_CALLBACK_1(JNICall::button8Callback , this));
	button8->setScale(3);
	button8->setPosition(
				Vec2(visibleSize.width / 2 + 300, visibleSize.height / 2 - 200));

	auto menu = Menu::create(button1, button2, button3, button4, button5,
			button6, button7, button8 , NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
// SET CALLBACK
////////////////////////////////////////////////////////////////////////////////////////

void JNICall::button1Callback(Ref* pSender) {
	jni_callVoid();
}

void JNICall::button2Callback(Ref* pSender) {
	jni_callBool();
	if (cReturn == true)
		log("true");
	if (cReturn == false)
		log("false");
}

void JNICall::button3Callback(Ref* pSender) {
	jni_callVoidWithInt(10);
}

void JNICall::button4Callback(Ref* pSender) {
	jni_callVoidWithJavaString("Toi la Vien");
}

void JNICall::button5Callback(Ref* pSender) {
	jni_callVoidCreateDialog("Dialog", "Messager", "OK", "Cancel");
}

void JNICall::button6Callback(Ref* pSender) {
	jni_setVibrationDevice();
}

void JNICall::button7Callback(Ref* pSender) {
	// Lay gia tri cua volum cua may
	int volumeLevel , maxLevel;
	volumeLevel = jni_getCurrentVolumeLevel();
	log("Volume current : %d " , volumeLevel);

	maxLevel = jni_getMaxVolumeLevel();
	log("Volume Max: %d " , maxLevel);

	Director::getInstance()->replaceScene(JNISound::createScene(volumeLevel , maxLevel));
}

void JNICall::button8Callback(Ref* pSender) {
	// Lay gia tri cua volum cua may
	Director::getInstance()->replaceScene(MusicPlayer::createScene());
}

////////////////////////////////////////////////////////////////////////////////////////
// CALL JNI FUNCTUON
////////////////////////////////////////////////////////////////////////////////////////

void JNICall::jni_callVoid() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo methodInfo;
	if(!JniHelper::getStaticMethodInfo(methodInfo
					, "org/cocos2dx/cpp/JavaClass" // Lop Java duoc goi den
					, "alertJNI"// Ten cua ham java
					, "()V"))// Doi so va kieu tra ve cua phuong thuc ben lop Java
	{
		log("Call Java Function False");
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID , methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

#endif
}

void JNICall::jni_callBool() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	cocos2d::JniMethodInfo boolMethod;
	if (!JniHelper::getStaticMethodInfo(boolMethod
					, "org/cocos2dx/cpp/JavaClass" // Lop Java duoc goi den
					, "boolJNI"// Ten cua ham java
					, "()Z"))// Doi so va kieu tra ve cua phuong thuc ben lop Java
	{
		log("Call Java Function Fail");
		return;
	}

	// Kieu du lieu duoc lay tu java la jboolean
	jboolean jReturn = (jboolean)boolMethod.env->CallStaticBooleanMethod(
			boolMethod.classID
			,boolMethod.methodID);

	boolMethod.env->DeleteLocalRef(boolMethod.classID);

	// Convert ve kieu cua C++
	cReturn = (bool)jReturn;

#endif
}

void JNICall::jni_callVoidWithInt(int number) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo intMethod;
	if(!JniHelper::getStaticMethodInfo(intMethod
					, "org/cocos2dx/cpp/JavaClass"
					, "intJNI"
					, "(I)V")) {
		log("Call Java Function Fail");
		return;
	}

	intMethod.env->CallVoidMethod(intMethod.classID , intMethod.methodID , number);
	intMethod.env->DeleteLocalRef(intMethod.classID);
#endif
}

void JNICall::jni_callVoidWithJavaString(const char *cString) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo stringMethod;
	if(!JniHelper::getStaticMethodInfo(stringMethod
					, "org/cocos2dx/cpp/JavaClass"
					, "stringJNI"
					, "(Ljava/lang/String;)V")) {
		log("Call Java Function Fail");
		return;
	}

	// Phai convert kieu truoc khi truyen tham so den Java
	jstring stringJava = stringMethod.env->NewStringUTF(cString);

	stringMethod.env->CallVoidMethod(stringMethod.classID , stringMethod.methodID , stringJava);
	stringMethod.env->DeleteLocalRef(stringMethod.classID);
	stringMethod.env->DeleteLocalRef(stringJava);
#endif
}

void JNICall::jni_callVoidCreateDialog(const char *cTitle,
		const char *cMessager, const char *cOkName, const char *cCancelName) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) // won't compile this part if IOS
	////////////////////////////////////////////////////////////////
	//Check Call back
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// Thuc hien truyen tham so
	////////////////////////////////////////////////////////////////
	JniMethodInfo minfo;
	if(JniHelper::getStaticMethodInfo(minfo
					, "org/cocos2dx/cpp/JavaClass"
					, "createDialogJNI"
					, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
	{
		// Convert tham so truyen vao ham sang kieu cua Java
		jstring javaTitle = minfo.env->NewStringUTF(cTitle);
		jstring javaMessager = minfo.env->NewStringUTF(cMessager);
		jstring javaOkName = minfo.env->NewStringUTF(cOkName);
		jstring javaCancelName = minfo.env->NewStringUTF(cCancelName);

		minfo.env->CallVoidMethod(minfo.classID , minfo.methodID , javaTitle , javaMessager , javaOkName , javaCancelName);
		minfo.env->DeleteLocalRef(javaTitle);
		minfo.env->DeleteLocalRef(javaMessager);
		minfo.env->DeleteLocalRef(javaOkName);
		minfo.env->DeleteLocalRef(javaCancelName);
	}
#endif
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_JavaClass_onMessagerCallback(
			JNIEnv* env, jobject thiz, jint jNum) {
		log("%d", int(jNum));
		log("This is code in C");
		env->DeleteLocalRef(thiz);
	}
}
#endif

void JNICall::jni_setVibrationDevice() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo methodInfo;
	if(!JniHelper::getStaticMethodInfo(methodInfo
					, "org/cocos2dx/cpp/JavaClass" // Lop Java duoc goi den
					, "vibrationJNI"// Ten cua ham java
					, "()V"))// Doi so va kieu tra ve cua phuong thuc ben lop Java
	{
		log("Call Java Function False");
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID , methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

#endif
}

int JNICall::jni_getCurrentVolumeLevel() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int volumeLevel;
	JniMethodInfo getVolumeMethod;
	if (!JniHelper::getStaticMethodInfo(
			getVolumeMethod,
			"org/cocos2dx/cpp/JavaClass"
			, "getCurrentVolumeLevel",
			"()I")) {
		log("Call Java Function Fail");
		return 0;
	}

	jint volume = (jint)getVolumeMethod.env->CallIntMethod(getVolumeMethod.classID , getVolumeMethod.methodID);
	volumeLevel = (int)volume;
	getVolumeMethod.env->DeleteLocalRef(getVolumeMethod.classID);

	return volumeLevel;
#endif

	return 0;
}

int JNICall::jni_getMaxVolumeLevel() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	int volumeLevel;
	JniMethodInfo getVolumeMethod;
	if (!JniHelper::getStaticMethodInfo(
			getVolumeMethod,
			"org/cocos2dx/cpp/JavaClass"
			, "getMaxVolumeLevel",
			"()I")) {
		log("Call Java Function Fail");
		return 0;
	}

	jint volume = (jint)getVolumeMethod.env->CallIntMethod(getVolumeMethod.classID , getVolumeMethod.methodID);
	volumeLevel = (int)volume;
	getVolumeMethod.env->DeleteLocalRef(getVolumeMethod.classID);

	return volumeLevel;
#endif

	return 0;
}


void JNICall::jni_getMusicFileDetails()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo songDetails;
	std::vector<std::string> cArray;

	if(!JniHelper::getStaticMethodInfo(songDetails
			, "org/cocos2dx/cpp/SongManager"
			, "getPlayList"
			, "()Ljava/lang/Object;"))
	{
		log("Call Java Function Fail");
		return;
	}

	jobjectArray jArray = (jobjectArray)songDetails.env->CallObjectMethod(songDetails.classID , songDetails.methodID);
	songDetails.env->DeleteLocalRef(songDetails.classID);

#endif
}

