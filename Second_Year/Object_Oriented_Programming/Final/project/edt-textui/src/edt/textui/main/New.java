/** @version $Id: New.java,v 1.7 2015/11/15 05:22:20 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Editor;


/**
 * Open a new document.
 */
public class New extends Command<Editor> {
	public New(Editor editor) {
		super(true,MenuEntry.NEW, editor);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		_receiver.newDocument();
		edt.textui.main.MenuBuilder.menuFor(_receiver, _receiver.getDocument());
	}

}
