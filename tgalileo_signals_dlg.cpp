#include "tgalileo_signals_dlg.h"
#include "ui_tgalileo_signals_dlg.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "tcalibration_factors_dlg.h"

using namespace std;
//************************************************************************************8
TGalileo_signals_dlg::TGalileo_signals_dlg(vector<Tfile_line_det_cal_lookup> &fline_, QWidget *parent) :
    QDialog(parent),
    fline(fline_),
    ui(new Ui::TGalileo_signals_dlg)
{
    ui->setupUi(this);

    pushButtons.push_back( ui->pushButton_00);
    pushButtons.push_back( ui->pushButton_01);
    pushButtons.push_back( ui->pushButton_02);
    pushButtons.push_back( ui->pushButton_03);
    pushButtons.push_back( ui->pushButton_04);
    pushButtons.push_back( ui->pushButton_05);
    pushButtons.push_back( ui->pushButton_06);
    pushButtons.push_back( ui->pushButton_07);
    pushButtons.push_back( ui->pushButton_08);
    pushButtons.push_back( ui->pushButton_09);

    pushButtons.push_back( ui->pushButton_10);
    pushButtons.push_back( ui->pushButton_11);
    pushButtons.push_back( ui->pushButton_12);
    pushButtons.push_back( ui->pushButton_13);
    pushButtons.push_back( ui->pushButton_14);
    pushButtons.push_back( ui->pushButton_15);
    pushButtons.push_back( ui->pushButton_16);
    pushButtons.push_back( ui->pushButton_17);
    pushButtons.push_back( ui->pushButton_18);
    pushButtons.push_back( ui->pushButton_19);

    pushButtons.push_back( ui->pushButton_20);
    pushButtons.push_back( ui->pushButton_21);
    pushButtons.push_back( ui->pushButton_22);
    pushButtons.push_back( ui->pushButton_23);
    pushButtons.push_back( ui->pushButton_24);
    pushButtons.push_back( ui->pushButton_25);
    pushButtons.push_back( ui->pushButton_26);
    pushButtons.push_back( ui->pushButton_27);
    pushButtons.push_back( ui->pushButton_28);
    pushButtons.push_back( ui->pushButton_29);

    pushButtons.push_back( ui->pushButton_30);
    pushButtons.push_back( ui->pushButton_31);

    // label

    labels.push_back( ui->label_00);
    labels.push_back( ui->label_01);
    labels.push_back( ui->label_02);
    labels.push_back( ui->label_03);
    labels.push_back( ui->label_04);
    labels.push_back( ui->label_05);
    labels.push_back( ui->label_06);
    labels.push_back( ui->label_07);
    labels.push_back( ui->label_08);
    labels.push_back( ui->label_09);

    labels.push_back( ui->label_10);
    labels.push_back( ui->label_11);
    labels.push_back( ui->label_12);
    labels.push_back( ui->label_13);
    labels.push_back( ui->label_14);
    labels.push_back( ui->label_15);
    labels.push_back( ui->label_16);
    labels.push_back( ui->label_17);
    labels.push_back( ui->label_18);
    labels.push_back( ui->label_19);

    labels.push_back( ui->label_20);
    labels.push_back( ui->label_21);
    labels.push_back( ui->label_22);
    labels.push_back( ui->label_23);
    labels.push_back( ui->label_24);
    labels.push_back( ui->label_25);
    labels.push_back( ui->label_26);
    labels.push_back( ui->label_27);
    labels.push_back( ui->label_28);
    labels.push_back( ui->label_29);

    labels.push_back( ui->label_30);
    labels.push_back( ui->label_31);




    specnames.push_back( ui->label_spec_NAME_00);
    specnames.push_back( ui->label_spec_NAME_01);
    specnames.push_back( ui->label_spec_NAME_02);
    specnames.push_back( ui->label_spec_NAME_03);
    specnames.push_back( ui->label_spec_NAME_04);
    specnames.push_back( ui->label_spec_NAME_05);
    specnames.push_back( ui->label_spec_NAME_06);
    specnames.push_back( ui->label_spec_NAME_07);
    specnames.push_back( ui->label_spec_NAME_08);
    specnames.push_back( ui->label_spec_NAME_09);

    specnames.push_back( ui->label_spec_NAME_10);
    specnames.push_back( ui->label_spec_NAME_11);
    specnames.push_back( ui->label_spec_NAME_12);
    specnames.push_back( ui->label_spec_NAME_13);
    specnames.push_back( ui->label_spec_NAME_14);
    specnames.push_back( ui->label_spec_NAME_15);
    specnames.push_back( ui->label_spec_NAME_16);
    specnames.push_back( ui->label_spec_NAME_17);
    specnames.push_back( ui->label_spec_NAME_18);
    specnames.push_back( ui->label_spec_NAME_19);

    specnames.push_back( ui->label_spec_NAME_20);
    specnames.push_back( ui->label_spec_NAME_21);
    specnames.push_back( ui->label_spec_NAME_22);
    specnames.push_back( ui->label_spec_NAME_23);
    specnames.push_back( ui->label_spec_NAME_24);
    specnames.push_back( ui->label_spec_NAME_25);
    specnames.push_back( ui->label_spec_NAME_26);
    specnames.push_back( ui->label_spec_NAME_27);
    specnames.push_back( ui->label_spec_NAME_28);
    specnames.push_back( ui->label_spec_NAME_29);

    specnames.push_back( ui->label_spec_NAME_30);
    specnames.push_back( ui->label_spec_NAME_31);


    radios.push_back( ui->CheckBox_00);
    radios.push_back( ui->CheckBox_01);
    radios.push_back( ui->CheckBox_02);
    radios.push_back( ui->CheckBox_03);
    radios.push_back( ui->CheckBox_04);
    radios.push_back( ui->CheckBox_05);
    radios.push_back( ui->CheckBox_06);
    radios.push_back( ui->CheckBox_07);
    radios.push_back( ui->CheckBox_08);
    radios.push_back( ui->CheckBox_09);

    radios.push_back( ui->CheckBox_10);
    radios.push_back( ui->CheckBox_11);
    radios.push_back( ui->CheckBox_12);
    radios.push_back( ui->CheckBox_13);
    radios.push_back( ui->CheckBox_14);
    radios.push_back( ui->CheckBox_15);
    radios.push_back( ui->CheckBox_16);
    radios.push_back( ui->CheckBox_17);
    radios.push_back( ui->CheckBox_18);
    radios.push_back( ui->CheckBox_19);

    radios.push_back( ui->CheckBox_20);
    radios.push_back( ui->CheckBox_21);
    radios.push_back( ui->CheckBox_22);
    radios.push_back( ui->CheckBox_23);
    radios.push_back( ui->CheckBox_24);
    radios.push_back( ui->CheckBox_25);
    radios.push_back( ui->CheckBox_26);
    radios.push_back( ui->CheckBox_27);
    radios.push_back( ui->CheckBox_28);
    radios.push_back( ui->CheckBox_29);

    radios.push_back( ui->CheckBox_30);
    radios.push_back( ui->CheckBox_31);
    for(auto r : radios)
    {
        r->setChecked(true);

    }

}
//***************************************************************
TGalileo_signals_dlg::~TGalileo_signals_dlg()
{
    delete ui;
}
//***************************************************************
void TGalileo_signals_dlg::update()
{

    for(int i = 0 ; i < 32 ; ++i)
    {
        //        ostringstream s;
        //        s << "etykieta_" << setfill('0') << setw(2) << i ;
        //        string nr =  s.str();

        //        labels[i]->setText(nr.c_str() );

        if(radios[i]->isChecked()  )
        {
            specnames[i]-> setStyleSheet("background-color: rgb(0, 128, 0);\n color: rgb(255, 255, 255);");
            radios[i]->setText("On");
            pushButtons[i]->setEnabled(true);
        }
        else {
            specnames[i]-> setStyleSheet("background-color: rgb(170, 170, 170);\n color: rgb(190, 190, 190);");
            radios[i]->setText("Off");
            pushButtons[i]->setEnabled(false);
        }

    }

    //this->adjustSize();
}


