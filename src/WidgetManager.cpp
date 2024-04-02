#include "WidgetManager.h"
#include "DatabaseManager.h"

// Class responsible for managing screen change.



// Constructs the WidgetManager and sets up connections between the screens.
WidgetManager::WidgetManager(QWidget *parent) : QWidget(parent)
{
    stackedWidget = new QStackedWidget(this);  // Initialize the stacked widget.

    QVBoxLayout *layout = new QVBoxLayout(this); // Main layout to hold the stackedWidget.
    layout->addWidget(stackedWidget);




    // Initialize and add the main screen to the stacked widget.
    mainScreen = new MainScreen();
    stackedWidget->addWidget(mainScreen);

    // Connection to switch to the Practice screen when its button is clicked.
    connect(mainScreen, &MainScreen::practiceButtonClicked, this, [this]()
    {
        practiceScreen->refreshLanguages();
        stackedWidget->setCurrentWidget(practiceScreen);
    });

    // Connection to refresh and switch to the Editor screen when its button is clicked.
    connect(mainScreen, &MainScreen::editorButtonClicked, this, [this]()
    {
        editorScreen->refreshComboBox();
        stackedWidget->setCurrentWidget(editorScreen);
    });

    // Statistics button clicked
    // ...



    // Initialize and add the Practice screen.
    practiceScreen = new PracticeScreen();
    stackedWidget->addWidget(practiceScreen);

    // Connections for selecting standard and reversed modes from the Practice screen.
    connect(practiceScreen, &PracticeScreen::standardModeSelected, this, [=](const QString &language) {
        standardScreen->setLanguage(language);
        standardScreen->prepareFlashcard();
        stackedWidget->setCurrentWidget(standardScreen);
    });

    connect(practiceScreen, &PracticeScreen::reversedModeSelected, this, [=](const QString &language)
    {
        reversedScreen->setLanguage(language);
        reversedScreen->prepareFlashcard();
        stackedWidget->setCurrentWidget(reversedScreen);
    });

    // Return to the main screen from the Practice screen.
    connect(practiceScreen, &PracticeScreen::returnButtonClicked, this, [this]()
    {
        stackedWidget->setCurrentWidget(mainScreen);
    });



    // Initialize the Standard and Reversed screens, add them, and set up connections for answer evaluation and screen navigation.
    setupScreen(standardScreen, true);
    setupScreen(reversedScreen, false);



    // Initialize and add the Editor screen, with a connection to return to the main screen.
    editorScreen = new EditorScreen();
    stackedWidget->addWidget(editorScreen);

    connect(editorScreen, &EditorScreen::returnButtonClicked, this, [this]()
    {
        stackedWidget->setCurrentWidget(mainScreen);
    });



    // "Statistics" screen
    // ...

    setLayout(layout);
}

WidgetManager::~WidgetManager() {}



// Helper function to setup Standard and Reversed screens.
void WidgetManager::setupScreen(StandardReversedScreen*& screen, bool isStandard)
{
    screen = new StandardReversedScreen(isStandard);
    stackedWidget->addWidget(screen);

    connect(screen, &StandardReversedScreen::wrongAnswerClicked, this, [this, screen]() {
        screen->prepareFlashcard();
        DatabaseManager::getInstance().updateFlashcardStatus(screen->getCardButton()->getCurrentFlashcardId(), false);
    });

    connect(screen, &StandardReversedScreen::correctAnswerClicked, this, [this, screen]() {
        screen->prepareFlashcard();
        DatabaseManager::getInstance().updateFlashcardStatus(screen->getCardButton()->getCurrentFlashcardId(), true);
    });

    connect(screen, &StandardReversedScreen::returnButtonClicked, this, [this]() {
        stackedWidget->setCurrentWidget(practiceScreen);
    });
}
