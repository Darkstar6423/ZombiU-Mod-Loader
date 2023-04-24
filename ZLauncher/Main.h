#pragma once
#include <Windows.h>
#include <stdio.h>
#include <filesystem>
#include <tchar.h>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "Config.h"
namespace fs = std::filesystem;





namespace ZLauncher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;




	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::String^ ZombiDirectory;
	private: System::Windows::Forms::Button^ LaunchButton;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::WebBrowser^ webBrowser1;


	private: System::ComponentModel::IContainer^ components;


	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LaunchButton = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// LaunchButton
			// 
			this->LaunchButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LaunchButton->Location = System::Drawing::Point(0, 610);
			this->LaunchButton->Name = L"LaunchButton";
			this->LaunchButton->Size = System::Drawing::Size(385, 78);
			this->LaunchButton->TabIndex = 0;
			this->LaunchButton->Text = L"Launch ZombiU";
			this->LaunchButton->UseVisualStyleBackColor = true;
			this->LaunchButton->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->BackColor = System::Drawing::SystemColors::Menu;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 25;
			this->listBox1->Location = System::Drawing::Point(0, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(385, 604);
			this->listBox1->TabIndex = 1;
			this->listBox1->Click += gcnew System::EventHandler(this, &Main::ListBox1_Click);
			// 
			// webBrowser1
			// 
			this->webBrowser1->Location = System::Drawing::Point(391, 0);
			this->webBrowser1->Margin = System::Windows::Forms::Padding(10);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(1189, 759);
			this->webBrowser1->TabIndex = 2;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Menu;
			this->ClientSize = System::Drawing::Size(1580, 757);
			this->Controls->Add(this->webBrowser1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->LaunchButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ZombiU Mod Loader";
			this->Load += gcnew System::EventHandler(this, &Main::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

		this->webBrowser1->Navigate(this->ZombiDirectory + L"\\mods\\default\\layout\\layout.html");


		gcnew cli::array<System::Object^>(100) ;

		this->listBox1->Items->Add("(No Mods)");
		std::string path = "mods";
		int i = 1;
		for (const auto& entry : fs::directory_iterator(path))
		{
			std::string filename = entry.path().filename().string();
			std::size_t found = filename.find(".", 0);
			if (entry.is_directory() && filename.compare("default") != 0 && i < 100)
			{
				auto managed = gcnew String(filename.c_str());
				this->listBox1->Items->Add(managed);
			}
		}
		this->listBox1->SetSelected(0, true);
	};
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {


		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(L"ZInjector.EXE",   // the path
			NULL,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		);
		config.settings["selectedMod"] = msclr::interop::marshal_as<std::string>(this->listBox1->SelectedItem->ToString());
		if (config.settings["selectedMod"].compare("(No Mods)") == 0)
		{
			config.settings["selectedMod"] = "default";
		}
		config.saveSettings();
		this->Close();
		return System::Void();

	};


	private: System::Void ListBox1_Click(System::Object^ sender, System::EventArgs^ e) {


		config.settings["selectedMod"] = msclr::interop::marshal_as<std::string>(this->listBox1->SelectedItem->ToString());
		if (config.settings["selectedMod"].compare("(No Mods)") == 0)
		{
			config.settings["selectedMod"] = "default";
		}
		auto tempSM = gcnew String(config.settings["selectedMod"].c_str());
		this->webBrowser1->Navigate(this->ZombiDirectory + L"\\mods\\"+ tempSM +"\\layout\\layout.html");


	};

	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
