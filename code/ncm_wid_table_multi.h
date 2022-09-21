#ifndef NCM_WID_TABLE_MULTI_H
#define NCM_WID_TABLE_MULTI_H

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
#include <QGridLayout>
#include <QHeaderView>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>
#include <ncm_wid_table.h>

//namespaces
using namespace std;

class NCM_WID_Table_Multi
{
public:
    NCM_WID_Table_Multi();
    NCM_WID_Table_Multi(QGridLayout* layout);

    void set_layout(QGridLayout* layout)        {if(!layout_set && layout != nullptr) {pLayout = layout; layout_set = true;}}
    void set_table_count(size_t nt);
    void set_table_rows(size_t nr);
    void delete_tables();

    void set_data(vector<vector<QString>> vv_data_cols_rows, QStringList column_names, QStringList row_names, bool autosize_rows, bool autosize_cols);
    void clear_data();



private:

    QGridLayout* pLayout;

    size_t count_tables = 1;
    size_t count_rows_per_table = 30;

    vector<QTableWidget*> vpTableWidget;
    vector<NCM_WID_Table*> vpTables;

    bool layout_set = false;
};

#endif // NCM_WID_TABLE_MULTI_H
