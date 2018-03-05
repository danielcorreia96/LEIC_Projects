/** @version $Id: ShowContent.java,v 1.6 2015/11/28 12:01:33 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;
import edt.textui.TextElementVisitor;
import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * §2.2.3.
 */
public class ShowContent extends SectionCommand {
	public ShowContent(Document document,Section section) {
		super(MenuEntry.SHOW_CONTENT, document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
	  	TextElementVisitor v = new TextElementVisitor();
  		_receiver.accept(v);
  		IO.println(v.getContent());
	}
}
