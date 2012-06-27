package team3.othello;

/*
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;*/

import team3.othello.R;
import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RadioButton;
import android.widget.RadioGroup;

//import android.graphics.*; //Import standard Android graphics library 

//import team3.othello.AI; //Import AI code for difficulty settings

public class Othello extends Activity implements OnClickListener {
	/** Called when the activity is first created. */
    /**
     * ***************************************************************
     *                     ANDROID FUNCTIONS
     * ***************************************************************
     */
	@Override // Parts for Android application
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
       // Set up Main Menu Buttons 
       View beginButton = findViewById(R.id.startButton);
       beginButton.setOnClickListener(this);
       View aboutUs = findViewById(R.id.about_button);
       aboutUs.setOnClickListener(this);
       View seeHighScore = findViewById(R.id.highScore);
       seeHighScore.setOnClickListener(this);
       
       //Read info from Radio buttons
       //Declare radio buttons
       RadioGroup difficulty;
       RadioButton selected;
       difficulty = (RadioGroup) findViewById(R.id.diffGroup);
       //Get selected radio button
       int selectedDiff = difficulty.getCheckedRadioButtonId();
       //RadioButton easyButton = new RadioButton();
       //RadioButton mediumButton = new RadioButton();
       //RadioButton hardButton = new RadioButton;
       System.out.println(selectedDiff);
       /*
        * Going to change tomorrow to follow this:
     	* http://android-er.blogspot.com/2009/11/radiogroup-and-radiobutton.html
        */
       
       
       RadioGroup colorChoice;
       colorChoice = (RadioGroup) findViewById(R.id.colorGroup);
       //RadioButton whiteButton = new RadioButton();
       //RadioButton blackButton = new RadioButton();
       //Get selected Radio Button
       int selectedColor = colorChoice.getCheckedRadioButtonId();
       System.out.println(selectedColor);
    }
	
	public void onClick(View v){
		//Actions for button clicks
		switch(v.getId()){
		case R.id.startButton:
			Intent i = new Intent(this, GameBoard.class);
			startActivity(i);
			break;
		case R.id.about_button:
			Intent j = new Intent(this, About.class);
			startActivity(j);
			break;
		case R.id.highScore:
			//Intent k = new Intent(this, Scores.class);
			//startActivity(k);
			break;
		}
	}
	
    
	/**
     * ***************************************************************
     *                     GAME USER INTERFACE
     * ***************************************************************
     */
	//make a new radio button
	//set ActionListener, onClick -> start Activity(this.Othello, GameBoard.java 
	//buttons for each possible square on the board
	
	
	
	/**
     * ***************************************************************
     *                     HIGH SCORE STORAGE
     * ***************************************************************
     */
	
}