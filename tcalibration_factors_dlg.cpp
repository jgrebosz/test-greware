#include "tcalibration_factors_dlg.h"
#include "ui_tcalibration_factors_dlg.h"

#include <QMessageBox>
#include <iostream>
using namespace std;

//********************************************************************
Tcalibration_factors_dlg::Tcalibration_factors_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tcalibration_factors_dlg)
{
    ui->setupUi(this);
}
//********************************************************************
Tcalibration_factors_dlg::~Tcalibration_factors_dlg()
{
    delete ui;
}
//********************************************************************
void Tcalibration_factors_dlg::setup(Tfile_line_det_cal_lookup line)
{
    line_local = line;

    ui->label_data_track->setText(("The signals from the data track: <span style=\" color:#b20000;\">"
                                  + line_local.channel +
                                  "</span><br/>will be assigned to the detector called: ").c_str() );

    ui->LineEdit_det_name->setText(line.name_of_detector.c_str());
    ui->doubleSpinBox_phi->setValue(line.phi);
    ui->doubleSpinBox_theta->setValue(line.theta);
    ui->spinBox_compton->setValue(line.compton_thresh);

    int degree = line.calib_factors.size()-1;

    ui->spinBox_degree ->setValue(degree);
    ui->tableWidget->setColumnCount(degree+1);

    for(unsigned int col = 0 ; col < line.calib_factors.size(); ++col)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem
                (tr("%1").arg(line.calib_factors[col]) );
        ui->tableWidget->setItem(0, col, newItem);     
    }
}
//***********************************************************************
void Tcalibration_factors_dlg::on_spinBox_degree_valueChanged(int degree)
{
    //cout << "arg1 = " << degree << endl;
    // so we have to change the nr of columns
    int old_degree = ui->tableWidget->columnCount()-1;

    ui->tableWidget->setColumnCount( degree+1);

    //    if previously was more - no problem
    if(degree > old_degree)
    {
        // if it is bigger - we need new items
        // adding items
        cout << "adding column" << endl;

        //        QTableWidgetItem *newItem = new QTableWidgetItem
        //                (tr("%1").arg(4.44) );
        //        ui->tableWidget->setItem(0, arg1-1, newItem);

        double new_value = ((unsigned int) degree >= line_local.calib_factors.size()   )? 0 : line_local.calib_factors[degree];
        ui->tableWidget->setItem(0, degree,
                                 new QTableWidgetItem (tr("%1").arg(new_value) )) ;

        // add title of the column
        QStringList labels;
        for(int i = 0 ; i<= degree ; ++i) labels+= ("a" + to_string(i)).c_str();
        ui->tableWidget->setHorizontalHeaderLabels (labels );
    }
    else{

    }
}
//********************************************************************************************
void Tcalibration_factors_dlg::on_tableWidget_cellChanged(int row, int column)
{

    bool success = false;
    double val = ui->tableWidget->item(row, column)->text().toDouble(&success);

    if(success)
    {
        cout << "tvalue = " << val << endl;
    }
    else
    {
        // cant open file warning
        QMessageBox::warning
                (0, "Wrong entry" ,
                 QString("The string \"" ) +
                 ui->tableWidget->item(row, column)->text() +
                 QString("\" can not be converted to a 'Double' number"),

                 QMessageBox::Yes | QMessageBox::Default ,  QMessageBox::NoButton );
    }

}
//********************************************************************************************
void Tcalibration_factors_dlg::on_buttonBox_accepted()
{
    // read all table into fact_local

    bool success = true;

    Tfile_line_det_cal_lookup f;

    f.channel = line_local.channel;
    f.name_of_detector = ui->LineEdit_det_name->text().toStdString();
    f.compton_thresh = ui->spinBox_compton ->value();
    f.theta = ui->doubleSpinBox_theta->value();
    f.phi = ui->doubleSpinBox_phi->value();
    f.cal_order = ui->spinBox_degree->value();

    for(int col = 0 ; col <= ui->spinBox_degree->value()  /* tableWidget->columnCount()*/ ; ++col )
    {
        double tmp = ui->tableWidget->item(0, col)->text().toDouble(&success);
        if(success) f.calib_factors.push_back(tmp);
        else {
            QMessageBox::warning
                    (0, "Wrong entry" ,
                     QString("The string \"" ) +
                     ui->tableWidget->item(0, col)->text() +
                     QString("\" can not be converted to a 'Double' number"),

                     QMessageBox::Yes | QMessageBox::Default ,  QMessageBox::NoButton );

        }
    }
    if(success) line_local = f;
    return;
}
