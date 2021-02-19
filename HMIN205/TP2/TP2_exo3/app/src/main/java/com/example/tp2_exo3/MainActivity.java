package com.example.tp2_exo3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    private SensorManager mSensorManager;
    private Sensor mSensor;
    private TextView valX;
    private TextView valY;
    private TextView valZ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        if (mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) != null) {
            mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        }

        valX = findViewById(R.id.valX);
        valY = findViewById(R.id.valY);
        valZ = findViewById(R.id.valZ);
        //valX.setTextColor(Color.parseColor("#FFFFFF"));

        boolean supported = mSensorManager.registerListener(
                (SensorEventListener) this,
                mSensor,
                SensorManager.SENSOR_DELAY_UI);

        if (!supported) {
            mSensorManager.unregisterListener
                    ((SensorEventListener) this,
                            mSensor);
        }

    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            onAccelerometerChanged(event);
        }
    }

    public void onAccelerometerChanged(SensorEvent event){
        // Récupérer les valeurs du capteur
        int x, y, z;
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            x = (int) event.values[0];
            y = (int) event.values[1];
            z = (int) event.values[2];

            String strx = "hh";
            //strx+=x;

            valX.setText("x : "+ x);
            valY.setText("y : " + y);
            valZ.setText("z : " + z);

            if(x > 0){
                valX.setTextColor(Color.rgb(0,255,0));
            }else {
                if ( x < 0)
                {
                    valX.setTextColor(Color.rgb(255,0,0));
                }else {
                    valX.setTextColor(Color.WHITE);
                }
            }

            if(y>0){
                valY.setTextColor(Color.rgb(0,255,0));
            }else {
                if(y < 0) {
                    valY.setTextColor(Color.rgb(255, 0, 0));
                }else{
                    valY.setTextColor(Color.WHITE);
                }
            }

            if(z>0){
                valZ.setTextColor(Color.rgb(0,255,0));
            }else {
                if(z < 0) {
                    valZ.setTextColor(Color.rgb(255, 0, 0));
                }else{
                    valZ.setTextColor(Color.WHITE);
                }
            }

        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        switch (accuracy) {
            case SensorManager.SENSOR_STATUS_ACCURACY_LOW:
            case SensorManager.SENSOR_STATUS_ACCURACY_MEDIUM:
            case SensorManager.SENSOR_STATUS_ACCURACY_HIGH:
            case SensorManager.SENSOR_STATUS_UNRELIABLE:
        }
        //Log.d("Sensor", sensor.getType() + ":" + accuracy);
    }


    @Override
    protected void onResume(){
        super.onResume();
        mSensorManager.registerListener(
                this,
                mSensor,
                SensorManager.SENSOR_DELAY_UI);
    }

    @Override
    protected void onPause(){
        super.onPause();
        mSensorManager.unregisterListener(this);
    }
}