#include "ncm_wid_table_multi.h"

NCM_WID_Table_Multi::NCM_WID_Table_Multi()
{

}

NCM_WID_Table_Multi::NCM_WID_Table_Multi(QGridLayout *layout)
{
    set_layout(layout);    
}

void NCM_WID_Table_Multi::set_layout(QGridLayout *layout)
{
    if(layout_set)
        return;

    if(layout == nullptr)
        return;

    pLayout = layout;
    layout_set = true;
    set_table_count(2);
}

void NCM_WID_Table_Multi::set_table_count(size_t nt)
{
    if(!layout_set)
        return;

    delete_tables();

    CountTables = nt;
    vpTables.resize(CountTables);
    vpTableWidget.resize(CountTables);

    for(size_t i = 0; i < CountTables; i++)
    {
        vpTableWidget[i] = new QTableWidget();
        pLayout->addWidget(vpTableWidget[i], 0, i);

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

    CountRowsPerTable = nr;
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
    //qDebug() << "NCM_WID_Table_Multi::set_data" << "start XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

    //qDebug() << "NCM_WID_Table_Multi::set_data" << "check layout";
    if(!layout_set)
        return;

    //qDebug() << "NCM_WID_Table_Multi::set_data" << "check table count";
    if(CountTables == 0)
        return;

    clear_data();

    //errors
    //qDebug() << "NCM_WID_Table_Multi::set_data" << "check empty";
    if(vv_data_cols_rows.empty())                                       return;
    if(vv_data_cols_rows[0].empty())                                    return;
    if(column_names.empty())                                            return;
    //qDebug() << "NCM_WID_Table_Multi::set_data" << "check size fit";
    if(vv_data_cols_rows.size() != size_t(column_names.size()))         return;
    for(size_t col = 0; col < vv_data_cols_rows.size(); col++)
        if(vv_data_cols_rows[col].size() != size_t(row_names.size()))   return;

    //qDebug() << "NCM_WID_Table_Multi::set_data" << "errors passed";

    size_t n_cols = vv_data_cols_rows.size();
    size_t n_rows = vv_data_cols_rows[0].size();
    //qDebug() << "NCM_WID_Table_Multi::set_data" << "count row" << n_rows;
    //qDebug() << "NCM_WID_Table_Multi::set_data" << "count col" << n_cols;

    //tablewise containers
    vector<vector<vector<QString>>> vvv_data_table_cols_rows(CountTables, vector<vector<QString>>(n_cols));
    vector<QStringList> vQSL_row_names(CountTables);

    //loop rows
    for(size_t r = 0; r < n_rows; r++)
    {
        //calc table index
        size_t t = min(size_t(CountTables - 1), size_t(r / CountRowsPerTable));

        //row names
        vQSL_row_names[t].append(row_names[r]);

        //loop cols
        for(size_t c = 0; c < n_cols; c++)
        {
            //append row content to new container
            vvv_data_table_cols_rows[t][c].push_back(vv_data_cols_rows[c][r]);
        }
    }

    //distribute data to tables
    for(size_t t = 0; t < CountTables; t++)
    {
        vpTables[t]->set_data(vvv_data_table_cols_rows[t], column_names, vQSL_row_names[t], autosize_rows, autosize_cols);
    }
}

void NCM_WID_Table_Multi::clear_data()
{
    for(size_t i = 0; i < vpTables.size(); i++)
        vpTables[i]->clear_data();
}
