/*
 * BasicDialog.h
 *
 *  Created on: 27 de ago de 2015
 *      Author: x
 */

#ifndef BASICDIALOG_H_
#define BASICDIALOG_H_

#include <wx/dialog.h>
#include "wx/textctrl.h"
#include <string>

class BasicDialog: public wxDialog
{
public:

	BasicDialog ( wxWindow * parent, wxWindowID id, const wxString & title,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE );

	wxTextCtrl * dialogText;
	std::string  GetText();

private:

	void OnOk( wxCommandEvent & event );

	std::string result;

	DECLARE_EVENT_TABLE()
};
#endif /* BASICDIALOG_H_ */

