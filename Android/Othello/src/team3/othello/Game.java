package team3.othello;

import team3.mechanicsAI.Mechanics;
import team3.othello.R;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.graphics.*;

public class Game extends Activity implements OnClickListener {
	
	LinearLayout ll;
	Draw2d c;
	Mechanics m;
	
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
		
		
		/*
		//Setting up game board buttons - Column A
		View a1Button = findViewById(R.id.a1);
		a1Button.setOnClickListener(this);
		View a2Button = findViewById(R.id.a2);
		a2Button.setOnClickListener(this);
		View a3Button = findViewById(R.id.a3);
		a3Button.setOnClickListener(this);
		View a4Button = findViewById(R.id.a4);
		a4Button.setOnClickListener(this);
		View a5Button = findViewById(R.id.a5);
		a5Button.setOnClickListener(this);
		View a6Button = findViewById(R.id.a6);
		a6Button.setOnClickListener(this);
		View a7Button = findViewById(R.id.a7);
		a7Button.setOnClickListener(this);
		View a8Button = findViewById(R.id.a8);
		a8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column B
		View b1Button = findViewById(R.id.b1);
		b1Button.setOnClickListener(this);
		View b2Button = findViewById(R.id.b2);
		b2Button.setOnClickListener(this);
		View b3Button = findViewById(R.id.b3);
		b3Button.setOnClickListener(this);
		View b4Button = findViewById(R.id.b4);
		b4Button.setOnClickListener(this);
		View b5Button = findViewById(R.id.b5);
		b5Button.setOnClickListener(this);
		View b6Button = findViewById(R.id.b6);
		b6Button.setOnClickListener(this);
		View b7Button = findViewById(R.id.b7);
		b7Button.setOnClickListener(this);
		View b8Button = findViewById(R.id.b8);
		b8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column C
		View c1Button = findViewById(R.id.c1);
		c1Button.setOnClickListener(this);
		View c2Button = findViewById(R.id.c2);
		c2Button.setOnClickListener(this);
		View c3Button = findViewById(R.id.c3);
		c3Button.setOnClickListener(this);
		View c4Button = findViewById(R.id.c4);
		c4Button.setOnClickListener(this);
		View c5Button = findViewById(R.id.c5);
		c5Button.setOnClickListener(this);
		View c6Button = findViewById(R.id.c6);
		c6Button.setOnClickListener(this);
		View c7Button = findViewById(R.id.c7);
		c7Button.setOnClickListener(this);
		View c8Button = findViewById(R.id.c8);
		c8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column D
		View d1Button = findViewById(R.id.d1);
		d1Button.setOnClickListener(this);
		View d2Button = findViewById(R.id.d2);
		d2Button.setOnClickListener(this);
		View d3Button = findViewById(R.id.d3);
		d3Button.setOnClickListener(this);
		View d4Button = findViewById(R.id.d4);
		d4Button.setOnClickListener(this);
		View d5Button = findViewById(R.id.d5);
		d5Button.setOnClickListener(this);
		View d6Button = findViewById(R.id.d6);
		d6Button.setOnClickListener(this);
		View d7Button = findViewById(R.id.d7);
		d7Button.setOnClickListener(this);
		View d8Button = findViewById(R.id.d8);
		d8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column E
		View e1Button = findViewById(R.id.e1);
		e1Button.setOnClickListener(this);
		View e2Button = findViewById(R.id.e2);
		e2Button.setOnClickListener(this);
		View e3Button = findViewById(R.id.e3);
		e3Button.setOnClickListener(this);
		View e4Button = findViewById(R.id.e4);
		e4Button.setOnClickListener(this);
		View e5Button = findViewById(R.id.e5);
		e5Button.setOnClickListener(this);
		View e6Button = findViewById(R.id.e6);
		e6Button.setOnClickListener(this);
		View e7Button = findViewById(R.id.e7);
		e7Button.setOnClickListener(this);
		View e8Button = findViewById(R.id.e8);
		e8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column F
		View f1Button = findViewById(R.id.f1);
		f1Button.setOnClickListener(this);
		View f2Button = findViewById(R.id.f2);
		f2Button.setOnClickListener(this);
		View f3Button = findViewById(R.id.f3);
		f3Button.setOnClickListener(this);
		View f4Button = findViewById(R.id.f4);
		f4Button.setOnClickListener(this);
		View f5Button = findViewById(R.id.f5);
		f5Button.setOnClickListener(this);
		View f6Button = findViewById(R.id.f6);
		f6Button.setOnClickListener(this);
		View f7Button = findViewById(R.id.f7);
		f7Button.setOnClickListener(this);
		View f8Button = findViewById(R.id.f8);
		f8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column G
		View g1Button = findViewById(R.id.g1);
		g1Button.setOnClickListener(this);
		View g2Button = findViewById(R.id.g2);
		g2Button.setOnClickListener(this);
		View g3Button = findViewById(R.id.g3);
		g3Button.setOnClickListener(this);
		View g4Button = findViewById(R.id.g4);
		g4Button.setOnClickListener(this);
		View g5Button = findViewById(R.id.g5);
		g5Button.setOnClickListener(this);
		View g6Button = findViewById(R.id.g6);
		g6Button.setOnClickListener(this);
		View g7Button = findViewById(R.id.g7);
		g7Button.setOnClickListener(this);
		View g8Button = findViewById(R.id.g8);
		g8Button.setOnClickListener(this);
		
		//Setting up game board buttons - Column H
		View h1Button = findViewById(R.id.h1);
		h1Button.setOnClickListener(this);
		View h2Button = findViewById(R.id.h2);
		h2Button.setOnClickListener(this);
		View h3Button = findViewById(R.id.h3);
		h3Button.setOnClickListener(this);
		View h4Button = findViewById(R.id.h4);
		h4Button.setOnClickListener(this);
		View h5Button = findViewById(R.id.h5);
		h5Button.setOnClickListener(this);
		View h6Button = findViewById(R.id.h6);
		h6Button.setOnClickListener(this);
		View h7Button = findViewById(R.id.h7);
		h7Button.setOnClickListener(this);
		View h8Button = findViewById(R.id.h8);
		h8Button.setOnClickListener(this);
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
			break;
			}
		case R.id.redo:{
			String ctrlY = "REDO";
			Log.d(buttonHit, ctrlY);
			//Redo
			break;
			}
		case R.id.quit:{
			String quitter = "Quit Game";
			Log.d(buttonHit, quitter);
			finish();
			break;
			}	
		//Cases for making a move
		//Column A
		/*case R.id.a1:
			//Check if move is valid
			//Change Piece Color
			//Redraw board with new move, and AI move 
			break;
		case R.id.a2:
			break;
		case R.id.a3:
			break;
		case R.id.a4:
			break;
		case R.id.a5:
			break;
		case R.id.a6:
			break;
		case R.id.a7:
			break;
		case R.id.a8:
			break;
		//Column B
		case R.id.b1:
			break;
		case R.id.b2:
			break;
		case R.id.b3:
			break;
		case R.id.b4:
			break;
		case R.id.b5:
			break;
		case R.id.b6:
			break;
		case R.id.b7:
			break;
		case R.id.b8:
			break;
		//Column C
		case R.id.c1:
			break;
		case R.id.c2:
			break;
		case R.id.c3:
			break;
		case R.id.c4:
			break;
		case R.id.c5:
			break;
		case R.id.c6:
			break;
		case R.id.c7:
			break;
		case R.id.c8:
			break;
		//Column D
		case R.id.d1:
			break;
		case R.id.d2:
			break;
		case R.id.d3:
			break;
		case R.id.d4:
			break;
		case R.id.d5:
			break;
		case R.id.d6:
			break;
		case R.id.d7:
			break;
		case R.id.d8:
			break;
		//Column E
		case R.id.e1:
			break;
		case R.id.e2:
			break;
		case R.id.e3:
			break;
		case R.id.e4:
			break;
		case R.id.e5:
			break;
		case R.id.e6:
			break;
		case R.id.e7:
			break;
		case R.id.e8:
			break;
		//Column F
		case R.id.f1:
			break;
		case R.id.f2:
			break;
		case R.id.f3:
			break;
		case R.id.f4:
			break;
		case R.id.f5:
			break;
		case R.id.f6:
			break;
		case R.id.f7:
			break;
		case R.id.f8:
			break;
		//Column G
		case R.id.g1:
			break;
		case R.id.g2:
			break;
		case R.id.g3:
			break;
		case R.id.g4:
			break;
		case R.id.g5:
			break;
		case R.id.g6:
			break;
		case R.id.g7:
			break;
		case R.id.g8:
			break;
		//Column H
		case R.id.h1:
			break;
		case R.id.h2:
			break;
		case R.id.h3:
			break;
		case R.id.h4:
			break;
		case R.id.h5:
			break;
		case R.id.h6:
			break;
		case R.id.h7:
			break;
		case R.id.h8:
			break;
			*/
		}
	}

}
