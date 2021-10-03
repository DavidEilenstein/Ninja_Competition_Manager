#include "ncm_starterlist.h"
#include "ui_ncm_starterlist.h"

NCM_StarterList::NCM_StarterList(QDir competition_dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_StarterList)
{
    ui->setupUi(this);

    DIR_Competition = competition_dir;

    DIR_Competitors.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]);
    if(!DIR_Competitors.exists())
        QDir().mkdir(DIR_Competitors.path());

    init_tables();

    get_data_dialog();

    connect(&timer_autoupdate, SIGNAL(timeout()), this, SLOT(update_starter_list()));

    setWindowTitle("Starter list - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));

    int size_button = 80;
    QSize RefIconSize(size_button, size_button);
    ui->pushButton_DavidEilenstein->setIcon(QIcon(":/logo/Logo_Final.jpg"));
    ui->pushButton_DavidEilenstein->setIconSize(RefIconSize);
}

NCM_StarterList::~NCM_StarterList()
{
    delete ui;
}

void NCM_StarterList::table_dims_dialog()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    bool ok;

    int n_tables = QInputDialog::getInt(
                this,
                "Table count",
                "How many starter list tables do you want to have side by side in layout?",
                count_tables,
                1,
                99,
                1,
                &ok);
    if(!ok)
        return;

    int n_rows = QInputDialog::getInt(
                this,
                "Row count",
                "How many rows shall a table (exept the last one) have at maximum?",
                count_rows_per_table,
                1,
                99999,
                1,
                &ok);
    if(!ok)
        return;

    count_tables = n_tables;
    count_rows_per_table = n_rows;

    init_tables();
}

void NCM_StarterList::init_tables()
{
    //qDebug() << "start init_tables";

    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    //qDebug() << "clear vTables";
    for(size_t i = 0; i < vTables.size(); i++)
        delete vTables[i];
    vTables.clear();

    //qDebug() << "clear vTableWidget";
    for(size_t i = 0; i < vTableWidget.size(); i++)
        delete vTableWidget[i];
    vTableWidget.clear();

    //qDebug() << "clear horizontalLayout_StarterLists";
    if(ui->horizontalLayout_StarterLists != NULL)
    {
        QLayoutItem* item;
        while((item = ui->horizontalLayout_StarterLists->takeAt(0)) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }

    //qDebug() << "refill tables";
    vTables.resize(count_tables);
    vTableWidget.resize(count_tables);
    for(int i = 0; i < count_tables; i++)
    {
        vTableWidget[i] = new QTableWidget(this);
        ui->horizontalLayout_StarterLists->layout()->addWidget(vTableWidget[i]);

        vTables[i] = new NCM_Table;
        vTables[i]->set_TW(vTableWidget[i]);
        vTables[i]->clear_data();

        QHeaderView *verticalHeader = vTableWidget[i]->verticalHeader();
        verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
        verticalHeader->setDefaultSectionSize(20);
    }

    //qDebug() << "finish init_tables";
}

void NCM_StarterList::get_data_dialog()
{
    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory for this stage",
                DIR_Competitors.path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    DIR_CompetitorsThisStage.setPath(QS_CompetitorsLoadPath);
    if(!DIR_CompetitorsThisStage.exists())
        return;

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select stage file",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_STAGES],
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    FI_StageFile.setFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;
    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;
    QS_StageName = FI_StageFile.baseName();
    ui->label_StageName->setText(QS_StageName);

    //------------------------------- output

    DIR_Runs_Out.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_RUNS] + "/" + QS_StageName);
    if(!DIR_Runs_Out.exists())
        QDir().mkdir(DIR_Runs_Out.path());

    //------------------------------- load if everything is correct

    if(!load_competitors())
        return;

    if(!update_starter_list())
        return;

    state_data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionChose_competitors_and_stage->setEnabled(false);
    ui->actionUpdate_now->setEnabled(true);
    ui->actionUpdate_automatically->setEnabled(true);
    ui->actionChange_table_settings->setEnabled(true);

    auto_update(true);
}

bool NCM_StarterList::load_competitors()
{
    for(size_t i = 0; i < vCompetitorsAll.size(); i++)
        delete vCompetitorsAll[i];
    vCompetitorsAll.clear();

    DIR_CompetitorsThisStage.setPath(DIR_CompetitorsThisStage.path());

    vCompetitorsAll.clear();
    QFileInfoList FIL_Competitors = DIR_CompetitorsThisStage.entryInfoList();
    for(int i = 0; i < FIL_Competitors.size(); i++)
    {
        //qDebug() << "try to load" << FIL_Competitors[i].absoluteFilePath();
        if(FIL_Competitors[i].exists())
            if(FIL_Competitors[i].suffix() == "txt" || FIL_Competitors[i].suffix() == "TXT")
                if(FIL_Competitors[i].baseName().startsWith("Competitor_"))
                {
                    NCM_Competitor *competitor = new NCM_Competitor(DIR_CompetitorsThisStage);
                    if(competitor->load(FIL_Competitors[i].absoluteFilePath()))
                        vCompetitorsAll.push_back(competitor);
                    else
                        delete competitor;
                }
    }

    //qDebug() << vCompetitorsAll.size() << "competitors found";
    return true;
}

