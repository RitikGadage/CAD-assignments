#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPoint>

class Scribble : public QWidget
{
    Q_OBJECT

public:
    explicit Scribble(QWidget *parent = nullptr);

    void setShape(const QString &shape);
    //for circle
    void addCircle(const QRect &circle);
    const QVector<QRect>& getCircles() const;

    //for rect
    void addRect(const QRect &rect);
    const QVector<QRect>& getRects() const;

    //for lines
    void addLine(const QRect &Line);
    const QVector<QRect>& getLines() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    struct ShapeData {
        QString shape;
        QVector<QPoint> points;
    };

    QString currentShape;
    QVector<ShapeData> shapes;
    bool drawingEnabled;
    bool isDrawing;

    QList<QRect> circles;
    QList<QRect> rects;
    QList<QRect> lines;


signals:
    void circleAdded();
    void circlesUpdated(const QVector<QRect>& circles);

    void rectAdded();
    void rectsUpdated(const QVector<QRect>& rects);

    void lineAdded();
    void linesUpdated(const QVector<QRect>& lines);

};

#endif // SCRIBBLE_H
