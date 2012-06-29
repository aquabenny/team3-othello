package team3.othello;

import team3.mechanicsAI.Mechanics;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;


public class Draw2d extends View{
	Mechanics m;
	public Draw2d(Context context, Mechanics m){
		super(context);
		this.m = m;
	}
	
	@Override
	protected void onDraw(Canvas c){
		super.onDraw(c);
		Paint paint = new Paint();
		paint.setStyle(Paint.Style.FILL);
		
		paint.setColor(Color.BLACK);
		c.drawPaint(paint);
		
		
		paint.setColor(Color.GREEN);
		//c.drawRect(20, 5, 50, 100, paint);
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				c.drawRect(60*i+5, 60*j+10 ,60*i+60 ,60*j+65, paint);
			}
		}
		
		
		paint.setAntiAlias(true);
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if(m.getState()[i][j] == m.BLACK){
					paint.setColor(Color.BLACK);
					c.drawCircle((float)32.5+i*60, (float)37.5+j*60, 25, paint);
				}
				if(m.getState()[i][j] == m.WHITE){
					paint.setColor(Color.WHITE);
					c.drawCircle((float)32.5+i*60, (float)37.5+j*60, 25, paint);
				}
			}
		}
		
		//c.drawCircle(80, 20, 20, paint);
		//paint.setColor(Color.RED);
		//paint.setStyle(Paint.Style.FILL);
		//paint.setAntiAlias(true);
		//paint.setTextSize(30);
		//c.drawText("This shit is pissing me off!", 30, 200, paint);
	}
}
