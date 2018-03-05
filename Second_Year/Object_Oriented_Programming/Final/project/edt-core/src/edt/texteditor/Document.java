package edt.texteditor;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;

import java.io.Serializable;


public class Document extends Section implements Serializable {

/*==============================================================================
 *	Attributes
 *============================================================================*/
	private TreeMap<String,TextElement> _elements = new TreeMap<String,TextElement>();
	private TreeMap<String,Author> _authors = new TreeMap<String,Author>();
	private String _filename = "";

/*==============================================================================
 *	Getters and Setters
 *============================================================================*/
	public String getFilename(){
		return _filename;
	}

	public void setFilename(String filename){
		_filename = filename;
	}

	public TreeMap<String,Author> getAuthors()	{	
		return _authors;			
	}

/*==============================================================================
 *	Author methods
 *============================================================================*/
	public List<Author> getAuthorsData(){
		List<Author> authorsdata = new ArrayList<Author>(_authors.values());
		return authorsdata;
	}

	public boolean addAuthor(String name, String email){
		if(_authors.containsKey(name)){
			return false;
		}
		else{
			_authors.put(name,new Author(name,email));
			return true;	
		}	
	}
 
/*==============================================================================
 *	TextElement methods
 *============================================================================*/
 	public void addTextElement(TextElement element){
 		_elements.put(element.getId(),element);
 	}

 	 public boolean hasTextElement(String id){
 		return _elements.containsKey(id);
 	}
 	public void removeTextElement(String id){
 		if(hasTextElement(id)){
 			_elements.remove(id);
 		}
 	}
 	
 	public void removeTextElements(List<String> removedIds){
 		for(String id : removedIds){
 			if(hasTextElement(id))
 				removeTextElement(id);
	    }
	}   

 	public TextElement getTextElement(String id) throws NoSuchTextElementException{
		TextElement element = _elements.get(id); 
 		if (element == null){
 			throw new NoSuchTextElementException();
 		}
 		else{ 
 			return element;
 		}
	}
 	
 	public void showTextElement(Visitor v, String id) throws NoSuchTextElementException{
	    try{
	     	TextElement element = getTextElement(id);
	     	element.accept(v);
	    }
	    catch(NoSuchTextElementException e) { 
	    	throw new NoSuchTextElementException();
	    }
 	}
 	
/*==============================================================================
 *	Document methods
 *============================================================================*/
 	public int getIdentifiers(){
 		return _elements.size();
 	}
 	
 	public void accept(Visitor v){
 		v.visitDocument(this);
 	}

 	public boolean nameSection(String uniqueid, int localid, Section section) throws NoSuchSectionException {
      // 1. Remover o textelement antigo com uniqueid
		String oldid = section.getSubsectionId(localid);
		updateSubsectionId(uniqueid);
		section.updateParagraphId(uniqueid);
		removeTextElement(uniqueid);

        // 2. Nomear seccao
		removeTextElement(oldid);
		section.setSubsectionId(localid,uniqueid);
		addTextElement(section.getSection(localid));

		if(oldid.equals(""))
			return false;
		return true;
	}

	public boolean nameParagraph(String uniqueid, int localid, Section section) throws NoSuchParagraphException {
       	// 1. Remover o textelement antigo com uniqueid
       	String oldid = section.getParagraphId(localid);
		updateSubsectionId(uniqueid);
		section.updateParagraphId(uniqueid);
		removeTextElement(uniqueid);

		// 2. Nomear paragrafo

		removeTextElement(oldid);
		section.setParagraphId(localid,uniqueid);
		addTextElement(section.getParagraph(localid));
		
		if (oldid.equals("")) 
			return false;
		return true;
	}
	
}
