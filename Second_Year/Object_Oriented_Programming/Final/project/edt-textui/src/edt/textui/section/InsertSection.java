/** @version $Id: InsertSection.java,v 1.7 2015/11/22 22:21:49 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * §2.2.5.
 */
public class InsertSection extends SectionCommand {
	public InsertSection(Document document,Section section) {
		super(MenuEntry.INSERT_SECTION, document,section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int local_id = IO.readInteger(Message.requestSectionId());
		String title = IO.readString(Message.requestSectionTitle());
		_receiver.insertSection(local_id,"",title);	
	}
}
