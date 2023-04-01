#ifndef MYMODELTABLE_H
#define MYMODELTABLE_H

#include <qqml.h>
#include <QAbstractTableModel>
#include <QDateTime>
#include <QDebug>

struct Task
{
    int m_id_thread;
    QString m_sequence;
    int m_begin_sequence;
    QDateTime m_data;
};

class MyModelTable : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:

    enum Roles {
        ThreadRole = Qt::UserRole + 1,       // id потока
        SequenceRole,                     // Последовательность
        BeginSequenceRole,                 // Начало последовательности
        DataTimeRole                      // Время обнаружения
    };

    MyModelTable(){
        qDebug() << __PRETTY_FUNCTION__;
//        m_tasks.append({1, "123", 23, QDateTime::currentDateTime()});
        beginInsertRows(QModelIndex(), 1, 1);

        m_tasks.insert(0, {1, "QString()", 25, QDateTime::currentDateTime()});
        m_tasks.insert(1, {1, "QString()", 25, QDateTime::currentDateTime()});

        endInsertRows();
    }

    int rowCount(const QModelIndex &parent) const override {
        return parent.isValid() ? 0 : m_tasks.size();
    }
    int columnCount(const QModelIndex &parent) const override {
        return parent.isValid() ? 0 : 4;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {

        if (role != Qt::DisplayRole) {
            return QVariant();
        }

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("№ Потока");
                break;
            case 1:
                return QString("Последовательность");
                break;
            case 2:
                return QString("Начало вхождения");
                break;
            case 3:
                return QString("Время обнаружения");
                break;
            default:
                break;
            }
        }

        return QVariant();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) {
            return QVariant();
        }
        if ((!index.row()) >= m_tasks.size() || index.row() < 0) {
            return QVariant();
        }

        if (role == Qt::DisplayRole) {
            const auto &task = m_tasks.at(index.row());

            switch (index.column()) {
            case 0:
                return task.m_id_thread;
                break;
            case 1:
                return task.m_sequence;
                break;
            case 2:
                return task.m_begin_sequence;
                break;
            case 3:
                return task.m_data;
                break;
            default:
                break;
            }
        }

        return QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        if (index.isValid()) {
            const int row = index.row();
            auto task = m_tasks.value(row);
            if (role == Qt::DisplayRole) {
                switch (index.column()) {
                case 0:
                    task.m_id_thread = value.toInt();
                    break;
                case 1:
                    task.m_sequence = value.toString();
                    break;
                case 2:
                    task.m_begin_sequence = value.toInt();
                    break;
                case 3:
                    task.m_data = value.toDateTime();
                    break;
                default:
                    return false;
                }
            }

            m_tasks.replace(row, task);
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }

        return false;
    }

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override {
        Q_UNUSED(index);
        beginInsertRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row) {
            m_tasks.insert(position, {int(), QString(), int(), QDateTime()});
        }

        endInsertRows();
        return true;
    }
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override {
        Q_UNUSED(index);
        beginRemoveRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row) {
            m_tasks.removeAt(position);
        }

        endRemoveRows();
        return true;
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
            roles[ThreadRole] = "id";
            roles[SequenceRole] = "sequence";
            roles[BeginSequenceRole] = "begin_sequence";
            roles[DataTimeRole] = "dataTime";

            return roles;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (!index.isValid())
            return Qt::ItemIsEnabled;

        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

//    const QVector<Task> &getTasks() const;
private:
    QVector<Task> m_tasks;
};


class MyModelTable1 : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:
    int rowCount(const QModelIndex & = QModelIndex()) const override {
        return 200;
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override {
        return 200;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {

        qDebug() << __PRETTY_FUNCTION__;

        if (role != Qt::DisplayRole) {
            return QVariant();
        }

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("№ Потока");
                break;
            case 1:
                return QString("Последовательность");
                break;
            case 2:
                return QString("Начало вхождения");
                break;
            case 3:
                return QString("Время обнаружения");
                break;
            default:
                break;
            }
        }

        return QVariant();
    }

    QVariant data(const QModelIndex &index, int role) const override {
//        qDebug() << __PRETTY_FUNCTION__;

        switch (role) {
        case Qt::DisplayRole:
            return QString("%1, %2").arg(index.column()).arg(index.row());
        default:
            break;
        }

        return QVariant();
    }


};

#endif // MYMODELTABLE_H
