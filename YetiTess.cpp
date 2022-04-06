#include "YetiTess.h"

YetiTess::YetiTess() {
	api = new tesseract::TessBaseAPI();
	if (api->Init("C:\\Users\\yongsheng\\repos\\yeti\\tessdata", "eng", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
}


wxString YetiTess::OCR(wxBitmap* bitmap) {
	/*int w = bitmap->GetWidth();
	int h = bitmap->GetHeight();
	int d = bitmap->GetDepth();*/

	const wxImage img = bitmap->ConvertToImage();
	img.SaveFile("test.png");

	// PIX* pix = pixCreate(w, h, d);
	PIX* pix = pixRead("test.png");
	
	api->SetImage(pix);
	char* outText;
	outText = api->GetUTF8Text();

	wxString out;
	out << out.Format("OCR output:\n%s", outText);

	delete[] outText;
	pixDestroy(&pix);
	return out;
}

YetiTess::~YetiTess() {
	if (api != nullptr) {
		api->End();
		delete api;
	}
}