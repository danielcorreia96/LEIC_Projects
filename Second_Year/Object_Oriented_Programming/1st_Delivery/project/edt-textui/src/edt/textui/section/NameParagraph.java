/** @version $Id: NameParagraph.java,v 1.4 2015/11/13 22:42:33 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

/* FIXME: import core classes here */
import edt.texteditor.Section;
import edt.texteditor.Document;

/**
 * §2.2.9.
 */
public class NameParagraph extends SectionCommand {
  public NameParagraph(Document document,Section section) {
    super(MenuEntry.NAME_PARAGRAPH, document,section);
  }

  @Override
  public final void execute() throws DialogException, IOException {
    /* FIXME: implement command */
  }
}