bool NCM_StarterList::load_runs()
{
    for(size_t i = 0; i < vRunsCompleted.size(); i++)
        delete vRunsCompleted[i];
    vRunsCompleted.clear();

    DIR_Runs_Out.setPath(DIR_Runs_Out.path());

    QFileInfoList FIL_Runs = DIR_Runs_Out.entryInfoList();
    for(int i = 0; i < FIL_Runs.size(); i++)
        if(FIL_Runs[i].exists())
            if(FIL_Runs[i].suffix() == "txt" || FIL_Runs[i].suffix() == "TXT")
                if(FIL_Runs[i].baseName().startsWith("Run_"))
                {
                    NCM_Run *run = new NCM_Run(DIR_Competition, QS_StageName);
                    if(run->load(FIL_Runs[i].absoluteFilePath()))
                        vRunsCompleted.push_back(run);
                    else
                        delete run;
                }

    qDebug() << vRunsCompleted.size() << "runs loaded";
    return true;
}

bool NCM_StarterList::calc_competitors_not_run_yet()
{
    QSL_CompetitorsNotRunYet.clear();
    for(size_t c = 0; c < vCompetitorsAll.size(); c++)
    {
        QString QS_NameOfCompetitor = vCompetitorsAll[c]->name();

        bool allready_run = false;
        for(size_t r = 0; r < vRunsCompleted.size() && !allready_run; r++)
            if(QS_NameOfCompetitor == vRunsCompleted[r]->name())
                allready_run = true;

        if(!allready_run)
            QSL_CompetitorsNotRunYet.append(QS_NameOfCompetitor);
    }



    //qDebug() << QSL_CompetitorsNotRunYet.size() << "competitors not run yet";
    return true;
}

bool NCM_StarterList::update_starter_list()
{
    if(state_update_running)
        return false;

    state_data_loaded = false;
    state_update_running = true;

    if(!load_competitors())
    {
        state_update_running = false;
        return false;
    }

    if(!load_runs())
    {
        state_update_running = false;
        return false;
    }

    if(!calc_competitors_not_run_yet())
    {
        state_update_running = false;
        return false;
    }

    state_data_loaded = true;

    QStringList QSL_Names_Columns = {
        "Number",
        "Name",
        "Class"};

    //row names
    //qDebug() << "row names";
    vector<QStringList> vQSL_Names_Rows(count_tables);
    for(int i = 0; i < QSL_CompetitorsNotRunYet.size(); i++)
    {
        size_t index_table = min(size_t(count_tables - 1), size_t(i / count_rows_per_table));
        vQSL_Names_Rows[index_table].append(QString::number(i));
    }

    //resize data container
    //qDebug() << "resize data container";
    vector<vector<vector<QString>>> vvvQS_Data(count_tables);
    for(int t = 0; t < count_tables; t++)
    {
        vvvQS_Data[t].resize(QSL_Names_Columns.size());
        for(size_t c = 0; c < vvvQS_Data[t].size(); c++)
        {
            vvvQS_Data[t][c].resize(vQSL_Names_Rows[t].size(), "???");
        }
    }

    //loop competitors
    //qDebug() << "loop competitors";
    for(int i = 0; i < QSL_CompetitorsNotRunYet.size(); i++)
    {
        //qDebug() << "competitor" << i;

        //target table
        size_t index_table = min(size_t(count_tables - 1), size_t(i / count_rows_per_table));
        //qDebug() << "table index" << index_table;

        //find competitor
        int competitor_index = -1;
        for(size_t c = 0; c < vCompetitorsAll.size() && competitor_index < 0; c++)
            if(QSL_CompetitorsNotRunYet[i] == vCompetitorsAll[c]->name())
                competitor_index = c;
        //qDebug() << "competitor index" << competitor_index;

        //row index
        size_t row_index = i;
        for(size_t t = 0; t < index_table; t++)
            row_index -= vQSL_Names_Rows[t].size();
        //qDebug() << "row index" << row_index;

        //write to table data
        if(competitor_index >= 0 && row_index < vvvQS_Data[index_table][0].size())
        {
            //qDebug() << "write datat to table";
            vvvQS_Data[index_table][0][row_index] = QString::number(vCompetitorsAll[competitor_index]->number());
            vvvQS_Data[index_table][1][row_index] = vCompetitorsAll[competitor_index]->name();
            vvvQS_Data[index_table][2][row_index] = vCompetitorsAll[competitor_index]->competitor_class();
        }
    }

    //write data to table
    //qDebug() << "write data to table";
    for(int t = 0; t < count_tables; t++)
        vTables[t]->set_data(
                    vvvQS_Data[t],
                    QSL_Names_Columns,
                    vQSL_Names_Rows[t],
                    false,
                    true);

    ui->label_Time->setText(QDateTime::currentDateTime().time().toString());

    state_update_running = false;
    return true;
}

void NCM_StarterList::on_actionChose_competitors_and_stage_triggered()
{
    get_data_dialog();
}

void NCM_StarterList::on_actionUpdate_now_triggered()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    update_starter_list();
}

void NCM_StarterList::auto_update(bool activate)
{
    if(activate)
    {
        bool ok;
        double time_s = QInputDialog::getDouble(
                    this,
                    "Autoupdate interval",
                    "Please select the interval for autoupdateing starterlist in seconds.",
                    1,
                    0.1,
                    300,
                    2,
                    &ok);
        if(!ok)
            return;

        timer_autoupdate.start(int(time_s * 1000));
    }
    else

    {
        timer_autoupdate.stop();
    }

    ui->actionUpdate_now->setEnabled(!activate);
}

void NCM_StarterList::on_actionUpdate_automatically_triggered(bool checked)
{
    auto_update(checked);
}

void NCM_StarterList::on_actionChange_table_settings_triggered()
{
    table_dims_dialog();
    update_starter_list();
}

void NCM_StarterList::on_pushButton_DavidEilenstein_clicked()
{
    QDesktopServices::openUrl(QUrl("www.instagram.com/davideilenstein"));
}
