package team3.othello;

import team3.othello.R;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.graphics.*;

public class Game extends Activity implements OnClickListener {

	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.game);
		
		//Going to have to define buttons here
	}
	
	public void onClick(View v){
		/*
		switch(v.getId()){
		case R.id.hint_button:
			break;
		case R.id.undo_button:
			break;
		case R.id.redo_button:
			break;
		case R.id.exit_button:
			finish();
			break;
		}*/
	}

}
