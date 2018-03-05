package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.textui.main.Message;

import edt.texteditor.Visitor;
import edt.texteditor.Document;
import edt.texteditor.Author;
import edt.texteditor.Paragraph;
import edt.texteditor.Section;

public class DocumentMetadataVisitor implements Visitor{
	private String content = "";

	public String getContent(){
		return content.substring(0,content.length()-1);

	}

	public void visitDocument(Document document){
		content += Message.documentTitle(document.getTitle()) + "\n";
		for(Author author : document.getAuthorsData()){
			content += Message.author(author.getName(),author.getEmail()) + "\n";
		}
		content += Message.documentSections(document.getSubsectionsSize()) + "\n";
		content += Message.documentBytes(document.getBytes()) + "\n";
		content += Message.documentIdentifiers(document.getIdentifiers()) + "\n";
	}

	public void visitSection(Section section){}
	public void visitParagraph(Paragraph paragraph){}
}