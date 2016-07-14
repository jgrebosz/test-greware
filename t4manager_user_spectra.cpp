#include "t4manager_user_spectra.h"
#include "ui_t4manager_user_spectra.h"

#include "t4user_spectrum_wizard.h"
#include "user_spectrum_description.h"
#include "paths.h"
#include <iostream>
#include <fstream>
#include <sstream>


#include <QProgressDialog>
#include <QDir>
#include <QMessageBox>
#include "t4pattern_defining_dlg.h"

#include "appl_form.h"
extern appl_form  *appl_form_ptr;

//************************************************************************************
T4manager_user_spectra::T4manager_user_spectra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T4manager_user_spectra)
{
    ui->setupUi(this);

    int     nr_rows = 0;
    ui->table->setRowCount( nr_rows );
    ui->table->setColumnCount(5);

    QStringList labels;
    labels << "Active" << "Name of the spectrum" << "Type" << "Condition assigned" << "Selfgates" ;
    ui->table->setHorizontalHeaderLabels ( labels );
    ui->table->resizeColumnsToContents ();

    labels.clear();
    labels << "Spectrum name" << "Dim"
           << "X bins" << "X beg" << "X end"
           << "Y bins" << "Y beg" << "Y end"
           << "X incrementers" << "its selfgate"
           << "Y incrementers" << "its selfgate"
           << "assigned condition" ;

    ui->review->setHorizontalHeaderLabels ( labels );
    ui->review->resizeColumnsToContents ();


    //ui->review->hide();
    //ui->review->setEnabled(false);
    //push_log->setEnabled(false);

    update_the_table() ;
    update_review();

}
//*************************************************************************************
T4manager_user_spectra::~T4manager_user_spectra()
{
    delete ui;
}
//*************************************************************************************
void T4manager_user_spectra::on_push_create_new_clicked()
{
    //cond_spec_wizard * dlg = new cond_spec_wizard ;
    T4user_spectrum_wizard * dlg = new T4user_spectrum_wizard ;
    user_spectrum_description us;

    dlg->set_parameters(&us, false) ;  // false means no editing, just creating
    if ( dlg->exec() == QDialog::Accepted )
    {

        // if it was succesfull - put into a vector
        vec_spectra.push_back(us) ;
        // display all current contents of the
        int last = vec_spectra.size() - 1 ;
        vec_spectra[last].name_of_spectrum
                = is_name_unique(vec_spectra[last].name_of_spectrum, last );
        vec_spectra[last].write_definitions(path.user_def_spectra);
        update_the_table() ;
        appl_form_ptr-> warning_spy_is_in_action();
    }
    raise();   // to the top of desktop
    // if not - delete it
}

