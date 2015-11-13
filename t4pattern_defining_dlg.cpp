#include "t4pattern_defining_dlg.h"
#include "ui_t4pattern_defining_dlg.h"

#include <string>
using namespace std;
#include <sstream>
#include "paths.h"

//************************************************************************************
T4pattern_defining_dlg::T4pattern_defining_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T4pattern_defining_dlg)
{
    ui->setupUi(this);
    nieb_pocz = "<span style=\" color:#0000ff;\">";

    czerw_pocz = "<span style=\" color:#ff0000;\">";
    kolor_kon = "</span>";
}
//************************************************************************************
T4pattern_defining_dlg::~T4pattern_defining_dlg()
{
    delete ui;
}
//************************************************************************************
void T4pattern_defining_dlg::set_parameters(std::string specname,
                                           std::string pattern,
                                           std::string *one_symbols,
                                           std::string *two_symbols)
{

    // finding the pattern in the name (may be few times)
    ui->label_spectrum_name->setText(specname.c_str());
    string skeleton = specname ;
    //    vector<string::size_type> position;

    for(string::size_type i = 0 ; ; i++)
    {
        string::size_type loc = skeleton.find(pattern);
        if( loc == string::npos )
        {
            break; // not found
        }
        //        cout << "found at position " << loc << endl;
        skeleton.replace(loc, pattern.size(),
                         "_" + nieb_pocz + "%1" + kolor_kon +
                         "_" +
                         czerw_pocz + "%2" + kolor_kon + "_");
    }

    // placing in the
    ui->lineEdit_skeleton->setText(skeleton.c_str() );
    ui->lineEdit_skeleton->hide();


    ui->label_skeleton->setText(skeleton.c_str() );

    ui->lineEdit_one->setText(one_symbols->c_str());
    ui->lineEdit_two->setText(two_symbols->c_str());
    show_spectra_names();

}
//************************************************************************************
void T4pattern_defining_dlg::get_parameters(vector<string> * vone, vector<string> * vtwo)
{
    *vone = vec_one;
    *vtwo = vec_two;

}
//************************************************************************************
void T4pattern_defining_dlg::show_spectra_names()
{
    string text_spectra_names ;
    spectra_names.clear();

    // take the current skeleton
    string  skeleton = ui->lineEdit_skeleton->text().toStdString();
    // for  %1
    istringstream s1(ui->lineEdit_one->text().toStdString());

    vec_one.clear();
    for(int i = 0 ;  ; i++)
    {
        string wyraz ;
        s1 >>  wyraz ;
        if(!s1) break;
        vec_one.push_back(wyraz);
    }
    // for %2
    istringstream s2(ui->lineEdit_two->text().toStdString() );
    vec_two.clear();
    for(int i = 0 ;  ; i++)
    {
        string wyraz ;
        s2 >>  wyraz ;
        if(!s2) break;
        vec_two.push_back(wyraz);
    }


    if(vec_one.empty()) vec_one.push_back("");
    if(vec_two.empty()) vec_two.push_back("");

    // make the list
    for(unsigned int i1 = 0 ; i1 < vec_one.size() ; i1++)
        for(unsigned int i2 = 0 ; i2 < vec_two.size() ; i2++)
        {
            string result = skeleton;
            size_t  poz = result.find("%1");
            if(poz != string::npos)
            {
                result.replace(poz, 2, nieb_pocz  +vec_one[i1]+ kolor_kon );
            }

            poz = result.find("%2");
            if(poz != string::npos)
            {
                // <span style=" font-size:10pt; color:#ff0000;">%2</span>

                result.replace(poz, 2, czerw_pocz  +vec_two[i2]+ kolor_kon  );
            }

            //cout << "result: " << result << endl;
            spectra_names.push_back(result);
            text_spectra_names += (result + "\n") ;
            // put the names into the vector of namespace
            // put in into the listbox
        }
    ui->textEdit_spectra_names->setText(text_spectra_names.c_str() );

    // restore the previous skeleton
    string n = path.autom + "last_skeleton";
    // just_save_skeleton(n);

}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_one_textChanged(const QString &  /* arg1*/)
{
    show_spectra_names();
}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_two_textChanged(const QString & /*arg1*/ )
{
    show_spectra_names();
}
//********************************************************************************
