package team3.othello;

import team3.othello.R;
import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class Othello extends Activity implements OnClickListener {

	/** Called when the activity is first created. */
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
       
       
       /*
        * Going to change tomorrow to follow this:
     	* http://android-er.blogspot.com/2009/11/radiogroup-and-radiobutton.html
     	* http://portiaplante.com/android/lectures/Android%20-%20Lecture%2014%20-%20Forms%203%20More%20Form%20Controls.pdf
     	* */

    }
	
	public void onClick(View v){
		//Actions for button clicks
		switch(v.getId()){
		case R.id.startButton:{
			//Get Difficulty Data from radio buttons
			RadioGroup diff;
			RadioGroup color;
			diff = (RadioGroup) findViewById(R.id.diffGroup);
			int selectDiff = diff.getCheckedRadioButtonId();
			RadioButton diffSelected = ((RadioButton)findViewById(selectDiff));
			String difficulty = diffSelected.getText().toString();
			String tag = "Diff Selection: ";
			Log.d(tag, difficulty); // Testing, letting debugger know what option we chose
			
			//Get Color Data
			color = (RadioGroup) findViewById(R.id.colorGroup);
			int selectColor = color.getCheckedRadioButtonId();
			RadioButton colorSelect = ((RadioButton)findViewById(selectColor));
			String colorSelected = colorSelect.getText().toString();
			String tag2 = "Color Selected: ";
			Log.d(tag2, colorSelected); // Testing, letting debugger know what option we chose
			
			//Start the Game Activity
			Intent i = new Intent(this, Game.class);
			i.putExtra("Difficulty", difficulty); //Passes difficulty and color setting to the Game class
			i.putExtra("Color", colorSelected);
			startActivity(i);
			break;
			}
		case R.id.about_button:{
			String tag = "Action: ";
			String abouts = "About";
			Intent j = new Intent(this, About.class);
			startActivity(j);
			Log.d(tag, abouts); //Debugger testing message
			break;
			}
		case R.id.highScore:{
			String tagger = "Action: ";
			String hs = "View High Scores";
			Intent k = new Intent(this, HighScores.class);
			startActivity(k);
			Log.d(tagger, hs); //Debugger testing message
			break;
			}
		}
	}
	
}