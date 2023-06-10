#include "MainFrame.h"
#include "passwords.h"
#include <wx/wx.h>
//#include <wx/spinctrl.h> NECCESARY FOR SOME CONTROLS


 //MUST BE POSTIVE. CANNOT BE 1 or 0. CANNOT BE BETWEEN 4999 - 5999
enum IDs 
{
	PASSWORD_ID = 2,
	USERNAME_ID = 3,
	MAINPANEL_ID = 4,
	HOMEPANEL_ID = 5,
	ENCRYPTPANEL_ID = 6,
	DECRYPTPANEL_ID = 7,
	PTBE_ID = 8,
	PTBD_ID = 9,
	GENERATEPANEL_ID = 10,
	DKEY_ID = 11,
};
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, MAINPANEL_ID, title)
{
	panel = new wxPanel(this); // Assign the panel

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); // Create a vertical box sizer

	mainSizer->Add(panel, 1, wxEXPAND); // Add the panel to the sizer

	SetSizer(mainSizer); // Set the mainSizer as the main sizer for the frame

	wxStaticText* welcomeText = new wxStaticText(panel, wxID_ANY, "Welcome to SDE", wxPoint(0, 180), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText->SetFont(welcomeText->GetFont().Scale(2.5));

	wxStaticText* loginText1 = new wxStaticText(panel, wxID_ANY, "Username:", wxPoint(250, 240), wxSize(800, -1));
	loginText1->SetFont(loginText1->GetFont().Scale(1.5));

	wxTextCtrl* usernameField = new wxTextCtrl(panel, USERNAME_ID, "", wxPoint(250, 270), wxSize(300, -1));

	wxStaticText* loginText2 = new wxStaticText(panel, wxID_ANY, "Password:", wxPoint(250, 310), wxSize(800, -1));
	loginText2->SetFont(loginText2->GetFont().Scale(1.5));

	wxTextCtrl* passwordField = new wxTextCtrl(panel, PASSWORD_ID, "", wxPoint(250, 340), wxSize(300, -1), wxTE_PASSWORD);

	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(450, 380), wxSize(100, 25));

	loginButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

	//TO UNBIND button->Unbind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	CreateStatusBar();
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt)
{
	wxTextCtrl* usernameField = wxDynamicCast(FindWindowById(USERNAME_ID), wxTextCtrl);
	wxTextCtrl* passwordField = wxDynamicCast(FindWindowById(PASSWORD_ID), wxTextCtrl);

	wxString username = usernameField->GetValue();
	wxString password = passwordField->GetValue();
		
	// Check if the username and password are in the array
	wxString usernames[] = { "user1", "user2", "user3" };
	wxString passwords[] = { "pass1", "pass2", "pass3" };

	bool found = false;
 for (size_t i = 0; i < sizeof(usernames) / sizeof(usernames[0]); i++) {
		if (username == usernames[i] && password == passwords[i]) {
			found = true;
			break;
		}
	}

	if (found) {
		wxLogStatus("Login successful");

		// Create the homepanel
		homePanel = new wxPanel(this, HOMEPANEL_ID);

		//Text

		wxStaticText* welcomeText = new wxStaticText(homePanel, wxID_ANY, "SD/E Home", wxPoint(0, 50), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
		welcomeText->SetFont(welcomeText->GetFont().Scale(3.5));

		//Buttons

		wxButton* encryptButton = new wxButton(homePanel, wxID_ANY, "Encrypt", wxPoint(150, 200), wxSize(150, 50));

		wxButton* decryptButton = new wxButton(homePanel, wxID_ANY, "Decrypt", wxPoint(500, 200), wxSize(150, 50));

		wxButton* generateButton = new wxButton(homePanel, wxID_ANY, "Generate", wxPoint(150, 400), wxSize(150, 50));

		//Event handling

		encryptButton->Bind(wxEVT_BUTTON, &MainFrame::OnEncryptButtonClicked, this);

		decryptButton->Bind(wxEVT_BUTTON, &MainFrame::OnDecryptButtonClicked, this);

		generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateButtonClicked, this);

		// Show the homepanel by removing mainpanel
		wxSizer* sizer = GetSizer();
		delete panel;
		panel = nullptr;
		sizer->Add(homePanel, 1, wxEXPAND);
		sizer->Layout();
	}
	else {
		wxLogMessage("Invalid login credentials");
	}
}

void MainFrame::OnGenerateButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("generate");

	// Panel create
	generatePanel = new wxPanel(this, GENERATEPANEL_ID);

	//Text
	wxStaticText* welcomeText = new wxStaticText(generatePanel, wxID_ANY, "Press Generate to generate a password", wxPoint(0, 80), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText->SetFont(welcomeText->GetFont().Scale(2));


	// Buttons
	wxButton* generateButton = new wxButton(generatePanel, wxID_ANY, "Generate", wxPoint(325, 200), wxSize(150, 50));

	wxButton* backButton = new wxButton(generatePanel, wxID_ANY, "Back", wxPoint(50, 525), wxSize(150, 50));

	// Event Handling
	generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGeneratePassButtonClicked, this);


	backButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateBackButtonClicked, this);


	// Hide the homePanel + Show encryptPanel
	wxSizer* sizer = GetSizer();
	homePanel->Hide();
	sizer->Add(generatePanel, 1, wxEXPAND);
	sizer->Layout();
}

