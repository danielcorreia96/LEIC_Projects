/** @version $Id: EditParagraph.java,v 1.7 2015/12/01 01:52:05 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
import edt.texteditor.NoSuchParagraphException;

/**
 * §2.2.10.
 */
public class EditParagraph extends SectionCommand {
	public EditParagraph(Document document,Section section) {
		super(MenuEntry.EDIT_PARAGRAPH,document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int localId = IO.readInteger(Message.requestParagraphId());
		String text = IO.readString(Message.requestParagraphContent());
		try{
			_receiver.editParagraph(localId,text);
		}
		catch(NoSuchParagraphException e){
			IO.println(Message.noSuchParagraph(localId));			
		}
	}
}
