
#-------------------------------------------------
#
# Project created by QtCreator 2010-12-17T12:19:05
#
#-------------------------------------------------

TARGET = greware
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += warn_on  static debug
#CONFIG  += warn_on  static release

#static is probably for pictures (loaded into program)

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -g        # <-- -g is must be on for debug

#QMAKE_CXXFLAGS += -std=c++11

target.path = ./grewareGUI/
INSTALLS += target

SOURCES += main.cxx\
        appl_form.cxx \
    paths.cpp \
    options.cpp \
    spectrum_2D.cpp \
    spectrum_1D.cpp \
    box_of_spectrum.cpp \
    box_of_matrix.cpp \
    box_of_counts.cpp \
    box_of_channels.cpp \
    swiat.cpp \
    gate_1D.cpp \
    Tpinup.cpp \
    tundo.cpp \
    polygon_gate.cpp \
    tplate_spectrum.cpp \
    Tfile_helper.cpp \
    t4results_of_integration.cpp \
    t4sum_spectra_dialog.cpp \
    t4select_spectra.cpp \
    t4setting_paths_dlg.cpp \
    t4size_spectrum_dlg.cpp \
    t4setting_times_dlg.cpp \
    t4binning_change_dlg.cpp \
    t4merge_2d_spectra_dlg.cpp \
    t4about_dlg.cpp \
    t4welcome.cpp \
    t4info_dlg.cpp \
    t4auto_calib_wizard.cpp \
    t4manager_user_spectra.cpp \
    t4user_spectrum_wizard.cpp \
    user_spectrum_description.cpp \
    t4incrementer_selector.cpp \
    t4manager_user_conditions.cpp \
    t4user_condition_wizard.cpp \
    Tcondition_description_cracow.cpp \
    t4addline_1d_wizard.cpp \
    t4important_dlg.cxx \
    t4collect_ntuple.cxx \
    t4addback_dlg.cxx \
    t4zet_aoq_ranges.cpp \
    t4verbose_dlg.cpp \
    t4good_minibal.cpp \
    t4doppler_dlg.cpp \
    t4other_spy_options.cpp \
    t4good_ger_dlg.cpp \
    t4good_hector_dlg.cpp \
    t4lycca_parameters.cpp \
    t4active_stopper_dlg.cpp \
    t4manager_user_incrementers.cpp \
    Tincrementer_description_cracow.cpp \
    t4user_incrementer_wizard.cpp \
    Tself_gate_abstract_descr.cpp \
    Tself_gate_ger_descr.cpp \
    t4options_visibility.cpp \
    t4selfgate_ger_dlg.cpp \
    t4selfgate_choice_dlg.cpp \
    t4picture_angle.cpp \
    tselfgate_type.cxx \
    t4selfgate_hec_dlg.cpp \
    Tself_gate_mib_descr.cpp \
    Tself_gate_hec_descr.cpp \
    Tself_gate_ger_addback_descr.cpp \
    Tself_gate_agata_psa_descr.cxx \
    t4selfgate_miniball_dlg.cpp \
    t4selfgate_geraddback_dlg.cpp \
    t4selfgate_agata_psa_dlg.cpp \
    t4pattern_defining_dlg.cpp \
    t4selfgate_selector.cpp \
    t4update_info_dlg.cpp \
    tgui_options.cpp \
    t4interesting_ranges_galileo.cpp \
    t4good_galileo_ge_dlg.cpp \
    t4selfgate_ge_cristal_galileo.cpp \
    Tself_gate_ge_galileo_descr.cpp \
    tgalileo_signals_dlg.cpp \
    tcalibration_factors_dlg.cpp \
    Tfile_line_det_cal_lookup.cpp

