package com.exadios.gpstest;

import android.os.Bundle;
import android.app.Activity;
import android.os.Bundle;
import android.location.*;
import android.widget.*;
import android.content.Context;
import android.content.Intent;
import android.provider.Settings;

public class Main extends Activity
{
  private LocationManager locationManager;
  private static boolean queriedLocationSettings = false;
  private Context context;
  private GPSListener gpslistener;

  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    this.context = this.getApplicationContext();
    this.locationManager = (LocationManager )getSystemService(LOCATION_SERVICE);
    if (!this.locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER) &&
                                                !queriedLocationSettings) {
      // Let user turn on GPS, XCSoar is not allowed to.
      Intent myIntent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
      this.context.startActivity(myIntent);
      queriedLocationSettings = true;
    }
    this.gpslistener = new GPSListener();
  }

  @Override
  public void onResume() {
    super.onResume();
    this.locationManager.requestLocationUpdates(this.locationManager.GPS_PROVIDER, 1000, 0, this.gpslistener);
    }

  @Override
  public void onPause() {
    this.locationManager.removeUpdates(this.gpslistener);
  }

  class GPSListener implements LocationListener {
    private TextView resultText;

    public GPSListener() {
      this.resultText = (TextView )findViewById(R.id.MeasuredSampleRate);
    }
    public void onLocationChanged(Location location) {
      long tt = location.getTime();
    }

    public void onProviderDisabled(String provider) {
    }

    public void onProviderEnabled(String provider) {
    }

    public void onStatusChanged(String provider, int status, Bundle extras) {
    }
  }
    
}
