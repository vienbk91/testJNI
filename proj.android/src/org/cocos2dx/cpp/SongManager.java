package org.cocos2dx.cpp;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.media.AudioManager;
import android.os.Bundle;
import android.util.Log;

public class SongManager extends Cocos2dxActivity{

	static Cocos2dxActivity _activity;
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		_activity = this;
		Log.d("onCreateJava" , "++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	}
	
	static final String MEDIA_PATH = new String("/sdcard/Music/");
	static private ArrayList<String> songsList = new ArrayList<String>();
	
	
	// Contructor
	public SongManager(){}
	
	/*
	 * Read file mp3 from sdcard and store the details in ArrayList
	 */
	public static ArrayList<String> getPlayList(){
		File home = new File(MEDIA_PATH);
		if(home.listFiles(new FileExtensionFilter()).length > 0){
			for(File file : home.listFiles(new FileExtensionFilter())){
				String song = new String();
				song = file.getName().substring(0, (file.getName().length() - 4 )); // - ".mp3"				
				// Add song
				songsList.add(song);
			}
		}
		return songsList;
	}
	
	/*
	 * Get current volume and max volume
	 */
	private static AudioManager audio;
	public static int getCurrentVolumeLevel() {
		audio = (AudioManager) getContext().getSystemService(
				Context.AUDIO_SERVICE);

		int currentVolume = audio.getStreamVolume(AudioManager.STREAM_MUSIC);
		Log.d("JNI Volume", (int) currentVolume + "");

		return (int) currentVolume; // /maxVolume
	}

	public static int getMaxVolumeLevel() {
		audio = (AudioManager) getContext().getSystemService(
				Context.AUDIO_SERVICE);

		int maxVolume = audio.getStreamMaxVolume(AudioManager.STREAM_MUSIC);

		Log.d("JNI VolumeMax ", (int) maxVolume + "");

		return (int) maxVolume;
	}
	
}

class FileExtensionFilter implements FilenameFilter{
	public boolean accept(File dir , String name){
		return (name.endsWith(".mp3") || name.endsWith(".MP3"));
	}
}
