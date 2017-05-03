
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    return app.exec();
}
