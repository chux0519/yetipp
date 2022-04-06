#pragma once

#include <wx/wx.h>

class YetiFrame : public wxFrame
{
public:
	YetiFrame();

private:
	void OnPaste(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxStaticBitmap* sbm;
	wxChoice* scaleChoice;
};