#include "EditorScreen.h"
#include "Buttons.h"
#include "DatabaseManager.h"



// Constructor initializes the editor screen layout and widgets.
EditorScreen::EditorScreen(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);



    // Create and configure the title label.
    QLabel *titleLabel = new QLabel("Editor", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(30); // Set the font size.
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->setAlignment(titleLabel, Qt::AlignCenter);
    layout->addStretch(1);



    // Create line edits for the front, back, and language fields.
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch(1);

    QStringList labels = {"Front", "Back", "Language"};

    for (int i = 0; i < 3; i++)
    {
        QVBoxLayout *verticalLayout = new QVBoxLayout;



        // Label.
        QLabel *verticalLabel = new QLabel(labels[i]);

        QFont verticalLabelFont = verticalLabel->font();
        verticalLabelFont.setPointSize(18);
        verticalLabel->setFont(verticalLabelFont);



        //QLineEdit.
        QLineEdit *lineEdit = new QLineEdit(this);

        lineEdit->setFixedSize(200,50);
        QFont lineEditFont = lineEdit->font();
        lineEditFont.setPointSize(18);
        lineEdit->setFont(lineEditFont);

        lineEdits.append(lineEdit);



        // Connect them in vertical layout and put into horizontal layout.
        verticalLayout->addWidget(verticalLabel);
        verticalLayout->addWidget(lineEdit);

        horizontalLayout->addLayout(verticalLayout);
    }

    horizontalLayout->addStretch(1);
    layout->addLayout(horizontalLayout);



    // Add button.
    CustomButton* addButton = new CustomButton("Add", this);
    layout->addWidget(addButton);
    layout->setAlignment(addButton, Qt::AlignCenter);

    connect(addButton, &QPushButton::clicked, this, &EditorScreen::addCard);



    // QComboBox with cards.
    cardComboBox = new QComboBox(this);

    cardComboBox->setFixedSize(200, 50);
    QFont comboBoxFont = cardComboBox->font();
    comboBoxFont.setPointSize(18);
    cardComboBox->setFont(comboBoxFont);

    layout->addWidget(cardComboBox);
    layout->setAlignment(cardComboBox, Qt::AlignCenter);



    // Delete button.
    CustomButton* deleteButton = new CustomButton("Delete", this);
    layout->addWidget(deleteButton);
    layout->setAlignment(deleteButton, Qt::AlignCenter);

    connect(deleteButton, &QPushButton::clicked, this, &EditorScreen::deleteCard);



    // Return button.
    CustomButton* returnButton = new CustomButton("Return", this);
    layout->addWidget(returnButton);
    layout->setAlignment(returnButton, Qt::AlignCenter);
    layout->addStretch(1);

    connect(returnButton, &QPushButton::clicked, this, &EditorScreen::returnButtonClicked);
    setLayout(layout);
}

EditorScreen::~EditorScreen(){}



// Slot to add a new card after validation of the input fields.
void EditorScreen::addCard() {
    QString frontText = this->lineEdits[0]->text();
    QString backText = this->lineEdits[1]->text();
    QString language = this->lineEdits[2]->text();

    if ((frontText.isEmpty()) || (backText.isEmpty()) || (language.isEmpty()))
    {
        return;
    }

    DatabaseManager::getInstance().addFlashcard(frontText, backText, language);

    // Clear QLineEdit for Front and Back but keep Language.
    lineEdits[0]->clear();
    lineEdits[1]->clear();

    // Refresh QComboBox.
    refreshComboBox();
}



// Updates the combobox with the current list of flashcards.
void EditorScreen::refreshComboBox() {
    cardComboBox->clear();
    auto cards = DatabaseManager::getInstance().getAllFlashcards();
    for (const auto& card : cards)
    {
        cardComboBox->addItem(card.front + " -- " + card.back, card.id);
    }
}



// Slot to delete the currently selected flashcard.
void EditorScreen::deleteCard() {
    int index = cardComboBox->currentIndex();
    QString id = cardComboBox->itemData(index).toString();

    DatabaseManager::getInstance().deleteFlashcard(id);
\
    refreshComboBox();
}
