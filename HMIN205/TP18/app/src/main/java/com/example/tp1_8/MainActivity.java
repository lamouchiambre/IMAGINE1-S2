package com.example.tp1_8;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {
    private ImageButton imageButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageButton = this.findViewById(R.id.imageButton);
        imageButton.setOnClickListener(v -> {
            Intent intent = new Intent(this, Recherche.class);
            startActivity(intent);
        });
    }
}