/** @version $Id: ShowMetadata.java,v 1.9 2015/11/28 13:48:34 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Document;


/**
 * §2.1.2.
 */
public class ShowMetadata extends Command<Document> {
	public ShowMetadata(Document document) {
		super(MenuEntry.SHOW_METADATA,document);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		DocumentMetadataVisitor v = new DocumentMetadataVisitor();
		_receiver.accept(v);
		IO.println(v.getContent());
	}
}

