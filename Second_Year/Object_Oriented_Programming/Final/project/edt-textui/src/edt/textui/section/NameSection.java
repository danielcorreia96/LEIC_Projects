/** @version $Id: NameSection.java,v 1.12 2015/12/01 02:07:09 ist180967 Exp $ */
package edt.textui.section;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.DialogException;

import java.io.IOException;

import edt.texteditor.Section;
import edt.texteditor.Document;
import edt.texteditor.NoSuchSectionException;
/**
 * §2.2.6.
 */
public class NameSection extends SectionCommand {
	public NameSection(Document document,Section section) {
		super(MenuEntry.NAME_SECTION,document, section);
	}

	@Override
	public final void execute() throws DialogException, IOException {
		int localid = IO.readInteger(Message.requestSectionId());
		String uniqueid = IO.readString(Message.requestUniqueId());
		if(uniqueid.equals("") == false){
			try{
				if(_document.nameSection(uniqueid,localid,_receiver)){
					IO.println(Message.sectionNameChanged());
				}
			}
			catch(NoSuchSectionException e){
				IO.println(Message.noSuchSection(localid));
			}
		}
	}
}
