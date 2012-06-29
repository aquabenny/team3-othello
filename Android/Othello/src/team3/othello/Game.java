package team3.othello;

import team3.mechanicsAI.Mechanics;
import team3.othello.R;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.graphics.*;

public class Game extends Activity implements OnClickListener {
	
	LinearLayout ll;
	Draw2d c;
	Mechanics m;
	
	boolean isError = true;
	
	//Create this stuff when Activity is started	
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.game);
		
		String tag = "IntentDiff: ";
		String tag2 = "IntentColor: ";
		//Get Difficulty and player color
		String aiLevel = getIntent().getStringExtra("Difficulty");
		String colorChoice = getIntent().getStringExtra("Color");
		Log.d(tag, aiLevel);
		Log.d(tag2, colorChoice);
		
		View hintButton = findViewById(R.id.hint);
		hintButton.setOnClickListener(this);
		View undoButton = findViewById(R.id.undo);
		undoButton.setOnClickListener(this);
		View redoButton = findViewById(R.id.redo);
		redoButton.setOnClickListener(this);
		View quitButton = findViewById(R.id.quit);
		quitButton.setOnClickListener(this);
		
		ll = (LinearLayout) findViewById(R.id.gameBoard);
		m = new Mechanics();
		c = new Draw2d(this, m);
		
		Draw2d pcc = new Draw2d(this, m);
		Bitmap result = Bitmap.createBitmap(25, 25, Bitmap.Config.ARGB_8888);
		Canvas canvas = new Canvas(result);
		pcc.draw(canvas);
		pcc.setLayoutParams(new LayoutParams(500, 500));
		ll.addView(pcc);
		
		/*
		Paint paint = new Paint();
		paint.setStyle(Paint.Style.FILL);
		paint.setColor(Color.BLACK);
		canvas.drawCircle(100, 100, 25, paint);
		*/
	}
	
	
	//When a button is clicked, pass instructions
	public void onClick(View v){
		String buttonHit = "Action: ";
		String moveMade = "Move: ";
		switch(v.getId()){
		case R.id.hint:{
			String needAHint = "SHOW_NEXT_POS";
			Log.d(buttonHit, needAHint);
			//Place Xs or something on possible moves
			break;
			}
		case R.id.undo:{
			String oops = "UNDO";
			Log.d(buttonHit, oops);
			//Undo move
			if(isError == true){
				Intent i = new Intent(this, Alerts.class);
				i.putExtra("Error", "undo");
				startActivity(i);
			}
			break;
			}
		case R.id.redo:{
			String ctrlY = "REDO";
			Log.d(buttonHit, ctrlY);
			//Redo
			if(isError == true){
				Intent i = new Intent(this, Alerts.class);
				i.putExtra("Error", "redo");
				startActivity(i);
			}
			break;
			}
		case R.id.quit:{
			String quitter = "Quit Game";
			Log.d(buttonHit, quitter);
			finish();
			break;
			}	
		}
	}

}
