/** @version $Id: RemoveSection.java,v 1.7 2015/11/30 10:09:18 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
import edt.texteditor.NoSuchSectionException;

/**
 * §2.2.7.
 */
public class RemoveSection extends SectionCommand {
	public RemoveSection(Document document, Section section) {
		super(MenuEntry.REMOVE_SECTION, document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int local_id = IO.readInteger(Message.requestSectionId());
		try{
		     _document.removeTextElements(_receiver.removeSection(local_id));
		}
		catch(NoSuchSectionException e){ 
			IO.println(Message.noSuchSection(local_id)); 
		} 
	}
}
