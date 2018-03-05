/** @version $Id: InsertSection.java,v 1.6 2015/11/13 22:42:33 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * §2.2.5.
 */
public class InsertSection extends SectionCommand {
  public InsertSection(Document document,Section section) {
    super(MenuEntry.INSERT_SECTION, document,section);
  }

  @Override
  public final void execute() throws DialogException, IOException {

  }
}
