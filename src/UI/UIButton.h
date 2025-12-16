#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <QGraphicsPixmapItem>
#include <QObject>

class UIButton : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    UIButton(const QString &imagePath, QGraphicsItem *parent = nullptr);
    
signals:
    void clicked();
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif