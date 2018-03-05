/** @version $Id: NameParagraph.java,v 1.12 2015/12/01 02:07:09 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
import edt.texteditor.NoSuchParagraphException;
/**
 * §2.2.9.
 */
public class NameParagraph extends SectionCommand {
  	public NameParagraph(Document document,Section section) {
    	super(MenuEntry.NAME_PARAGRAPH, document,section);
  	}

  	@Override
  	public final void execute() throws DialogException, IOException {
 		int localid = IO.readInteger(Message.requestParagraphId());
		String uniqueid = IO.readString(Message.requestUniqueId());
		if(uniqueid.equals("") == false){
			try{
				if(_document.nameParagraph(uniqueid,localid,_receiver)){
					IO.println(Message.paragraphNameChanged());
				}
			}
			catch(NoSuchParagraphException e){
				IO.println(Message.noSuchParagraph(localid));
			}
		}
  	}
}
