package edt.textui;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.textui.main.Message;

import edt.texteditor.Visitor;
import edt.texteditor.Document;
import edt.texteditor.Section;
import edt.texteditor.Paragraph;

public class TextElementVisitor implements Visitor {
	private String content = "";
	
	public String getContent(){	
		return content.substring(0,content.length()-1);	
	}

	public void visitDocument(Document document){
		content += "{" + document.getTitle() + "}\n";
		for (Paragraph paragraph: document.getParagraphs()) {
			paragraph.accept(this);
		}
		for(Section subsection: document.getSubsections()){
			subsection.accept(this);
		}
	}
	public void visitSection(Section section){
		content += Message.sectionIndexEntry(section.getId(),section.getTitle()) + "\n";
		for (Paragraph paragraph: section.getParagraphs()) {
			paragraph.accept(this);
		}
		for(Section subsection: section.getSubsections()){
			subsection.accept(this);
		}
	}

	public void visitParagraph(Paragraph paragraph){
		content += paragraph.getText() + "\n";
	}

}