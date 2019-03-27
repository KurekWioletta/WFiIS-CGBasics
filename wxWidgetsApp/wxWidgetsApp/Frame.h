#pragma once
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>

class Frame : public wxFrame
{
public:
	Frame();
	~Frame();
private:
	void setUpUi();
	void bindEvents();
	void refresh();

	void onExit(wxCommandEvent& event);
	void onPaint(wxPaintEvent& event);
	void onUpdate(wxUpdateUIEvent& event);
	void onButtonSaveDrawingClick(wxCommandEvent&  e);
	void onButtonColorPickClick(wxCommandEvent&  e);
	void onCheckboxClick(wxCommandEvent&  e);
	void onScrollBarScroll(wxScrollEvent&   e);
	void onChoiceSelected(wxCommandEvent&  e);

	void draw(wxClientDC &drawClient);

	wxButton* m_buttonSaveDrawing;
	wxButton* m_buttonColorPick;
	wxCheckBox* m_checkBoxImgShow;
	wxScrollBar* m_scrollBarArmAngle;
	wxGauge* m_gaugeArmAngle;
	wxChoice* m_choiceImgPick;
	wxTextCtrl* m_textCtrl;

	wxPanel* m_panelDrawing;
	wxBoxSizer* m_bSizerContainer;
	wxBoxSizer* m_bSizerDrawingContainer;
	wxBoxSizer* m_bSizerUiContainer;

	wxString m_text;
	wxBitmap m_bitmapBanana;
	wxBitmap m_bitmapSavedImg;
	wxColour m_color;

	enum {
		ID_WXBUTTON_SAVE_DRAWING = 1001,
		ID_WXBUTTON_COLOR_PICK = 1002,
		ID_WXCHECKBOX_IMG_SHOW = 1003,
		ID_WXSCROLLBAR_ARM_ANGLE = 1004,
		ID_WXGAUGE_ARM_ANGLE = 1005,
		ID_WXCHOICE_IMG_PICK = 1006,
		ID_WXTEXTCTRL = 1007,
		ID_WXPANEL = 1008
	};
};

