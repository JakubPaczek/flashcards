#ifndef EDITORSCREEN_H
#define EDITORSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QVector>



// EditorScreen class defines the UI for editing flashcards.
class EditorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit EditorScreen(QWidget *parent = nullptr); // Constructor
    ~EditorScreen(); // Destructor

    // Updates the flashcard selection combobox.
    void refreshComboBox();

private slots:
    // Slot to handle adding a new flashcard.
    void addCard();

    // Slot to handle deleting an existing flashcard.
    void deleteCard();

private:
    QComboBox *cardComboBox; // Combobox for selecting flashcards.
    QVector<QLineEdit*> lineEdits; // Vector to hold line edits for front, back, and language.

signals:
    // Signal emitted when the return button is clicked.
    void returnButtonClicked();

};

#endif // EDITORSCREEN_H
