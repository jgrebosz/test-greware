#include "t4pattern_defining_dlg.h"
#include "ui_t4pattern_defining_dlg.h"

#include <string>
#include <iostream> // cout
#include <fstream>
//#include <format> // c++20

#include <stdio.h>

#include <QMessageBox>
#include <QInputDialog>

using namespace std;
#include <sstream>
#include "paths.h"

//char znak = '#';

//************************************************************************************
T4pattern_defining_dlg::T4pattern_defining_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T4pattern_defining_dlg)
{
    ui->setupUi(this);
    nieb_pocz = "<span style=\"  font-weight:600; color:#0000ff;\">";

    czerw_pocz = "<span style=\"  font-weight:600; color:#ff0000;\">";
    kolor_kon = "</span>";
	pattern1 = "" ; // "%%";
    ui->lineEdit_pattern1->setText(pattern1.c_str());

    flag_second_pattern = false;

    ui->lineEdit_pattern2->setVisible( flag_second_pattern);
    //ui->lineEdit_two->setVisible( flag_second_pattern);
    ui->lineEdit_two->setEnabled(flag_second_pattern);

    ui->groupBox_pattern_found->setVisible(false);
    ui->groupBox_results->setVisible(false);
}
//************************************************************************************
T4pattern_defining_dlg::~T4pattern_defining_dlg()
{
    delete ui;
}
//************************************************************************************
void T4pattern_defining_dlg::set_parameters(std::string specname,
                                            std::string pattern1_,
                                            std::string pattern2_,
                                            std::string *one_symbols,
                                            std::string *two_symbols, string contents)
{
    pattern1 = pattern1_;
    pattern2 = pattern2_;
    suggested_one = *one_symbols;
    suggested_second = *two_symbols;
    ui->lineEdit_one->setText(suggested_one.c_str());
    ui->lineEdit_two->setText(suggested_second.c_str());
    original_specname = specname ;
    template_file_contents = contents;

	choose_proper_forbidden_character();

    // finding the pattern in the name (may be few times)
    ui->label_spectrum_name->setText(specname.c_str());

    //pattern = pattern1;
    find_patterns_and_make_skeleton_with_procents(original_specname);
    show_spectra_names();

    ui->groupBox_pattern_found->setVisible(false);
    ui->groupBox_results->setVisible(false);
}
//*******************************************************************
string T4pattern_defining_dlg::find_patterns_and_make_skeleton_with_procents(string text)
{
//	if(text.size() > 20) return "";   // for debugging time
//	cout << __func__ << "with argument (" << text << ")" << endl;

    bool flag_some_pattern_found = false;
    string skeleton = text;
	string temporary_pattern1(50, forbiden_character);

	if(pattern1.empty() == false )
    {
		// we do not want that pattern2 would penetrate the pattern1 occurences, so at first
		// we make the replacement with a fake pattern which is build of so called many forbidden characters
		// The 'forbidden charcter' is the one which
		//    - is not occuring in a file name
		//    - is not ocurring in a contents of file
		//   - and is also not occuring as a firs character in pattern2

		skeleton = find_patterns_and_replace(skeleton, pattern1, temporary_pattern1, flag_some_pattern_found);
		// pattern second --------------------------------------------------------------------------------
        if(!pattern2.empty() && flag_second_pattern ){
			skeleton = find_patterns_and_replace(skeleton, pattern2, "%2", flag_some_pattern_found);
        }		
		skeleton = find_patterns_and_replace(skeleton, temporary_pattern1, "%1", flag_some_pattern_found);
    }

	if(!flag_some_pattern_found)
	{

        skeleton = "";
        ui->groupBox_pattern_found->setVisible(false);
        ui->groupBox_results->setVisible(false);
    }
    else{
        ui->groupBox_pattern_found->setVisible(true);
        ui->groupBox_results->setVisible(true);
    }
    return skeleton;

}
//************************************************************************************
string T4pattern_defining_dlg::find_patterns_and_replace(string text, string pattern, string replacement, bool & flag_some_pattern_found)
{
	string skeleton = text;
	string::size_type loc;
	// pattern first --------------------------------------------------------------------
	vector<string::size_type> zapisek;

	// finding the places (location) where the pattern1 was found in the text
	// for(string::size_type i = skeleton.size() -1;  ; --i)
	for(uint i = 0 ; i < skeleton.size() ; )
	{
		//  cout << skeleton << " searching at position " << i << endl;
		loc = skeleton.find(pattern, i);
		if( loc == string::npos)
		{
			break; // not found
		}

		zapisek.push_back( loc);
		i = loc;
		i += pattern.size();
		// cout << "pattern1 [" << pattern1 << "] found at loc: " << loc << endl;
	}

	// now we know where are pattern1

//        for(unsigned int i = 0 ; i< zapisek.size(); ++i)
	for(int i = zapisek.size()-1; i>=0;  --i)
	{
		skeleton.replace(zapisek.at(i),
						 pattern.size(),

						 replacement   // "%1"    // what to put thee

						 );
//						cout << "found at position " << loc << ", after blue_replacement = "
//							 << skeleton
//							 << endl;
		flag_some_pattern_found = true;

	}
	zapisek.clear();
	return skeleton;
}
//************************************************************************************
/// We try to choose a charcter which does not exist in a filename and contents of the file
void T4pattern_defining_dlg::choose_proper_forbidden_character()
{



	char but_not_this_one { 'x'}; // fake
	if(ui->checkBox_pattern2->checkState() && pattern2.size())
	{
		but_not_this_one = pattern2[0];
	}

	string set_of_forbidden_characters { "<>;:'$&!^`" };
	for(uint i = 0 ; i < set_of_forbidden_characters.size() ; ++i)
	{
		char znak = set_of_forbidden_characters[i] ;

		if(znak == but_not_this_one){
			cout << "we skip character " << znak;
			continue;
		}

		if(
				original_specname.find(znak) == string::npos
				&&
				template_file_contents.find(znak) == string::npos
		)
		{
			forbiden_character = set_of_forbidden_characters[i];
			cout << "forbiden_character found as: "<< forbiden_character << endl;
			return;
		}
			cout << "character " << set_of_forbidden_characters[i] << " found in filename ofr contents: " << endl;
	}
	cout << "Strange... Forbidden character can not be chosen proprery... Amost impossible" << endl;
}
//************************************************************************************
void T4pattern_defining_dlg::get_parameters(vector<string> * vone, vector<string> * vtwo, vector<string> *filenames)
{
    *vone = vec_one;
    *vtwo = vec_two;
    *filenames = bw_spectra_names;
}
//************************************************************************************
void T4pattern_defining_dlg::show_spectra_names()
{
    //cout << "New run\n" ;
    string text_spectra_names ;
    spectra_names.clear();
    bw_spectra_names.clear();

    // take the current skeleton

//	cout << "Qstring  Edit_skeleton.txt = "
//			<<
//			<< endl;

//	ui->lineEdit_skeleton->text();



    string  skeleton = ui->lineEdit_skeleton->text().toStdString();

	cout << "std::string taken from LIneEdit skeleton = " << skeleton << endl;

	bool flag_pattern2_in_use = (skeleton.find("%2") != string::npos);
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
    if(flag_second_pattern)
    {
        istringstream s2(ui->lineEdit_two->text().toStdString() );
        vec_two.clear();
        for(int i = 0 ;  ; i++)
        {
            string wyraz ;
            s2 >>  wyraz ;
            if(!s2) break;
            vec_two.push_back(wyraz);
        }
    }

    if(vec_one.empty()) vec_one.push_back("");
    if(vec_two.empty()) vec_two.push_back("");



    // make the list of filenames - in colours
    for(unsigned int i1 = 0 ; i1 < vec_one.size() ; i1++)
        for(unsigned int i2 = 0 ; i2 < vec_two.size() ; i2++)
        {
            bool flag_any_change = false;
            string result_bw;


//			cout << "\n\n,we call cloning skeleton: " << skeleton << ", for arguments: [" << vec_one[i1] << "] [" << vec_two[i2]
//							 << "], pattern2 = [" << pattern2 << "]"<< endl;
            if( (!flag_second_pattern && i2 > 0) || (i2 > 0 && !flag_pattern2_in_use) ) continue;
            string result = make_a_clone_from_skeleton_using_kombination(skeleton,
                                                                         vec_one[i1], vec_two[i2],
                                                                         &result_bw,
                                                                         &flag_any_change);



            if(!flag_any_change) continue;
			//cout << "result: " << result << endl;
            if(flag_second_pattern == false && i2) continue;
            spectra_names.push_back(result);
            text_spectra_names += (result + "<br>") ;
            //bw_spectra_names.push_back(result_bw);

        }
    ui->textEdit_spectra_names->setText(text_spectra_names.c_str() );

    QList<int> lista = { 9, 1};  // 1:9 OK
    ui->splitter->setSizes(lista);




}
//********************************************************************************
string T4pattern_defining_dlg::make_a_clone_from_skeleton_using_kombination(string skeleton, string proc1, string proc2, string *result_bw_glob, bool *flag_any_change)
{

    *flag_any_change = false;
    string result = skeleton;

//	cout << __func__
//		 << "skel = " << skeleton
//		 << ", proc1= " << proc1
//		 << ", proc2 = " << proc2
//		 << endl;

    size_t  poz ;
    do{
		poz = result.find("%1");
        if(poz != string::npos)
        {
            result.replace(poz, 2, nieb_pocz  +proc1+ kolor_kon );
            *flag_any_change = true;
        }
    }while(poz != string::npos);


    if(proc2 != "")
        do{
		poz = result.find("%2");
        if(poz != string::npos)
        {
            result.replace(poz, 2, czerw_pocz  +proc2+ kolor_kon  );
            *flag_any_change = true;
        }else continue;
    }while(poz != string::npos);


    if(!(*flag_any_change)) return ("");
//	cout << __LINE__ << "result: " << result << endl;

    if(flag_second_pattern == false && proc2.size() > 2) return "";


    // remove colours from the name ========================================
    string result_bw = result;

    do{
        poz = result_bw.rfind(czerw_pocz);
        if(poz != string::npos)
            result_bw.erase(poz, czerw_pocz.size());
    } while(poz != string::npos);

    do{
        poz = result_bw.rfind(nieb_pocz);
        if(poz != string::npos)
            result_bw.erase(poz, nieb_pocz.size());
    }    while(poz != string::npos);

    do{
        poz = result_bw.rfind(kolor_kon);
        if(poz != string::npos)
            result_bw.erase(poz, kolor_kon.size());
    }       while(poz != string::npos);

    bw_spectra_names.push_back(result_bw);
    *result_bw_glob = result_bw;

	// cout << __LINE__ << " Tpattern_defining_dlg::make_a_clone_from_skeleton     BW result =" << result_bw << endl;
    return result;
}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_one_textChanged(const QString &  /* arg1*/)
{
	cout << "text changed \n\n";
    show_spectra_names();
    prepare_file_contents_skeleton();
}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_two_textChanged(const QString & /*arg1*/ )
{
    show_spectra_names();
    prepare_file_contents_skeleton();
}
//********************************************************************************

