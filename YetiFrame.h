#pragma once

#include <wx/wx.h>
#include "YetiTess.h"

class YetiFrame : public wxFrame
{
public:
	YetiFrame();
	~YetiFrame();

private:
	void OnPaste(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxStaticBitmap* sbm;
	wxStaticText* ocrText;


	YetiTess* tess;
};