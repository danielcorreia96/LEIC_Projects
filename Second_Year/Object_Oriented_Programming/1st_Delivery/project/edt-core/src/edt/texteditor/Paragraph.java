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
	public int getParagraphBytes(){
		return _text.length();
	}

/*==============================================================================
 *	Constructors
 *============================================================================*/
 	public Paragraph(String text){
		_text = text;
	}

	public Paragraph(String id, String text){
		super(id);
		_text = text;
	}

/*==============================================================================
 *	Methods
 *============================================================================*/
	public String showContent(){
		// FIXME ENTREGA FINAL
		return "";
	}

}