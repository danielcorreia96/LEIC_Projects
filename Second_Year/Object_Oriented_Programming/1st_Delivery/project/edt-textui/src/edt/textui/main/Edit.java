/** @version $Id: Edit.java,v 1.7 2015/11/15 05:22:20 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Document;

/**
 * §2.3.1.
 */
public class Edit extends Command<Document> {
  public Edit(Document document) {
    super(MenuEntry.OPEN_DOCUMENT_EDITOR, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    edt.textui.section.MenuBuilder.menuFor(_receiver,_receiver);
  }

}
