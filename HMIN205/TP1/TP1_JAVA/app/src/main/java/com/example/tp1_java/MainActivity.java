package com.example.tp1_java;

import android.annotation.SuppressLint;
import android.icu.text.MessagePattern;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.InputType;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LinearLayout layout_principale = new LinearLayout(this);
        layout_principale.setOrientation(LinearLayout.VERTICAL);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        layout_principale.setLayoutParams(layoutParams);

        LinearLayout l1 = new LinearLayout(this);
        LinearLayout l2 = new LinearLayout(this);
        LinearLayout l3 = new LinearLayout(this);
        LinearLayout l4 = new LinearLayout(this);
        LinearLayout l5 = new LinearLayout(this);

        l1.setOrientation(LinearLayout.HORIZONTAL);
        l2.setOrientation(LinearLayout.HORIZONTAL);
        l3.setOrientation(LinearLayout.HORIZONTAL);
        l4.setOrientation(LinearLayout.HORIZONTAL);
        l5.setOrientation(LinearLayout.HORIZONTAL);

        LinearLayout.LayoutParams layoutParamsText = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,ViewGroup.LayoutParams.WRAP_CONTENT);
        //LinearLayout.LayoutParams layoutParamsSec = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,ViewGroup.LayoutParams.WRAP_CONTENT);

        l1.setLayoutParams(layoutParams);
        l2.setLayoutParams(layoutParams);
        l3.setLayoutParams(layoutParams);
        l4.setLayoutParams(layoutParams);
        l5.setLayoutParams(layoutParams);

        TextView text_prenom = new TextView(this);
        TextView text_nom = new TextView(this);
        TextView text_age = new TextView(this);
        TextView text_domain = new TextView(this);
        TextView text_phone = new TextView(this);

        text_prenom.setText(getString(R.string.prenom));
        text_nom.setText(getString(R.string.nom));
        text_age.setText(getString(R.string.age));
        text_domain.setText(getString(R.string.domain));
        text_phone.setText(getString(R.string.telephone));

        text_prenom.setLayoutParams(layoutParamsText);
        text_nom.setLayoutParams(layoutParamsText);
        text_age.setLayoutParams(layoutParamsText);
        text_domain.setLayoutParams(layoutParamsText);
        text_phone.setLayoutParams(layoutParamsText);


        EditText edit_prenom = new EditText(this);
        EditText edit_nom = new EditText(this);
        EditText edit_age = new EditText(this);
        EditText edit_domain = new EditText(this);
        EditText edit_phone = new EditText(this);

        edit_age.setInputType(InputType.TYPE_CLASS_NUMBER);
        edit_prenom.setInputType(InputType.TYPE_CLASS_TEXT);
        edit_nom.setInputType(InputType.TYPE_CLASS_TEXT);
        edit_phone.setInputType(InputType.TYPE_CLASS_PHONE);
        edit_domain.setInputType(InputType.TYPE_CLASS_TEXT);

        edit_prenom.setLayoutParams(layoutParams);
        edit_nom.setLayoutParams(layoutParams);
        edit_age.setLayoutParams(layoutParams);
        edit_domain.setLayoutParams(layoutParams);
        edit_phone.setLayoutParams(layoutParams);

        l1.addView(text_prenom);l1.addView(edit_prenom);
        l2.addView(text_nom);l2.addView(edit_nom);
        l3.addView(text_age);l3.addView(edit_age);
        l4.addView(text_domain);l4.addView(edit_domain);
        l5.addView(text_phone);l5.addView(edit_phone);

        Button button = new Button(this);
        button.setGravity(Gravity.CENTER);
        button.setText(getString(R.string.soumettre));
        button.setLayoutParams(layoutParams);

        layout_principale.addView(l1);
        layout_principale.addView(l2);
        layout_principale.addView(l3);
        layout_principale.addView(l4);
        layout_principale.addView(l5);
        layout_principale.addView(button);

        setContentView(layout_principale);
        //setContentView(R.layout.activity_main);

    }
}