//**********************************************************************************
void TGalileo_signals_dlg::setup(string title, string kolory,
                                 vector<string> widma)
{


    ui->labe_title->setText(title.c_str() );  // "Galileo detectors signals");
    ui->labe_title-> setStyleSheet(kolory.c_str()); // "color: rgb(0, 255, 234);\nbackground-color: rgb(0, 17, 255);");


    //    int max_width {200} ;
    //    QRect r;
    for(int i = 0 ; i < 32 ; ++i)
    {
        labels[i]->setText( (fline[i].channel + "  " + fline[i].name_of_detector).c_str() );
        //        labels[i]->adjustSize();
        enables.push_back(fline[i].enable);


//        specnames[i]->setText(widma[i].c_str() );


        cal_factors.push_back(fline[i].calib_factors);

    }
    int i = 0 ;
    for(auto sn: widma)
    {
        specnames[i++]->setText(sn.c_str() );
    }
    //cout << "enab size = " << enables_.size() << endl;

    for(unsigned int i = 0 ; i < enables.size() ; ++i)
    {
        radios[i]->setChecked(enables[i]);
        //cout << "radio " << i << " is " << enables_[i] << endl;
    }

    update();
    //adjustSize();
}
//**********************************************************************************
void TGalileo_signals_dlg::on_CheckBox_00_clicked()
{     update(); }
void TGalileo_signals_dlg::on_CheckBox_01_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_02_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_03_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_04_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_05_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_06_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_07_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_08_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_09_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_10_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_11_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_12_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_13_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_14_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_15_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_16_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_17_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_18_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_19_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_20_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_21_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_22_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_23_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_24_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_25_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_26_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_27_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_28_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_29_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_30_clicked()
{    update(); }
void TGalileo_signals_dlg::on_CheckBox_31_clicked()
{    update(); }

