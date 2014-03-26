package com.exadios.gyrotest;

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

public class GyroTest extends Activity {
    /** Called when the activity is first created. */
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
     * The gyro routine.
     */
    private GyroListener listener;

    /**
     * UI components.
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      this.listener = new GyroListener();
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

    class GyroListener implements SensorEventListener {

      /**
       * The sensor manager.
       */
      private SensorManager sensors;
 
      /**
       * The accelerometers.
       */
      private Sensor gyro;

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
    	private long  gyroTimeStamp;
    	private long  lastsysTime;
      private int   i;
    	
      public GyroListener() {
        this.sensors = (SensorManager )getSystemService(SENSOR_SERVICE);
        this.gyro = this.sensors.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        setContentView(R.layout.main);
        TextView mr = (TextView )findViewById(R.id.MaxRateReport);
        mr.setText("Maximum gyro SR: " + gyro.getMinDelay() + "uS");

        this.resultText = (TextView )findViewById(R.id.MeasuredSampleRate);
        this.rate(SensorManager.SENSOR_DELAY_UI);
      }

      private void onCreate() {
        this.rate(SensorManager.SENSOR_DELAY_UI);
      }

      private void onResume() {
        this.sensors.registerListener(this,
                                      this.gyro,
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
			  if (event.sensor.getType() != Sensor.TYPE_GYROSCOPE) {
                return;
        }
        if (this.i < 0) {
          this.lastsysTime = System.currentTimeMillis();
          this.i++;
        }
        else if (this.i < 100) {
			    this.gyroTimeStamp = event.timestamp;
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
        this.sensors.registerListener(this, this.gyro, delay);
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
