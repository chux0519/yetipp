#pragma once

#include <wx/wx.h>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>



class YetiTess
{

public:
	YetiTess();
	~YetiTess();

	wxString OCR(wxBitmap* bitmap);

private:
	tesseract::TessBaseAPI* api = nullptr;
};

