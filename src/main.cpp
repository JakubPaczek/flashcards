#include "WidgetManager.h"

#include <QApplication>



// The entry point of the Qt application.
int main(int argc, char *argv[])
{
    // Initialize the QApplication object with command-line arguments.
    QApplication a(argc, argv);

    // Create an instance of the WidgetManager.
    WidgetManager w;

    // Display the WidgetManager window.
    w.show();

    // Enter the main event loop and wait until exit() is called.
    // Return the value that was set to exit() (which defaults to 0 if exec() exits normally).
    return a.exec();
}
