package com.example.tp1_8;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Spinner;

import java.util.ArrayList;

public class Recherche extends AppCompatActivity {

    private Spinner spinner;
    private Button submit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recherche);

        spinner = (Spinner) findViewById(R.id.spinner);
        String[] arriver = {"Arrive", "Go"};
        ArrayAdapter<String> dataAdapterR = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item,arriver);
        dataAdapterR.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(dataAdapterR);

        /*-------------------------------------------------------------*/
/*
        submit = (Button) findViewById(R.id.rechercher);
        submit.setOnClickListener(v->{
            Intent intent = new Intent(this, Resultats.);*/
       // });
    }
}