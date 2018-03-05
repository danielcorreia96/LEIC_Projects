package edt.texteditor;

import java.io.Serializable;

public abstract class TextElement implements Serializable {
	private String _id = "";
	
	public TextElement(){}
	
	public TextElement(String id){
		_id = id;
	}
	public String getId(){	
		return _id;	
	}
	public void setId(String id){
		_id = id;
	}
	public abstract void accept(Visitor v);
}