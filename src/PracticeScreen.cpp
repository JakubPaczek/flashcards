#include "PracticeScreen.h"
#include "Buttons.h"
#include "DatabaseManager.h"



// Constructor initializes the practice screen layout and widgets.
PracticeScreen::PracticeScreen(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this); // Main layout manager.



    // Title label setup.
    QLabel *titleLabel = new QLabel("Practice", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(30); // Set the font size.
    titleFont.setBold(true); // Makes the title bold.
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->addStretch(1);



    // Language selection ComboBox setup.
    languageComboBox = new QComboBox(this);

    languageComboBox->setFixedSize(200, 50);
    QFont comboBoxFont = languageComboBox->font();
    comboBoxFont.setPointSize(18);
    languageComboBox->setFont(comboBoxFont);


    layout->addWidget(languageComboBox);
    layout->setAlignment(languageComboBox, Qt::AlignCenter);



    // Standard mode button setup and signal connection.
    CustomButton* standardButton = new CustomButton("Standard", this);
    layout->addWidget(standardButton);
    layout->setAlignment(standardButton, Qt::AlignCenter);

    connect(standardButton, &QPushButton::clicked, this, [=]()
    {
        QString selectedLanguage = languageComboBox->currentText();
        emit standardModeSelected(selectedLanguage);
    });



    // Reversed mode button setup and signal connection.
    CustomButton* reversedButton = new CustomButton("Reversed", this);
    layout->addWidget(reversedButton);
    layout->setAlignment(reversedButton, Qt::AlignCenter);

    connect(reversedButton, &QPushButton::clicked, this, [=]()
    {
        QString selectedLanguage = languageComboBox->currentText();
        emit reversedModeSelected(selectedLanguage);
    });



    /*// Test mode button
    CustomButton* testButton = new CustomButton("Test", this);
    layout->addWidget(testButton);
    layout->setAlignment(testButton, Qt::AlignCenter);



    // True or false mode button
    CustomButton* trueFalseButton = new CustomButton("True/False", this);
    layout->addWidget(trueFalseButton);
    layout->setAlignment(trueFalseButton, Qt::AlignCenter);
    */



    // Return button setup and signal connection for returning to the main menu.
    CustomButton* returnButton = new CustomButton("Return", this);
    layout->addWidget(returnButton);
    layout->setAlignment(returnButton, Qt::AlignCenter);
    layout->addStretch(1);

    connect(returnButton, &QPushButton::clicked, this, &PracticeScreen::returnButtonClicked);

    setLayout(layout);
}

PracticeScreen::~PracticeScreen(){}



// Refreshes the language selection ComboBox with available languages from the database.
void PracticeScreen::refreshLanguages()
{
    languageComboBox->clear(); // Clears existing entries.
    languageComboBox->addItem("Any language"); // Adds default option.
    QStringList languages = DatabaseManager::getInstance().getAvailableLanguages();
    languageComboBox->addItems(languages); // Refills the ComboBox.
}

