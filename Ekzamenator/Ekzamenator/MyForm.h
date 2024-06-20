#pragma once

namespace Ekzamenator {
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();
            // Установка размера формы
            this->ClientSize = System::Drawing::Size(460, 200); // Размеры окна
            this->questionLabel->AutoSize = true; // Размеры метки автоматически меняются в зависимости от содержимого
            this->option1RadioButton->AutoSize = true; // Размеры кнопки автоматически меняются в зависимости от содержимого

            // Инициализация массивов в конструкторе
            questions = gcnew array<String^> {
                "Яка клавішна комбінація використовується для копіювання тексту?",
                    "Як називається програма, що захищає комп'ютер від шкідливих програм?",
                    "Яка одиниця вимірювання інформації в комп'ютерах?",
                    "Які типи файлів можна зберігати на флеш-накопичувачах?",
                    "Що означає скорочення 'LAN' у комп'ютерних технологіях?",
                    "Яка клавішна комбінація використовується для відкриття меню 'Пуск' у Windows?",
                    "Які інструменти використовуються для створення презентацій?",
                    "Які з цих програм є електронною поштою?",
                    "Яка команда використовується для закриття вікна програми в ОС Windows?",
                    "Як називається програма, яка дозволяє переглядати веб-сторінки?"
            };

            options = gcnew array<array<String^>^> {
                gcnew array<String^>{"Ctrl + C", "Ctrl + V", "Ctrl + X"},
                    gcnew array<String^>{"Антипрограм", "Антихакер", "Антивірус"},
                    gcnew array<String^>{"Гігабайт", "Мегабайт", "Байт"},
                    gcnew array<String^>{"Текстові, зображення, відео", "Тільки текстові файли", "Тільки відео файли"},
                    gcnew array<String^>{"Лінійний адаптер", "Локальна мережа", "Локальний адаптер мережі"},
                    gcnew array<String^>{"Win + R", "Ctrl + Esc", "Win"},
                    gcnew array<String^>{"PowerPoint, Google Slides", "Photoshop, Illustrator", "Word, Excel"},
                    gcnew array<String^>{"Gmail, Outlook", "Word, Excel", "Photoshop, Illustrator"},
                    gcnew array<String^>{"Alt + F4", "Ctrl + C", "Ctrl + Z"},
                    gcnew array<String^>{"Текстовий редактор", "Антивірус", "Веб-браузер"}
            };

            correctAnswers = gcnew array<int> { 0, 2, 2, 0, 1, 2, 0, 0, 0, 2 };

            // Инициализация переменной для подсчета баллов
            score = 0;
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ questionLabel;
        System::Windows::Forms::RadioButton^ option1RadioButton;
        System::Windows::Forms::RadioButton^ option2RadioButton;
        System::Windows::Forms::RadioButton^ option3RadioButton;
        System::Windows::Forms::Button^ nextButton;

        int currentQuestionIndex; // Индекс текущего вопроса
        const int totalQuestions = 10; // Общее количество вопросов

