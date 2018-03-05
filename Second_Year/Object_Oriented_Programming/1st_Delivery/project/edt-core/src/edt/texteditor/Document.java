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

	public TreeMap<String,Author> get_authors()	{	
		return _authors;			
	}

/*==============================================================================
 *	Author methods
 *============================================================================*/
	public List<String> getAuthorsData(){
		List<String> authorsdata = new ArrayList<String>();
		for(Map.Entry<String,Author> entry : _authors.entrySet()){			
			authorsdata.add((entry.getValue()).get_name());
			authorsdata.add((entry.getValue()).get_email());
		}
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
 	public void add_TextElement(TextElement element){
 		_elements.put(element.get_id(),element);
 	}

 	public boolean has_TextElement(String id){
 		return _elements.containsKey(id);
 	}

 	public String show_TextElement(String id){
 		return _elements.get(id).showContent();
 	}

 	public TextElement get_TextElement(String id){
 		return _elements.get(id);
 	}
 	
/*==============================================================================
 *	Document methods
 *============================================================================*/
  	public List<String> getTopSections(){
 		ArrayList<Section> sections = getSubsections();
 		List<String> topSectionsList = new ArrayList<String>();
 		for (Section section : sections) {
			topSectionsList.add(section.get_id());
			topSectionsList.add(section.getTitle());
		}
		return topSectionsList;
 	}
 	public List<Integer> getMetaData(){
 		List<Integer> metadata = new ArrayList<Integer>();
 		metadata.add(getSubsections().size());
 		metadata.add(getBytes());
 		metadata.add(_elements.size());
 		return metadata;
 	}
}
