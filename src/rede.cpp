
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

#include "Grafo.h"
#include "Board.h"
#include "BasicDialog.h"

#include "wx/dialog.h"
#include <algorithm>
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
    void OnDijkstra(wxCommandEvent& event);
    void OnRestart(wxCommandEvent& event);
    void OnRandom(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
	Grafo grafo;
    std::vector<string> nodosSelecionados;
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_FileOpen = wxID_OPEN,

	Minimal_FileDikstra = wxID_FILE1,
	Minimal_restart = wxID_FILE2,
	Minimal_random = wxID_FILE3,

    Minimal_Quit = wxID_EXIT,

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

    cout << "app.onpaint\n";

    wxSize size = GetClientSize();
    std::vector<Nodo> nodos = grafo.getNodos();

    for (int i=0; i< nodos.size(); i++)
    {
    	int x = nodos[i].getX();
    	int y = nodos[i].getY();
    	string id = nodos[i].getId();
    	if (std::find(nodosSelecionados.begin(),
    					nodosSelecionados.end(),
						id) != nodosSelecionados.end() )
		{
			dc.SetBrush(*wxGREEN_BRUSH); // green filling
			dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 5-pixels-thick red outline
		}
    	else
    	{
			dc.SetBrush(*wxBLACK_BRUSH);
			dc.SetPen( wxPen( wxColor(255,0,0), 1 ) );
		}

    	dc.DrawCircle(x*MULTIPLIER, size.y-y*MULTIPLIER, 5);
    	dc.DrawText(wxString::FromUTF8(id.c_str()),
    			x*MULTIPLIER, size.y-y*MULTIPLIER);

    	std::vector<Vertice> vizinhos = nodos[i].getVizinhos();
    	for (int j=0; j<vizinhos.size(); j++)
    	{
    		string v=vizinhos[j].getId();
    		int peso=vizinhos[j].getCusto();
    		cout << "vizinho " << v << "\n";
    		int ind = grafo.procura(v);
    		int x1 = nodos[ind].getX();
    		int y1 = nodos[ind].getY();
    		dc.DrawLine(x*MULTIPLIER, size.y-y*MULTIPLIER,
    				x1*MULTIPLIER, size.y-y1*MULTIPLIER);
    		dc.DrawText(wxString::Format(_T("%d"), peso),
    				((x+x1)/2)*MULTIPLIER,
    				size.y-((y+y1)/2)*MULTIPLIER);
    	}
    }
}


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(Minimal_FileOpen,  MyFrame::OnOpen)
	EVT_MENU(Minimal_FileDikstra,  MyFrame::OnDijkstra)
	EVT_MENU(Minimal_restart,  MyFrame::OnRestart)
	EVT_MENU(Minimal_random,  MyFrame::OnRandom)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
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
    MyFrame *frame = new MyFrame(_T("Redes Sem Fio App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->SetSize(600, 600);
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
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
    wxMenu *toolsMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    fileMenu->Append(Minimal_FileOpen, _T("&Open...\tF1"), _T("Open file"));
    fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    toolsMenu->Append(Minimal_restart, _T("&Restart\tAlt-R"), _T(""));
    toolsMenu->Append(Minimal_random, _T("R&andom\tAlt-A"), _T(""));
    toolsMenu->Append(Minimal_FileDikstra, _T("&Djisktra...\tF2"), _T("Calc Djistra"));


    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(toolsMenu, _T("&Ferramentas"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
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
		// apaga grafo ja carregado
		grafo.init();

	    wxString fileName = openFileDialog->GetPath();
	    grafo.load(string(fileName.ToAscii()));
	    grafo.loadcoords(string(fileName.ToAscii()));
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
                 _T("About Redes Sem Fio App"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnDijkstra(wxCommandEvent& event) {
	if (nodosSelecionados.size()==2)
	{
		grafo.caminhomaiscurto(nodosSelecionados[0],
				nodosSelecionados[1]);

		wxMessageBox(wxString::Format(
		                    _T("Welcome to %s!\n")
		                    _T("\n")
		                    _T("\n")
		                    _T("running under %s."),
		                    wxVERSION_STRING,
		                    wxGetOsDescription().c_str()
		                 ),
		                 _T("About Redes Sem Fio App"),
		                 wxOK | wxICON_INFORMATION,
		                 this);
	}
	else
		SetStatusText("selecione 2 nodos");
}


void MyFrame::OnRestart(wxCommandEvent& event) {

	while (nodosSelecionados.size()>0)
		nodosSelecionados.pop_back();

	this->Refresh(true);
	this->Update();
}

void MyFrame::OnRandom(wxCommandEvent& event) {


    BasicDialog aboutDialog ( this, -1, _("Digite numero de nós"),
    	                          wxPoint(100, 100), wxSize(200, 200) );
    	if ( aboutDialog.ShowModal() != wxID_OK )
    		SetStatusText(_("The about box was cancelled.\n"));
    	else
    	{
			grafo.init();

			string result = aboutDialog.GetText();
			grafo.criaRandom(atoi(result.c_str()));

			this->Refresh(true);
			this->Update();
    	}
}

void MyFrame::OnMouse(wxMouseEvent& event) {

	int ind = -1;
	{
		wxSize size = GetClientSize();
		int x = event.GetX();
		int y = event.GetY();
		SetStatusText(wxString::Format(_T("x: %d, y: %d"), x, y));
		ind = grafo.procura(x/MULTIPLIER, (size.y - y)/MULTIPLIER);
		if (ind >= 0)
		{
			std::vector<Nodo> nodos = grafo.getNodos();
			SetStatusText(wxString::Format(_T("x: %d, y: %d, nodo: %s"),
					x, y, nodos[ind].getId().c_str()));

			if (event.LeftUp())
			{
				vector <string>::iterator i = nodosSelecionados.begin ();
				i = std::find(nodosSelecionados.begin(),
						nodosSelecionados.end(),
						nodos[ind].getId().c_str());
				if (i == nodosSelecionados.end() )
				{
					nodosSelecionados.push_back(nodos[ind].getId().c_str());
				}
				else
					nodosSelecionados.erase(i);

				SetStatusText("select!");
				this->Refresh(true);
				this->Update();
			}
		}
	}


}
