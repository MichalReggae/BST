#pragma once
#include "des.h"
#include "msclr\marshal_cppstd.h"

namespace DESAPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		bool bSkipping;
		//List<String^>round_keys;

		
		DESClass *testdes;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
			testdes = new DESClass();
			testdes->generate_key();
		}
		

		
	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ inputText;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ encryptButton;
	private: System::Windows::Forms::TextBox^ encyptedMessage;
	private: System::Windows::Forms::TextBox^ decryptedMessage;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ decryptButton;
	private: System::Windows::Forms::Button^ generateKey;
	private: System::Windows::Forms::ErrorProvider^ errorProvider1;
	private: System::ComponentModel::IContainer^ components;

		   

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->inputText = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->encryptButton = (gcnew System::Windows::Forms::Button());
			this->encyptedMessage = (gcnew System::Windows::Forms::TextBox());
			this->decryptedMessage = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->decryptButton = (gcnew System::Windows::Forms::Button());
			this->generateKey = (gcnew System::Windows::Forms::Button());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			this->SuspendLayout();
			// 
			// inputText
			// 
			this->inputText->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->inputText->Location = System::Drawing::Point(157, 68);
			this->inputText->MaxLength = 16;
			this->inputText->Name = L"inputText";
			this->inputText->Size = System::Drawing::Size(320, 20);
			this->inputText->TabIndex = 0;
			this->inputText->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			this->inputText->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::inputText_KeyPress);
			this->inputText->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::inputText_Validating);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->label1->Location = System::Drawing::Point(216, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(202, 18);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Wiadomosc do zakodowania";
			// 
			// encryptButton
			// 
			this->encryptButton->Location = System::Drawing::Point(157, 106);
			this->encryptButton->Name = L"encryptButton";
			this->encryptButton->Size = System::Drawing::Size(320, 23);
			this->encryptButton->TabIndex = 2;
			this->encryptButton->Text = L"Zaszyfruj";
			this->encryptButton->UseVisualStyleBackColor = true;
			this->encryptButton->Click += gcnew System::EventHandler(this, &MyForm::encryptButton_Click);
			// 
			// encyptedMessage
			// 
			this->encyptedMessage->Location = System::Drawing::Point(157, 195);
			this->encyptedMessage->MaxLength = 16;
			this->encyptedMessage->Multiline = true;
			this->encyptedMessage->Name = L"encyptedMessage";
			this->encyptedMessage->Size = System::Drawing::Size(320, 50);
			this->encyptedMessage->TabIndex = 3;
			this->encyptedMessage->TextChanged += gcnew System::EventHandler(this, &MyForm::encyptedMessage_TextChanged);
			// 
			// decryptedMessage
			// 
			this->decryptedMessage->Location = System::Drawing::Point(157, 294);
			this->decryptedMessage->MaxLength = 16;
			this->decryptedMessage->Multiline = true;
			this->decryptedMessage->Name = L"decryptedMessage";
			this->decryptedMessage->Size = System::Drawing::Size(320, 50);
			this->decryptedMessage->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->label2->Location = System::Drawing::Point(230, 156);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(175, 18);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Zakodowana wiadomoœæ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->label3->Location = System::Drawing::Point(226, 260);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(183, 18);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Zdekodowana wiadomoœæ";
			// 
			// decryptButton
			// 
			this->decryptButton->Location = System::Drawing::Point(157, 365);
			this->decryptButton->Name = L"decryptButton";
			this->decryptButton->Size = System::Drawing::Size(320, 23);
			this->decryptButton->TabIndex = 7;
			this->decryptButton->Text = L"Zdeszyfruj";
			this->decryptButton->UseVisualStyleBackColor = true;
			this->decryptButton->Click += gcnew System::EventHandler(this, &MyForm::decryptButton_Click);
			// 
			// generateKey
			// 
			this->generateKey->Location = System::Drawing::Point(157, 412);
			this->generateKey->Name = L"generateKey";
			this->generateKey->Size = System::Drawing::Size(320, 23);
			this->generateKey->TabIndex = 8;
			this->generateKey->Text = L"Generuj nowy klucz";
			this->generateKey->UseVisualStyleBackColor = true;
			this->generateKey->Click += gcnew System::EventHandler(this, &MyForm::generateKey_Click);
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(634, 461);
			this->Controls->Add(this->generateKey);
			this->Controls->Add(this->decryptButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->decryptedMessage);
			this->Controls->Add(this->encyptedMessage);
			this->Controls->Add(this->encryptButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->inputText);
			this->Name = L"MyForm";
			this->Text = L"DESAPP";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		
	}
	private: System::Void encryptButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->ValidateChildren()) {
			String^ msg = inputText->Text;
			string msg1 = msclr::interop::marshal_as<string>(msg);

			string output = MyForm::testdes->DES(msg1);
			encyptedMessage->Text = msclr::interop::marshal_as<String^>(output);
		}
		else {
			MessageBox::Show("Validation failed");
		}
		
	}
private: System::Void decryptButton_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ msg = encyptedMessage->Text;
	string msg1 = msclr::interop::marshal_as<string>(msg);
	string output = MyForm::testdes->DES_decryption(msg1);
	decryptedMessage->Text = msclr::interop::marshal_as<String^>(output);
}
private: System::Void generateKey_Click(System::Object^ sender, System::EventArgs^ e) {
	MyForm::testdes->generate_key();
}
private: System::Void encyptedMessage_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void inputText_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	String^ val = inputText->Text;
	string val1 = msclr::interop::marshal_as<string>(val);
	if (val1.length() < 16) {
		errorProvider1->SetError(inputText, "Mniej ni¿ 16 znaków");
		e->Cancel = true;
	}
	else {
		e->Cancel = false;
	}
	
}
private: System::Void MyForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	
}
private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	Application::Exit();
}
private: System::Void inputText_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	char c = e->KeyChar;
	if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')|| (c >= 'a' && c <= 'f')|| c== (char)8))
	{
		e->Handled = true;
	}


}
};

}
