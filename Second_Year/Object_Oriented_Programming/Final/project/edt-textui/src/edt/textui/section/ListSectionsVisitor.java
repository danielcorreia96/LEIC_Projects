package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.textui.section.Message;

import edt.texteditor.Visitor;
import edt.texteditor.Document;
import edt.texteditor.Section;
import edt.texteditor.Paragraph;

public class ListSectionsVisitor implements Visitor {
	private String content = "";
	public String getContent(){
		return content.substring(0,content.length()-1);
	}

	public void visitDocument(Document document){
		for (Section subsection : document.getSubsections()) {
			content += Message.sectionIndexEntry(subsection.getId(),subsection.getTitle()) + "\n";
			subsection.accept(this);
		}
	}
	public void visitSection(Section section){
		for (Section subsection : section.getSubsections()) {
			content += Message.sectionIndexEntry(subsection.getId(),subsection.getTitle()) + "\n";
			subsection.accept(this);
		}
	}
	public void visitParagraph(Paragraph paragraph){}
}