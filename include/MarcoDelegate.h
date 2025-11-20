#ifndef MARCODELEGATE_H
#define MARCODELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class MarcoDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

        QVariant data = index.data(Qt::UserRole);
        
        if (!data.isValid()) {
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }

        painter->save();
        
        QRect rect = option.rect;

        double anchoUnitario = rect.width() / 5.0;
        
        QList<QVariant> estados = data.toList();
        
        for(int i = 0; i < 5; ++i) {
            int estado = estados[i].toInt();
            QRectF subRect(rect.x() + (i * anchoUnitario), rect.y(), anchoUnitario, rect.height());
            
            QColor color;

            if (estado == -1) color = Qt::white;       
            else if (estado == -2) color = Qt::black;   
            else {
                switch(estado) {
                    case 1: color = Qt::blue; break;
                    case 2: color = Qt::red; break;
                    case 3: color = Qt::magenta; break; 
                    default: color = Qt::gray; break;
                }
            }
            
            painter->fillRect(subRect, color);

            painter->setPen(QPen(Qt::lightGray, 1));
            painter->drawRect(subRect);
        }

        painter->setPen(Qt::black);
        painter->drawRect(rect);

        painter->restore();
    }
};

#endif