#include "YetiFrame.h"

#include <wx/clipbrd.h>

enum
{
	ID_Paste = 1
};

YetiFrame::YetiFrame()
	: wxFrame(NULL, wxID_ANY, "Yeti")
{
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Paste, "&Paste...\tCtrl-V",
		"This will load image from your clipboard.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("No Picture");

	Bind(wxEVT_MENU, &YetiFrame::OnPaste, this, ID_Paste);
	Bind(wxEVT_MENU, &YetiFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &YetiFrame::OnExit, this, wxID_EXIT);

	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	sbm = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap);

	ocrText = new wxStaticText(panel, wxID_ANY, "No Output Yet", { 10, 10 });


	// boxSizer->Add(scaleChoice, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 20);
	boxSizer->Add(sbm, 0, wxGROW | wxALL, 20);
	boxSizer->Add(ocrText, 1, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 20);

	sbm->SetScaleMode(wxStaticBitmap::Scale_AspectFit);
	
	// sbm->SetWindowStyle(wxBORDER_SIMPLE);
	wxInitAllImageHandlers();
	panel->SetSizerAndFit(boxSizer);

	tess = new YetiTess();
}

YetiFrame::~YetiFrame() {
	delete tess;
	delete sbm;
}

void YetiFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}


void YetiFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Yeti v0.0.0",
		"About Yeti", wxOK | wxICON_INFORMATION);
}

void YetiFrame::OnPaste(wxCommandEvent& event)
{
	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported(wxDF_BITMAP))
		{
			wxBitmapDataObject data;
			wxTheClipboard->GetData(data);

			wxBitmap bitmap = data.GetBitmap();
			int w = bitmap.GetWidth();
			int h = bitmap.GetHeight();
			int d = bitmap.GetDepth();

			SetClientSize({ w + 40, h + 40 });
			sbm->SetBitmap({ bitmap });

			wxString status;
			status << status.Format("%d x %d, color depth: %d", w, h, d);
			SetStatusText(status);
			
			wxString ocrRes = tess->OCR(&bitmap);
			ocrText->SetLabelText(ocrRes);
		}
		wxTheClipboard->Close();
	}
}