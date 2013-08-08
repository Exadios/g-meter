package com.exadios.g_meter;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class Main extends Service {
	public Main() {
		;
	}
	private static final String TAG = "com.exadios.g_meter.Main";
	public class LocalBinder extends Binder {
		Main getService() {
			return Main.this;
		}
	}
	private final IBinder binder = new LocalBinder();
	
	@Override
	public IBinder onBind(Intent intent) {
		Log.d(TAG, "onBind");
		return this.binder;
	}
	
	@Override
	public void onCreate() {
		Log.d(TAG, "onCreate");
	}
	
	@Override
	public void onDestroy() {
		Log.d(TAG, "onDestroy");
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.d(TAG, "onStart");
		return START_STICKY;
	}

}
