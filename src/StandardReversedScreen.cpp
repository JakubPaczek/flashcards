#include "StandardReversedScreen.h"
#include "Buttons.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>



// Constructor initializes the screen based on the standard or reversed mode.
StandardReversedScreen::StandardReversedScreen(bool standardReversed, QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this); // Main layout manager.



    // Title setup based on mode.
    QLabel *titleLabel = new QLabel("Standard", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(30); // Set the font size.
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->addStretch(1);



    // Flashcard display button.
    cardButton = new FlashcardButton(standardReversed);
    layout->addWidget(cardButton);
    layout->setAlignment(cardButton, Qt::AlignCenter);



    // Layout for wrong and correct buttons.
    QHBoxLayout *layoutRow = new QHBoxLayout();
    layoutRow->addStretch(1);



    // Wrong answer button.
    wrongButton = new CustomButton("Wrong", this);
    layoutRow->addWidget(wrongButton);

    connect(wrongButton, &QPushButton::clicked, this, &StandardReversedScreen::wrongAnswerClicked);



    // Correct answer button.
    correctButton = new CustomButton("Correct", this);
    layoutRow->addWidget(correctButton);

    connect(correctButton, &QPushButton::clicked, this, &StandardReversedScreen::correctAnswerClicked);

    layoutRow->addStretch(1);
    layout->addLayout(layoutRow);



    // Return button setup.
    returnButton = new CustomButton("Return", this);
    layout->addWidget(returnButton);
    layout->setAlignment(returnButton, Qt::AlignCenter);

    connect(returnButton, &QPushButton::clicked, this, &StandardReversedScreen::returnButtonClicked);

    layout->addStretch(1);
    setLayout(layout); // Apply layout to the widget.
}

StandardReversedScreen::~StandardReversedScreen(){}



// Prepares and displays the next flashcard based on the selected language.
void StandardReversedScreen::prepareFlashcard()
{
    cardButton->randomFlashcard(this->Language);
}

// Sets the current language for flashcards.
void StandardReversedScreen::setLanguage(const QString &selectedLanguage)
{
    this->Language = selectedLanguage;
}

// Returns the pointer to the card display button.
FlashcardButton* StandardReversedScreen::getCardButton()
{
    return cardButton;
}
