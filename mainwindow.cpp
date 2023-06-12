#include "mainwindow.h"
#include <QVBoxLayout> // Add this line to include the necessary header file

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scribble = new Scribble(this);

    lineButton = new QPushButton("Line", this);
    lineButton->setCheckable(true);
    circleButton = new QPushButton("Circle", this);
    circleButton->setCheckable(true);
    rectButton = new QPushButton("Rect", this);
    rectButton->setCheckable(true);
    listButton = new QPushButton("List", this);
    listButton->setCheckable(true);

    connect(lineButton, &QPushButton::clicked, this, &MainWindow::onShapeButtonClicked);
    connect(circleButton, &QPushButton::clicked, this, &MainWindow::onShapeButtonClicked);
    connect(rectButton, &QPushButton::clicked, this, &MainWindow::onShapeButtonClicked);
    connect(listButton, &QPushButton::clicked, this, &MainWindow::onShapeButtonClicked);
    connect(scribble, &Scribble::circleAdded, this, &MainWindow::onCircleAdded);
    connect(scribble, &Scribble::rectAdded, this, &MainWindow::onRectAdded);
    connect(scribble, &Scribble::lineAdded, this, &MainWindow::onLineAdded);

    shapeList = new QListWidget(this); // Created a single QListWidget

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(lineButton);
    layout->addWidget(circleButton);
    layout->addWidget(rectButton);
    layout->addWidget(listButton);
    layout->addWidget(shapeList); // Add the single QListWidget
    layout->addWidget(scribble);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::onShapeButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button == lineButton) {
        scribble->setShape("Line");
    } else if (button == circleButton) {
        scribble->setShape("Circle");
    } else if (button == rectButton) {
        scribble->setShape("Rect");
    } else if (button == listButton) {
        // Show the shape list
        shapeList->clear();
        const QVector<QRect>& circles = scribble->getCircles();
        const QVector<QRect>& rects = scribble->getRects();
        const QVector<QRect>& lines = scribble->getLines();

        // Add circles to the list
        for (int i = 0; i < circles.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem("Circle " + QString::number(i + 1), shapeList);
            shapeList->addItem(item);
        }

        // Add rects to the list
        for (int i = 0; i < rects.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem("Rectangle " + QString::number(i + 1), shapeList);
            shapeList->addItem(item);
        }

        // Add lines to the list
        for (int i = 0; i < lines.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem("Line " + QString::number(i + 1), shapeList);
            shapeList->addItem(item);
        }
    }
}

void MainWindow::onCircleAdded()
{
    const QVector<QRect>& circles = scribble->getCircles();

    // Clear the existing items in the shape list
    shapeList->clear();

    // Add circles to the list
    for (int i = 0; i < circles.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem("Circle " + QString::number(i + 1), shapeList);
        shapeList->addItem(item);
    }
}

void MainWindow::onRectAdded()
{
    const QVector<QRect>& rects = scribble->getRects();

    // Clear the existing items in the shape list
    shapeList->clear();

    // Add rects to the list
    for (int i = 0; i < rects.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem("Rectangle " + QString::number(i + 1), shapeList);
        shapeList->addItem(item);
    }
}

void MainWindow::onLineAdded()
{
    const QVector<QRect>& lines = scribble->getLines();

    // Clear the existing items in the shape list
    shapeList->clear();

    // Add lines to the list
    for (int i = 0; i < lines.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem("Line " + QString::number(i + 1), shapeList);
        shapeList->addItem(item);
    }
}

