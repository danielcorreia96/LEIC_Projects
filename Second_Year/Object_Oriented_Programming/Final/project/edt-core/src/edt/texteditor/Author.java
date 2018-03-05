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
	public String getName(){	
	  return _name;	
	}
	
	public String getEmail(){	
	  return _email;	
	}
	
	public void setName(String name){
	    _name = name;	
	}
	
	public void setEmail(String email){
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