HEADERS  += appl_form.h \
    options.h \
    paths.h \
    spectrum_2D.h \
    spectrum_1D.h \
    box_of_spectrum.h \
    box_of_matrix.h \
    box_of_counts.h \
    box_of_channels.h \
    swiat.h \
    gate_1D.h \
    Tpinup.h \
    tundo.h \
    polygon_gate.h \
    tplate_spectrum.h \
    Tfile_helper.h \
    t4results_of_integration.h \
    t4sum_spectra_dialog.h \
    t4select_spectra.h \
    t4setting_paths_dlg.h \
    t4size_spectrum_dlg.h \
    t4setting_times_dlg.h \
    t4binning_change_dlg.h \
    t4merge_2d_spectra_dlg.h \
    t4about_dlg.h \
    t4welcome.h \
    t4info_dlg.h \
    t4auto_calib_wizard.h \
    t4manager_user_spectra.h \
    t4user_spectrum_wizard.h \
    user_spectrum_description.h \
    t4incrementer_selector.h \
    t4manager_user_conditions.h \
    t4user_condition_wizard.h \
    Tcondition_description_cracow.h \
    t4addline_1d_wizard.h \
    t4important_dlg.h \
    t4collect_ntuple.h \
    t4addback_dlg.h \
    t4zet_aoq_ranges.h \
    t4verbose_dlg.h \
    t4good_minibal.h \
    t4doppler_dlg.h \
    t4other_spy_options.h \
    t4good_ger_dlg.h \
    t4good_hector_dlg.h \
    t4lycca_parameters.h \
    t4active_stopper_dlg.h \
    t4manager_user_incrementers.h \
    t4user_incrementer_wizard.h \
    Tself_gate_abstract_descr.h \
    Tself_gate_ger_descr.h \
    t4options_visibility.h \
    t4selfgate_ger_dlg.h \
    t4selfgate_choice_dlg.h \
    t4picture_angle.h \
    tselfgate_type.h \
    t4selfgate_hec_dlg.h \
    Tself_gate_mib_descr.h \
    Tself_gate_hec_descr.h \
    Tself_gate_ger_addback_descr.h \
    Tself_gate_agata_psa_descr.h \
    t4selfgate_miniball_dlg.h \
    t4selfgate_geraddback_dlg.h \
    t4selfgate_agata_psa_dlg.h \
    t4pattern_defining_dlg.h \
    t4selfgate_selector.h \
    t4update_info_dlg.h \
    tgui_options.h \
    t4interesting_ranges_galileo.h \
    t4good_galileo_ge_dlg.h \
    t4selfgate_ge_cristal_galileo.h \
    Tself_gate_ge_galileo_descr.h \
    tgalileo_signals_dlg.h \
    tcalibration_factors_dlg.h \
    Tfile_line_det_cal_lookup.h


FORMS    += appl_form.ui \
    tplate_spectrum.ui \
    t4results_of_integration.ui \
    t4sum_spectra_dialog.ui \
    t4select_spectra.ui \
    t4setting_paths_dlg.ui \
    t4size_spectrum_dlg.ui \
    t4setting_times_dlg.ui \
    t4binning_change_dlg.ui \
    t4merge_2d_spectra_dlg.ui \
    t4about_dlg.ui \
    t4welcome.ui \
    t4info_dlg.ui \
    t4auto_calib_wizard.ui \
    t4manager_user_spectra.ui \
    t4user_spectrum_wizard.ui \
    t4incrementer_selector.ui \
    t4manager_user_conditions.ui \
    t4user_condition_wizard.ui \
    t4addline_1d_wizard.ui \
    t4important_dlg.ui \
    t4collect_ntuple.ui \
    t4addback_dlg.ui \
    t4zet_aoq_ranges.ui \
    t4verbose_dlg.ui \
    t4good_minibal.ui \
    t4doppler_dlg.ui \
    t4other_spy_options.ui \
    t4good_ger_dlg.ui \
    t4good_hector_dlg.ui \
    t4lycca_parameters.ui \
    t4active_stopper_dlg.ui \
    t4manager_user_incrementers.ui \
    t4user_incrementer_wizard.ui \
    t4options_visibility.ui \
    t4selfgate_ger_dlg.ui \
    t4selfgate_choice_dlg.ui \
    t4picture_angle.ui \
    t4selfgate_hec_dlg.ui \
    t4selfgate_miniball_dlg.ui \
    t4selfgate_geraddback_dlg.ui \
    t4selfgate_agata_psa_dlg.ui \
    t4selfgate_selector.ui \
    t4pattern_defining_dlg.ui \
    t4update_info_dlg.ui \
    tgui_options.ui \
    t4interesting_ranges_galileo.ui \
    t4good_galileo_ge_dlg.ui \
    t4selfgate_ge_cristal_galileo.ui \
    tgalileo_signals_dlg.ui \
    tcalibration_factors_dlg.ui

#IMAGES	= images/tracking2.jpeg \
#        images/zarowka.png \
#        images/literaK.png \
#        images/krakow.jpg \
#        images/strzala_prawo_all.png \
#        images/strzala_prawo.png \
#        images/strzala_lewo.png \
#        images/print.png \
#        images/fileopen.png \
#        images/filesave.png \
#        images/filenew.png \
#        images/bananas.png \
#        images/clone.png \
#        images/user_spec_wizard.png \
#        images/cond_manager.png \
#        images/spectra_manager.png \
#        images/lupa.png \
#        images/matching.png \
#        images/undo.png \
#        images/print_ps.png \
#        images/user_spec_manager.png \
#        images/rising_doppler.jpeg \
#        images/1d_binning.png \
#        images/do_apply_to_all.png \
#        images/select_spectra.png \
#        images/expand.xpm \
#        images/all_spectrum.xpm \
##        images/all_graph.png \
#        images/projection.png \
#        images/draw_scale.png \
##        images/logo_krak005.jpg \
##        images/logo_krak005_25proc.jpg \
##        images/logo_krak007_z_napisami.jpg \
##        images/start_stop.png \
##        images/start_stop_small.png



OTHER_FILES +=

RESOURCES += \
    greware_icons.qrc







