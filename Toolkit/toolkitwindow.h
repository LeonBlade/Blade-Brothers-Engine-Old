#ifndef TOOLKITWINDOW_H
#define TOOLKITWINDOW_H

#include <QMainWindow>
#include <QtOpenGL/QGLWidget>

namespace Ui {
    class ToolkitWindow;
}

class ToolkitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolkitWindow(QWidget *parent = 0);
    ~ToolkitWindow();

private:
    Ui::ToolkitWindow *ui;
    QGLWidget *mapWidget;
};

#endif // TOOLKITWINDOW_H
