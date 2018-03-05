/** @version $Id: SectionCommand.java,v 1.5 2015/11/13 22:42:33 ist180967 Exp $ */
package edt.textui.section;

import ist.po.ui.Command;

/* FIXME: import core classes here */
import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * Superclass of all section-context commands.
 */
public abstract class SectionCommand extends Command<Section> {
  /* FIXME: put here the declaration of the second receiver: the document-context one */
  	Document _document;
	public SectionCommand(String title, Document document, Section section) {
		super(title, section);
		_document = document;
		/* FIXME: initialize second receiver */
	}

}
