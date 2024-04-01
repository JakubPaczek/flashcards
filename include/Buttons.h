#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QFont>



// CustomButton extends QPushButton with predefined styling.
class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(const QString &text, QWidget *parent = nullptr);
};



// FlashcardButton is a specialized button for displaying flashcards.
class FlashcardButton : public CustomButton
{
    Q_OBJECT

public:
    // Constructor for the flashcard button. Takes a boolean to determine if the card should start in standard or reversed mode.
    FlashcardButton(bool standardReversed, QWidget *parent = nullptr);

    // Loads a random flashcard from the database for a specified language.
    void randomFlashcard(QString Language);

    // Returns the ID of the current flashcard.
    QString getCurrentFlashcardId();

protected slots:
    // Toggles the flashcard between its front and back text.
    void toggleFlashcard();


private:
    QString id; // Flashcard ID.
    QString frontText; // Text displayed on the front of the flashcard.
    QString backText; // Text displayed on the back of the flashcard.
    bool isFrontVisible; // Tracks whether the front of the flashcard is currently visible.
    bool standardOrReversed; // Determines if the flashcard is in standard or reversed mode.

    // Updates the button text based on the current flashcard side being displayed.
    void updateButtonText();
};

#endif // BUTTONS_H
