package org.cocos2dx.cpp;

import java.util.regex.Pattern;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import android.R.bool;
import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Vibrator;
import android.util.Log;
import android.util.Patterns;
import android.view.View;

public class JavaClass extends Cocos2dxActivity {
	
	static Cocos2dxActivity _activity;


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		_activity = this;
		Log.d("onCreateJava", "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		
	}
	

	
	// Ham Java khong co doi so truyen vao
	public static void alertJNI() {

		Log.d("JNI Void", " Showing alert dialog I've been called from C++ ");

		Log.d("Device OS", java.lang.System.getProperty("os.name"));
		Log.d("Version OS", System.getProperty("os.version"));
		Log.d("Architecture", System.getProperty("os.arch"));
		Log.d("SDK Version", Build.VERSION.RELEASE);

		Pattern emailPattern = Patterns.EMAIL_ADDRESS; // API level 8+
		Account[] accounts = AccountManager.get(getContext()).getAccounts();
		for (Account account : accounts) {
			if (emailPattern.matcher(account.name).matches()) {
				String email = account.name;
				Log.d("Email", email);
			}
		}

		String driveName = getDeviceName();
		Log.d("Device Name", driveName);

		// Vibration cancel
		/*
		 * Vibrator vib = (Vibrator)
		 * getContext().getSystemService(Context.VIBRATOR_SERVICE);
		 * vib.cancel(); Log.d("JNI Vibration" , "Vibration Cancel");
		 */
	}

	/*
	 * Ham lay ten thiet bi
	 */
	public static String getDeviceName() {
		String manufacturer = Build.MANUFACTURER;
		String model = Build.MODEL;
		if (model.startsWith(manufacturer)) {
			return capitalize(model);
		} else {
			return capitalize(manufacturer) + " " + model;
		}
	}

	public static String capitalize(String s) {
		if (s == null || s.length() == 0) {
			return "";
		}
		char first = s.charAt(0);
		if (Character.isUpperCase(first)) {
			return s;
		} else {
			return Character.toUpperCase(first) + s.substring(1);
		}
	}

	public static boolean boolJNI() {
		Boolean jReturn;
		Log.d("JNI Bool", "Hello JNI in Cocos2dx");
		int a = 0;
		int b = 5;
		if ((a < 10) && (b < 10)) {
			jReturn = true;
		} else {
			jReturn = false;
		}

		return jReturn;
	}

	public static void intJNI(int jNumber) {
		if (jNumber % 2 == 0) {
			Log.d("JNI Interger", jNumber + " la so chan!!");

		} else {
			Log.d("JNI Interger", jNumber + " la so le!!");

		}
	}

	public static void stringJNI(String jString) {
		Log.d("JNI String", jString + " la chuoi truyen tu C++");
	}

	private static native void onMessagerCallback(final int num);

	public static void createDialogJNI(final String javaTitle,
			final String javaMessager, final String OKName,
			final String CancelName) {
		try {
			Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {

				@Override
				public void run() {
					// TODO Auto-generated method stub

					AlertDialog.Builder dialog = new AlertDialog.Builder(
							Cocos2dxHelper.getActivity());
					dialog.setTitle(javaTitle.subSequence(0, javaTitle.length()));
					dialog.setMessage(javaMessager.subSequence(0,
							javaMessager.length()));

					dialog.setPositiveButton(OKName, new OnClickListener() {

						@Override
						public void onClick(DialogInterface dialog, int which) {
							// TODO Auto-generated method stub
							// Su dung ham callback duoc xay dung tai C
							//onMessagerCallback(1);
						}
					});

					dialog.setNegativeButton(CancelName, new OnClickListener() {

						@Override
						public void onClick(DialogInterface dialog, int which) {
							// TODO Auto-generated method stub
							// Su dung ham callback duoc xay dung tai C
							//onMessagerCallback(2);
						}
					});

					dialog.show();
				}

			});
		} catch (Exception e) {
			// TODO: handle exception
			Log.d("ERROR", e + "");
		}
	}

	public static void vibrationJNI() {
		Vibrator vib = (Vibrator) getContext().getSystemService(
				Context.VIBRATOR_SERVICE);
		// {daley time , vibrate time , sleep time}
		long[] parttern = { 0, 100, 1000 };
		vib.vibrate(1000); // rung trong thoi gian co dinh
		// vib.vibrate(parttern, 1); // Repeat 1 lan
		Log.d("JNI Vibration", "Vibration Succesfull");
	}

	private static AudioManager audio;

	public static int getCurrentVolumeLevel() {
		audio = (AudioManager) getContext().getSystemService(
				Context.AUDIO_SERVICE);

		int currentVolume = audio.getStreamVolume(AudioManager.STREAM_MUSIC);
		int maxVolume = audio.getStreamMaxVolume(AudioManager.STREAM_MUSIC);

		Log.d("JNI Volume", (int) currentVolume + "");

		return (int) currentVolume; // /maxVolume
	}

	public static int getMaxVolumeLevel() {
		audio = (AudioManager) getContext().getSystemService(
				Context.AUDIO_SERVICE);

		int maxVolume = audio.getStreamMaxVolume(AudioManager.STREAM_MUSIC);

		Log.d("JNI VolumeMax ", (int) maxVolume + "");

		return (int) maxVolume; // /maxVolume
	}

}
