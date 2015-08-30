
/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp 43915 2006-12-11 09:33:34Z CE $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "Lista.h"
#include "defs.h"
#include <wx/wx.h>
#include "linhasDialog.h"
#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Linha.h"
#include "SistemaTransportePublico.h"


using namespace std;
using namespace rapidjson;
// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
//#if !defined(__WXMSW__) && !defined(__WXPM__)
//    #include "../sample.xpm"
//#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnOpen(wxCommandEvent& event);
    void OnLinhasAbreArquivo(wxCommandEvent& event);
    void OnRotasAbreArquivo(wxCommandEvent& event);
    void OnOnibusAbreArquivo(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()

	SistemaTransportePublico RIT;
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    menu_FileOpen = wxID_OPEN,
    menuArquivoLinhas= wxID_FILE1,
	menuArquivoRotas,
	menuArquivoVeiculos,
	menuArquivoHorarios,

	menuSair = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
#define MULTIPLIER 30

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    std::cout << "app.onpaint\n";

    //wxSize size = GetClientSize();

}

inline void MyFrame::OnRotasAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();

	    LinhasDialog dialog ( this, -1, _("Digite numero de nós"),
	    		string(fileName.ToAscii()),
				wxPoint(100, 100), wxSize(200, 200) );
		if ( dialog.ShowModal() != wxID_OK )
			SetStatusText(_("The about box was cancelled.\n"));
		else
		{

		}

	}
}

inline void MyFrame::OnOnibusAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();
	    //grafo.load(string(fileName.ToAscii()));
	    this->Refresh(true);
	    this->Update();
	}
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(menu_FileOpen,  MyFrame::OnOpen)
	EVT_MENU(menuArquivoLinhas,  MyFrame::OnLinhasAbreArquivo)
    EVT_MENU(menuSair,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MOUSE_EVENTS(MyFrame::OnMouse)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame(_T("URBS App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));

    // set the frame icon
    //SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // cria árvore de menus
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
    wxMenu *menuLinhas = new wxMenu;

    fileMenu->Append(menuArquivoLinhas, _T("Carrega linhas..."), _T(""));
    fileMenu->Append(menuArquivoRotas, _T("Carrega rotas..."), _T(""));
    fileMenu->Append(menuArquivoHorarios, _T("Carrega horarios..."), _T(""));

    fileMenu->Append(menuSair, _T("E&ncerra\tAlt-X"), _T("Encerra este programa"));


    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&Arquivo"));
    menuBar->Append(menuLinhas, _T("&Linhas"));
    menuBar->Append(helpMenu, _T("&Ajuda"));

    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    //SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR

    //Board *board = new Board(this);
    //board->SetFocus();
}


// event handlers
void MyFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
//	wxTextCtrl *tc;
//	tc = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1),
//	    wxSize(-1, -1), wxTE_MULTILINE);

	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();
	    //grafo.load(string(fileName.ToAscii()));
	    this->Refresh(true);
	    this->Update();
	}
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("Welcome to %s!\n")
                    _T("\n")
                    _T("\n")
                    _T("running under %s."),
                    wxVERSION_STRING,
                    wxGetOsDescription().c_str()
                 ),
                 _T("About URBS App"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnLinhasAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

	    wxString fileName = openFileDialog->GetPath();

		    LinhasDialog dialog ( this, -1, _("Digite numero de nós"),
		    		string(fileName.ToAscii()),
					wxPoint(100, 100), wxSize(400, 400) );
			if ( dialog.ShowModal() != wxID_OK )
				SetStatusText(_("The about box was cancelled.\n"));
			else
			{
				    Document d;
				    d.Parse(dialog.GetText().c_str());
				    assert(d.IsArray());
				    cout << d.Size() << endl;
				    for (SizeType i = 0; i < d.Size(); i++)
				    {
				    	assert(d[i].IsObject());
				    	assert(d[i].HasMember(JSON_LINHA_CODIGO));
				    	assert(d[i][JSON_LINHA_CODIGO].IsString());
				    	assert(d[i].HasMember(JSON_LINHA_NOME));
				    	assert(d[i][JSON_LINHA_NOME].IsString());
				    	Linha l (d[i][JSON_LINHA_CODIGO].GetString(),
				    			d[i][JSON_LINHA_NOME].GetString());



				    }
			}

	}
}

void MyFrame::OnMouse(wxMouseEvent& event) {

	if (event.LeftUp())
	{
	/*	wxSize size = GetClientSize();
	*	int x = event.GetX();
		int y = event.GetY();
		SetStatusText(wxString::Format(_T("x: %d, y: %d"), x, y));
		int ind = grafo.procura(x/MULTIPLIER, (size.y - y)/MULTIPLIER);
		if (ind >= 0)
		{
			std::vector<Nodo> nodos = grafo.getNodos();
			SetStatusText(wxString::Format(_T("x: %d, y: %d, nodo: %s"),
					x, y, nodos[ind].getId().c_str()));
		}
*/	}
}
