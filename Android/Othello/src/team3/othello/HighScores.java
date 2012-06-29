package team3.othello;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.IOException; 

import org.xmlpull.v1.XmlPullParser; //Import XML parsers
import org.xmlpull.v1.XmlPullParserException;

import android.content.res.Resources;
import android.content.res.XmlResourceParser;
import android.app.Activity;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class HighScores extends Activity {

	EditText txtData;
	
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.highscores);
		
		TextView myXML = (TextView)findViewById(R.id.xml_scores);
		
		//From Lab 3 - Read in the XML file and display it in TextView
		try{
		File myFile = new File("/sdcard/example.xml");
		FileInputStream fStream = new FileInputStream(myFile);
		BufferedReader reader = new BufferedReader(new InputStreamReader(fStream));
		String aDataRow = "";
		String aBuffer = "";
		while((aDataRow = reader.readLine()) != null){
			aBuffer += aDataRow + "\n";
		}
		
		myXML.setText(aBuffer);
		reader.close();
		Toast.makeText(getBaseContext(), "Done reading SDCard", Toast.LENGTH_SHORT).show();
		}
		catch(Exception e){
			Toast.makeText(getBaseContext(), e.getMessage(), Toast.LENGTH_SHORT).show();
		}
		 	
	}
	
}
