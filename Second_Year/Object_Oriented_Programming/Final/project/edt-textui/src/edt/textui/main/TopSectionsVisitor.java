package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.textui.main.Message;

import edt.texteditor.Visitor;
import edt.texteditor.Document;
import edt.texteditor.Section;
import edt.texteditor.Paragraph;


public class TopSectionsVisitor implements Visitor {
	private String content = "";

	public String getContent(){
		return content.substring(0,content.length()-1);
	}

	public void visitDocument(Document document){
		content += "{" + document.getTitle() + "}\n";
		for(Section section : document.getSubsections()){
			content += Message.sectionIndexEntry(section.getId(),section.getTitle()) + "\n";
		}
	}

	public void visitSection(Section section){}
	public void visitParagraph(Paragraph paragraph){}
}