#include "ncm_wid_table.h"

NCM_WID_Table::NCM_WID_Table()
{

}

void NCM_WID_Table::set_TW(QTableWidget *TW)
{
    TW_table = TW;
    TW_is_set = true;
    clear_data();
}

void NCM_WID_Table::set_data(vector<vector<QString> > vv_data_c_r, QStringList col_names, QStringList row_names, bool autosize_rows, bool autosize_cols)
{
    clear_data();

    if(!TW_is_set)                                                  return;

    if(vv_data_c_r.empty())                                         return;
    if(vv_data_c_r[0].empty())                                      return;
    if(col_names.empty())                                           return;

    if(vv_data_c_r.size() != size_t(col_names.size()))              return;
    for(size_t col = 0; col < vv_data_c_r.size(); col++)
        if(vv_data_c_r[col].size() != size_t(row_names.size()))     return;

    //Columns (1st index)
    TW_table->setColumnCount(col_names.size());
    TW_table->setHorizontalHeaderLabels(col_names);

    //Rows (2nd index)
    TW_table->setRowCount(row_names.size());
    TW_table->setVerticalHeaderLabels(row_names);

    //Data
    for(size_t row = 0; row < vv_data_c_r[0].size(); row++)
    {
        QColor color;
        bool color_indicator_found = false;
        for(size_t col = 0; col < vv_data_c_r.size() && !color_indicator_found; col++)
        {
            if(vv_data_c_r[col][row].contains("♀"))
            {
                color = QColor(128, 0, 0);
                color_indicator_found = true;
            }
            if(vv_data_c_r[col][row].contains("♂"))
            {
                color = QColor(0, 0, 128);
                color_indicator_found = true;
            }
        }

        for(size_t col = 0; col < vv_data_c_r.size(); col++)
        {
            TW_table->setItem(int(row), int(col), new QTableWidgetItem(vv_data_c_r[col][row]));
            TW_table->item(row, col)->setTextColor(color);
        }
    }

    if(autosize_rows)
        TW_table->resizeRowsToContents();
    if(autosize_cols)
        TW_table->resizeColumnsToContents();
}

void NCM_WID_Table::clear_data()
{
    TW_table->setColumnCount(1);
    TW_table->setRowCount(1);
    TW_table->setItem(0, 0, new QTableWidgetItem(""));
    TW_table->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    TW_table->setVerticalHeaderItem(0, new QTableWidgetItem(""));
}


