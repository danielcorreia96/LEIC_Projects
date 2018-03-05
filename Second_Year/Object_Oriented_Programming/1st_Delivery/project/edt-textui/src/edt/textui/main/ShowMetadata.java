/** @version $Id: ShowMetadata.java,v 1.8 2015/11/15 05:22:21 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import java.util.List;
import java.util.ArrayList;

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
		IO.println(Message.documentTitle(_receiver.getTitle()));
		List<String> authors_data = _receiver.getAuthorsData();
		for (int i = 0;i < authors_data.size();i+=2) {
			IO.println(Message.author(authors_data.get(i),authors_data.get(i+1)));
		}
		List<Integer> metadata = _receiver.getMetaData();
		IO.println(Message.documentSections(metadata.get(0)));
		IO.println(Message.documentBytes(metadata.get(1)));
		IO.println(Message.documentIdentifiers(metadata.get(2)));
	}
}

