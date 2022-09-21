#include "ncm_wid_table_multi.h"

NCM_WID_Table_Multi::NCM_WID_Table_Multi()
{

}

NCM_WID_Table_Multi::NCM_WID_Table_Multi(QGridLayout *layout)
{
    set_layout(layout);
}

void NCM_WID_Table_Multi::set_table_count(size_t nt)
{
    if(!layout_set)
        return;

    delete_tables();

    count_tables = nt;
    vpTables.resize(count_tables);
    vpTableWidget.resize(count_tables);

    for(size_t i = 0; i < count_tables; i++)
    {
        vpTableWidget[i] = new QTableWidget();
        pLayout->layout()->addWidget(vpTableWidget[i]);

        vpTables[i] = new NCM_WID_Table;
        vpTables[i]->set_TW(vpTableWidget[i]);
        vpTables[i]->clear_data();

        QHeaderView *verticalHeader = vpTableWidget[i]->verticalHeader();
        verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
        verticalHeader->setDefaultSectionSize(20);
    }
}

void NCM_WID_Table_Multi::set_table_rows(size_t nr)
{
    if(!layout_set)
        return;

    count_rows_per_table = nr;
    clear_data();
}

void NCM_WID_Table_Multi::delete_tables()
{
    if(!layout_set)
        return;

    //tables
    for(size_t i = 0; i < vpTables.size(); i++)
        delete vpTables[i];
    vpTables.clear();

    //tables widgets
    for(size_t i = 0; i < vpTableWidget.size(); i++)
        delete vpTableWidget[i];
    vpTableWidget.clear();

    //layout
    if(pLayout != NULL)
    {
        QLayoutItem* item;
        while((item = pLayout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
    }
}

void NCM_WID_Table_Multi::set_data(vector<vector<QString>> vv_data_cols_rows, QStringList column_names, QStringList row_names, bool autosize_rows, bool autosize_cols)
{
    if(!layout_set)
        return;

    clear_data();

    //errors
    if(vv_data_cols_rows.empty())                                       return;
    if(vv_data_cols_rows[0].empty())                                    return;
    if(column_names.empty())                                            return;
    if(vv_data_cols_rows.size() != size_t(column_names.size()))         return;
    for(size_t col = 0; col < vv_data_cols_rows.size(); col++)
        if(vv_data_cols_rows[col].size() != size_t(row_names.size()))   return;

    size_t n_cols = vv_data_cols_rows.size();
    size_t n_rows = vv_data_cols_rows[0].size();

    //tablewise containers
    vector<vector<vector<QString>>> vvv_data_table_cols_rows(count_tables, vector<vector<QString>>(n_cols));
    vector<QStringList> vQSL_row_names(count_tables);

    //loop rows
    for(size_t r = 0; r < n_rows; r++)
    {
        //calc table index
        size_t t = min(size_t(count_tables - 1), size_t(r / count_rows_per_table));

        //loop cols
        for(size_t c = 0; c < n_cols; c++)
        {
            //append row content to new container
            vvv_data_table_cols_rows[t][c].push_back(vv_data_cols_rows[c][r]);
            vQSL_row_names[t].append(row_names[r]);
        }
    }

    //distribute data to tables
    for(size_t t = 0; t < count_tables; t++)
    {
        set_data(vvv_data_table_cols_rows[t], column_names, vQSL_row_names[t], autosize_rows, autosize_cols);
    }
}

void NCM_WID_Table_Multi::clear_data()
{
    for(size_t i = 0; i < vpTables.size(); i++)
        vpTables[i]->clear_data();
}
