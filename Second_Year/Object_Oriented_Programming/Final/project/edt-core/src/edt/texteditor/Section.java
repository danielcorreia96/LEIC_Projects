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

	public ArrayList<Paragraph> getParagraphs(){
		return _paragraphs;
	}

	/** 
	 *	Gets section that has a specific unique id.
	 *
	 *	@param unique_id  the unique id
	 *	@return the section that has the unique id
	 */
	public Section getSection(String unique_id){
	  	for(Section section : _subsections){
			if (section.getId().equals(unique_id)){
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
	public Section getSection(int local_id) throws NoSuchSectionException {
		try{
			return _subsections.get(local_id);
		}
		catch(IndexOutOfBoundsException e){
			throw new NoSuchSectionException();
		}
	}

	public Paragraph getParagraph(int localid) throws NoSuchParagraphException {
		try{
			return _paragraphs.get(localid);
		}
		catch(IndexOutOfBoundsException e){
			throw new NoSuchParagraphException();
		}
	}

/*==============================================================================
 *	Constructors
 *============================================================================*/
	/** 
	 *  Creates a section.
	 * 
	 */
	public Section(){}
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
 *	Section Methods
 *============================================================================*/
	/** 
	 *	Inserts a new subsection in a specific position.
	 *
	 *	@param index       the specific position
	 *	@param subsection  the new subsection
	 */
	public Section insertSection(int index,String id,String title){
	    Section subsection = new Section(id, title);
		try{
			_subsections.add(index,subsection);
		}
		catch(IndexOutOfBoundsException e){
			_subsections.add(subsection);
		}
	    return subsection;
	}
	public List<String> removeSection(int index) throws NoSuchSectionException{
		try{
			Section removedsection = _subsections.remove(index);
			List<String> removedIds = removedsection.getAllIds();
			return removedIds;
		}
		catch(IndexOutOfBoundsException e){ 
			throw new NoSuchSectionException();
		}
	}
	 public int getSubsectionsSize(){
 		return _subsections.size();
 	}

	public String getSubsectionId(int localid) throws NoSuchSectionException {
		return getSection(localid).getId();
	}

	public void setSubsectionId(int localid, String uniqueid) throws NoSuchSectionException {
		Section newsubsection = getSection(localid);
		newsubsection.setId(uniqueid);
		_subsections.set(localid,newsubsection);
	}

	public void updateSubsectionId(String uniqueid){
		for (int i = 0; i < _subsections.size();i++) {
			Section subsection = _subsections.get(i);
			if(subsection.getId().equals(uniqueid)){
				subsection.setId("");
				_subsections.set(i,subsection);
			}
		}
	}
/*==============================================================================
 *	Paragraph Methods
 *============================================================================*/
	/** 
	 *  Inserts a new paragraph in a specific position.
	 *  
	 *	@param index      the specific position
	 * 	@param paragraph  the paragraph
	 */
	public void insertParagraph(int index,String text){
		Paragraph paragraph = new Paragraph(text);
		try{
			_paragraphs.add(index,paragraph);
		}
		catch(IndexOutOfBoundsException e){
			_paragraphs.add(paragraph);
		}
	}

	public String removeParagraph(int index) throws NoSuchParagraphException{
		try{
			return _paragraphs.remove(index).getId();
		}
		catch(IndexOutOfBoundsException e){ throw new NoSuchParagraphException(); }
	}
	
	public void editParagraph(int index, String text) throws NoSuchParagraphException {
	    getParagraph(index).setText(text);
	}
	
	public String getParagraphId(int index) throws NoSuchParagraphException {
	    return getParagraph(index).getId();
	}
	
	public void setParagraphId(int localid, String uniqueid) throws NoSuchParagraphException {
		Paragraph newparagraph = getParagraph(localid);
		newparagraph.setId(uniqueid);
		_paragraphs.set(localid,newparagraph);		
	}

	public void updateParagraphId(String uniqueid){
		for (int i = 0; i < _paragraphs.size();i++) {
			Paragraph paragraph = _paragraphs.get(i);
			if(paragraph.getId().equals(uniqueid)){
				paragraph.setId("");
				_paragraphs.add(i,paragraph);
			}
		}
	}

/*==============================================================================
 *	Other Methods
 *============================================================================*/
	/** 
	 * 	Gets number of bytes.
	 *
	 * 	@return the number of bytes of the section
	 */
	public int getBytes(){
		int bytes = 0;
		for(Paragraph paragraph: _paragraphs){
			bytes +=paragraph.getBytes();
		}
		for(Section paragraph: _subsections){
			bytes += paragraph.getBytes();
		}
		return bytes + _title.length();
	}
	
	public void accept(Visitor v){
		v.visitSection(this);
	}

	public List<String> getAllIds(){
		List<String> totalids = new ArrayList<String>();
		if(getId().equals("") == false){	
			totalids.add(getId());	
		}
		for(Paragraph paragraph : getParagraphs()){
			if(paragraph.getId().equals("") == false){	
				totalids.add(paragraph.getId());
			}
		}
		for(Section subsection : getSubsections()){
			totalids.addAll(subsection.getAllIds());
		}	
		return totalids;
	}
}