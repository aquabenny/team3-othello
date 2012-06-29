package team3.othello;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.IOException; 
import java.util.ArrayList;

import org.xmlpull.v1.XmlPullParser; //Import XML parsers
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import android.content.res.Resources;
import android.content.res.XmlResourceParser;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class HighScores extends Activity {
	
	//Constant members used in XML file - Nodes in the parser
	/*private static final String RESULTS = "results";
	//Nodes that will repeat
	private static final String RESULT = "result";
	private static final String PLACE = "id";
	private static final String NAME = "name";
	private static final String SCORE = "score";
	private ArrayList<String> scores;*/
		
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.highscores);
		
		TextView myXML = (TextView)findViewById(R.id.xml_scores);
		
		/*try {
			parser();
		} catch (XmlPullParserException e) {
			e.printStackTrace();
			Toast.makeText(getBaseContext(), "PullParserException", Toast.LENGTH_SHORT);
		} catch (IOException e) {
			e.printStackTrace();
			Toast.makeText(getBaseContext(), "IOException", Toast.LENGTH_SHORT);
		}*/
		
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
	
	/*public void parser() throws XmlPullParserException, IOException {
		//Create new parser objects
		XmlPullParserFactory factory = XmlPullParserFactory.newInstance();
		factory.setNamespaceAware(true);
		XmlPullParser pullParser = factory.newPullParser(); //Parser we'll actually use
		
		//Access the file, create input stream from file
		File myFile = new File("/sdcard/example.xml");
		FileInputStream fins = new FileInputStream(myFile);
		pullParser.setInput(new InputStreamReader(fins));
		
		int eventType = pullParser.getEventType(); //Help break apart XML file by tags
		
		String node = pullParser.getName();
		Log.d("pullParser", "Starting file");
		/*
		 * Parser tags file in the following way:
		 * START TAG
		 * TEXT
		 * END TAG
		 * END DOCUMENT 
		 
		
		while(eventType != XmlPullParser.END_DOCUMENT){//Starts parsing loop
			if(eventType == XmlPullParser.START_DOCUMENT){
				Log.d("parser:", "Starting Document");
			}
			else if(eventType == XmlPullParser.END_DOCUMENT){
				Log.d("parser:", "Ending Document");
			}
			else if(eventType == XmlPullParser.START_TAG){
				node = pullParser.getName();
				Log.d("parser:", node);
				if(node.contentEquals(RESULTS)){
					//scores = new ArrayList<String>();
				}
			}
			Log.d("parser: ", "starting scores");
			if(node.contentEquals(PLACE)){
				
			}
		}
		
	}*/
	
}
