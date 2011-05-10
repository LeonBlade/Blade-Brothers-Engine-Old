#include "mapwidget.h"

#include <QMouseEvent>
#include <QKeyEvent>

MapWidget::MapWidget(QWidget *parent) : QGLWidget(parent) {}

void MapWidget::initializeGL()
{
    // set clear color black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // set the ortho to the screen
    glOrtho(0.0f, 640.f, 480.f, 0.0f, -1.0f, 1.0f);

    // enable texture 2d
    glEnable(GL_TEXTURE_2D);

    // enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MapWidget::resizeGL(int w, int h)
{
    // prevent catastrophic meltdown
    if (h == 0) h = 1;

    // set the viewport to the window dimentions
    glViewport(0, 0, w, h);

    // reset the coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set the ortho to the screen
    glOrtho(0.0f, 640.f, 480.f, 0.0f, -1.0f, 1.0f);

    // set back to model view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();
}

void MapWidget::paintGL()
{
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // for testing just create a simple quad
    glBegin(GL_QUADS);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(_x, _y);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(640, 0);

        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2i(640, 480);

        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2i(0, 480);
    }
    glEnd();
}

QSize MapWidget::minimumSizeHint() const
{
    return QSize(640, 480);
}

QSize MapWidget::sizeHint() const
{
    return QSize(640, 480);
}

void MapWidget::keyPressEvent(QKeyEvent *e)
{
    updateGL();
}

void MapWidget::mouseMoveEvent(QMouseEvent *e)
{
    _x = e->x();
    _y = e->y();
    updateGL();
}
