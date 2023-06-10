#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
private:
	wxPanel* panel;
	wxPanel* homePanel;
	wxPanel* encryptPanel;
	wxPanel* decryptPanel;
	wxPanel* generatePanel;

	//panel
	void OnButtonClicked(wxCommandEvent& evt);

	//homePanel
	void OnEncryptButtonClicked(wxCommandEvent& evt);
	void OnDecryptButtonClicked(wxCommandEvent& evt);
	void OnGenerateButtonClicked(wxCommandEvent& evt);

	//encryptPanel
	void OnEncryptPassButtonClicked(wxCommandEvent& evt);
	void OnEncryptBackButtonClicked(wxCommandEvent& evt);

	//decryptPanel
	void OnDecryptPassButtonClicked(wxCommandEvent& evt);
	void OnDecryptBackButtonClicked(wxCommandEvent& evt);

	//generatePanel
	void OnGeneratePassButtonClicked(wxCommandEvent& evt);
	void OnGenerateBackButtonClicked(wxCommandEvent& evt);

public:
	MainFrame(const wxString& title);
};

	