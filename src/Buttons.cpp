#include "Buttons.h"
#include "DatabaseManager.h"



// Constructor for CustomButton that initializes button size and font.
CustomButton::CustomButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    this->setFixedSize(200, 50); // Sets a fixed size for the button.
    QFont buttonFont = this->font(); // Retrieves the current font.
    buttonFont.setPointSize(18); // Sets the font size to 18.
    this->setFont(buttonFont); // Applies the updated font to the button.
}



// Constructor for FlashcardButton that initializes its state and connects the click signal to the toggle slot.
FlashcardButton::FlashcardButton(bool standardReversed, QWidget *parent)
    : CustomButton("", parent), frontText(""), backText(""), isFrontVisible(standardReversed), standardOrReversed(standardReversed)
{
    connect(this, &QPushButton::clicked, this, &FlashcardButton::toggleFlashcard);
}

// Slot that toggles the flashcard text between the front and back.
void FlashcardButton::toggleFlashcard()
{
    isFrontVisible = !isFrontVisible; // Toggle the visibility flag.
    setText(isFrontVisible ? frontText : backText); // Update the button text based on the new flag state.
}

// Returns the ID of the currently displayed flashcard.
QString FlashcardButton::getCurrentFlashcardId()
{
    return id;
}

// Loads a random flashcard for the given language from the database and updates the button text.
void FlashcardButton::randomFlashcard(QString language)
{
    auto flashcard = DatabaseManager::getInstance().getRandomFlashcard(language);
    if (!flashcard.id.isEmpty()) // Checks if a valid flashcard was returned.
    {
        id = flashcard.id;
        frontText = flashcard.front;
        backText = flashcard.back;
    }
    else // If no valid flashcard was returned, clear the fields.
    {
        id.clear(); // Clears the id to indicate no valid flashcard.
        frontText = "N/A";
        backText = "N/A";
    }

    // Sets the initial button text based on the flashcard mode.
    setText(standardOrReversed ? frontText : backText);
    isFrontVisible = standardOrReversed;
}
