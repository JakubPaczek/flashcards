#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>



// MainScreen class defines the main window of the application.
class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr); // Constructor with optional parent widget.
    ~MainScreen(); // Destructor

signals:
    // Emitted when the Practice button is clicked.
    void practiceButtonClicked();

     // Emitted when the Editor button is clicked.
    void editorButtonClicked();

    // Emitted when the Statistics button is clicked.
    // void statisticsButtonClicked();
};

#endif // MAINSCREEN_H
