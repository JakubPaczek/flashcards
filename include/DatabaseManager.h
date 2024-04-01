#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QStringList>
#include <QDebug>



// Structure to hold flashcard data.
struct FlashcardData {
    QString id;
    QString front;
    QString back;
    QString language;
};




// Singleton class to manage database operations for flashcards.
class DatabaseManager {
private:
    QSqlDatabase db;  // Holds the database connection.

    // Private constructor to prevent instantiation.
    DatabaseManager();
    // Destructor to handle resource cleanup.
    ~DatabaseManager();

    // Copy operations are disabled to ensure singleton integrity.
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

public:
    // Provides access to the singleton instance of the database manager.
    static DatabaseManager& getInstance();
    // Returns a reference to the QSqlDatabase object.
    QSqlDatabase& database();

    // Updates the status of a flashcard based on whether the answer was correct.
    void updateFlashcardStatus(QString flashcardId, bool isCorrect);

    // Retrieves a random flashcard from the database.
    FlashcardData getRandomFlashcard(const QString& language);

     // Gets a list of all languages available in the database.
    QStringList getAvailableLanguages();

    // Adds a new flashcard to the database.
    void addFlashcard(const QString& front, const QString& back, const QString& language);

    // Deletes a flashcard from the database.
    void deleteFlashcard(const QString& id);

    // Retrieves all flashcards from the database.
    QList<FlashcardData> getAllFlashcards();
};

#endif // DATABASEMANAGER_H
