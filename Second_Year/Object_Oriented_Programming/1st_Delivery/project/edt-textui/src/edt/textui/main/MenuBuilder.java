/** @version $Id: MenuBuilder.java,v 1.8 2015/11/15 05:22:20 ist180967 Exp $ */
package edt.textui.main;

import ist.po.ui.Command;
import ist.po.ui.Menu;

import edt.texteditor.Editor;
import edt.texteditor.Document;

public abstract class MenuBuilder {
  public static void menuFor(Editor editor,Document document) {
    Menu menu = new Menu(MenuEntry.TITLE,
        new Command<?>[] { 
            new New(editor), 
            new Open(editor),
            new Save(editor),
            new ShowMetadata(document),
            new AddAuthor(document), 
            new ShowIndex(document), 
            new ShowTextElement(document), 
            new Edit(document), 
    });
    menu.open();
  }
}
