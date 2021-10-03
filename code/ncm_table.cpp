#include "ncm_table.h"

NCM_Table::NCM_Table(QWidget *parent) : QWidget(parent)
{

}

void NCM_Table::set_TW(QTableWidget *TW)
{
    TW_table = TW;
    TW_is_set = true;
    clear_data();
}

void NCM_Table::set_data(vector<vector<QString> > vv_data, QStringList column_names, QStringList row_names, bool autosize_rows, bool autosize_cols)
{
    clear_data();

    //errors
    if(!TW_is_set)                                              return;
    if(vv_data.empty())                                         return;
    if(vv_data[0].empty())                                      return;
    if(column_names.empty())                                    return;
    if(vv_data.size() != size_t(column_names.size()))           return;
    for(size_t col = 0; col < vv_data.size(); col++)
        if(vv_data[col].size() != size_t(row_names.size()))     return;

    //Columns (1st index)
    TW_table->setColumnCount(column_names.size());
    TW_table->setHorizontalHeaderLabels(column_names);

    //Rows (2nd index)
    TW_table->setRowCount(row_names.size());
    TW_table->setVerticalHeaderLabels(row_names);

    //Data
    for(size_t col = 0; col < vv_data.size(); col++)
        for(size_t row = 0; row < vv_data[col].size(); row++)
            TW_table->setItem(int(row), int(col), new QTableWidgetItem(vv_data[col][row]));

    if(autosize_rows)
        TW_table->resizeRowsToContents();
    if(autosize_cols)
        TW_table->resizeColumnsToContents();
}

void NCM_Table::clear_data()
{
    TW_table->setColumnCount(1);
    TW_table->setRowCount(1);
    TW_table->setItem(0, 0, new QTableWidgetItem(""));
    TW_table->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    TW_table->setVerticalHeaderItem(0, new QTableWidgetItem(""));
}

