package edt.texteditor;

import java.util.Map;
import java.util.TreeMap;
import java.io.Serializable;

public class Paragraph extends TextElement implements Serializable{
/*==============================================================================
 *	Attributes
 *============================================================================*/
	private String _text = "";

/*==============================================================================
 *	Getters and Setters
 *============================================================================*/
	public String getText(){
		return _text;
	}
	
	public void setText(String text){
		_text = text;
	}	

/*==============================================================================
 *	Constructors
 *============================================================================*/
 	public Paragraph(String text){
		_text = text;
	}

	public Paragraph(String uniqueid, String text){
		super(uniqueid);
		_text = text;
	}

/*==============================================================================
 *	Methods
 *============================================================================*/
	public int getBytes(){
		return _text.length();
	}

	public void accept(Visitor v){
		v.visitParagraph(this);
	}

}