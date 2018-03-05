/** @version $Id: RemoveParagraph.java,v 1.7 2015/11/30 10:09:18 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
import edt.texteditor.NoSuchParagraphException;

/**
 * §2.2.11.
 */
public class RemoveParagraph extends SectionCommand {
	public RemoveParagraph(Document document, Section section) {
		super(MenuEntry.REMOVE_PARAGRAPH, document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int localId = IO.readInteger(Message.requestParagraphId());
		try{
		    _document.removeTextElement(_receiver.removeParagraph(localId));
		}
		catch(NoSuchParagraphException e){ 
			IO.println(Message.noSuchParagraph(localId));
		}
	}

}
