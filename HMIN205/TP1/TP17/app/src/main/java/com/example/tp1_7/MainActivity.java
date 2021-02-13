package com.example.tp1_7;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import java.util.concurrent.atomic.AtomicReference;

public class MainActivity extends AppCompatActivity {

    private Button button;
    private EditText firstname_;
    private EditText lastname_;
    private EditText age_;
    private EditText domain_;
    private EditText phone_;

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
                                start_greeting();
                            })
                            .setNegativeButton("Annul", (dialog, which) -> {
                                lastname.setTextColor(Color.parseColor("#FF3369"));
                                firstname.setTextColor(Color.parseColor("#FF3369"));
                                age.setTextColor(Color.parseColor("#FF3369"));
                                domain.setTextColor(Color.parseColor("#FF3369"));
                                phone.setTextColor(Color.parseColor("#FF3369"));
                            })
                            .create()
                            .show();

                }
        );

    }

    public void start_greeting(){
        Intent intent = new Intent(this, GreetingActivity.class);
        firstname_ = (EditText) findViewById(R.id.editPrenom);
        lastname_ = (EditText) findViewById(R.id.editNom);
        this.domain_ = (EditText) findViewById(R.id.editDomain);
        this.age_ = (EditText) findViewById(R.id.editAge);
        this.phone_ = (EditText) findViewById(R.id.editPhone);
        String message = "Hello " + firstname_.getText();
        //String last_name = lastname_.getText();
        intent.putExtra("first_", firstname_.getText().toString());

        intent.putExtra("lastname_", lastname_.getText().toString());
        intent.putExtra("domain_", domain_.getText().toString());
        intent.putExtra("age_", age_.getText().toString());
        intent.putExtra("phone_", phone_.getText().toString());
        startActivity(intent);

        //String fullName= this.editTextFullName.getText().toString();

        //Intent intent = new Intent(this,GreetingActivity.class);
        //intent.putExtra("fullName", fullName);
        //intent.putExtra("message", message);
    }
}