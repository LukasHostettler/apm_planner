#include "ArduPilotMegaMAV.h"
#include "chooseactiondialog.h"
#include "ui_chooseactiondialog.h"


ChooseActionDialog::ChooseActionDialog(QWidget *parent,UAS * uas) :
    QDialog(parent),
    m_uas(uas),
    ui(new Ui::ChooseActionDialog)
{
    ui->setupUi(this);
    reaction=NO_REACTION;
    remaining_seconds = 30;
    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_update()));
        timer->start(1000);
}

ChooseActionDialog::~ChooseActionDialog()
{
    delete ui;
    timer->stop();
}

void ChooseActionDialog::on_doNothingButton_clicked()
{
    reaction = NO_REACTION;
    close();
    //send action taken
}

void ChooseActionDialog::on_chuteButton_clicked()
{
    reaction = LAUNCH_PARACHUTE;
    if(m_uas)
        m_uas->setParameter(1,"AFS_TERMINATE",1);
    //send action taken
    close();
}

void ChooseActionDialog::on_rtlButton_clicked()
{
    reaction = INITATE_RTL;
    m_uas->setMode(1,ApmPlane::RTL);
    //send action taken
    close();
}

void ChooseActionDialog::on_timer_update(){
    //QLOG_INFO() << "Timer shot :D";
    this->ui->lcdNumber->display(remaining_seconds--);
    if(remaining_seconds<0){
        //send no action taken
        close();
    }
}
