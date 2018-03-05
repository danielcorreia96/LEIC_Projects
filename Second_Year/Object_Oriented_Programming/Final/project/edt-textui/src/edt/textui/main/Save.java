/** @version $Id: Save.java,v 1.11 2015/11/15 05:22:21 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Editor;

/**
 * Save to file under current name (if unnamed, query for name).
 */
public class Save extends Command<Editor> {
	public Save(Editor editor) {
		super(MenuEntry.SAVE, editor);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		String filename = _receiver.getDocumentFilename();
		while(filename.equals(""))
			filename = IO.readString(Message.newSaveAs());
		_receiver.save(filename);
	}
}
