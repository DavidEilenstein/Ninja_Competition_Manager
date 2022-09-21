#ifndef NCM_WID_TABLE_H
#define NCM_WID_TABLE_H

//Qt
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QDateEdit>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>

//namespaces
using namespace std;

class NCM_WID_Table
{
public:
    NCM_WID_Table();

    void set_TW(QTableWidget *TW);
    void set_data(vector<vector<QString>> vv_data, QStringList column_names, QStringList row_names, bool autosize_rows, bool autosize_cols);

    void clear_data();

private:

    bool            TW_is_set = false;
    QTableWidget    *TW_table;
};

#endif // NCM_WID_TABLE_H