void T4pattern_defining_dlg::on_checkBox_pattern2_clicked(bool checked)
{
    // cout << "checked = " << checked << endl;
    flag_second_pattern = checked;
    ui->lineEdit_pattern2  ->setVisible(checked);  //  ->setEnabled(checked);
    //ui->lineEdit_two->setVisible(checked);
    ui->lineEdit_two->setEnabled(checked);
    prepare_filename_skeleton();
    show_spectra_names();
}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_pattern1_textChanged(const QString &arg1)
{
    pattern1 = arg1.toStdString();
    prepare_filename_skeleton();
    show_spectra_names();
}
//********************************************************************************
void T4pattern_defining_dlg::on_lineEdit_pattern2_textChanged(const QString &arg1)
{
    pattern2 = arg1.toStdString();


    prepare_filename_skeleton();
    show_spectra_names();
}
//********************************************************************************
void T4pattern_defining_dlg::prepare_filename_skeleton()
{
	choose_proper_forbidden_character();
    string skel = find_patterns_and_make_skeleton_with_procents(original_specname);
    // placing in the
    ui->lineEdit_skeleton->setText(skel.c_str() );
    ui->lineEdit_skeleton->hide();
    ui->label_skeleton->setText(skel.c_str() );

    ui->textLabel1_2->setText(!skel.empty() ? "Your spectrum name contains some patern":
                                              "Your spectrum name DOES NOT contain such paterns");
    if(skel.empty() == false)     prepare_file_contents_skeleton();
}
//********************************************************************************
void T4pattern_defining_dlg::prepare_file_contents_skeleton()
{
    string result = find_patterns_and_make_skeleton_with_procents(template_file_contents);

    ui->textEdit_contents_of_cloned_file->setText("");
    size_t  poz ;
    if(vec_one.empty() ) return;

    string proc1 = vec_one[0] ; // { "PATTERN_1"};

    //bool flag_any_change = false;
    do{
		poz = result.find("%1");
        if(poz != string::npos)
        {
            result.replace(poz, 2, nieb_pocz  +proc1+ kolor_kon );
            //flag_any_change = true;
        }
    }while(poz != string::npos);


    if(flag_second_pattern && vec_two.size())
    {
        string proc2 = vec_two[0] ;

        do{
			poz = result.find("%2");
            if(poz != string::npos)
            {
                result.replace(poz, 2, czerw_pocz  +proc2+ kolor_kon);
                //flag_any_change = true;
            }else continue;
        }while(poz != string::npos);
    }

    do{
        poz = result.find("\n");
        if(poz != string::npos)
        {
            result.replace(poz, 1, "<br>");
            //flag_any_change = true;
        }else continue;
    }while(poz != string::npos);


    string rt = R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">
            <html><head><meta name="qrichtext" content="1" /><style type="text/css">
            p, li { white-space: pre-wrap; }
    </style></head><body style=" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;">
            <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">)";
            rt += result;

    ui->textEdit_contents_of_cloned_file->setText(rt.c_str());
}
//*****************************************************************************************************
void T4pattern_defining_dlg::on_pushButton_give_numbers_clicked()
{

    // asking question
    // starting number
	string message { "Type\n    starting number    stoping number    'C format'\n\n\n"
					 "For example: if you type:\n \n     7   9  _%02d_\n\nyou will get:\n\n      _07_  _08_  _09_"};

    static string sugestion ;
    bool ok;
    QString res = QInputDialog::getText(this,
                                        "Make me row of numbers",
                                        QString ( message.c_str() ), // label

                                        QLineEdit::Normal,
                                        sugestion.c_str(),
                                        &ok);
    sugestion = res.toStdString();
    if(ok)
    {
        // user selected an item and pressed OK

        int pocz = 0;
        int kon = 0;
        string format_txt;

        char buforek[40];
        istringstream s(res.toStdString());
        s >> pocz >> kon >> format_txt;


//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wformat-nonliteral"

        string rezultat;
        for (int i = pocz ; i <= kon ; ++i)
        {
           sprintf(buforek, format_txt.c_str(), i);// warning, but OK
           rezultat += (string(buforek) + " ");
        }

//#pragma clang diagnostic pop

        rezultat = "if you are satisfied with result, copy it and paste it - where you want\n" + rezultat;
        QMessageBox::question ( this,
                                             "Result ", rezultat.c_str()
                                        );
    }
}
//*********************************************************************************************************
void T4pattern_defining_dlg::on_pushButton_clicked()
{
    // asking question
    // starting number
	string message { "Type:\n   starting character   stoping character   'C-format'\n\n\n"
					 "For example: if you type:\n\n      B D  _%c_\n\nyou will get:\n\n      _B_  _C_  _D_ "};

    static string sugestion ;
    bool ok;
    QString res = QInputDialog::getText(this,
                                        "Make me row of characters",
                                        QString ( message.c_str() ), // label

                                        QLineEdit::Normal,
                                        sugestion.c_str(),
                                        &ok);
    sugestion = res.toStdString();
    if(ok)
    {
        // user selected an item and pressed OK

        char pocz = 0;
        char kon = 0;
        string format_txt;

        char buforek[40];
        istringstream s(res.toStdString());
        s >> pocz >> kon >> format_txt;


        string rezultat;
        for (int i = pocz ; i <= kon ; ++i)
        {
           sprintf(buforek, format_txt.c_str(), i);  // warning, but OK
           rezultat += (string(buforek) + " ");
        }


        rezultat = "if you are satisfied with result, copy it and paste it - where you want\n" + rezultat;
        QMessageBox::question ( this,
                                             "Result ", rezultat.c_str()
                                        );
    }
}
