#include "scribble.h"
#include <QMouseEvent>

Scribble::Scribble(QWidget *parent)
    : QWidget(parent), currentShape("Line"), drawingEnabled(false), isDrawing(false)
{
    setFixedSize(400, 400);

}

void Scribble::setShape(const QString &shape)
{
    currentShape = shape;
    drawingEnabled = !currentShape.isEmpty();
    update();
}

void Scribble::addCircle(const QRect &circle)
{
    circles.append(circle);
    update();
}

void Scribble::addRect(const QRect &rect)
{
    rects.append(rect);
    update();
}

void Scribble::addLine(const QRect &line)
{
    lines.append(line);
    update();
}

const QVector<QRect>& Scribble::getCircles() const
{
    return circles;
}

const QVector<QRect>& Scribble::getRects() const
{
    return rects;
}

const QVector<QRect>& Scribble::getLines() const
{
    return lines;
}

void Scribble::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const ShapeData& shapeData : shapes) {
        const QString& shape = shapeData.shape;
        const QVector<QPoint>& points = shapeData.points;

        if (shape == "Line" && points.size() >= 2) {
            painter.setPen(Qt::black);
            painter.drawLine(points[0], points[1]);
        }
        else if (shape == "Circle" && points.size() >= 2) {
            painter.setPen(Qt::black);
            int radius = QLineF(points[0], points[1]).length();
            painter.drawEllipse(points[0], radius, radius);
        }
        else if (shape == "Rect" && points.size() >= 2) {
            painter.setPen(Qt::black);
            painter.drawRect(QRect(points[0], points[1]));
        }
    }

    if (isDrawing && currentShape != "" && shapes.size() > 0) {
        const ShapeData& currentShapeData = shapes.last();
        const QVector<QPoint>& currentPoints = currentShapeData.points;

        if (currentPoints.size() >= 2) {
            painter.setPen(Qt::black);

//            if (currentShape == "Line") {
//                painter.drawLine(currentPoints[0], currentPoints[1]);
//            }
//            else if (currentShape == "Circle") {
//                int radius = QLineF(currentPoints[0], currentPoints[1]).length();
//                painter.drawEllipse(currentPoints[0], radius, radius);
//            }
//            else if (currentShape == "Rect") {
//                painter.drawRect(QRect(currentPoints[0], currentPoints[1]));
//            }

        }
    }


}

void Scribble::mousePressEvent(QMouseEvent *event)
{
    if (drawingEnabled && event->button() == Qt::LeftButton) {
        if (currentShape == "Circle") {
            shapes.append({ currentShape, { event->pos(), event->pos() } });
            isDrawing = true;
            update();
        } else if (currentShape == "Rect") {
            shapes.append({ currentShape, { event->pos(), event->pos() } });
            isDrawing = true;
            update();
        } else if (currentShape == "Line") {
            shapes.append({ currentShape, { event->pos(), event->pos() } });
            isDrawing = true;
            update();
        }
    }
}



void Scribble::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing && event->buttons() & Qt::LeftButton) {
        if (shapes.size() > 0) {
            ShapeData& currentShapeData = shapes.last();
            QVector<QPoint>& currentPoints = currentShapeData.points;
            currentPoints[1] = event->pos();
            update();
        }
    }
}

void Scribble::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDrawing && event->button() == Qt::LeftButton) {
        if (currentShape == "Circle") {
            ShapeData& currentShapeData = shapes.last();
            QVector<QPoint>& currentPoints = currentShapeData.points;
            QPoint center = currentPoints[0];
            int radius = QLineF(currentPoints[0], currentPoints[1]).length();
            QRect circleRect(center.x() - radius, center.y() - radius, radius * 2, radius * 2);
            circles.append(circleRect);
            emit circlesUpdated(circles);
        }
        else if (currentShape == "Rect") {
            ShapeData& currentShapeData = shapes.last();
            QVector<QPoint>& currentPoints = currentShapeData.points;
            QRect rect(currentPoints[0], currentPoints[1]);
            rects.append(rect);
            emit rectsUpdated(rects);
        }
        else if (currentShape == "Line") {
            ShapeData& currentShapeData = shapes.last();
            QVector<QPoint>& currentPoints = currentShapeData.points;
            QRect line(currentPoints[0], currentPoints[1]);
            lines.append(line);
            emit linesUpdated(lines);
        }

        isDrawing = false;
        update();
    }
}


