package edt.texteditor;

import java.io.Serializable;

public abstract class TextElement implements Serializable {
	private String _id = "";
	
	public TextElement(){}
	
	public TextElement(String id){
		_id = id;
	}
	public String get_id(){	
		return _id;	
	}
	public void set_id(String id){
		_id = id;
	}
	public abstract String showContent();

}