package com.example.tp2_exo5;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    private SensorManager mSensorManager;
    private Sensor lSensor;
    private Sensor mSensor;
    private TextView valX;
    private TextView valY;
    private TextView valZ;
    private TextView comment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        if (mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE) != null) {
            mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        }

        if (mSensorManager.getDefaultSensor(Sensor.TY) != null) {
            lSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
        }

        valX = findViewById(R.id.valX);
        valY = findViewById(R.id.valY);
        valZ = findViewById(R.id.valZ);
        comment = findViewById(R.id.light);
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
        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            onGyroscopeChanged(event);
        }
    }

    public void onAccelerometerChanged(SensorEvent event){
        // Récupérer les valeurs du capteur
        float x, y, z;
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            x = event.values[0];
            y = event.values[1];
            z = event.values[2];

            String strx = "hh";
            //strx+=x;

            valX.setText("x : "+(int)x);
            valY.setText("y : " + (int) y);
            valZ.setText("z : " + (int) z);

            if(x>0){
                valX.setTextColor(Color.rgb(0,255,0));
            }else {
                valX.setTextColor(Color.rgb(255,0,0));
            }

            if(y>0){
                valY.setTextColor(Color.rgb(0,255,0));
            }else {
                valY.setTextColor(Color.rgb(255,0,0));
            }

            if(z>0){
                valZ.setTextColor(Color.rgb(0,255,0));
            }else {
                valZ.setTextColor(Color.rgb(255,0,0));
            }
        }
    }

    public void onGyroscopeChanged(SensorEvent event){
        // Récupérer les valeurs du capteur
        float x, y, z;
        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            x = (int) event.values[0];
            y = (int) event.values[1];
            z = (int) event.values[2];

            String strx = "hh";
            //strx+=x;

            valX.setText("x : "+ x);
            valY.setText("y : " + y);
            valZ.setText("z : " + z);

            if(x>0){
                valX.setTextColor(Color.rgb(0,255,0));
                comment.setText("Haut");
            }else {
                if(x<0) {
                    valX.setTextColor(Color.rgb(255, 0, 0));
                    comment.setText("Bas");
                }else
                    valX.setTextColor(Color.rgb(255, 255, 255));
            }

            if(y>0){
                valY.setTextColor(Color.rgb(0,255,0));
                if(y*y>x*x){
                    comment.setText("Droite");
                }
            }else {
                if(y<0) {
                    valY.setTextColor(Color.rgb(255,0,0));
                    comment.setText("Gauche");
                }
                else
                    valY.setTextColor(Color.rgb(255,255,255));
            }

            if(z>0){
                valZ.setTextColor(Color.rgb(0,255,0));
            }else {
                if(z<0){
                    valZ.setTextColor(Color.rgb(255,0,0));
                }else
                    valZ.setTextColor(Color.rgb(255,255,255));
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