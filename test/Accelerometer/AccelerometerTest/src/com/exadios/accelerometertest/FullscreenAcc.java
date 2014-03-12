package com.exadios.accelerometertest;

import com.exadios.accelerometertest.util.SystemUiHider;

import android.annotation.TargetApi;
import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 *
 * @see SystemUiHider
 */
public class FullscreenAcc extends Activity {
    /**
     * Whether or not the system UI should be auto-hidden after
     * {@link #AUTO_HIDE_DELAY_MILLIS} milliseconds.
     */
    private static final boolean AUTO_HIDE = true;

    /**
     * If {@link #AUTO_HIDE} is set, the number of milliseconds to wait after
     * user interaction before hiding the system UI.
     */
    private static final int AUTO_HIDE_DELAY_MILLIS = 3000;

    /**
     * If set, will toggle the system UI visibility upon interaction. Otherwise,
     * will show the system UI visibility upon interaction.
     */
    private static final boolean TOGGLE_ON_CLICK = true;

    /**
     * The flags to pass to {@link SystemUiHider#getInstance}.
     */
    private static final int HIDER_FLAGS = SystemUiHider.FLAG_HIDE_NAVIGATION;

    /**
     * The instance of the {@link SystemUiHider} for this activity.
     */
    private SystemUiHider mSystemUiHider;

    /**
     * The acceleromenter routine.
     */
    private AccListener listener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      this.listener = new AccListener();
      this.listener.onCreate();
    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);

        // Trigger the initial hide() shortly after the activity has been
        // created, to briefly hint to the user that UI controls
        // are available.
        delayedHide(100);
    }

    protected void onResume() {
        super.onResume();
        this.listener.onResume();
    }

    protected void onPause() {
        super.onPause();
        this.listener.onPause();
    }

    class AccListener implements SensorEventListener {

      /**
       * The sensor manager.
       */
      private SensorManager sensors;
 
      /**
       * The accelerometers.
       */
      private Sensor acc;

      /**
       * State variables.
       */
    	private float x;
    	private float y;
    	private float z;
    	private long accTimeStamp;
    	private long lastsysTime;
    	private long sysTime;
    	private long deltaTime;
    	
      private void onCreate() {
        this.sensors = (SensorManager )getSystemService(SENSOR_SERVICE);
        setContentView(R.layout.activity_fullscreen_acc);
        this.acc = this.sensors.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
      }

      private void onResume() {
        this.sensors.registerListener(this,
                                      this.acc,
                                      SensorManager.SENSOR_DELAY_UI);

      }

      private void onPause() {
        this.sensors.unregisterListener(this);
      }

    	@Override
    	public void onAccuracyChanged(Sensor sensor, int accuracy) {
    		
    	}

		  @Override
		  public void onSensorChanged(SensorEvent event) {
			  if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER)
                return;
			  this.x = event.values[0];
			  this.y = event.values[1];
			  this.z = event.values[2];
			  this.accTimeStamp = event.timestamp;
			  this.lastsysTime = this.sysTime;
			  this.sysTime = System.nanoTime();
			  this.deltaTime = this.sysTime - this.lastsysTime;
		  }

      protected void onResume(SensorManager sensors, Sensor acc) {
          sensors.registerListener(this,
                                   acc,
                                   SensorManager.SENSOR_DELAY_UI);
    
      }

      protected void onPause(SensorManager sensors) {
          sensors.unregisterListener(this);
      }
    }

    /**
     * Touch listener to use for in-layout UI controls to delay hiding the
     * system UI. This is to prevent the jarring behavior of controls going away
     * while interacting with activity UI.
     */
    View.OnTouchListener mDelayHideTouchListener = new View.OnTouchListener() {
        @Override
        public boolean onTouch(View view, MotionEvent motionEvent) {
            if (AUTO_HIDE) {
                delayedHide(AUTO_HIDE_DELAY_MILLIS);
            }
            return false;
        }
    };

    Handler mHideHandler = new Handler();
    Runnable mHideRunnable = new Runnable() {
        @Override
        public void run() {
            mSystemUiHider.hide();
        }
    };

    /**
     * Schedules a call to hide() in [delay] milliseconds, canceling any
     * previously scheduled calls.
     */
    private void delayedHide(int delayMillis) {
        mHideHandler.removeCallbacks(mHideRunnable);
        mHideHandler.postDelayed(mHideRunnable, delayMillis);
    }
}
