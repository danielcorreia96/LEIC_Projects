/** @version $Id: MenuBuilder.java,v 1.5 2015/11/13 22:42:33 ist180967 Exp $ */
package edt.textui.section;

import ist.po.ui.Command;
import ist.po.ui.Menu;

/* FIXME: import core classes here */
import edt.texteditor.Section;
import edt.texteditor.Document;
/**
 * Menu builder for search operations.
 */
public class MenuBuilder {
  public static void menuFor(Document document,Section section) {
    Menu menu = new Menu(MenuEntry.TITLE,
        new Command<?>[] { //
            new ChangeTitle(document, section), //
            new ListSections(document, section), //
            new ShowContent(document, section), //
            new SelectSection(document, section), //
            new InsertSection(document, section), //
            new NameSection(document, section), //
            new RemoveSection(document, section), //
            new InsertParagraph(document, section), //
            new NameParagraph(document, section), //
            new EditParagraph(document, section), //
            new RemoveParagraph(document, section), //
    });
    menu.open();
  }
}
