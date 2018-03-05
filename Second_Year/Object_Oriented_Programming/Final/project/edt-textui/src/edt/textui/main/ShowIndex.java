/** @version $Id: ShowIndex.java,v 1.8 2015/11/28 13:48:34 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import java.util.List;

import edt.texteditor.Document;


/**
 * §2.1.4.
 */
public class ShowIndex extends Command<Document> {
	public ShowIndex(Document document) {
		super(MenuEntry.SHOW_INDEX, document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		TopSectionsVisitor v = new TopSectionsVisitor();
		_receiver.accept(v);
		IO.println(v.getContent());
	}
}
