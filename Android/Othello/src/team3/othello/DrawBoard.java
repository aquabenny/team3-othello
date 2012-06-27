package team3.othello;

import android.view.*;
import android.content.Context;
import android.graphics.*;

public class DrawBoard extends View {

	
	private float width;
	private float height;
	private int seleX;
	private int seleY;
	private final Rect selRect = new Rect();
	private final Game game;
	
	public DrawBoard(Context context){
		super(context);
		this.game = (Game) context;
	}
	
	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh){
		width = w/8f;
		height = h/8f;
		getRect(seleX, seleY, selRect);
		super.onSizeChanged(w, h, oldw, oldh);
	}
	
	private void getRect(int x, int y, Rect rect){
		//Stuff
	}
	
	protected void onDraw(Canvas canvas){
		Paint bkg = new Paint();
		bkg.setColor(getResources().getColor(R.color.background));
		canvas.drawRect(0,0, getWidth(), getHeight(), bkg);	
		
		Paint line = new Paint();
		line.setColor(getResources().getColor(R.color.gridLine));
	}
	
}
