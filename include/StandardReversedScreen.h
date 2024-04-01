#ifndef STANDARDREVERSEDSCREEN_H
#define STANDARDREVERSEDSCREEN_H

#include <QWidget>
#include "Buttons.h"

// StandardReversedScreen class defines the UI for practicing flashcards in standard or reversed mode.
class StandardReversedScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructor with a flag indicating if the mode is standard (true) or reversed (false), and an optional parent widget.
    StandardReversedScreen(bool standardReversed, QWidget *parent = nullptr);
    ~StandardReversedScreen(); // Destructor

    // UI components
    FlashcardButton *cardButton; // Displays the flashcard content.
    CustomButton* correctButton; // Button to mark answer as correct.
    CustomButton* wrongButton; // Button to mark answer as wrong.
    CustomButton* returnButton; // Button to return to the previous screen.

    QString Language; // Holds the currently selected language for flashcards.

    // Prepares the next flashcard for display.
    void prepareFlashcard();

    // Sets the flashcards language.
    void setLanguage(const QString &language);

    // Returns the cardButton.
    FlashcardButton* getCardButton();

signals:
    // Signals to manage screen transitions and flashcard evaluations.
    void standardModeSelected(const QString &language);
    void reversedModeSelected(const QString &language);

    // Answer buttons signals
    void correctAnswerClicked();
    void wrongAnswerClicked();

    // Return to "Practice" screen signal
    void returnButtonClicked();
};

#endif // STANDARDREVERSEDSCREEN_H
