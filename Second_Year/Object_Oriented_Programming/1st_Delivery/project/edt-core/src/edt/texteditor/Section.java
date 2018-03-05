package edt.texteditor;

import java.util.List;
import java.util.ArrayList;
import java.io.Serializable;

/** 
 *  Class that represents the concept of a Section. 
 *	Has a title, a list of subsections and a list of paragraphs.
 */
public class Section extends TextElement implements Serializable {

/*==============================================================================
 *	Attributes
 *============================================================================*/
	/**
	 *  The list of subsections.
	 */
	private ArrayList<Section> _subsections = new ArrayList<Section>();
	/** 
	 *  The list of paragraphs.
	 */
	private ArrayList<Paragraph> _paragraphs = new ArrayList<Paragraph>();
	/** 
	 *  The title.
	 */
	private String _title = "";

/*==============================================================================
 *	Getters and Setters
 *============================================================================*/
	/** 
	 *  Returns the title of the section.
	 *
	 *  @return _title
	 */
	public String getTitle(){
	  return _title;
	}

	/** 
	 *  Changes the tile of the section.
	 *
	 *  @param title  the new title
	 */
	public void setTitle(String title){
		_title = title;
	}

	/** 
	 *  Returns the list of subsections.
	 * 
	 *  @return _subsections
	 */
	public ArrayList<Section> getSubsections(){
		return _subsections;
	}

	/** 
	 *	Gets section that has a specific unique id.
	 *
	 *	@param unique_id  the unique id
	 *	@return the section that has the unique id
	 */
	public Section getSection(String unique_id){
	  for(Section section : _subsections){
	    if (section.get_id()==unique_id){
	      return section;
	    }
	  }
	  return null;
	}

	/** 
	 *	Gets section located at a local id.
	 *	
	 *	@param local_id  the local id
	 *	@return the section located at local id
	 */
	public Section getSection(int local_id){
		return _subsections.get(local_id);
	}

/*==============================================================================
 *	Constructors
 *============================================================================*/
	/** 
	 *  Creates a section.
	 * 
	 */
	public Section(){

	}
	/** 
	 *  Creates a section with a title.
	 * 
	 *  @param title
	 *         	the title of the section
	 */
	public Section(String title){
		_title = title;
	}

	/** 
	 *  Creates a section with a title and an id.
	 *
	 *  @param title  the title of the section
	 *  @param id     the id of the section
	 */
	public Section(String id, String title){
		super(id);
		_title=title;
	}
	
/*==============================================================================
 *	Methods
 *============================================================================*/
	/**
	 *	FIXME
	 *	Entrega Final
	 */
	public String showContent(){
	     return "";
	}

	/** 
	 *	Inserts a new subsection in a specific position.
	 *
	 *	@param index       the specific position
	 *	@param subsection  the new subsection
	 */
	public Section insertSection(int index,String id,String title){
	    Section subsection = new Section(id, title);
		if((index == -1)||(index >= _subsections.size())){
			_subsections.add(subsection);
		}
		else{ 
			_subsections.add(index,subsection);
		}
	     return subsection;
	}
	
	/** 
	 *	Lists the titles and ids of the subsections.
	 *
	 *	@return the list with the title and id of the subsections
	 */
	public List<String> listSections(){
		List<String> sections_list = new ArrayList<String>();
		for (Section section : _subsections) {
			sections_list.add(section.get_id());
			sections_list.add(section.getTitle());
		}
		return sections_list;
	}

	/** 
	 *  Inserts a new paragraph in a specific position.
	 *  
	 *	@param index      the specific position
	 * 	@param paragraph  the paragraph
	 */
	public void insertParagraph(int index,String text){
		Paragraph paragraph = new Paragraph(text);
		if((index == -1)||(index >= _paragraphs.size())){
			_paragraphs.add(paragraph);
		}
		else{ 
			_paragraphs.add(index,paragraph);
		}
	}

	/** 
	 * 	Gets number of bytes.
	 *
	 * 	@return the number of bytes of the section
	 */
	public int getBytes(){
		int bytes = 0;

		for(Paragraph p: _paragraphs){
			bytes+=p.getParagraphBytes();
		}

		for(Section s: _subsections){
			bytes+= s.getBytes();
		}

		return bytes + _title.length();
	}
	
}
