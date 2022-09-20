#ifndef NCM_TABLE_H
#define NCM_TABLE_H

//general
#include <iostream>
#include <vector>
#include <fstream>

//Qt
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileInfo>
#include <QFileDialog>

//namespaces
using namespace std;

class NCM_Table : public QWidget
{
    Q_OBJECT
public:
    explicit NCM_Table(QWidget *parent = nullptr);

    //setter
    void            set_TW(QTableWidget *TW);
    void            set_data(vector<vector<QString>> vv_data, QStringList column_names, QStringList row_names, bool autosize_rows, bool autosize_cols);

    void            clear_data();

private:
    bool            TW_is_set = false;
    QTableWidget    *TW_table;
};

#endif // NCM_TABLE_H
