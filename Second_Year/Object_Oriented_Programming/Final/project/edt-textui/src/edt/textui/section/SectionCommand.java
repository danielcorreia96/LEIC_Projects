/** @version $Id: SectionCommand.java,v 1.7 2015/12/01 01:52:05 ist180967 Exp $ */
package edt.textui.section;

import ist.po.ui.Command;

import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * Superclass of all section-context commands.
 */
public abstract class SectionCommand extends Command<Section> {
  	Document _document;
	public SectionCommand(String title, Document document, Section section) {
		super(title, section);
		_document = document;
	}

}
