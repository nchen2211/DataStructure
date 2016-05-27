#include "lib/LoadWindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	LoadWindow loadWindow;
	loadWindow.show();

	return app.exec();
}
