package edt.texteditor;

import java.io.ObjectOutputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
 
import java.io.ObjectInputStream;
import java.io.BufferedInputStream;
import java.io.FileInputStream;

import java.io.BufferedReader;
import java.io.FileReader;

import java.io.IOException;

public class Editor {

/*==============================================================================
 *	Attributes
 *============================================================================*/
	private Document _document;

/*==============================================================================
 *	Getters and Setters
 *============================================================================*/
	public Document getDocument(){
		return _document;
	}

	public void newDocument(){
		_document = new Document();
	}

/*==============================================================================
 *	Constructor
 *============================================================================*/
	public Editor(String filename){
		try{
			_document = new Document();
			if(filename.equals("") == false){
				BufferedReader r = new BufferedReader(new FileReader(filename));
				String linha;
				_document.setTitle(r.readLine());
				Section old_section = _document;
				while ((linha = r.readLine()) != null) {
					String dados[] = linha.split("\\|");
					if(dados[0].equals("SECTION")){
						old_section = _document.insertSection(-1,dados[1],dados[2]);
						if(old_section.getId().equals("") == false){ 
						_document.addTextElement(old_section);
						}
					}	
					else if(dados[0].equals("PARAGRAPH")){
						old_section.insertParagraph(-1,dados[1]);
					}
					else { // Author
						for (String author : dados) {
							String info[] = author.split("/");
							_document.addAuthor(info[0],info[1]);
						}
					}
				}
				r.close();
			}
		}
		catch(IOException e){ 	e.printStackTrace();	}
	}

/*==============================================================================
 *	Methods
 *============================================================================*/
	public void save(String filename) {
			try {
				_document.setFilename(filename);
				ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(filename)));
				oos.writeObject(getDocument());
				oos.close();
			}
			catch(IOException e){	e.printStackTrace();	}

	}

	public void open(String filename) throws FileNotFoundException{
		try {
			ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(new FileInputStream(filename)));	
			Document documento = (Document)ois.readObject();
			ois.close();
			_document = documento;
		}
		catch(IOException e) {
			throw new FileNotFoundException();
		}
		catch(ClassNotFoundException e){	e.printStackTrace();	}
	}

	public String getDocumentFilename(){
		return _document.getFilename();
	}
}
