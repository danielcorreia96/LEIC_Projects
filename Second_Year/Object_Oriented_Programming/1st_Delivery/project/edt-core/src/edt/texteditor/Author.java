package edt.texteditor;

import java.io.Serializable;

public class Author implements Serializable {
	
/*==============================================================================
 *	Attributes
 *============================================================================*/
	private String _name = "";
	private String _email = "";

/*==============================================================================
 *	Getters and Setters
 *============================================================================*/
	public String get_name(){	
	  return _name;	
	}
	
	public String get_email(){	
	  return _email;	
	}
	
	public void set_name(String name){
	    _name = name;	
	}
	
	public void set_email(String email){
	    _email = email;
	}

/*==============================================================================
 *	Constructor
 *============================================================================*/
	public Author(String name, String email){
		_name = name;
		_email = email;
	}
}