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
import android.widget.*;

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

    /**
     * UI components.
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      this.listener = new AccListener();
      this.listener.onCreate();
    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
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
       * The result.
       */
      TextView resultText;

      /**
       * State variables.
       */
    	private float x;
    	private float y;
    	private float z;
    	private long  accTimeStamp;
    	private long  lastsysTime;
      private int   i;
    	
      public AccListener() {
        this.sensors = (SensorManager )getSystemService(SENSOR_SERVICE);
        this.acc = this.sensors.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        setContentView(R.layout.activity_fullscreen_acc);
        TextView mr = (TextView )findViewById(R.id.MaxRateReport);
        mr.setText("Maximum accelerometer SR: " + acc.getMinDelay() + "uS");

        this.resultText = (TextView )findViewById(R.id.MeasuredSampleRate);
        this.rate(SensorManager.SENSOR_DELAY_UI);
      }

      private void onCreate() {
        this.rate(SensorManager.SENSOR_DELAY_UI);
      }

      private void onResume() {
        this.sensors.registerListener(this,
                                      this.acc,
                                      SensorManager.SENSOR_DELAY_UI);
        this.rate(SensorManager.SENSOR_DELAY_UI);

      }

      private void onPause() {
        this.sensors.unregisterListener(this);
      }

    	@Override
    	public void onAccuracyChanged(Sensor sensor, int accuracy) {
    		
    	}

		  @Override
		  public void onSensorChanged(SensorEvent event) {
			  if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER) {
                return;
        }
        if (this.i < 0) {
          this.lastsysTime = System.currentTimeMillis();
          this.i++;
        }
        else if (this.i < 100) {
			    this.accTimeStamp = event.timestamp;
          this.i++;
        } 
        else if (i == 100) {
          this.resultText.setText("dT: " + (float )(System.currentTimeMillis() - this.lastsysTime) / (float )102);
          this.i++;
        }
        else {
        }
		  }

      protected void onPause(SensorManager sensors) {
        sensors.unregisterListener(this);
      }

      private void rate(int delay) {
        this.sensors.unregisterListener(this);
        this.sensors.registerListener(this, this.acc, delay);
        this.i = -1;
        this.resultText.setText("");
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
            return false;
        }
    };

    Handler mHideHandler = new Handler();
    
    public void rateHighest(View view) {
      this.listener.rate(SensorManager.SENSOR_DELAY_FASTEST);
    }

    public void rateHigh(View view) {
      this.listener.rate(SensorManager.SENSOR_DELAY_GAME);
    }

    public void rateMedium(View view) {
      this.listener.rate(SensorManager.SENSOR_DELAY_NORMAL);
    }

    public void rateLow(View view) {
      this.listener.rate(SensorManager.SENSOR_DELAY_UI);
    }
}
