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
void Tcalibration_factors_dlg::setup(std::vector<double> fact)
{
    fact_local = fact;
    ui->spinBox_degree ->setValue(fact.size()-1);
    ui->tableWidget->setColumnCount(fact.size());

    for(unsigned int col = 0 ; col < fact.size(); ++col)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem
                (tr("%1").arg(fact[col]) );
        //                (tr("%1").arg(col ));
        ui->tableWidget->setItem(0, col, newItem);

        //ui->tableWidget->setItem(0, col).
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

        double new_value = ((unsigned int) degree >= fact_local.size()   )? 0 : fact_local[degree];
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

    vector<double> f;
    for(int col = 0 ; col <= ui->spinBox_degree->value()  /* tableWidget->columnCount()*/ ; ++col )
    {
        double tmp = ui->tableWidget->item(0, col)->text().toDouble(&success);
        if(success) f.push_back(tmp);
        else {
            QMessageBox::warning
                    (0, "Wrong entry" ,
                     QString("The string \"" ) +
                     ui->tableWidget->item(0, col)->text() +
                     QString("\" can not be converted to a 'Double' number"),

                     QMessageBox::Yes | QMessageBox::Default ,  QMessageBox::NoButton );

        }
    }
    if(success) fact_local = f;
    return;
}
