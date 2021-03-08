package com.example.tp3_exo3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    private final static String MA_CLE = "MaCle";
    private final static String ID = "USER";
    public final static String F_KEY = "F_KEY";

    private TextView user;
    private  TextView count;
    private int id_user;
    private Button button;

    //EditText
    private EditText nom;
    private EditText prenom;
    private EditText age;
    private EditText telephone;
    private EditText mdp;

    private String fileName;
    private final String TAG = this.getClass().getSimpleName();
    private Utilisation utilisation;


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
        user.setText(String.valueOf(id_user));

        count = findViewById(R.id.count);

        nom = findViewById(R.id.nom);
        prenom = findViewById(R.id.prenom);
        age = findViewById(R.id.age);
        telephone = findViewById(R.id.phone);
        mdp = findViewById(R.id.mdp);

        fileName = "filname";
        button = findViewById(R.id.submit);

        button.setOnClickListener(v -> {
            Toast.makeText(this,"CLik",Toast.LENGTH_SHORT).show();
            if(!fieldEmpty()){
                fileName = nom.getText().toString() + id_user;
                try {
                    FileOutputStream fos = null;
                    fos = openFileOutput(fileName, Context.MODE_PRIVATE);
                    fos.write(nom.getText().toString().concat("\n").getBytes());
                    fos.write(prenom.getText().toString().concat("\n").getBytes());
                    fos.write(age.getText().toString().concat("\n").getBytes());
                    fos.write(telephone.getText().toString().concat("\n").getBytes());
                    fos.write(String.valueOf(id_user).getBytes());
                    Log.i(TAG, "Ecriture du fichier " + fileName);
                    fos.close();

//                    Intent intent = new Intent(MainActivity.this, mainSec.class);
//                    intent.putExtra(F_KEY, fileName);
//                    startActivity(intent);

                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }else{
                Toast.makeText(this,"non c'est pas remplit",Toast.LENGTH_SHORT).show();
            }


        });

        utilisation = new Utilisation();
        getLifecycle().addObserver(utilisation);
        count.setText(count.getText().toString().concat(String.valueOf(utilisation.getCounter())));
    }


    public boolean fieldEmpty() {
        return TextUtils.isEmpty(nom.getText())
                || TextUtils.isEmpty(prenom.getText())
                || TextUtils.isEmpty(telephone.getText())
                || TextUtils.isEmpty(age.getText())
                || TextUtils.isEmpty(mdp.getText());
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