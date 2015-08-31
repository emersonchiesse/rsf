
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
#include "ListaDialog.h"
#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Linha.h"
#include "Coordenada.h"
#include "PontoLinha.h"
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



class MyFrame;


// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnOpen(wxCommandEvent& event);
    void OnLinhasAbreArquivo(wxCommandEvent& event);
	void OnPontosAbreArquivo(wxCommandEvent& event);
    void OnLinhasMostraLista(wxCommandEvent& event);
    void OnRotasAbreArquivo(wxCommandEvent& event);
    void OnOnibusAbreArquivo(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);

    double converteLat(int x);
    double converteLon(int y);
    int converteX(double lat);
    int converteY(double lon);


private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
    wxBitmap image;
    int raioPonto;

    float margemEsquerda = -25.481558;
    float margemDireita = -25.357287;
    float margemSuperior;
    float margemInferior;

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
	menuArquivoPontos,
	menuArquivoVeiculos,
	menuArquivoHorarios,
	menuLinhasLista,

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

    // desenha mapa
    dc.DrawBitmap( image, 0, 0, false );

    // plota pontos
    // para todas as linhas (selecionadas)
    //Lista<Linha> *linhas = RIT.getLinhas();
    ListaLinhas *linhas = RIT.getLinhas();
    if (linhas == NULL)
    	return;

//    for (Lista<Linha>::iterator l= linhas->begin();
//    		l != linhas->end(); l++)
    {

			//RIT.getPontos(linha)
		Linha *linha = linhas->procura("303");
		if (linha == NULL)
			return;

		List<PontoLinha> *pontos = linha->getPontos();
		if (pontos == NULL)
			return;

		for (List<PontoLinha>::iterator i = pontos->begin();
				i != pontos->end(); i++)
		{
			PontoLinha p = (PontoLinha)(*i);
			Coordenada *c = p.getCoordenada();
			dc.DrawCircle(converteX(c->getLongitude()),
					converteY(c->getLatitude()), raioPonto);
		}
    }
//    while (p != NULL;)

    // desenha pontos



    // desenha rotas

    //wxSize size = GetClientSize();
    // escolhe cor, se estiver selecionado
	if (true)
	{
		dc.SetBrush(*wxGREEN_BRUSH); // green filling
		dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 5-pixels-thick red outline
	}
//	else
//	{
//		dc.SetBrush(*wxBLACK_BRUSH);
//		dc.SetPen( wxPen( wxColor(255,0,0), 1 ) );
//	}

	// desenha nodos
	dc.DrawCircle(100, 100, raioPonto);
//	dc.DrawText(wxString::FromUTF8(id.c_str()),
//			x*MULTIPLIER+5, size.y-y*MULTIPLIER+5);


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

void MyFrame::OnLinhasMostraLista(wxCommandEvent& event) {
	string lista = RIT.listaLinhas();
    ListaDialog dialog ( this, -1, _("Linhas"),
    		lista,
			wxPoint(100, 100), wxSize(400, 400) );
	if ( dialog.ShowModal() != wxID_OK )
		SetStatusText(_("The about box was cancelled.\n"));
	else
	{
	}
}

