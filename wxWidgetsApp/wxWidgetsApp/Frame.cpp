#include "Frame.h"

Frame::Frame() : wxFrame(NULL, wxID_ANY, "wxStart")
{
	this->SetSizeHints(wxSize(800, 500), wxDefaultSize);

	setUpUi();
	bindEvents();

	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
}

Frame::~Frame()
{
	delete m_buttonSaveDrawing;
	delete m_buttonColorPick;
	delete m_checkBoxImgShow;
	delete m_scrollBarArmAngle;
	delete m_gaugeArmAngle;
	delete m_choiceImgPick;
	delete m_textCtrl;
	delete m_panelDrawing;
}

void Frame::setUpUi()
{
	m_bSizerContainer = new wxBoxSizer(wxHORIZONTAL);
	m_bSizerDrawingContainer = new wxBoxSizer(wxHORIZONTAL);
	m_bSizerUiContainer = new wxBoxSizer(wxVERTICAL);

	m_bSizerContainer->SetMinSize(wxSize(600, 400));
	m_bSizerUiContainer->SetMinSize(wxSize(200, 400));

	// load texture
	wxImage banana = wxImage();
	banana.AddHandler(new wxPNGHandler);
	banana.LoadFile("img/banan.png", wxBITMAP_TYPE_PNG);
	m_bitmapBanana = wxBitmap(banana);

	// set up drawing panel
	m_panelDrawing = new wxPanel(this, ID_WXPANEL, wxDefaultPosition, wxSize(400, 400), wxTAB_TRAVERSAL);
	m_panelDrawing->SetBackgroundColour(wxColour(255, 255, 255));

	// set up img picker
	wxArrayString imagesOptionsToPick;
	imagesOptionsToPick.Add(wxT("gwiazdka"));
	imagesOptionsToPick.Add(wxT("ksiezyc"));
	imagesOptionsToPick.Add(wxT("slonko"));

	m_choiceImgPick = new wxChoice(this, ID_WXCHOICE_IMG_PICK, wxDefaultPosition, wxDefaultSize, imagesOptionsToPick, 0);
	m_choiceImgPick->SetSelection(0);

	// set up cpntrols responsible for angle of an arm on drawing
	m_scrollBarArmAngle = new wxScrollBar(this, ID_WXSCROLLBAR_ARM_ANGLE, wxDefaultPosition, wxSize(200, 20), wxSB_HORIZONTAL);
	m_scrollBarArmAngle->SetScrollbar(0, 1, 100, 1);
	m_scrollBarArmAngle->Disable();
	m_gaugeArmAngle = new wxGauge(this, ID_WXGAUGE_ARM_ANGLE, 99, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gaugeArmAngle->SetValue(0);

	// set up other ui controls
	m_buttonSaveDrawing = new wxButton(this, ID_WXBUTTON_SAVE_DRAWING, "zapis do pliku", wxDefaultPosition, wxDefaultSize, 0);
	m_buttonColorPick = new wxButton(this, ID_WXBUTTON_COLOR_PICK, "kolor gwiazdki", wxDefaultPosition, wxDefaultSize, 0);
	m_checkBoxImgShow = new wxCheckBox(this, ID_WXCHECKBOX_IMG_SHOW, "banan", wxDefaultPosition, wxDefaultSize, 0);
	m_textCtrl = new wxTextCtrl(this, ID_WXTEXTCTRL, m_text, wxDefaultPosition, wxDefaultSize, 0);
	m_textCtrl->SetValue("tekst");


	m_bSizerDrawingContainer->Add(m_panelDrawing, 1, wxEXPAND | wxALL);
	m_bSizerUiContainer->Add(m_buttonSaveDrawing, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_checkBoxImgShow, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_scrollBarArmAngle, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_gaugeArmAngle, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_buttonColorPick, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_textCtrl, 0, wxALIGN_CENTER | wxALL, 5);
	m_bSizerUiContainer->Add(m_choiceImgPick, 0, wxALIGN_CENTER | wxALL, 5);

	m_bSizerContainer->Add(m_bSizerDrawingContainer, 1, wxEXPAND);
	m_bSizerContainer->Add(m_bSizerUiContainer, 0, wxEXPAND);

	SetSizer(m_bSizerContainer);
	SetAutoLayout(true);
	Layout();
	Centre(wxBOTH);

}

void Frame::bindEvents()
{
	Bind(wxEVT_MENU, &Frame::onExit, this, wxID_EXIT);

	Bind(wxEVT_PAINT, &Frame::onPaint, this);
	Bind(wxEVT_UPDATE_UI, &Frame::onUpdate, this);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::onButtonSaveDrawingClick, this, ID_WXBUTTON_SAVE_DRAWING);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::onButtonColorPickClick, this, ID_WXBUTTON_COLOR_PICK);
	Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &Frame::onCheckboxClick, this, ID_WXCHECKBOX_IMG_SHOW);
	Bind(wxEVT_SCROLL_THUMBTRACK, &Frame::onScrollBarScroll, this, ID_WXSCROLLBAR_ARM_ANGLE);
	Bind(wxEVT_COMMAND_CHOICE_SELECTED, &Frame::onChoiceSelected, this, ID_WXCHOICE_IMG_PICK);

}

void Frame::refresh()
{
	wxClientDC dcClient(m_panelDrawing);
	draw(dcClient);
}

void Frame::onExit(wxCommandEvent & event)
{
	Close(true);
}

void Frame::onPaint(wxPaintEvent & event)
{
	refresh();
}

void Frame::onUpdate(wxUpdateUIEvent & event)
{
	refresh();
}

