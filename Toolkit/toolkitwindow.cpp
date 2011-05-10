#include "toolkitwindow.h"
#include "ui_toolkitwindow.h"

ToolkitWindow::ToolkitWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolkitWindow)
{
    ui->setupUi(this);
}

ToolkitWindow::~ToolkitWindow()
{
    delete ui;
}