void MyFrame::OnPontosAbreArquivo(wxCommandEvent& event) {
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK){

		wxString fileName = openFileDialog->GetPath();

		// extrai o nome da linha, do nome do arquivo
		int ind = fileName.Find("-")+1;
		string linha = fileName.SubString(ind, ind+2).ToStdString();

		LinhasDialog dialog ( this, -1, _("Abre arquivo de pontos"),
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
				assert(d[i].HasMember(JSON_PONTO_NOME));
				assert(d[i][JSON_PONTO_NOME].IsString());
				assert(d[i].HasMember(JSON_PONTO_LATITUDE));
				assert(d[i][JSON_PONTO_LATITUDE].IsString());
				assert(d[i].HasMember(JSON_PONTO_LONGITUDE));
				assert(d[i][JSON_PONTO_LONGITUDE].IsString());
				assert(d[i].HasMember(JSON_PONTO_TIPO));
				assert(d[i][JSON_PONTO_TIPO].IsString());
				assert(d[i].HasMember(JSON_PONTO_NUMERO));
				assert(d[i][JSON_PONTO_NUMERO].IsString());
				assert(d[i].HasMember(JSON_PONTO_SENTIDO));
				assert(d[i][JSON_PONTO_SENTIDO].IsString());
				assert(d[i].HasMember(JSON_PONTO_SEQUENCIA));
				assert(d[i][JSON_PONTO_SEQUENCIA].IsString());

				string lat = d[i][JSON_PONTO_LATITUDE].GetString();
				lat[3]='.';
				string lon = d[i][JSON_PONTO_LONGITUDE].GetString();
				lon[3]='.';

				Coordenada c (lat, lon);

				PontoLinha *p = new PontoLinha(
						d[i][JSON_PONTO_NOME].GetString(),
						d[i][JSON_PONTO_NUMERO].GetString(),
						d[i][JSON_PONTO_TIPO].GetString(),
						d[i][JSON_PONTO_SENTIDO].GetString(),
						0,
						0,
						c
				);

				cout << "ponto: " << d[i][JSON_PONTO_NOME].GetString()
						<< " lat " << lat
						<< " lon " << lon
						<< endl;


				RIT.inserePontoLinha (linha, p);
			}

			this->Refresh(true);
			this->Update();
		}

	}
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(menu_FileOpen,  MyFrame::OnOpen)
	EVT_MENU(menuArquivoLinhas,  MyFrame::OnLinhasAbreArquivo)
	EVT_MENU(menuArquivoPontos,  MyFrame::OnPontosAbreArquivo)
	EVT_MENU(menuLinhasLista,  MyFrame::OnLinhasMostraLista)
    EVT_MENU(menuSair,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MOUSE_EVENTS(MyFrame::OnMouse)
	EVT_PAINT(MyFrame::OnPaint)
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
    frame->SetSize(640, 640);
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
	fileMenu->Append(menuArquivoPontos, _T("Carrega pontos..."), _T(""));
	fileMenu->Append(menuArquivoRotas, _T("Carrega rotas..."), _T(""));
    fileMenu->Append(menuArquivoHorarios, _T("Carrega horarios..."), _T(""));

    fileMenu->Append(menuSair, _T("E&ncerra\tAlt-X"), _T("Encerra este programa"));

    menuLinhas->Append(menuLinhasLista, _T("lista as linhas..."), _T(""));


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

    image.LoadFile("/home/x/msc/urbs/staticmap.png", wxBITMAP_TYPE_PNG);
    raioPonto=2;
//    margemEsquerda = -25.481558;
//    margemDireita = -25.357287;
//    margemSuperior = -49.185682;
//    margemInferior = -49.357169;
	margemEsquerda = -49.476909;
	margemDireita = -49.097456;
	margemSuperior = -25.238254;
	margemInferior = -25.608483;

    RIT.Init();
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
				    	Linha *l = new Linha (d[i][JSON_LINHA_CODIGO].GetString(),
				    			d[i][JSON_LINHA_NOME].GetString());

				    		cout << "cod: " << d[i][JSON_LINHA_CODIGO].GetString() << endl;

				    	RIT.insereLinha (l);
				    }
			}

	}
}

double MyFrame::converteLat(int x)
{
	if (x == 0)
		return margemEsquerda;
	return (margemEsquerda - x*(margemEsquerda-margemDireita)/640);
}

double MyFrame::converteLon(int y)
{
	if (y == 0)
		return margemSuperior;
	return (margemSuperior - y*(margemSuperior-margemInferior)/640);
}

int MyFrame::converteX(double lat)
{
	return (-(lat - margemEsquerda)*640)/(margemEsquerda-margemDireita);
}

int MyFrame::converteY(double lon)
{
	return (-(lon-margemSuperior)*640/(margemSuperior-margemInferior));
}

void MyFrame::OnMouse(wxMouseEvent& event) {

	int ind = -1;
	{
		wxSize size = GetClientSize();
		int x = event.GetX();
		int y = event.GetY();

		SetStatusText(wxString::Format(_T("x: %f, y: %f"),
				converteLat(x), converteLon(y)));

//		ind = grafo.procura(x/MULTIPLIER, (size.y - y)/MULTIPLIER);
//		if (ind >= 0)
//		{
//			std::vector<Nodo> nodos = grafo.getNodos();
//			SetStatusText(wxString::Format(_T("x: %d, y: %d, nodo: %s"),
//					x, y, nodos[ind].getId().c_str()));
//
//			if (event.LeftUp())
//			{
//				vector <string>::iterator i = nodosSelecionados.begin ();
//				i = std::find(nodosSelecionados.begin(),
//						nodosSelecionados.end(),
//						nodos[ind].getId().c_str());
//				if (i == nodosSelecionados.end() )
//					nodosSelecionados.push_back(nodos[ind].getId().c_str());
//				else
//					nodosSelecionados.erase(i);
//
//				SetStatusText("select!");
//				this->Refresh(true);
//				this->Update();
//			}
//		}
	}
}