void Frame::onButtonSaveDrawingClick(wxCommandEvent & e)
{

	wxFileDialog saveFileDialog(this, "Save as", "", "", "BMP files (*.bmp)|*.bmp|JPG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return; 

	wxImage image = m_bitmapSavedImg.ConvertToImage();
	image.AddHandler(new wxJPEGHandler);
	image.AddHandler(new wxPNGHandler);
	image.SaveFile(saveFileDialog.GetPath());
}

void Frame::onButtonColorPickClick(wxCommandEvent & e)
{
	wxColourDialog chooseColourDialog(this, nullptr);
	if (chooseColourDialog.ShowModal() == wxID_OK) {
		m_color = chooseColourDialog.GetColourData().GetColour();
		refresh();
	}
}

void Frame::onCheckboxClick(wxCommandEvent & e)
{
	m_checkBoxImgShow->IsChecked() ? m_scrollBarArmAngle->Enable() : m_scrollBarArmAngle->Disable();
}

void Frame::onScrollBarScroll(wxScrollEvent & e)
{
	m_gaugeArmAngle->SetValue(m_scrollBarArmAngle->GetThumbPosition());
	refresh();
}

void Frame::onChoiceSelected(wxCommandEvent & e)
{
}

void Frame::draw(wxClientDC &dcClient)
{
	m_bitmapSavedImg = wxBitmap(m_panelDrawing->GetSize().x, m_panelDrawing->GetSize().y);
	wxBufferedDC dcBuffer(&dcClient, m_bitmapSavedImg);
	PrepareDC(dcBuffer);

	dcBuffer.Clear();

	int x = (m_panelDrawing->GetSize().x) / 2;
	int y = (m_panelDrawing->GetSize().y) / 2;

	float phi = 3.14 + (100 - m_gaugeArmAngle->GetValue() * 1.75) * (3.14*0.33) / 100.;
	float xa = 70.*cos(phi);
	float ya = 70.*sin(phi);

	// draw different face based on checkbox value and banana 
	if (m_checkBoxImgShow->IsChecked()) 
		dcBuffer.DrawBitmap(m_bitmapBanana, x - (m_bitmapBanana.GetWidth() / 2 + 24) + xa, y - (m_bitmapBanana.GetHeight() / 2 + 40)  - ya);

	dcBuffer.DrawCircle(x, y - 100, 40);
	dcBuffer.DrawEllipse(x - 27, y - 115, 20, 14);

	if (m_checkBoxImgShow->IsChecked()) {
		dcBuffer.DrawEllipse(x + 7, y - 115, 20, 14);
		dcBuffer.DrawEllipticArc(x - 30, y - 100, 60, 20, 180, 360);
	}
	else {
		dcBuffer.DrawEllipse(x + 10, y - 118, 14, 20);
		dcBuffer.DrawEllipticArc(x - 30, y - 90, 60, 20, 0, 180);
	}

	dcBuffer.DrawLine(x , y - 40, x - 24 + xa, y - 40 - ya);

	// draw body
	dcBuffer.DrawLine(x, y + 60, x, y - 60);
	dcBuffer.DrawLine(x, y - 40, x + 60, y + 20);
	dcBuffer.DrawLine(x, y + 60, x + 50, y + 150);
	dcBuffer.DrawLine(x, y + 60, x - 50, y + 150);

	// draw texts
	dcBuffer.SetPen(wxPen(wxColor(0, 0, 0), 3));
	dcBuffer.DrawText(m_textCtrl->GetValue(), x - 130, y + 140);

	dcBuffer.SetFont(wxFont(25, wxSWISS, wxITALIC, wxBOLD, false));
	dcBuffer.SetPen(wxPen(wxColor(0, 0, 0), 15, wxPENSTYLE_SOLID));
	dcBuffer.DrawRotatedText(m_textCtrl->GetValue(), x + 90, y + 150, 90);

	switch (m_choiceImgPick->GetSelection()) {
	case 0:
	{
		dcBuffer.SetBrush(wxBrush(m_color));
		dcBuffer.SetPen(wxPen(m_color));
		wxPoint points[5] = {
			wxPoint(x - 130, y - 160),
			wxPoint(x - 130 + 20, y - 160 + 50),
			wxPoint(x - 130 - 30, y - 160 + 20),
			wxPoint(x - 130 + 30, y - 160 + 20),
			wxPoint(x - 130 - 20, y - 160 + 50)
		};
		dcBuffer.DrawPolygon(5, points, wxWINDING_RULE);
	}
	break;

	case 1:
	{
		dcBuffer.SetBrush(*wxLIGHT_GREY_BRUSH);
		dcBuffer.SetPen(*wxLIGHT_GREY_PEN);
		dcBuffer.DrawCircle(x - 132, y - 137, 20);
		dcBuffer.SetBrush(*wxWHITE_BRUSH);
		dcBuffer.SetPen(*wxWHITE_PEN);
		dcBuffer.DrawCircle(x - 142, y - 150, 20);
		dcBuffer.SetBrush(*wxBLACK_BRUSH);
		dcBuffer.SetPen(*wxBLACK_PEN);
		dcBuffer.DrawCircle(x - 122, y - 137, 2);
		dcBuffer.DrawLine(x - 132, y - 130, x - 127, y - 127);
	}
	break;

	case 2:
	{
		dcBuffer.SetBrush(*wxYELLOW_BRUSH);
		dcBuffer.SetPen(*wxYELLOW_PEN);
		dcBuffer.DrawCircle(x - 132, y - 137, 20);
	}
	break;
	}
}