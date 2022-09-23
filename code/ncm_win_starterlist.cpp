#include "ncm_win_starterlist.h"
#include "ui_ncm_win_starterlist.h"

NCM_WIN_StarterList::NCM_WIN_StarterList(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_StarterList)
{
    ui->setupUi(this);
    Table.set_layout(ui->gridLayout_StarterList);

    Competition = comp;
    get_data();

    connect(&TimerAutoupdate, SIGNAL(timeout()), this, SLOT(update()));
    TimerAutoupdate.start(1000);

    setWindowTitle("Starter List - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));

    int size_button = 80;
    QSize RefIconSize(size_button, size_button);
    ui->pushButton_DE->setIcon(QIcon(":/img/Logo_Final.jpg"));
    ui->pushButton_DE->setIconSize(RefIconSize);
}

NCM_WIN_StarterList::~NCM_WIN_StarterList()
{
    delete ui;
}

void NCM_WIN_StarterList::get_data()
{
    if(data_loaded)
        return;

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory",
                Competition.dir(COMP_DIR_COMPETITORS).path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    QDir DIR_Competitors(QS_CompetitorsLoadPath);
    if(!DIR_Competitors.exists())
        return;

    Competitors_All.set_dir(DIR_Competitors);

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select stage file",
                Competition.dir(COMP_DIR_STAGES).path(),
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    QFileInfo FI_StageFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;

    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;

    Stage.set_file(FI_StageFile);
    Stage.load();
    ui->label_Name->setText(Stage.name());

    //------------------------------- runs

    QDir DIR_Runs(Competition.dir(COMP_DIR_RUNS).path() + "/" + Stage.name());

    if(!DIR_Runs.exists())
        QDir().mkdir(DIR_Runs.path());
    if(!DIR_Runs.exists())
        return;

    Runs.set_dir(DIR_Runs);

    //------------------------------- load if everything is correct

    load_competitors();
    load_runs();
    calc_competitors_allowed();

    data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionget_data->setEnabled(false);
}

void NCM_WIN_StarterList::table_dims_dialog()
{
    //wait for update to finish
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    bool ok;

    int n_tables = QInputDialog::getInt(
                this,
                "Table count",
                "How many starter list tables do you want to have side by side in layout?",
                Table.count_tables(),
                1,
                10,
                1,
                &ok);
    if(!ok)
        return;

    int n_rows = QInputDialog::getInt(
                this,
                "Row count",
                "How many rows shall a table (exept the last one) have at maximum?",
                Table.count_rowsPerTable(),
                1,
                1000,
                1,
                &ok);
    if(!ok)
        return;

    Table.set_table_count(n_tables);
    Table.set_table_rows(n_rows);
}

void NCM_WIN_StarterList::load_competitors()
{
    Competitors_All.load();
}

void NCM_WIN_StarterList::load_runs()
{
    Runs.load();
}

void NCM_WIN_StarterList::calc_competitors_allowed()
{
    Competitors_Allowed = Competitors_All.subtract(Runs.competitors_list());
}

void NCM_WIN_StarterList::update()
{
    if(!data_loaded)
        return;

    if(update_running)
        return;

    update_running = true;

    //load stuff
    load_competitors();
    load_runs();
    calc_competitors_allowed();

    //update time
    ui->label_Time->setText(QDateTime::currentDateTime().time().toString());

    //stage end time
    if(Runs.size() >= 3)
    {
        QTime start_time = Runs.run_latest().recorded().addMSecs(Runs.average_time_start_to_start_ms() * (Competitors_Allowed.size() + 1)).time();
        QString QS_EndTime;

        if(start_time.hour() < 10)
            QS_EndTime.append("0");
        QS_EndTime.append(QString::number(start_time.hour()));

        QS_EndTime.append(":");

        if(start_time.minute() < 10)
            QS_EndTime.append("0");
        QS_EndTime.append(QString::number(start_time.minute()));

        ui->label_End->setText(QS_EndTime);
    }
    else
    {
        ui->label_End->setText("please wait");
    }

    //data
    size_t n_cols = COL_NUMBER_OF;
    size_t n_rows = Competitors_Allowed.size();
    vector<vector<QString>> vvQS_TableContent_c_r(n_cols, vector<QString>(n_rows, "..."));

    //loop competitors
    for(size_t r = 0; r < n_rows; r++)
    {
        //competitor
        NCM_OBJ_Competitor competitor = Competitors_Allowed.get_competitor(r);

        //competitor info
        vvQS_TableContent_c_r[COL_NAME][r]   = competitor.name();
        vvQS_TableContent_c_r[COL_NUMBER][r] = QString::number(competitor.number());
        vvQS_TableContent_c_r[COL_CLASS][r]  = competitor.competitor_class_symbol();

        //estimate start time
        if(Runs.size() >= 3)
        {
            QTime start_time = Runs.run_latest().recorded().addMSecs(Runs.average_time_start_to_start_ms() * (r + 1)).time();
            QString QS_StartTime;

            if(start_time.hour() < 10)
                QS_StartTime.append("0");
            QS_StartTime.append(QString::number(start_time.hour()));

            QS_StartTime.append(":");

            if(start_time.minute() < 10)
                QS_StartTime.append("0");
            QS_StartTime.append(QString::number(start_time.minute()));

            vvQS_TableContent_c_r[COL_EST_TIME][r] = QS_StartTime;
        }
        else
        {
            vvQS_TableContent_c_r[COL_EST_TIME][r] = "please wait";
        }
    }

    //row names
    QStringList QSL_NamesRows;
    for(size_t r = 0; r < n_rows; r++)
        QSL_NamesRows.append(QString::number(r + 1));

    //set table data
    Table.set_data(vvQS_TableContent_c_r, QSL_NamesColumns, QSL_NamesRows, true, true);

    update_running = false;
}

void NCM_WIN_StarterList::update_auto(bool activate)
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
        {
            ui->actionAutoupdate->setChecked(false);
            return;
        }

        TimerAutoupdate.start(int(time_s * 1000));
    }
    else
    {
        TimerAutoupdate.stop();
    }

    ui->actionUpdate->setEnabled(!activate);
}

void NCM_WIN_StarterList::on_actionget_data_triggered()
{
    get_data();
}

void NCM_WIN_StarterList::on_actionreload_competitors_and_runs_triggered()
{
    load_competitors();
    load_runs();
    calc_competitors_allowed();
}



void NCM_WIN_StarterList::on_actionUpdate_triggered()
{
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    update();
}

void NCM_WIN_StarterList::on_actionAutoupdate_triggered(bool checked)
{
    update_auto(checked);
}

void NCM_WIN_StarterList::on_actionChange_Table_Settings_triggered()
{
    table_dims_dialog();
}
