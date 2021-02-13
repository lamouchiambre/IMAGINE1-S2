package com.example.tp1_7;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

public class GreetingActivity extends AppCompatActivity {

    private Button buttonBack;
    private Button buttonOk;
    private TextView title;
    private TextView text;
    private String num_phone;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_greeting);

        this.buttonBack = (Button) this.findViewById(R.id.button_back);
        this.buttonBack.setOnClickListener(v -> goBack());
        //
        this.buttonOk = (Button) this.findViewById(R.id.button_ok);
        this.buttonOk.setOnClickListener(v -> act_3());
        //
        this.title = (TextView) this.findViewById(R.id.textViewP);
        this.text = (TextView) this.findViewById(R.id.textView_message);
        //
        Intent intent = this.getIntent();

        String last_ = intent.getStringExtra("lastname_");
        String first_ = intent.getStringExtra("first_");
        String age_ = intent.getStringExtra("age_");
        String domain_ = intent.getStringExtra("domain_");
        String phone_ = intent.getStringExtra("phone_");
        this.num_phone = intent.getStringExtra("phone_");
        //TextView test = (TextView) this.findViewById(R.id.textView2);
        String action_text = "Your registration has been registered with the following information:\n" +
                "First name: " + first_ + "\n" +
                "Last name: " + last_ +"\n" +
                "Age: " + age_ + "\n" +
                "area of competence: " + domain_ +"\n" +
                "phone number: " + phone_ +"\n";
        //test.setText("last");
        //test.setText(intent.getStringExtra("lastname_"));
        this.title.setText(first_ + " "+ last_);
        this.text.setText(action_text);

    }

    // The method is called when the user clicks the "Back" button.
    public void goBack()  {
        // Calling onBackPressed() method to back to the previous Activity.
        this.onBackPressed();
    }
    public void act_3(){
        Intent intent = new Intent(this, Activity3.class);
        intent.putExtra("num", this.num_phone);
        startActivity(intent);
    }
}