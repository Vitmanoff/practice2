#pragma once

#include <unordered_map>
#include <ctime>

namespace Fon {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();
            this->WindowState = FormWindowState::Maximized;
            srand((unsigned)time(0)); // ������������� ���������� ��������� �����
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::ComboBox^ comboBox1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ buttonRandom;
    private: System::Windows::Forms::Button^ buttonSpecial;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
               this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->buttonRandom = (gcnew System::Windows::Forms::Button());
               this->buttonSpecial = (gcnew System::Windows::Forms::Button());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
               this->SuspendLayout();
               // 
               // pictureBox1
               // 
               this->pictureBox1->Location = System::Drawing::Point(12, 12);
               this->pictureBox1->Name = L"pictureBox1";
               this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
               this->pictureBox1->TabIndex = 0;
               this->pictureBox1->TabStop = false;
               this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
               // 
               // comboBox1
               // 
               this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->comboBox1->FormattingEnabled = true;
               this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
                   L"�����", L"���������", L"�������", L"������", L"������", L"������", L"������������", L"����"
               });
               this->comboBox1->Location = System::Drawing::Point(12, 12);
               this->comboBox1->Name = L"comboBox1";
               this->comboBox1->Size = System::Drawing::Size(121, 200);
               this->comboBox1->Anchor = System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left;
               this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
               // 
               // button1
               // 
               this->button1->Location = System::Drawing::Point(12, 40);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(121, 25);
               this->button1->TabIndex = 2;
               this->button1->Text = L"�����������";
               this->button1->UseVisualStyleBackColor = true;
               this->button1->Anchor = System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left;
               this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
               // 
               // buttonRandom
               // 
               this->buttonRandom->Location = System::Drawing::Point(12, 70);
               this->buttonRandom->Name = L"buttonRandom";
               this->buttonRandom->Size = System::Drawing::Size(121, 25);
               this->buttonRandom->TabIndex = 3;
               this->buttonRandom->Text = L"������";
               this->buttonRandom->UseVisualStyleBackColor = true;
               this->buttonRandom->Click += gcnew System::EventHandler(this, &Form1::buttonRandom_Click);
               // 
               // buttonSpecial
               // 
               this->buttonSpecial->Location = System::Drawing::Point(12, 100);
               this->buttonSpecial->Name = L"buttonSpecial";
               this->buttonSpecial->Size = System::Drawing::Size(121, 40);
               this->buttonSpecial->TabIndex = 4;
               this->buttonSpecial->Text = L"���������� �����������";
               this->buttonSpecial->UseVisualStyleBackColor = true;
               this->buttonSpecial->Click += gcnew System::EventHandler(this, &Form1::buttonSpecial_Click);
               // 
               // Form1
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(224, 253);
               this->Controls->Add(this->buttonSpecial);
               this->Controls->Add(this->buttonRandom);
               this->Controls->Add(this->button1);
               this->Controls->Add(this->comboBox1);
               this->Controls->Add(this->pictureBox1);
               this->Name = L"Form1";
               this->Text = L"Fon";
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
               this->ResumeLayout(false);
           }
#pragma endregion
    private:
        // ����� ��� �������� ����������� ��� ��������� ���������
        void LoadImageForProfession(String^ profession) {
            Image^ img = nullptr;
            if (profession == "�����") {
                img = Image::FromFile("images/malar.jpg");
            }
            else if (profession == "���������") {
                img = Image::FromFile("images/fura.jpg");
            }
            else if (profession == "�������") {
                img = Image::FromFile("images/miner.jpg");
            }
            else if (profession == "������") {
                img = Image::FromFile("images/barber.jpg");
            }
            else if (profession == "������") {
                img = Image::FromFile("images/barmen.jpg");
            }
            else if (profession == "������") {
                img = Image::FromFile("images/kyra.png");
            }
            else if (profession == "������������") {
                img = Image::FromFile("images/meha.png");
            }
            else if (profession == "����") {
                img = Image::FromFile("images/vrach.jpg");
            }
            // ��������� ����������� � PictureBox
            pictureBox1->Image = img;
        }

    private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        // ��������� ��������� ���������
        String^ selectedProfession = comboBox1->SelectedItem->ToString();
        // ����������� ��� ��������� ���������
        LoadImageForProfession(selectedProfession);
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        // �������� ��������� ���������
        String^ selectedProfession = comboBox1->SelectedItem != nullptr ? comboBox1->SelectedItem->ToString() : nullptr;
        if (selectedProfession != nullptr) {
            // ��������� � ����������� � ��������� ���������
            MessageBox::Show("�� ������� ���������: " + selectedProfession, "�������������", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        else {
            // ���������, ���� ��������� �� �������
            MessageBox::Show("����������, �������� ��������� �� ������.", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }

           // ���������� ������� ��� ������ "������"
    private: System::Void buttonRandom_Click(System::Object^ sender, System::EventArgs^ e) {
        // ������ � �����������
        cli::array<String^>^ professions = gcnew cli::array<String^>(8) {
            "�����", "���������", "�������", "������", "������", "������", "������������", "����"
        };

        // ����� ��������� ���������
        int index = rand() % professions->Length;
        String^ randomProfession = professions[index];

        // ����������� ��� ��������� ���������
        LoadImageForProfession(randomProfession);

        // ���������� ��������� � ����������� � ��������� ���������
        MessageBox::Show("��������� ���������: " + randomProfession, "������", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

           // ���������� ������� ��� ������ "����������� �����������"
    private: System::Void buttonSpecial_Click(System::Object^ sender, System::EventArgs^ e) {
        // ���� � ����� ����� ������ ��������
        Form^ inputForm = gcnew Form();
        inputForm->Text = "������� ����� ��������";
        inputForm->Size = System::Drawing::Size(300, 150);
        inputForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        inputForm->MaximizeBox = false;

        Label^ label = gcnew Label();
        label->Text = "����� ��������:";
        label->Location = Point(10, 20);
        label->AutoSize = true;

        TextBox^ textBox = gcnew TextBox();
        textBox->Location = Point(120, 20);
        textBox->Size = System::Drawing::Size(150, 20);

        Button^ confirmButton = gcnew Button();
        confirmButton->Text = "�����������";
        confirmButton->Location = Point(100, 60);
        confirmButton->DialogResult = System::Windows::Forms::DialogResult::OK;

        inputForm->Controls->Add(label);
        inputForm->Controls->Add(textBox);
        inputForm->Controls->Add(confirmButton);

        if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            String^ phoneNumber = textBox->Text;
            // ����������� ����������� � ���������
            String^ specialImage = "images/3b.jpg"; 
            String^ specialMessage = "�� ������ ���������� �����! �� �������� � ���� �� ������ ��������: " + phoneNumber;

            pictureBox1->Image = Image::FromFile(specialImage);

            MessageBox::Show(specialMessage, "���������� �����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    };
}