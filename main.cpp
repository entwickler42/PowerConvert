#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QtDeclarative>
#include "emathlistmodel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QmlApplicationViewer viewer;
		
	qmlRegisterType<EmathListModel>("EmathListModel", 1, 0, "EmathListModel");
	
	EmathListModel model;
	
	viewer.engine()->rootContext()->setContextProperty("listModel", &model);
	
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    viewer.setMainQmlFile(QLatin1String("qml/PowerConvert/main.qml"));	
	viewer.showFullScreen();	

    return app.exec();
}
