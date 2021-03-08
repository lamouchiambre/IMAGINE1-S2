package com.example.tp3_exo1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private final static String MA_CLE = "MaCle";
    private final static String ID = "USER";
    private TextView user;
    private int id_user;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if ((savedInstanceState != null) &&(savedInstanceState.containsKey(MA_CLE))) {
            String val = savedInstanceState.getString(MA_CLE);
            Toast.makeText(this,
                "onCreate() : " + val,
                Toast.LENGTH_SHORT).show();
            if (savedInstanceState.containsKey(ID)) {
                    id_user = Integer.parseInt(savedInstanceState.get(ID).toString());
            }
        }else{
            id_user = 1 + (int) (Math.random() * ((100000 - 1) + 1));
            Toast.makeText(this, "User registered : " +
                    id_user,
                    Toast.LENGTH_SHORT).show();
        }

        user = findViewById(R.id.User);
//        Toast.makeText(this, user.getText(),
//                Toast.LENGTH_SHORT).show();
        user.setText(String.valueOf(id_user));



    }

    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putString(MA_CLE, "Ma valeur !");

        savedInstanceState.putString(ID, String.valueOf(id_user));
        //    Toast.makeText(this, "Etat de l'activité sauvegardé", Toast.LENGTH_SHORT).show();

        Toast.makeText(this, "Etat de l'activité sauvegardé",
                Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        Toast.makeText(this,
                "Etat de l'activité restauré",
                Toast.LENGTH_SHORT).show();
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        Toast.makeText(this,
                "L'activité est détruite",
                Toast.LENGTH_SHORT).show();
    }
}