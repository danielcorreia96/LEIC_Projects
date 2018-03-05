/** @version $Id: ShowIndex.java,v 1.7 2015/11/15 05:22:21 ist180967 Exp $ */
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
		IO.println("{"+_receiver.getTitle()+"}");
		List<String> list = _receiver.getTopSections();
		for(int i=0; i < list.size();i = i + 2){
			IO.println(Message.sectionIndexEntry(list.get(i),list.get(i+1)));
		}
	}
}
