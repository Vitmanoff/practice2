#pragma once

#include <cstdlib>
#include <ctime>

namespace Minesweeper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        int rows;
        int cols;
        int mines;
        array<Button^, 2>^ buttons;
        array<int, 2>^ mineField;
        Panel^ modePanel;

    public:
        MyForm(void)
        {
            InitializeComponent();
            ShowModeSelection();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->SuspendLayout();
               // 
               // MainForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(300, 320); 
               this->Name = L"MainForm";
               this->Text = L"Minesweeper";
               this->ResumeLayout(false);
           }
#pragma endregion

    private:
        void ShowModeSelection() {
            modePanel = gcnew Panel();
            modePanel->Size = System::Drawing::Size(300, 320);
            modePanel->Location = System::Drawing::Point(0, 0);

            Button^ btnEasy = gcnew Button();
            btnEasy->Location = System::Drawing::Point(50, 30);
            btnEasy->Size = System::Drawing::Size(200, 50);
            btnEasy->Text = L"Easy";
            btnEasy->Click += gcnew System::EventHandler(this, &MyForm::btnEasy_Click);
            modePanel->Controls->Add(btnEasy);

            Button^ btnMedium = gcnew Button();
            btnMedium->Location = System::Drawing::Point(50, 100);
            btnMedium->Size = System::Drawing::Size(200, 50);
            btnMedium->Text = L"Medium";
            btnMedium->Click += gcnew System::EventHandler(this, &MyForm::btnMedium_Click);
            modePanel->Controls->Add(btnMedium);

            Button^ btnHard = gcnew Button();
            btnHard->Location = System::Drawing::Point(50, 170);
            btnHard->Size = System::Drawing::Size(200, 50);
            btnHard->Text = L"Hard";
            btnHard->Click += gcnew System::EventHandler(this, &MyForm::btnHard_Click);
            modePanel->Controls->Add(btnHard);

            Button^ btnExit = gcnew Button();
            btnExit->Location = System::Drawing::Point(50, 240);
            btnExit->Size = System::Drawing::Size(200, 50);
            btnExit->Text = L"Exit";
            btnExit->Click += gcnew System::EventHandler(this, &MyForm::btnExit_Click);
            modePanel->Controls->Add(btnExit);

            this->Controls->Add(modePanel);
        }

        void InitializeGame(int rows, int cols, int mines) {
            this->rows = rows;
            this->cols = cols;
            this->mines = mines;

            this->Controls->Clear(); 

            buttons = gcnew array<Button^, 2>(rows, cols);
            mineField = gcnew array<int, 2>(rows, cols);
            InitializeMineField();

            this->SuspendLayout();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    buttons[i, j] = gcnew Button();
                    buttons[i, j]->Size = System::Drawing::Size(25, 25);
                    buttons[i, j]->Location = System::Drawing::Point(25 * j, 25 * i);
                    buttons[i, j]->Tag = gcnew Point(i, j);
                    buttons[i, j]->TabStop = false;
                    buttons[i, j]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Button_MouseDown);
                    this->Controls->Add(buttons[i, j]);
                }
            }
            this->ClientSize = System::Drawing::Size(25 * cols, 25 * rows); // Изменяемое разрешение в зависимости от режима
            this->ResumeLayout(false);
        }

        void InitializeMineField() {
            srand((unsigned int)time(nullptr));
            // Расставляем мины
            for (int k = 0; k < mines; k++) {
                int r, c;
                do {
                    r = rand() % rows;
                    c = rand() % cols;
                } while (mineField[r, c] == -1);
                mineField[r, c] = -1;
            }

            // Подсчет количества мин вокруг каждой ячейки
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (mineField[i, j] == -1) continue;
                    int count = 0;
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                            int ni = i + x;
                            int nj = j + y;
                            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && mineField[ni, nj] == -1) {
                                count++;
                            }
                        }
                    }
                    mineField[i, j] = count;
                }
            }
        }

        void btnEasy_Click(Object^ sender, EventArgs^ e) {
            InitializeGame(10, 10, 10); 
        }

        void btnMedium_Click(Object^ sender, EventArgs^ e) {
            InitializeGame(16, 16, 40); 
        }

        void btnHard_Click(Object^ sender, EventArgs^ e) {
            InitializeGame(24, 24, 99); 
        }

        void Button_MouseDown(Object^ sender, MouseEventArgs^ e) {
            Button^ clickedButton = dynamic_cast<Button^>(sender);
            if (clickedButton != nullptr) {
                Point^ position = dynamic_cast<Point^>(clickedButton->Tag);
                if (position != nullptr) {
                    int row = position->X;
                    int col = position->Y;

                    if (e->Button == System::Windows::Forms::MouseButtons::Right) {
                        // Обработка правого клика (помечает мину)
                        if (clickedButton->Text == "F") {
                            clickedButton->Text = "";
                        }
                        else {
                            clickedButton->Text = "F";
                        }
                    }
                    else if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                        // Обработка левого клика (открывает ячейку)
                        if (clickedButton->Text != "F") {
                            if (mineField[row, col] == -1) {
                                // Показывает все мины после поражения
                                ShowAllMines();
                                clickedButton->Text = "M";
                                clickedButton->BackColor = System::Drawing::Color::Red;
                                MessageBox::Show("Game Over!");
                                DisableAllButtons();
                                ReturnToMainMenu();
                            }
                            else {
                                clickedButton->Text = mineField[row, col].ToString();
                                clickedButton->BackColor = System::Drawing::Color::LightGray;
                                clickedButton->Enabled = false;
                                CheckWinCondition(); // Проверяет условие победы после открытия ячейки
                            }
                        }
                    }
                    CheckWinCondition(); // Проверяет условие победы также после пометки флажком
                }
            }
        }

        void ShowAllMines() {
            // Показывает все мины на поле(в данном случае при поражении)
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (mineField[i, j] == -1) {
                        buttons[i, j]->Text = "M"; // Мина
                        buttons[i, j]->BackColor = System::Drawing::Color::Red;
                    }
                }
            }
        }

        void CheckWinCondition() {
            int openedCells = 0;
            int correctlyFlaggedMines = 0;

            // Подсчитывает открытые ячейки без мин и правильно помеченные мины
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (!buttons[i, j]->Enabled) {
                        openedCells++;
                    }
                    if (buttons[i, j]->Text == "F" && mineField[i, j] == -1) {
                        correctlyFlaggedMines++;
                    }
                }
            }

            // Проверяет условие победы
            if (openedCells == (rows * cols - mines) && correctlyFlaggedMines == mines) {
                MessageBox::Show("You Win!");
                DisableAllButtons();
                ReturnToMainMenu();
            }
        }

        void DisableAllButtons() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    buttons[i, j]->Enabled = false;
                }
            }
        }

        void ReturnToMainMenu() {
            this->Controls->Clear();
            ShowModeSelection();
            this->ClientSize = System::Drawing::Size(300, 320);
            this->ResumeLayout(false);
        }

        void btnExit_Click(Object^ sender, EventArgs^ e) {
            Application::Exit();
        }
    };
}

