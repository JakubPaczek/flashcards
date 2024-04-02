#include "mainScreen.h"
#include "Buttons.h"



// Constructor sets up the UI of the main window.
MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this); // Main layout manager.



    // Create and configure the title label.
    QLabel *titleLabel = new QLabel("Flashcards", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(30); // Set the font size.
    titleFont.setBold(true); // Make the font bold.
    titleLabel->setFont(titleFont);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->setAlignment(titleLabel, Qt::AlignCenter);
    layout->addStretch(1);



    // Create the Practice button and connect it to its signal.
    CustomButton* practiceButton = new CustomButton("Practice", this);
    layout->addWidget(practiceButton);
    layout->setAlignment(practiceButton, Qt::AlignCenter);

    connect(practiceButton, &QPushButton::clicked, this, &MainScreen::practiceButtonClicked);



    // Create the Editor button and connect it to its signal.
    CustomButton* editorButton = new CustomButton("Editor", this);
    layout->addWidget(editorButton);
    layout->setAlignment(editorButton, Qt::AlignCenter);

    connect(editorButton, &QPushButton::clicked, this, &MainScreen::editorButtonClicked);



    // Code for a Statistics button and connect it to its signal.
    /*
    CustomButton* statisticsButton = new CustomButton("Statistics", this);
    layout->addWidget(statisticsButton);
    layout->setAlignment(statisticsButton, Qt::AlignCenter);

    connect(statisticsButton, &QPushButton::clicked, this, &MainScreen::statisticsButtonClicked);
    */



    // Create the Exit button with a lambda function to quit the application.
    CustomButton* exitButton = new CustomButton("Exit", this);
    layout->addWidget(exitButton);
    layout->setAlignment(exitButton, Qt::AlignCenter);

    connect(exitButton, &QPushButton::clicked, []()
    {
        // Quit the application
        QApplication::quit();
    });

    layout->addStretch(1);
    setLayout(layout); // Apply the layout to the widget.
}



MainScreen::~MainScreen() {}
