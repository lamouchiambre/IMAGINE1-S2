package com.example.td1;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

//    @Override
//    protected void onCreate(Bundle savedInstanceState) {

        //exercice 1
//        super.onCreate(savedInstanceState);
//        LinearLayout l = new LinearLayout(this);
//        TextView tv = new TextView(this);
//        EditText et = new EditText(this);
//        tv.setText("Hello, Android");
//        l.addView(tv);
//        l.addView(et);
//
//        setContentView(l);
/*-------------------------------------------*/
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);

//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);

        // Exo 4
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//        Button button = findViewById(R.id.mainbutton);
//        Button button2 = findViewById(R.id.btn2);
//
//        button2.setOnClickListener(v -> {
//            Toast.makeText(this, R.string.toastMsg, Toast.LENGTH_SHORT).show();
//            new AlertDialog.Builder(MainActivity.this)
//                    .setMessage(R.string.dialogMsg)
//                    .create()
//                    .show();
//        });
//
//        button2.setOnLongClickListener(v -> {
//            Toast.makeText(this, R.string.toastMsgLong, Toast.LENGTH_SHORT).show();
//            return true;
//        });

//        button.setOnClickListener(v -> {
//            new AlertDialog.Builder(MainActivity.this)
//                    .setTitle("Ambre")
//                    .setMessage("est la plus belle")
//                    .setPositiveButton("oui", (dialog, which) ->
//                            button.setBackgroundColor(getResources().getColor(R.color.green)))
//                    .setNegativeButton("non", (dialog, which) ->
//                            button.setBackgroundColor(getResources().getColor(R.color.red)))
//                    .create()
//                    .show();
//        });

                //(DialogInterface.OnClickListener) arg0 -> Toast.makeText(getApplicationContext(),"Message Bouton 1", Toast.LENGTH_LONG).show());

//    }


    private CheckBox linux, macos, windows;
    private Button button;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        addListenerOnChkWindows();
        addListenerOnButton();
    }
    public void addListenerOnChkWindows() {
        windows = (CheckBox) findViewById(R.id.windows_option);
        windows.setOnClickListener(v -> {
            if (((CheckBox) v).isChecked()) {
                Toast.makeText(MainActivity.this,"Bro, try Linux :)", Toast.LENGTH_LONG).show();
            }
        });
    }
    public void addListenerOnButton() {
        linux = (CheckBox) findViewById(R.id.linux_option);
        macos = (CheckBox) findViewById(R.id.macos_option);
        windows = (CheckBox) findViewById(R.id.windows_option);
        button = (Button) findViewById(R.id.button);
        button.setOnClickListener(v -> {
            StringBuffer result = new StringBuffer();
            result.append("Linux check : ").append(linux.isChecked());
            result.append("\nMac OS check : ").append(macos.isChecked());
            result.append("\nWindows check :").append(windows.isChecked());
            Toast.makeText(MainActivity.this, result.toString(), Toast.LENGTH_LONG).show();
        });
    }
}