#include "YetiTess.h"

YetiTess::YetiTess() {
	api = new tesseract::TessBaseAPI();
	if (api->Init("tessdata", "eng+enm", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	api->SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
}


// TODO: move it into another thread, it could be very slow
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

	wxString out = wxString::FromUTF8(outText);

	delete[] outText;

	// wxString out;

	/*api->Recognize(0);
	tesseract::ResultIterator* ri = api->GetIterator();
	tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
	if (ri != 0) {
		do {
			const char* word = ri->GetUTF8Text(level);
			wxString wordStr = wxString::FromUTF8(word);

			float conf = ri->Confidence(level);
			int x1, y1, x2, y2;
			ri->BoundingBox(level, &x1, &y1, &x2, &y2);
			out << out.Format("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
				wordStr, conf, x1, y1, x2, y2);

			delete[] word;
		} while (ri->Next(level));
	}*/


	pixDestroy(&pix);
	return out;
}

YetiTess::~YetiTess() {
	if (api != nullptr) {
		api->End();
		delete api;
	}
}