void MainFrame::OnGeneratePassButtonClicked(wxCommandEvent& evt)
{
	wxString generate{passwordGen(16)};
	wxLogStatus(generate);


	// Text
	wxStaticText* welcomeText2 = new wxStaticText(generatePanel, wxID_ANY, "Your new password is:", wxPoint(0, 275), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText2->SetFont(welcomeText2->GetFont().Scale(1.8));
	wxTextCtrl* pEncryptedText = new wxTextCtrl(generatePanel, wxID_ANY, generate, wxPoint(250, 325), wxSize(300, 35));
	pEncryptedText->SetFont(pEncryptedText->GetFont().Scale(1.4));
}

void MainFrame::OnGenerateBackButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("back");

	// Remove the encryptPanel from the sizer
	wxSizer* sizer = GetSizer();
	delete generatePanel;
	generatePanel = nullptr;

	// Show the homePanel
	homePanel->Show();

	// Layout the sizer to update the display
	sizer->Layout();
}

void MainFrame::OnEncryptButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("encrypt");

	// Panel create
	encryptPanel = new wxPanel(this, ENCRYPTPANEL_ID);

	//Text
	wxStaticText* welcomeText = new wxStaticText(encryptPanel, wxID_ANY, "Please enter the password to be encrypted:", wxPoint(0, 80), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText->SetFont(welcomeText->GetFont().Scale(2));

	wxTextCtrl* passwordField = new wxTextCtrl(encryptPanel, PTBE_ID, "", wxPoint(250, 150), wxSize(300, -1));

	// Buttons
	wxButton* encryptButton = new wxButton(encryptPanel, wxID_ANY, "Encrypt", wxPoint(325, 200), wxSize(150, 50));

	wxButton* backButton = new wxButton(encryptPanel, wxID_ANY, "Back", wxPoint(50, 525), wxSize(150, 50));

	// Event Handling
	encryptButton->Bind(wxEVT_BUTTON, &MainFrame::OnEncryptPassButtonClicked, this);

	backButton->Bind(wxEVT_BUTTON, &MainFrame::OnEncryptBackButtonClicked, this);


	// Hide the homePanel + Show encryptPanel
	wxSizer* sizer = GetSizer();
	homePanel->Hide();
	sizer->Add(encryptPanel, 1, wxEXPAND);
	sizer->Layout();
}

