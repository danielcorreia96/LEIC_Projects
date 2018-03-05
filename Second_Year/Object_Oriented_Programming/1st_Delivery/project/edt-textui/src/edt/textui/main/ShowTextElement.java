/** @version $Id: ShowTextElement.java,v 1.4 2015/11/15 05:22:21 ist180967 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Document;


/**
 * §2.1.5.
 */
public class ShowTextElement extends Command<Document> {
  public ShowTextElement(Document document) {
    super(MenuEntry.SHOW_TEXT_ELEMENT, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    /* FIXME: implement command */
  }
}
