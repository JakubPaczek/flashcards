#ifndef PRACTICESCREEN_H
#define PRACTICESCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>



// PracticeScreen class defines the UI for the practice options screen.
class PracticeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PracticeScreen(QWidget *parent = nullptr); // Constructor with optional parent widget.
    ~PracticeScreen();


private:
    QComboBox *languageComboBox; // ComboBox to select the language for practice.


signals:
    // Signals to notify about user actions.
    void languageChanged(const QString &Language);

    void standardButtonClicked();
    void standardModeSelected(const QString &language);

    void reversedButtonClicked();
    void reversedModeSelected(const QString &language);

    void returnButtonClicked();
};



#endif // PRACTICESCREEN_H
