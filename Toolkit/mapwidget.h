#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>

class MapWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);

public slots:

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    int _x, _y;

};

#endif // MAPWIDGET_H
