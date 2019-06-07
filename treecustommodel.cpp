#include "treecustommodel.h"

TreeCustomModel::TreeCustomModel(QObject *parent):QAbstractItemModel(parent){

    rootNode = new Node();
    rootNode->Parent = nullptr;

    //Temp
    rootNode->columnData.push_back(QString("Name"));
    rootNode->columnData.push_back(QString("Summary"));
    rootNode->columnData.push_back(QString("Other"));
}

TreeCustomModel::~TreeCustomModel()
{
     delete rootNode;
}

QVariant TreeCustomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    Node *selectedNode = static_cast<Node*>(index.internalPointer());

    return selectedNode->columnData[index.column()];
}

Qt::ItemFlags TreeCustomModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()){
            return 0;
    }
    return QAbstractItemModel::flags(index);
}

QVariant TreeCustomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootNode->columnData[section];

    return QVariant();
}

QModelIndex TreeCustomModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)){
        return QModelIndex();
    }

    Node *parentNode;

    if (!parent.isValid()){
        parentNode = rootNode;
    }
    else{
        parentNode = static_cast<Node*>(parent.internalPointer());
    }
    if(row >= parentNode->children.length()){
        return QModelIndex();
    }
    else{
        return createIndex(row, column, parentNode->children[row]);
    }
}

QModelIndex TreeCustomModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()){
        return QModelIndex();
    }
    Node *childNode = static_cast<Node*>(index.internalPointer());
    Node *parentNode = childNode->Parent;

    if (parentNode == rootNode){
        return QModelIndex();
    }

    int row = 0;
    if(parentNode->Parent){
        //Ask the parent where I am;
        row = parentNode->Parent->children.indexOf(parentNode);
    }
    return createIndex(row, 0, parentNode);
}

int TreeCustomModel::rowCount(const QModelIndex &parent) const
{
    Node *parentNode;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid()){
        parentNode = rootNode;
    }
    else{
        parentNode = static_cast<Node*>(parent.internalPointer());
    }

    return parentNode->children.length();

}

int TreeCustomModel::columnCount(const QModelIndex &index) const
{
    if (index.isValid()){
        return static_cast<Node*>(index.internalPointer())->children.length();
    }
    else{
        return rootNode->columnData.length();
    }

}

bool TreeCustomModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Node* parentNode;
    if (!parent.isValid()){
        parentNode = rootNode;
    }
    else{
        parentNode =static_cast<Node*>(parent.internalPointer());
    }
    beginInsertRows(parent, parentNode->children.length(), parentNode->children.length() + count);
    if(row == 0){
        for (int i = 0; i < count; ++i) {
            Node* tempNode = new Node();
            tempNode->Parent = parentNode;
            tempNode->columnData.push_back(QString("default"));
            tempNode->columnData.push_back(QString("default"));

            tempNode->columnData.push_back(QString("default"));

            parentNode->children.prepend(tempNode);

        }
        endInsertRows();
        return true;
    }
    else{

        for (int i = 0; i < count; ++i) {
            Node* tempNode = new Node();
            tempNode->Parent = parentNode;
            tempNode->columnData.push_back(QString("default"));
            tempNode->columnData.push_back(QString("default"));

            tempNode->columnData.push_back(QString("default"));

            parentNode->children.push_back(tempNode);

        }
        endInsertRows();
        return true;
    }
    //Never
    return false;
}


