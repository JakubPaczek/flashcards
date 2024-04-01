#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include "mainScreen.h"
#include "PracticeScreen.h"
#include "StandardReversedScreen.h"
#include "EditorScreen.h"
#include <QWidget>
#include <QStackedWidget>



// WidgetManager class orchestrates switching between different screens in the application.
class WidgetManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetManager(QWidget *parent = nullptr); // Constructor
    ~WidgetManager(); // Destructor

    // Helper function to setup Standard and Reversed screens.
    void setupScreen(StandardReversedScreen*& screen, bool isStandard);

private:
    QStackedWidget *stackedWidget; // Manages the application's screens in a stack.

    // Pointers to the various screens managed by this widget.
    MainScreen *mainScreen;
    PracticeScreen *practiceScreen;
    StandardReversedScreen *standardScreen;
    StandardReversedScreen *reversedScreen;
    EditorScreen *editorScreen;

};
#endif // WIDGETMANAGER_H
