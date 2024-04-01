#include "DatabaseManager.h"



// Constructor initializes the database connection and sets up the flashcards table if it does not exist.
DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // Set the database to use SQLite.
    db.setDatabaseName("flashcards.db"); // Name the SQLite database file.

    // Attempt to open the database, log fatal error if it fails.
    if (!db.open())
    {
        qFatal("Cannot open database.");
        return;
    }

    // Create the Flashcards table if it doesn't already exist in the database.
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS Flashcards ("
                              "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "Language TEXT NOT NULL, "
                              "Front TEXT NOT NULL, "
                              "Back TEXT NOT NULL, "
                              "LastTime TEXT DEFAULT (datetime('now','localtime')) NOT NULL, "
                              "Points INTEGER DEFAULT 0 NOT NULL CHECK (Points >= 0 AND Points <= 100), "
                              "Correct INTEGER DEFAULT 0 NOT NULL, "
                              "Wrong INTEGER DEFAULT 0 NOT NULL);");

    // Log an error if the table creation fails.
    if (!success)
    {
        qCritical() << "SQL error: " << query.lastError().text();
    }
}

// Destructor closes the database connection.
DatabaseManager::~DatabaseManager()
{
    db.close();
}



// Provides access to the singleton instance of DatabaseManager.
DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

// Returns a reference to the database connection.
QSqlDatabase& DatabaseManager::database()
{
    return db;
}



// Retrieves a list of distinct languages available in the Flashcards table.
QStringList DatabaseManager::getAvailableLanguages()
{
    QStringList languages;
    QSqlQuery query("SELECT DISTINCT Language FROM Flashcards ORDER BY Language ASC");

    while (query.next())
    {
        languages << query.value(0).toString();
    }

    // Log an error if the query fails.
    if (query.lastError().isValid())
    {
        qDebug() << query.lastError();
    }

    return languages;
}



// Selects a random flashcard from the database, optionally filtered by language.
FlashcardData DatabaseManager::getRandomFlashcard(const QString& language)
{
    QSqlQuery query(db);
    QString queryLanguage = (language == "Any language") ? "%" : language;

    query.prepare("SELECT ID, Front, Back FROM Flashcards "
                  "WHERE (Language LIKE :language) AND "
                  "(Points >= 0 AND Points < 10) OR "
                  "(Points >= 10 AND Points < 20 AND LastTime < datetime('now', 'localtime', '-1 minute')) OR "
                  "(Points >= 20 AND Points < 30 AND LastTime < datetime('now', 'localtime', '-10 minutes')) OR "
                  "(Points >= 30 AND Points < 40 AND LastTime < datetime('now', 'localtime', '-30 minutes')) OR "
                  "(Points >= 40 AND Points < 50 AND LastTime < datetime('now', 'localtime', '-2 hours')) OR "
                  "(Points >= 50 AND Points < 60 AND LastTime < datetime('now', 'localtime', '-1 day')) OR "
                  "(Points >= 60 AND Points < 70 AND LastTime < datetime('now', 'localtime', '-3 days')) OR "
                  "(Points >= 70 AND Points < 80 AND LastTime < datetime('now', 'localtime', '-7 days')) OR "
                  "(Points >= 80 AND Points < 90 AND LastTime < datetime('now', 'localtime', '-1 month')) OR "
                  "(Points >= 90 AND Points < 100 AND LastTime < datetime('now', 'localtime', '-3 months')) OR "
                  "(Points = 100 AND LastTime < datetime('now', 'localtime', '-6 months')) "
                  "ORDER BY RANDOM() LIMIT 1;");
    query.bindValue(":language", queryLanguage);

    // Initialize FlashcardData with empty strings to ensure front and back are empty if no record is returned.
    FlashcardData flashcardData = { "", "", "", "" };

    if (query.exec() && query.next())
    {
        flashcardData =  {query.value(0).toString(), query.value(1).toString(), query.value(2).toString()};
    }
    else
    {
        qDebug() << "SQL error: " << query.lastError().text();
    }

    return flashcardData;
}



// Updates the points and count of correct or incorrect answers for a flashcard.
void DatabaseManager::updateFlashcardStatus(QString flashcardId, bool isCorrect)
{
    QSqlQuery query;

    // Prepare the query based on whether the answer was correct or incorrect.
    if (isCorrect)
    {
        query.prepare("UPDATE Flashcards SET "
                      "Points = CASE WHEN Points + 10 < 100 THEN Points + 10 ELSE 100 END, "
                      "Correct = Correct + 1, "
                      "LastTime = datetime('now','localtime') "
                      "WHERE ID = :flashcardId");
    }
    else
    {
        query.prepare("UPDATE Flashcards SET "
                      "Points = CASE WHEN Points - 5 > 0 THEN Points - 5 ELSE 0 END, "
                      "Wrong = Wrong + 1, "
                      "LastTime = datetime('now','localtime') "
                      "WHERE ID = :flashcardId");
    }

    query.bindValue(":flashcardId", flashcardId);

    // Log an error if the update fails.
    if (!query.exec())
    {
        qCritical() << "Could not update flashcard: " << query.lastError();
    }
}



// Inserts a new flashcard into the database.
void DatabaseManager::addFlashcard(const QString& front, const QString& back, const QString& language) {
    QSqlQuery query;
    query.prepare("INSERT INTO Flashcards (Language, Front, Back) VALUES (:language, :front, :back)");
    query.bindValue(":language", language);
    query.bindValue(":front", front);
    query.bindValue(":back", back);

    // Log an error if the insert fails.
    if (!query.exec())
    {
        qCritical() << "Could not insert flashcard: " << query.lastError();
    }
}



// Retrieves all flashcards from the database.
QList<FlashcardData> DatabaseManager::getAllFlashcards() {
    QList<FlashcardData> flashcards;
    QSqlQuery query(database());

    query.prepare("SELECT ID, Front, Back, Language FROM Flashcards ORDER BY Front ASC");

    if (query.exec())
    {
        while (query.next())
        {
            FlashcardData flashcard;
            flashcard.id = query.value(0).toString();
            flashcard.front = query.value(1).toString();
            flashcard.back = query.value(2).toString();
            flashcard.language = query.value(3).toString();
            flashcards.append(flashcard);
        }
    }
    else
    {
        qCritical() << "Could not retrieve flashcards: " << query.lastError().text();
    }

    return flashcards;
}



// Deletes a flashcard from the database using its ID.
void DatabaseManager::deleteFlashcard(const QString& id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Flashcards WHERE ID = :id");
    query.bindValue(":id", id);

    // Log an error if the delete fails.
    if (!query.exec())
    {
        qCritical() << "Could not delete flashcard: " << query.lastError();
    }
}
