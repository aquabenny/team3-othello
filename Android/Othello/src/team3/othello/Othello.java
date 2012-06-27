package team3.othello;

/*
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;*/

import team3.othello.R;
import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;
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
       
       /**
       //Read info from Radio buttons
       //Declare radio buttons
       RadioGroup difficulty;
       difficulty = (RadioGroup) findViewById(R.id.diffGroup);
       //Get selected radio button
       int selectedDiff = difficulty.getCheckedRadioButtonId();
       RadioButton selected = ((RadioButton)findViewById(selectedDiff));
       String diffSelected = selected.getText().toString();
       String message = "Selected diff: ";
       
       Log.d(message, diffSelected);
       
       
       /*
        * Going to change tomorrow to follow this:
     	* http://android-er.blogspot.com/2009/11/radiogroup-and-radiobutton.html
     	* http://portiaplante.com/android/lectures/Android%20-%20Lecture%2014%20-%20Forms%203%20More%20Form%20Controls.pdf
        
       
       
       RadioGroup colorChoice;
       colorChoice = (RadioGroup) findViewById(R.id.colorGroup);
       //Get selected Radio Button
       int selectedColor = colorChoice.getCheckedRadioButtonId();
       RadioButton colorSelect = ((RadioButton)findViewById(selectedColor));
       String colorSelected = colorSelect.getText().toString();
       String message2 = "Selected color: ";
       Log.d(message2, colorSelected);
       */
    }
	
	public void onClick(View v){
		//Actions for button clicks
		switch(v.getId()){
		case R.id.startButton:
			//Get Difficulty Data
			RadioGroup diff;
			RadioGroup color;
			diff = (RadioGroup) findViewById(R.id.diffGroup);
			int selectDiff = diff.getCheckedRadioButtonId();
			RadioButton diffSelected = ((RadioButton)findViewById(selectDiff));
			String difficulty = diffSelected.getText().toString();
			String tag = "Selection: ";
			Log.d(tag, difficulty);
			
			//Get Color Data
			color = (RadioGroup) findViewById(R.id.colorGroup);
			int selectColor = color.getCheckedRadioButtonId();
			RadioButton colorSelect = ((RadioButton)findViewById(selectColor));
			String colorSelected = colorSelect.getText().toString();
			Log.d(tag, colorSelected);
			
			//Start Activity
			Intent i = new Intent(this, Game.class);
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