/** @version $Id: ShowTextElement.java,v 1.7 2015/11/30 20:58:11 ist181151 Exp $ */
package edt.textui.main;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.textui.TextElementVisitor;
import edt.texteditor.Document;
import edt.texteditor.TextElement;
import edt.texteditor.NoSuchTextElementException;


/**
 * §2.1.5.
 */
public class ShowTextElement extends Command<Document> {
  public ShowTextElement(Document document) {
    super(MenuEntry.SHOW_TEXT_ELEMENT, document);
  }

  @Override
  public final void execute() throws DialogException, IOException {
  	String id = IO.readString(Message.requestElementId());
  		try{
  		TextElementVisitor v = new TextElementVisitor();
  	        _receiver.showTextElement(v, id);
  		IO.println(v.getContent());
		}
  		catch(NoSuchTextElementException e) {IO.println(Message.noSuchTextElement(id));}
  	}
}
