#ifndef TREECUSTOMMODEL_H
#define TREECUSTOMMODEL_H

#include <QAbstractItemModel>


class TreeCustomModel : public QAbstractItemModel
{


public:
    explicit TreeCustomModel(QObject*parent=nullptr);
    ~TreeCustomModel() override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
private:
    struct Node{
        Node* Parent = nullptr;
        QList<QVariant> columnData;
        QList<Node*> children;
    };

    Node* rootNode = nullptr;


};

#endif // TREECUSTOMMODEL_H
