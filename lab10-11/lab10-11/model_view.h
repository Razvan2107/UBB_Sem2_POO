#pragma once
// mymodel.h
#include <QAbstractTableModel>
#include "service.h"

class MyModel : public QAbstractTableModel
{
    ATService& srv;
    Q_OBJECT
public:
    explicit MyModel(ATService& srv) :srv{ srv } {};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return srv.getAll().size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return 4;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole) {
            auto r = srv.getAll()[index.row()];
            if(index.column()==0)
                return QString::fromStdString(r.getDenumire());
            if (index.column() == 1)
                return QString::fromStdString(r.getDestinatie());
            if (index.column() == 2)
                return QString::fromStdString(r.getTip());
            if (index.column() == 3)
                return QString::number(r.getPret());

        }
        return QVariant();
    }
};