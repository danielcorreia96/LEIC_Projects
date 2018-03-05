/** @version $Id: ShowContent.java,v 1.4 2015/11/13 22:42:33 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * §2.2.3.
 */
public class ShowContent extends SectionCommand {
	public ShowContent(Document document,Section section) {
		super(MenuEntry.SHOW_CONTENT, document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
	  	/* FIXME: implement command */
	}
}