void TGalileo_signals_dlg::on_pushButton_00_clicked()
{
    edit_calib_factors(0);
}

void TGalileo_signals_dlg::on_pushButton_01_clicked()
{
    edit_calib_factors(1);

}

void TGalileo_signals_dlg::on_pushButton_02_clicked()
{
    edit_calib_factors(2);

}

void TGalileo_signals_dlg::on_pushButton_03_clicked()
{
    edit_calib_factors(3);

}

void TGalileo_signals_dlg::on_pushButton_04_clicked()
{
    edit_calib_factors(4);

}

void TGalileo_signals_dlg::on_pushButton_05_clicked()
{
    edit_calib_factors(5);

}

void TGalileo_signals_dlg::on_pushButton_06_clicked()
{
    edit_calib_factors(6);

}

void TGalileo_signals_dlg::on_pushButton_07_clicked()
{
    edit_calib_factors(7);

}

void TGalileo_signals_dlg::on_pushButton_08_clicked()
{
    edit_calib_factors(8);


}

void TGalileo_signals_dlg::on_pushButton_09_clicked()
{
    edit_calib_factors(9);

}

void TGalileo_signals_dlg::on_pushButton_10_clicked()
{
    edit_calib_factors(10);

}

void TGalileo_signals_dlg::on_pushButton_11_clicked()
{
    edit_calib_factors(11);

}

void TGalileo_signals_dlg::on_pushButton_12_clicked()
{
    edit_calib_factors(12);

}

void TGalileo_signals_dlg::on_pushButton_13_clicked()
{
    edit_calib_factors(13);

}

void TGalileo_signals_dlg::on_pushButton_14_clicked()
{
    edit_calib_factors(14);

}

void TGalileo_signals_dlg::on_pushButton_15_clicked()
{
    edit_calib_factors(15);

}

void TGalileo_signals_dlg::on_pushButton_16_clicked()
{
    edit_calib_factors(16);

}

void TGalileo_signals_dlg::on_pushButton_17_clicked()
{
    edit_calib_factors(17);

}

void TGalileo_signals_dlg::on_pushButton_18_clicked()
{
    edit_calib_factors(18);

}

void TGalileo_signals_dlg::on_pushButton_19_clicked()
{
    edit_calib_factors(19);

}

void TGalileo_signals_dlg::on_pushButton_20_clicked()
{
    edit_calib_factors(20);

}

void TGalileo_signals_dlg::on_pushButton_21_clicked()
{
    edit_calib_factors(21);

}

void TGalileo_signals_dlg::on_pushButton_22_clicked()
{
    edit_calib_factors(22);

}

void TGalileo_signals_dlg::on_pushButton_23_clicked()
{
    edit_calib_factors(23);

}

void TGalileo_signals_dlg::on_pushButton_24_clicked()
{
    edit_calib_factors(24);

}

void TGalileo_signals_dlg::on_pushButton_25_clicked()
{
    edit_calib_factors(25);

}

void TGalileo_signals_dlg::on_pushButton_26_clicked()
{
    edit_calib_factors(26);

}

void TGalileo_signals_dlg::on_pushButton_27_clicked()
{
    edit_calib_factors(27);

}

void TGalileo_signals_dlg::on_pushButton_28_clicked()
{
    edit_calib_factors(28);

}

void TGalileo_signals_dlg::on_pushButton_29_clicked()
{
    edit_calib_factors(29);

}

void TGalileo_signals_dlg::on_pushButton_30_clicked()
{
    edit_calib_factors(30);

}

void TGalileo_signals_dlg::on_pushButton_31_clicked()
{
    edit_calib_factors(31);

}
//********************************************************************
void TGalileo_signals_dlg::edit_calib_factors(int nr)
{
    vector <double> ccc = cal_factors[nr];
    Tcalibration_factors_dlg dlg;
    dlg.setup(ccc);
    if(dlg.exec() == QDialog::Accepted)
    {
        cal_factors[nr] = dlg.fact_local;

    }
}
//********************************************************************


void TGalileo_signals_dlg::on_buttonBox_accepted()
{
    for(unsigned int nr = 0 ; nr <fline.size() ; ++nr)
    {
       fline[nr].enable = radios[nr]->isChecked();
       fline[nr].cal_order = cal_factors[nr].size();
    }
}
