#include "taskydesign.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>

//@author A0105750N
int main(int argc, char *argv[])
{
	const int ONE_INSTANCE_MODE = 1;
	const QString APP_NAME = "TaskyDesign";

	int ret = 0;
	QSharedMemory singletonCheck(APP_NAME);

	singletonCheck.create(ONE_INSTANCE_MODE);
	if(singletonCheck.error() != QSharedMemory::AlreadyExists){
		QApplication app(argc, argv);
		Q_INIT_RESOURCE(taskydesign);
		TaskyDesign window;
		window.show();
		ret = app.exec();
	}
	return ret;
}