void MainFrame::OnEncryptPassButtonClicked(wxCommandEvent& evt)
{
	wxTextCtrl* ptbeField = wxDynamicCast(FindWindowById(PTBE_ID), wxTextCtrl);
	wxString ptbe{ ptbeField->GetValue()};
	wxLogStatus(ptbe);
	std::vector<std::string>encryptedPwordVector{ encrypt_decrypt(wxStringToVector(ptbe), false)};
	std::vector<wxString>wxEncryptedPwordVector{ vectorToWxString(encryptedPwordVector) };
	wxString wxEnPword{wxSplit(wxEncryptedPwordVector, false)};
	wxString wxEnKey{ wxSplit(wxEncryptedPwordVector, true)};

	// Text
	wxStaticText* welcomeText2 = new wxStaticText(encryptPanel, wxID_ANY, "Your password encrypted is:", wxPoint(0, 275), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText2->SetFont(welcomeText2->GetFont().Scale(1.8));
	wxTextCtrl* pEncryptedPwordText = new wxTextCtrl(encryptPanel, wxID_ANY, wxEnPword, wxPoint(250, 325), wxSize(300, 35));
	pEncryptedPwordText->SetFont(pEncryptedPwordText->GetFont().Scale(1.4));
	wxStaticText* welcomeText3 = new wxStaticText(encryptPanel, wxID_ANY, "Your encryption key is:", wxPoint(0, 375), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText3->SetFont(welcomeText3->GetFont().Scale(1.8));
	wxTextCtrl* pEncryptKeyText = new wxTextCtrl(encryptPanel, wxID_ANY, wxEnKey, wxPoint(250, 425), wxSize(300, 35));
	pEncryptKeyText->SetFont(pEncryptKeyText->GetFont().Scale(1.4));
}

void MainFrame::OnEncryptBackButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("back");

	// Remove the encryptPanel from the sizer
	wxSizer* sizer = GetSizer();
	delete encryptPanel;
	encryptPanel = nullptr;

	// Show the homePanel
	homePanel->Show();

	// Layout the sizer to update the display
	sizer->Layout();
}

void MainFrame::OnDecryptButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("decrypt");

	// Panel create
	decryptPanel = new wxPanel(this, DECRYPTPANEL_ID);

	//Text
	wxStaticText* welcomeText = new wxStaticText(decryptPanel, wxID_ANY, "Please enter a password followed by its decryption key:", wxPoint(0, 80), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText->SetFont(welcomeText->GetFont().Scale(2));

	wxStaticText* loginText1 = new wxStaticText(decryptPanel, wxID_ANY, "Password:", wxPoint(250, 130), wxSize(800, -1));

	wxTextCtrl* passwordField = new wxTextCtrl(decryptPanel, PTBD_ID, "", wxPoint(250, 150), wxSize(300, -1));

	wxStaticText* loginText2 = new wxStaticText(decryptPanel, wxID_ANY, "Decryption Key:", wxPoint(250, 180), wxSize(800, -1));

	wxTextCtrl* decryptionKeyField = new wxTextCtrl(decryptPanel, DKEY_ID, "", wxPoint(250, 200), wxSize(300, -1));

	// Buttons
	wxButton* decryptButton = new wxButton(decryptPanel, wxID_ANY, "Decrypt", wxPoint(325, 240), wxSize(150, 50));

	wxButton* backButton = new wxButton(decryptPanel, wxID_ANY, "Back", wxPoint(50, 525), wxSize(150, 50));

	// Event Handling
	decryptButton->Bind(wxEVT_BUTTON, &MainFrame::OnDecryptPassButtonClicked, this);

	backButton->Bind(wxEVT_BUTTON, &MainFrame::OnDecryptBackButtonClicked, this);


	// Hide the homePanel + Show encryptPanel
	wxSizer* sizer = GetSizer();
	homePanel->Hide();
	sizer->Add(decryptPanel, 1, wxEXPAND);
	sizer->Layout();
}

void MainFrame::OnDecryptPassButtonClicked(wxCommandEvent& evt)
{
	wxTextCtrl* ptbdField = wxDynamicCast(FindWindowById(PTBD_ID), wxTextCtrl);
	wxString ptbd{ ptbdField->GetValue() };
	wxTextCtrl* dkeyField = wxDynamicCast(FindWindowById(DKEY_ID), wxTextCtrl);
	wxString dkey{ dkeyField->GetValue() };
	wxLogStatus(ptbd);
	std::vector<std::string>decryptedPwordVector{ encrypt_decrypt(wxStringToVectorx2(dkey, ptbd), true)};
	std::vector<wxString>wxDecryptedPwordVector{ vectorToWxString(decryptedPwordVector) };
	wxString wxDecryptedPword{ wxSplit(wxDecryptedPwordVector, true) };

	// Text
	wxStaticText* welcomeText2 = new wxStaticText(decryptPanel, wxID_ANY, "Your password decrypted is:", wxPoint(0, 290), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	welcomeText2->SetFont(welcomeText2->GetFont().Scale(1.8));
	wxTextCtrl* pDecryptedText = new wxTextCtrl(decryptPanel, wxID_ANY, wxDecryptedPword, wxPoint(250, 340), wxSize(300, 35));
	pDecryptedText->SetFont(pDecryptedText->GetFont().Scale(1.4));
}

void MainFrame::OnDecryptBackButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("back");

	// Remove the encryptPanel from the sizer
	wxSizer* sizer = GetSizer();
	delete decryptPanel;
	decryptPanel = nullptr;

	// Show the homePanel
	homePanel->Show();


	// Layout the sizer to update the display
	sizer->Layout();
}


























//Sample controls
	/*wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35), wxBU_LEFT);

	wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "Checkbox", wxPoint(550, 55), wxSize(100, -1), wxCHK_3STATE | wxCHK_ALLOW_3RD_STATE_FOR_USER);

	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Static text - not editable", wxPoint(0, 150), wxSize(400, -1), wxALIGN_CENTER_HORIZONTAL);
	staticText->SetBackgroundColour(*wxLIGHT_GREY);

	wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "Text Ctrl - editable", wxPoint(500, 145), wxSize(200, -1), wxTE_PASSWORD);

	wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(100, 250), wxSize(200, -1), wxSL_VALUE_LABEL);

	wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(500, 255), wxSize(200, -1));
	gauge->SetValue(50);

	wxArrayString choices;
	choices.Add("Item A");
	choices.Add("Item B");
	choices.Add("Item C");

	wxChoice* choice = new wxChoice(panel, wxID_ANY, wxPoint(150, 375), wxSize(100, -1), choices);
	choice->Select(0);

	wxSpinCtrl* spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(500, 375), wxSize(100, -1));

	wxListBox* listBox = new wxListBox(panel, wxID_ANY, wxPoint(150, 475), wxSize(100, -1), choices);

	wxRadioBox* radioBox = new wxRadioBox(panel, wxID_ANY, "Radio Box", wxPoint(500, 475), wxDefaultSize, choices);*/