        array<String^>^ questions;
        array<array<String^>^>^ options;
        array<int>^ correctAnswers;
        int score; // Переменная для отслеживания результата

        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->questionLabel = gcnew System::Windows::Forms::Label();
            this->option1RadioButton = gcnew System::Windows::Forms::RadioButton();
            this->option2RadioButton = gcnew System::Windows::Forms::RadioButton();
            this->option3RadioButton = gcnew System::Windows::Forms::RadioButton();
            this->nextButton = gcnew System::Windows::Forms::Button();
            this->SuspendLayout();
            // 
            // questionLabel
            // 
            this->questionLabel->AutoSize = true;
            this->questionLabel->Location = System::Drawing::Point(33, 31);
            this->questionLabel->Name = L"questionLabel";
            this->questionLabel->Size = System::Drawing::Size(35, 13);
            this->questionLabel->TabIndex = 0;
            this->questionLabel->Text = L"label1";
            // 
            // option1RadioButton
            // 
            this->option1RadioButton->AutoSize = true;
            this->option1RadioButton->Location = System::Drawing::Point(36, 67);
            this->option1RadioButton->Name = L"option1RadioButton";
            this->option1RadioButton->Size = System::Drawing::Size(85, 17);
            this->option1RadioButton->TabIndex = 1;
            this->option1RadioButton->TabStop = true;
            this->option1RadioButton->Text = L"radioButton1";
            this->option1RadioButton->UseVisualStyleBackColor = true;
            // 
            // option2RadioButton
            // 
            this->option2RadioButton->AutoSize = true;
            this->option2RadioButton->Location = System::Drawing::Point(36, 90);
            this->option2RadioButton->Name = L"option2RadioButton";
            this->option2RadioButton->Size = System::Drawing::Size(85, 17);
            this->option2RadioButton->TabIndex = 2;
            this->option2RadioButton->TabStop = true;
            this->option2RadioButton->Text = L"radioButton2";
            this->option2RadioButton->UseVisualStyleBackColor = true;
            // 
            // option3RadioButton
            // 
            this->option3RadioButton->AutoSize = true;
            this->option3RadioButton->Location = System::Drawing::Point(36, 113);
            this->option3RadioButton->Name = L"option3RadioButton";
            this->option3RadioButton->Size = System::Drawing::Size(85, 17);
            this->option3RadioButton->TabIndex = 3;
            this->option3RadioButton->TabStop = true;
            this->option3RadioButton->Text = L"radioButton3";
            this->option3RadioButton->UseVisualStyleBackColor = true;
            // 
            // nextButton
            // 
            this->nextButton->Location = System::Drawing::Point(36, 150);
            this->nextButton->Name = L"nextButton";
            this->nextButton->Size = System::Drawing::Size(75, 23);
            this->nextButton->TabIndex = 4;
            this->nextButton->Text = L"Next";
            this->nextButton->UseVisualStyleBackColor = true;
            this->nextButton->Click += gcnew System::EventHandler(this, &MyForm::nextButton_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 212);
            this->Controls->Add(this->nextButton);
            this->Controls->Add(this->option3RadioButton);
            this->Controls->Add(this->option2RadioButton);
            this->Controls->Add(this->option1RadioButton);
            this->Controls->Add(this->questionLabel);
            this->Name = L"MyForm";
            this->Text = L"Test";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
            // Инициализирует тест первым вопросом
            currentQuestionIndex = 0;
            LoadQuestion();
        }

        System::Void LoadQuestion() {
            // Загружает текущий вопрос и варианты
            questionLabel->Text = questions[currentQuestionIndex];
            option1RadioButton->Text = options[currentQuestionIndex][0];
            option2RadioButton->Text = options[currentQuestionIndex][1];
            option3RadioButton->Text = options[currentQuestionIndex][2];
        }

        System::Void nextButton_Click(System::Object^ sender, System::EventArgs^ e) {
            // Проверяет, выбран ли какой-либо вариант ответа
            if (option1RadioButton->Checked || option2RadioButton->Checked || option3RadioButton->Checked) {
                // Проверяет, правильный ли выбранный ответ
                if ((option1RadioButton->Checked && correctAnswers[currentQuestionIndex] == 0) ||
                    (option2RadioButton->Checked && correctAnswers[currentQuestionIndex] == 1) ||
                    (option3RadioButton->Checked && correctAnswers[currentQuestionIndex] == 2)) {
                    // Увеличивает счетчик правильных ответов
                    score++;
                }

                // Переходит к следующему вопросу
                currentQuestionIndex++;

                // Если все вопросы были отвечены, отображает окно с результатами
                if (currentQuestionIndex == totalQuestions) {
                    // Отображение сообщение о завершении теста и выводим счет
                    String^ message = "Test finished!\nYour score: " + score + " out of " + totalQuestions;
                    MessageBox::Show(message);

                    // Сбрасывает тест
                    currentQuestionIndex = 0;
                    score = 0;
                    LoadQuestion();
                }
                else {
                    // Загружает следующий вопрос
                    LoadQuestion();

                    // Сбрасывает выбранный вариант ответа
                    option1RadioButton->Checked = false;
                    option2RadioButton->Checked = false;
                    option3RadioButton->Checked = false;
                }
            }
            else {
                // Если не выбран ни один вариант ответа, сообщает пользователю об этом
                MessageBox::Show("Please select an option!");
            }
        }
    };
}

