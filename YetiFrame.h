#pragma once

#include <wx/wx.h>

class YetiFrame : public wxFrame
{
public:
    YetiFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};