//***********************************************************************
void T4manager_user_spectra::update_the_table()
{

    // As sometimes this take very long - we show progress dialog
    int how_many_items = 100;
    QString infor("Some disks (directories) can be very slow!\nReading the directory: ");
    infor += path.Quser_def_spectra() + "..." ;

    QProgressDialog progress( infor,
                              "Abort reading", 0, how_many_items,
                              this);
    progress.setMinimumDuration (5000) ; // miliseconds
    progress.setValue(2);
    qApp->processEvents();

    //----------------------

    vec_spectra.clear() ;
    // read the spectra from the disk and load them to the vector
    //   vector<user_spectra> vec_spectra

    // taking the spectra names from the directory - only

    QDir katalog2(path.Quser_def_spectra() );

    QString filtr = ui->ComboBox_filter->currentText ();
    QString name_filter = "*" + filtr + ("*" + user_spec_ext).c_str() ;

    progress.setValue(2);
    qApp->processEvents();
    how_many_items = katalog2.count() ;
    progress.setMaximum(how_many_items);

    // in the polygon dir
    QStringList lista = katalog2.entryList (QStringList(name_filter) ) ;

    int nr = 0 ;
    for ( QStringList::Iterator it = lista.begin() ; it != lista.end() ;  ++it, nr++ )
    {
        if(! (nr % 10))
        {
            //     cout << "nr = " << nr << endl;
            progress.setValue( nr );
            qApp->processEvents();
        }
        if ( progress.wasCanceled() )
            break;


        user_spectrum_description us ;

        // cout << "Trying to read spectrum definition " << *it << endl;

        us.name_of_spectrum = (*it).toStdString();
        int pos = us.name_of_spectrum.rfind(".") ;
        us.name_of_spectrum.erase(pos) ;

        string name_to_compare = us.name_of_spectrum ; // to trace the possible error

        us.read_from(path.user_def_spectra + (*it).toStdString() );
        if(us.name_of_spectrum != name_to_compare)
        {
            cout << "Error - the spectrum name inside the file is different from the file_name ("
                 << name_to_compare << " while inside is "
                 << us.name_of_spectrum << ") fixing this error...\n" ;
            // This may happen when somebody renamed the spectrum
            // using the operating system mv command.

            // fixing this error
            us.name_of_spectrum = name_to_compare ; // correct it properly
            us.write_definitions(path.user_def_spectra); // and save to the disk
        }

        vec_spectra.push_back(us) ;

        //
        // combo->insertItem(short_long_name(*it));
    }
    progress.setValue( how_many_items );

    int nr_rows =vec_spectra.size();

    ui->table->clearContents();
    ui->table->setRowCount( nr_rows );
    ui->table->setColumnCount(5);


    for (int j = 0; j < nr_rows; ++j )
    {
        //      ui->table->setItem( j, 0, new QCheckTableItem( table, "" ));  // safe !
        ui->table->setItem( j, 0, new QTableWidgetItem(Qt::ItemIsUserCheckable) );  // safe !

        ui->table->setItem ( j, 1,
                             new QTableWidgetItem (
                                 vec_spectra[j].name_of_spectrum.c_str(),
                                 Qt::ItemIsEnabled )
                             );


        ui->table->setItem(j, 2,
                           new QTableWidgetItem (vec_spectra[j].dimmension == 1 ? "1D": "2D"));

        string nam_no_ext = vec_spectra[j].condition_name.substr(0,vec_spectra[j].condition_name.rfind("."));
        ui->table->setItem(j, 3,
                           new QTableWidgetItem (nam_no_ext.c_str() ));

        // here should be the loop over all used selfgates (on X and Y incrementors
        //ui->table->setText(j, 4, "inf about slef-gates not implemented yet");
        ui->table->setItem(j, 4,
                           new QTableWidgetItem (
                               vec_spectra[j].get_selfgates().c_str(), Qt::NoItemFlags )  );


        // check/uncheck
        ui->table->item(j, 0)->   setCheckState(  vec_spectra[j].enabled ? Qt::Checked : Qt::Unchecked);

        table_changed(j, 0) ; // to enable/disable columns "spec name" and "type"

    }
    ui->table->resizeColumnsToContents ();
    update_review();
}
//*********************************************************************
//*********************************************************************
void T4manager_user_spectra::table_changed( int row, int col )
{
    if(row >= ui->table->rowCount() ) return;
    //    cout << "Table value changed row = " << row << ", col " << col << endl;
    bool stan  ;
    if(col == 0)
    {
        stan =( (ui->table->item( row, 0)->checkState () ) == Qt::Checked );
        ui->table->item( row, 1)->setFlags(stan ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable): (Qt::NoItemFlags| Qt::ItemIsSelectable) ) ;   // name
        ui->table->item( row, 2)->setFlags(stan ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable): (Qt::NoItemFlags| Qt::ItemIsSelectable) ) ;    // type
        ui->table->item( row, 3)->setFlags(stan ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable): (Qt::NoItemFlags| Qt::ItemIsSelectable) ) ;    // condition
        ui->table->item( row, 4)->setFlags(stan ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable): (Qt::NoItemFlags| Qt::ItemIsSelectable) ) ;   ;
        vec_spectra[row].enabled = stan ;
        vec_spectra[row].write_definitions(path.user_def_spectra) ;
    }

}
//**********************************************************************************
void T4manager_user_spectra::update_review()
{

    QApplication::setOverrideCursor( QCursor(Qt::WaitCursor) );
    ui->review->hide();
    // ui->review->setUpdatesEnabled( false );


    int nr_rows =vec_spectra.size();
    //ui->review->setRowCount( nr_rows );
    ui->review->clearContents();

    int linijka = 0 ;
    for (int j = 0; j < nr_rows; ++j, linijka++ )
    {
        ui->review->setRowCount(linijka+1);
        ui->review->setItem(linijka, 0,
                            new QTableWidgetItem( vec_spectra[j].name_of_spectrum.c_str()));

        //        cout << "spectrum name = " <<  vec_spectra[j].name_of_spectrum.c_str() << endl;


        ui->review->setItem(linijka, 1,
                            new QTableWidgetItem(vec_spectra[j].dimmension == 1 ? "1D": "2D"));

        // binning
        ui->review->setItem(linijka, 2,
                            new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_bins_x())));
        ui->review->setItem(linijka, 3,
                            new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_beg_x())));
        ui->review->setItem(linijka, 4,
                            new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_end_x())));

        if(vec_spectra[j].dimmension != 1)
        {
            ui->review->setItem(linijka, 5, new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_bins_y() ))) ;
            ui->review->setItem(linijka, 6, new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_beg_y()  )));
            ui->review->setItem(linijka, 7, new QTableWidgetItem(QString("%1").arg(vec_spectra[j].give_end_y()  )));
        }
        else
        {
            ui->review->setItem(linijka, 5, new QTableWidgetItem("-") );
            ui->review->setItem(linijka, 6, new QTableWidgetItem("-") );
            ui->review->setItem(linijka, 7, new QTableWidgetItem("-") );
        }
        // General condition
        string nam_no_ext = vec_spectra[j].condition_name.substr(0,vec_spectra[j].condition_name.rfind("."));

        ui->review->setItem(linijka, 12, new QTableWidgetItem(nam_no_ext.c_str() ) );


        // here should be the loop over all used selfgates (on X and Y incrementors

        vector< pair<string, string> > & incrementors_x   =  vec_spectra[j].give_x_incr();
        vector< pair<string, string> > & incrementors_y   =  vec_spectra[j].give_y_incr();

        unsigned k = 0;  // extra rows in table, needed for multiple incrementors
        for(k = 0 ; k < max(incrementors_x.size(), incrementors_y.size()) ; k++, linijka++)
        {
            //            cout << "now we will make many incrementers and selfgates k = " << k << endl;

            if(k >0)
            {
                ui->review->setRowCount(linijka+1);  // for k = 0 we do not need to create new
                //                cout << "Adding (continuation) row of table. Now is " << linijka << endl;
                ui->review->setItem(linijka, 0, new QTableWidgetItem("          (cont.) ") );
            }

            //-------------X ----------------
            string sg = (k < incrementors_x.size()) ?
                        incrementors_x[k].second.substr(0,incrementors_x[k].second.rfind("."))
                      : " --- " ;

            ui->review->setItem(linijka, 8, new QTableWidgetItem ((k < incrementors_x.size()) ? incrementors_x[k].first.c_str() : " --- " ));
            ui->review->setItem(linijka, 9, new QTableWidgetItem(sg.c_str() ) ) ;
            //----------- Y ---------------

            ui->review->setItem(linijka, 10, new QTableWidgetItem ((k < incrementors_y.size()) ? incrementors_y[k].first.c_str() : " --- " ));

            sg = (k < incrementors_y.size()) ?
                        incrementors_y[k].second.substr(0,incrementors_y[k].second.rfind("."))
                      : " --- " ;

            ui->review->setItem(linijka, 11, new QTableWidgetItem(sg.c_str()) ) ;

            // just enabling
            for(int c = 0 ; c < ui->review->columnCount(); c++)
            {
                // cout << "trying to enable item row=" << linijka << ", column =" << c << endl;
                if(ui->review->item(linijka, c) )
                {
                    ui->review->item(linijka, c)->setFlags( Qt::ItemIsEnabled);
                }
            }

        }
        if(k) linijka-- ;
    }


    ui->review->resizeColumnsToContents ();
    ui->review->show() ;
    QApplication::restoreOverrideCursor();
}
//********************************************************************************
//********************************************************************************
string T4manager_user_spectra::is_name_unique( string n, int nr )
{
    // perhaps such a cloned spectrum already exists ?
    bool changed = false ;
    string new_name = n ;
    for(unsigned i = 0 ; i < vec_spectra.size() ; i++)
    {
        if(new_name == vec_spectra[i].name_of_spectrum
                &&
                i != (unsigned)nr )
        {
            new_name += "A" ;
            i = 0 ; // starting again
            changed = true ;
        }
    }
    if(changed)
    {
        QMessageBox::warning(this,
                             "Duplicate name of the spectrum",
                             QString("The name of the spectrum:\n\t%1\n"
                                     "was already existing in the list, so it had to be changed into:\n"
                                     "\t%2\n").arg(n.c_str())
                             .arg(new_name.c_str() ),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
    }
    return new_name ;
}
//***********************************************************************

//************************************************************************************
void T4manager_user_spectra::on_table_cellClicked(int row, int column)
{
    table_changed(row, column);
}
//************************************************************************************
void T4manager_user_spectra::on_table_cellDoubleClicked(int /*row*/ , int column)
{
    // here, editing spectrum
    //    cout << "Dobule click at " << row << ", " << column << endl;
    if(column == 1) on_push_edit_selected_clicked();
}
//************************************************************************************
void T4manager_user_spectra::on_push_remove_selected_released()
{

    // here should be a loop over many regions of selecion
    // many lines of every selection

    QList<QTableWidgetSelectionRange> range = ui->table->selectedRanges() ;

    //cout << "Selection has " << (range.count()) << " ranges" << endl;


    if(range.count() == 0)
    {
        QMessageBox::warning(this,
                             "No spectrum name selected",
                             QString("Select the spectrum by clicking once on its name\n"),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
        return ;
    }

bool flag_any_change = false;
    bool flag_yes_to_all = false;

    for(int s = range.count()-1; s >=0 ; s--)    // can be many separated ranges on this list
    {
        cout << "range[s].bottomRow()= " << range[s].bottomRow() << ", range[s].topRow()= " <<  range[s].topRow() << endl;
        for(int row = range[s].bottomRow() ; row >= range[s].topRow() ; row--)
        {
            cout << "remowing row = " << row << " while range[s].topRow() = " << range[s].topRow() << endl;

            //  unsigned row = tab->selectRow();    ro sel currentRow() ;
            if(row >= (signed int) vec_spectra.size() )
            {
                cout << "STRANGE --> row >= (signed int) vec_spectra.size()  ? " << __FILE__ << ":"<< __LINE__  << endl;
                return ;
            }

            int answ = QMessageBox::Cancel;

            if(flag_yes_to_all == false)
            {
                QMessageBox msgBox;
                msgBox.setText("Removing the spectrum definition");
                msgBox.setInformativeText( QString("You are going to remove the definition nr %1\nof the spectrum %2\n"
                                                   "Are you sure?").arg(row+1).arg(vec_spectra[row].name_of_spectrum.c_str() ) ) ;
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::YesToAll |  QMessageBox::No | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::No);
                answ = msgBox.exec();
            }

            if(answ == QMessageBox::YesToAll) flag_yes_to_all = true;

            if(answ == QMessageBox::Yes || answ == QMessageBox::YesToAll || flag_yes_to_all )  /*Yes, Yes_to_all */
            {
                // remove from the directory
                string fname = path.Quser_def_spectra().toStdString() + vec_spectra[row].name_of_spectrum + user_spec_ext;

                // cout << "Yes, so removing " << fname << ", name taken from the memory, (not from table)" << endl;

                // create 'removed'subdirectrory (if it does not exists) ---------------
                string remdir = path.Qspectra().toStdString() + "removed/" ;

                QDir dir(remdir.c_str() );
                if(dir.exists() == false)
                {
                    dir.mkdir(remdir.c_str());
                }
                else {
                    // cout << "subdir already exists " << endl;
                }

                // --------- now the moving
                string moving_command = "mv " + fname + " ";
                moving_command += remdir + vec_spectra[row].name_of_spectrum + user_spec_ext;
                //cout << "Komenda " << moving_command << endl;
                int result = system(moving_command.c_str());
                if(result) cout << "Problem with moving the definition, so no backup made" << endl;

                // ----- now removing from the memory of the  computer

                //cout << "In the memory this row has " << vec_spectra[row].name << endl;
                vec_spectra.erase(vec_spectra.begin() + row) ;

                ui->table->item(row, 1)->setSelected(false);
                flag_any_change = true;

            }
            else if(answ == QMessageBox::No)
            {
                // just ignore
                ui->table->item(row, 0)->setSelected(false);

            }
            else if(answ == QMessageBox::Cancel)
            {
                goto outside;
            }
            else {
                cout << "Should never be here "<< __FILE__ << ":" << __LINE__ << endl;
            }

        } // for row
    } // for sel range
outside:
    if(flag_any_change)appl_form_ptr-> warning_spy_is_in_action();
    update_the_table() ;
}
//**********************************************************************
void T4manager_user_spectra::row_is_selected()
{
    int row_nr = ui->table->currentRow() ;
    ui->table->selectRow (row_nr);
}
//**********************************************************************

void T4manager_user_spectra::on_push_edit_selected_clicked()
{

    int nr = ui->table->currentRow() ;
    if(nr >= ui->table->rowCount() || nr == -1)
    {
        QMessageBox::warning(this,
                             "No spectrum selected",
                             QString(nr == -1 ? "Nothing to edit" : "Select the spectrum by clicking once on its name\n"),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
        return ;
    }
    row_is_selected();
    //cond_spec_wizard * dlg = new cond_spec_wizard ;

    T4user_spectrum_wizard * dlg = new T4user_spectrum_wizard ;
    dlg->set_parameters(& vec_spectra[nr], true) ; // true = editing, cloning is allowed
    if ( dlg->exec() == QDialog::Accepted )
    {
        vec_spectra[nr].name_of_spectrum
                = is_name_unique(vec_spectra[nr].name_of_spectrum, nr);

        vec_spectra[nr].write_definitions(path.user_def_spectra);
        update_the_table() ;
        appl_form_ptr-> warning_spy_is_in_action();
    }
    raise();   // to the top of desktop

}
//*****************************************************************************************
void T4manager_user_spectra::on_push_clone_clicked()
{

    QMessageBox::information(this,
                             "Cloning the definition of the spectrum",
                             QString("If you want to clone some spectrum\n\n"
                                     "   1. Open it for editing (Press button: Edit Selected Spectrum)\n\n"
                                     "   2. On the first page of the editing wizard - change the name of this spectrum\n\n"
                                     "   3. Go to the last page of the wizard - and press Finish\n\n\n"
                                     "Note: By this you created a new spectrum definition on the disk "
                                     "while the original spectrum is not touched"
                                     //"and the new-named spectrum (clone) will be stored on the disk independently\n"
                                     ),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
}
//*****************************************************************************************
void T4manager_user_spectra::create_condition()
{
    /*
  T4condition_wizard * dlg = new T4condition_wizard;
  Tcondition_description_cracow  cnd;

  dlg->set_parameters(&cnd) ;
  if ( dlg->exec() == QDialog::Accepted )
  {
    cnd.save_condition();
  }
*/
}
//***********************************************************************
void T4manager_user_spectra::edit_condition()
{
    /*
  condition_wizard * dlg = new condition_wizard;
  dlg->exec();
  */
}
//**********************************************************************
void T4manager_user_spectra::make_report_file()
{

    ofstream plik((path.user_def_spectra+ "report_spec.txt").c_str() );

    int nr_rows = ui->review->rowCount();

    for (int j = 0; j < nr_rows; j++ )
    {
        for(int k = 0 ; k < 13; k++)
        {
            //string co = ui->review->text(j, k).ascii() ;
            if( ui->review->item(j, k)->text().isNull() )
                plik << "    " << " ; " ;
            else
                plik << (ui->review->item(j, k)->text().toStdString() ) << " ; " ;
        }
        plik << "\n";

    }

    plik.close() ;

    QString wiad ;
    if(plik)
    {
        wiad = QString("Report succesfully written as \n") +
                (path.user_def_spectra+ "report_spec.txt").c_str() ;
        QMessageBox::information(this,
                                 "Report about user defined spectra",
                                 wiad,
                                 QMessageBox::Ok,
                                 QMessageBox::NoButton,
                                 QMessageBox::NoButton);
    }
    else
    {
        wiad = QString("Error while writing the report \n") +
                (path.user_def_spectra+ "report_spec.txt").c_str() ;

        QMessageBox::critical(this,
                              "Report about user defined spectra",
                              wiad,
                              QMessageBox::Ok,
                              QMessageBox::NoButton,
                              QMessageBox::NoButton);
    }
    return ;

}
//**********************************************************************************
void T4manager_user_spectra::on_review_cellDoubleClicked(int /*row*/, int /*column*/ )
{
    review_double_clicked();
}
//********************************************************************************
void T4manager_user_spectra::review_double_clicked()
{
    int nrc = ui->review->currentRow() ;
    if(nrc >= ui->review->rowCount())
    {
        QMessageBox::warning(this,
                             "No spectrum selected",
                             QString("Select the spectrum by clicking once on its name\n"),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
        return ;
    }

    cout << "Dbl click on the row of review" << nrc << endl;
    string last_legal_name ;
    for(int i = 0 ; i <= nrc ; i ++)
    {
        string current_name = ui->review->item(i, 0)->text().toStdString() ;
        //    cout << "Checking name " << current_name << endl;
        if(current_name.find("(continuation)") != string::npos)
        {
            //cout << "cont " << endl;
        }
        else
        {
            //cout << " so far  legal was " << last_legal_name << endl;
            last_legal_name = current_name;
        }
    }
    //  cout << "this means the spectrum name " <<  last_legal_name << endl;
    // find this name in the vector
    int which = -1 ;
    for(unsigned i = 0 ; i < vec_spectra.size() ; i++)
    {
        //    cout << "comparing with " << vec_spectra[i].name_of_spectrum << endl;
        if(vec_spectra[i].name_of_spectrum ==  last_legal_name)
        {
            which = i ;
            //       cout << "remembered as spectrum nr " << i << endl ;
        }
    }
    if(which == -1)
        return ;

    //row_is_selected();

    // find such a name in the vector

    T4user_spectrum_wizard * dlg = new T4user_spectrum_wizard ;
    dlg->set_parameters(& vec_spectra[which], true) ; // true = editing, cloning is allowed
    if ( dlg->exec() == QDialog::Accepted )
    {
        vec_spectra[which].name_of_spectrum
                = is_name_unique(vec_spectra[which].name_of_spectrum, which);


        vec_spectra[which].write_definitions(path.user_def_spectra);
        update_the_table() ;
        appl_form_ptr-> warning_spy_is_in_action();
    }

}
//****************************************************************

void T4manager_user_spectra::on_ComboBox_filter_textChanged(const QString & /*arg1*/)
{
    update_the_table() ;
    ui->ComboBox_filter->setFocus();
}
//****************************************************************
void T4manager_user_spectra::on_push_A_1_clone_clicked()
{
    class error
    {
    public:
        string title ;
        string message;
        int kind ; // 1 error, 2 warning
    };
    error e;
    //---------------

    string introduction_txt =  "This is the option to clone a spectrum which contains \n"
            "at most 2 pattern of characters which had to be smartly replaced\n"
            "Such substring will be replaced with your desired values"
            "(i.e. for all possible cluster crystals)\n"
            "By this action, the set of new spectra wiil be created.\n\n"
            "The replacement will be done :\n"
            "    1. Inside  the name of the spectrum,\n"
            "    2. Inside the name of any incrementer,\n"
            "    3. Inside the name of any used selfgates (not very useful!)\n"
            "    4. Inside the name of condition assigned to this spectrum_1D.\n" ;


    bool flag_any_change = false;
    try
    {

        int nr = ui->table->currentRow() ;
        if(nr >= ui->table->rowCount() || nr == -1)
        {
            e.title = "No spectrum selected";
            e.message = "\n\n\nSelect some spectrum name containing patters to be cloned '"
                    "`\n\n\n\nINFO:\n" + introduction_txt;
            ;
            e.kind = 2; //warning;
            throw e;

        }
        row_is_selected();

        // checking if the name of the spectrum contains the pattern (substring A_1)

        string specname = vec_spectra[nr].name_of_spectrum;
#if 0
         if(specname.empty() ||  row == -1)
        {
            e.title = "No spectrum is selected now";
            e.message = "\n\n\nPlease select a spectrum which you want to clone\n\n"
 +
                    introduction_txt;
            e.kind = 1; // critcial
            throw e;
        }

#endif

         string::size_type loc ;
        string pattern1 = "_00_";
        string pattern2  = "";
        string one = "B C";
        string two = "01 02 ";

        vector<string> chain_one;   // for result
        vector<string> chain_two;
        vector<string> filenames;


        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        T4pattern_defining_dlg dlg;
        dlg.set_parameters(specname, pattern1, pattern2, &one, &two);
        if( dlg.exec() != QDialog::Accepted) return;

        dlg.get_parameters(&chain_one, &chain_two, &filenames);

        cout << "After closing the dialog for parameters there are following spectra" << endl;

        for(auto x : filenames)
        {
            cout << x << endl;

        }

        //  reading the whole contents of the template file
        string pathed_name = path.user_def_spectra + specname + user_spec_ext;
        //string pathed_name =  specname;
        ifstream plik(pathed_name.c_str() );
        if(!plik)
        {
            string m = "Error while opening the file :";
            m + pathed_name;

            e.title = "Can't open a file ";
            e.message = m ;
            e.kind = 1; // critical
            throw e;
        }

        // read in the whole contents - to replace strings in the memory
        string contents;
        string one_line;
        while(plik)
        {
            getline(plik, one_line);  // delimiter (\n) is not added to the string
            // so we add it
            contents += one_line;
            contents += '\n';
        }


        string file_contents_skeleton = dlg.find_patterns_and_make_skeleton_with_procents(contents);

//        cout << "SZKIELET WIDMA ZAWIERA: \n"<< file_contents_skeleton << endl;

        //  search all the positions of the pattern substrings and replace with  %1 %2

        // FOR loop over all crystals========================================
        // ready to create the new spectra

        string txt = /*introduction_txt + */
                "\n\nDo you really want to create such set of clones ? ";

        for(auto x : filenames) {  txt += x + "   "; }
        int result = QMessageBox::information(this,
                                              "Cloning the spectra",
                                              txt.c_str(),
                                              QMessageBox::Yes,
                                              QMessageBox::No,
                                              QMessageBox::Cancel);
        if(result != QMessageBox::Yes )
        {
            return ;
        }
#if 1
         bool flag_pattern2_in_use = (file_contents_skeleton.find("%2") != string::npos);
         int file_nr = 0 ;
        for(unsigned int d = 0 ; d < chain_one.size() ; d++)
            for(unsigned int k= 0 ; k < chain_two.size() ; k++)
            {
                // if(d == 0 && k == 1) continue; // to skip the first one - which is a wzor

                // changing the contents ---------------


                bool flag_any_change = false;
                string result_bw;

//                cout << "chain one size =" << chain_one.size();
//                cout << ", chain two size =" << chain_two.size();
//                cout << ", d = " << d ;
//                cout << ", k = " << k  << endl;


//                cout << "cloning skeleton for arguments: [" << chain_one[d] << "] [" << chain_two[k]
//                     << "], pattern2 = [" << pattern2 << "]"<< endl;

                if(  (k > 0 && !flag_pattern2_in_use) ) continue;


                string result =
                        dlg.make_a_clone_from_skeleton_using_kombination(file_contents_skeleton,
                                                                             chain_one[d],
                                                                             chain_two[k],
                                                                             &result_bw,
                                                                             &flag_any_change);


                if(!flag_any_change) continue;
                //cout << "result: " << result << endl;



                // ------------------------------------

                // save under a proper name --------------------------

                string new_filename = filenames[file_nr++]; // specname;
                //cout << "New file " << nr << ")  = " << new_filename << endl;
                // adding the path --------------
                new_filename =  path.user_def_spectra + new_filename +  user_spec_ext;

                // checking if it exists
                static bool make_checking_if_clone_exists = true;
                if(make_checking_if_clone_exists)
                {
                    ifstream plik_exists(new_filename.c_str());
                    if(plik_exists)
                    {
                        int odp =  QMessageBox::question(this,
                                                         "Overwrite ?",
                                                         string("Spectrum called \n" +
                                                                new_filename +
                                                                "\nalready exist. \n Overwite it?").c_str(),
                                                         QMessageBox::Yes,
                                                         QMessageBox::YesAll,
                                                         QMessageBox::No);
                        switch(odp)
                        {
                            case QMessageBox::No: continue; break;
                            case QMessageBox::Yes: break;
                            case QMessageBox::YesAll: make_checking_if_clone_exists = false ; break;
                        }
                    } // if exists
                } // if make checking
                cerr << "saving file " << new_filename << endl;

                ofstream plikB(new_filename.c_str());
                if(!plikB)
                {
                    e.message= string ("Can't open the file for writing: ") +  new_filename ;
                    e.title = "Error while opening the file";
                    e.kind = 1; // critial
                    throw e;
                }
                plikB << result_bw;
                if(!plikB)
                {
                    e.message= string ("Can't write the file ") +  new_filename ;
                    e.title = "Error while writing the file";
                    e.kind = 1; // critial
                    throw e;
                }
                plikB.close();
                flag_any_change = true;
            } // end for  d (detectors) and for k
#endif

        update_the_table() ;
        if(flag_any_change)appl_form_ptr-> warning_spy_is_in_action();

    }// end of try
    catch(error m)
    {
        QMessageBox::warning(this,
                             m.title.c_str(),
                             m.message.c_str(),
                             QMessageBox::Ok,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
        return;
    }
    raise();   // to the top of desktop
}
//****************************************************************
void T4manager_user_spectra::on_push_log_clicked()
{
    make_report_file();
}
