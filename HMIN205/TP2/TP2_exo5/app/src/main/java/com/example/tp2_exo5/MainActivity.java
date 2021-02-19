package com.example.tp2_exo5;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;
import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;

@RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
public class MainActivity extends AppCompatActivity implements SensorEventListener {
    private SensorManager mSensorManager;
    private Sensor lSensor;
    private Sensor mSensor;
    private TextView valX;
    private TextView valY;
    private TextView valZ;
    private TextView comment;
    private CameraManager flash;
    private Boolean estAllumee;
    private Long currentTime;
    private Long diffTime;
    private Long startTime;

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        startTime = System.currentTimeMillis();
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        estAllumee = false;

        if (mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE) != null) {
            mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        }

        if(true){
            flash = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
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

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE &&
                getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH)) {
            try {
                onGyroscopeChanged(event);
            } catch (CameraAccessException e) {
                e.printStackTrace();
            }
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

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    public void onGyroscopeChanged(SensorEvent event) throws CameraAccessException {
        // Récupérer les valeurs du capteur
        float x, y, z;

        String cameraId = flash.getCameraIdList()[0];
        currentTime = System.currentTimeMillis();

        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            x = (int) event.values[0];
            y = (int) event.values[1];
            z = (int) event.values[2];

            String strx = "hh";
            //strx+=x;

            valX.setText("x : " + x);
            valY.setText("y : " + y);
            valZ.setText("z : " + z);

            if (x > 0) {
                valX.setTextColor(Color.rgb(0, 255, 0));
                comment.setText("Haut");
            } else {
                if (x < 0) {
                    valX.setTextColor(Color.rgb(255, 0, 0));
                    comment.setText("Bas");
                } else
                    valX.setTextColor(Color.rgb(255, 255, 255));
            }

            if (y > 0) {
                valY.setTextColor(Color.rgb(0, 255, 0));
                if (y * y > x * x) {
                    comment.setText("Droite");
                }
            } else {
                if (y < 0) {
                    valY.setTextColor(Color.rgb(255, 0, 0));
                    comment.setText("Gauche");
                } else
                    valY.setTextColor(Color.rgb(255, 255, 255));
            }

            if (z > 0) {
                valZ.setTextColor(Color.rgb(0, 255, 0));
            } else {
                if (z < 0) {
                    valZ.setTextColor(Color.rgb(255, 0, 0));
                } else
                    valZ.setTextColor(Color.rgb(255, 255, 255));
            }

            //startTime = null;
            diffTime = currentTime - startTime;


            if( (x*x + y*y + z*z) > 100 ){
                startTime = currentTime;
                startTime = currentTime;
                estAllumee = !estAllumee;
                if(estAllumee){
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                        flash.setTorchMode(cameraId, true);
                        getWindow().getDecorView().setBackgroundColor(Color.YELLOW);

                    }
                }else{
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                        flash.setTorchMode(cameraId,false);
                        getWindow().getDecorView().setBackgroundColor(Color.BLACK);
                    }
                }
            }

        }/**/

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