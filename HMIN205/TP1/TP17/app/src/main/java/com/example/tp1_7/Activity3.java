package com.example.tp1_7;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

public class Activity3 extends AppCompatActivity {
    private Button appel;
    private String numero;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_3);

        Intent intentBack = this.getIntent();
        TextView txt = (TextView) this.findViewById(R.id.textView);
        numero = intentBack.getStringExtra("num");
        txt.setText(numero);
        appel = (Button) this.findViewById(R.id.appel);
        this.appel.setOnClickListener(v -> appeler());

    }

    void appeler(){
        Intent intentBack = this.getIntent();
        Uri uri = Uri.parse("tel:"+intentBack.getStringExtra("num"));
        Intent intent = new Intent(Intent.ACTION_CALL, uri);
        startActivity(intent);
    }
}