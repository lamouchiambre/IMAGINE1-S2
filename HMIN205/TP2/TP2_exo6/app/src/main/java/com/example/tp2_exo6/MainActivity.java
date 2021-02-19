package com.example.tp2_exo6;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements SensorEventListener {

    SensorManager sensorManager;
    Sensor sensor;
    ImageView imageView;
    TextView tv0;
    TextView tv1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        sensor = sensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY);

        this.imageView = (ImageView) this.findViewById(R.id.image);

        boolean supported = sensorManager.registerListener(this,
                sensor,
                SensorManager.SENSOR_DELAY_UI);

        if (!supported) {
            sensorManager.unregisterListener(this, sensor);
            tv0.setText(R.string.proximity_unavailable);
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_PROXIMITY) {
            onProximityChanged(event);
        }
    }

    private void onProximityChanged(SensorEvent event) {

        if (event.values[0] < sensor.getMaximumRange()) {
            getWindow().getDecorView().setBackgroundColor(Color.BLACK);
            this.imageView.setImageResource(R.drawable.img);
        } else {
            getWindow().getDecorView().setBackgroundColor(Color.WHITE);
            this.imageView.setImageResource(R.drawable.trans);
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}