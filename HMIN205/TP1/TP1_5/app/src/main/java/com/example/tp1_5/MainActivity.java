package com.example.tp1_5;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import java.util.concurrent.atomic.AtomicReference;

public class MainActivity extends AppCompatActivity {

    private Button button;
    //private EditText lastname;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button) findViewById(R.id.buttonSubmit);
        EditText lastname = (EditText) findViewById(R.id.editNom);
        EditText firstname = (EditText) findViewById(R.id.editPrenom);
        EditText age = (EditText) findViewById(R.id.editAge);
        EditText domain = (EditText) findViewById(R.id.editDomain);
        EditText phone = (EditText) findViewById(R.id.editPhone);
        AtomicReference<Boolean> submite = null;

        //add button listener
        button.setOnClickListener( v -> {
            AlertDialog.Builder alertD = new AlertDialog.Builder(this);
            alertD.setTitle("Recapitulatif")
                    .setMessage("first name : "+firstname.getText()+"\n"
                            + "last name : " + lastname.getText()+"\n"
                            + "age : " + age.getText() + "\n"
                            + "domain : " + domain.getText() + "\n"
                            + "phone : " + phone.getText()+"\n"
                    )
                    .setPositiveButton("Confirm", (dialog, which) -> {
                        lastname.setTextColor(Color.parseColor("#00FF7F"));
                        firstname.setTextColor(Color.parseColor("#00FF7F"));
                        age.setTextColor(Color.parseColor("#00FF7F"));
                        domain.setTextColor(Color.parseColor("#00FF7F"));
                        phone.setTextColor(Color.parseColor("#00FF7F"));
                    })
                    .setNegativeButton("Annul", (dialog, which) -> {
                        lastname.setTextColor(Color.parseColor("#FF0000"));
                        firstname.setTextColor(Color.parseColor("#FF0000"));
                        age.setTextColor(Color.parseColor("#FF0000"));
                        domain.setTextColor(Color.parseColor("#FF0000"));
                        phone.setTextColor(Color.parseColor("#FF0000"));
                    })
                    .create()
                    .show();

                }
        );

    }
}