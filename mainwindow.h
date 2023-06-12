#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include "scribble.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onShapeButtonClicked();

     void onCircleAdded();
     void onRectAdded();
     void onLineAdded();

private:
    QPushButton *lineButton;
    QPushButton *circleButton;
    QPushButton *rectButton;
    Scribble *scribble;

    QPushButton *listButton;
//    QListWidget *circleList;
//    QListWidget *rectList;
//    QListWidget *lineList;
    QListWidget *shapeList;
    void updateShapeList(const QVector<QString>& shapes);
//    QListWidget* shapeList;
    void updateCircleList();
    void updateRectList();
    void updateLineList();

};

#endif // MAINWINDOW_H
