///////////////////////////////////////////////////////////////////////////////
// HistDir and FiguresDir have to be defined before init_local.C
// mu- --> e- figure numbering conventions:

// Figure 160 : electrons P>100 MeV/c : momentum at VD2
// Figure 161 : electrons P>100 MeV/c : time at VD2
// Figure 260 : electrons P>100 MeV/c : momentum at VD6.
// Figure 261 : electrons P>100 MeV/c : time at VD6
// Figure 360 : electrons P>100 MeV/c : momentum at VD9
// Figure 361 : electrons P>100 MeV/c : time at VD9
// Figure 362 : electrons P>100 MeV/c : tan_th at VD9
//
// su2020_HistDir is defined n .rootrc
// ----------------------------------------

const char* NoteRepo         = "mu2e-40523.su2020_beam_electrons";
char su2020_HistDir [500]    = "/projects/mu2e/hist/su2020" ;
char mdc2020_HistDir[500]    = "/projects/mu2e/hist/mdc2020";

#include <stdio.h>
#include <string.h>
#include "Stntuple/scripts/stn_catalog.hh"
#include "Stntuple/scripts/plot_hist_1D.C"
#include "Stntuple/scripts/plot_hist_2D.C"

stn_catalog*   catalog;

#include "su2020/ana/scripts/init_su2020_datasets.C"

#include "make_periodic_histograms.C"
#include "plot_proton_pulse_shape.C"
#include "plot_stopped_particles.C"
#include "plot_muon_beam_at_vd9.C"
#include "plot_oot_particles.C"
#include "plot_decays_in_flight.C"
#include "plot_muon_scattering.C"
//-----------------------------------------------------------------------------
void init() {
  stn_book* book;

  catalog = new stn_catalog("my");
//-----------------------------------------------------------------------------
// initialize directories -- mu2e.NotesDir and mu2e.HistDir are assumed to be defined
// in the local .rootrc
//-----------------------------------------------------------------------------
  const char* notes_dir = gEnv->GetValue("mu2e.NotesDir","./");
  printf("notes_dir: %s\n",notes_dir);
  gEnv->SetValue("FiguresDir",Form("%s/%s/figures",notes_dir,NoteRepo));

  const char* hist_dir  = gEnv->GetValue("mu2e.HistDir" ,"./");
  sprintf(su2020_HistDir,"%s/su2020",hist_dir);
  printf("su2020_HistDir: %s\n",su2020_HistDir);
//-----------------------------------------------------------------------------
// initialize books and datasets
//-----------------------------------------------------------------------------
  book = new stn_book("su2020",su2020_HistDir);
  init_su2020_datasets(book);
  catalog->AddBook(book);
  
  printf(" after init_local\n");

  printf(" after init_channels\n");
}

//-----------------------------------------------------------------------------
void plot(int Figure, int Print = 0, const char* Format = "eps") {
  init();
//-----------------------------------------------------------------------------
// Figure 160 : 
//-----------------------------------------------------------------------------
  if (Figure == 160) {
    plot_data_t          p(2);
    
    const char* dsid   = "su2020.bmum0s16b0";
    const char* dsid2  = "su2020.bmum0s26b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_102/mom");
    p.hd[0].fNewName       = "bmum0s16b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_102/mom");
    p.hd[1].fNewName       = "bmum0s26b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "end of Stage2"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "P_{e}, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons produced upstream TS31 coll";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s16b0_vdet_102_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 161 : time at VD2
//-----------------------------------------------------------------------------
  else if (Figure == 161) {
    plot_data_t          p(2);
    
    const char* dsid   = "su2020.bmum0s16b0";
    const char* dsid2  = "su2020.bmum0s26b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_102/time");
    p.hd[0].fNewName       = "bmum0s16b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_102/time");
    p.hd[1].fNewName       = "bmum0s26b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "end of Stage2"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "time, ns";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons produced upstream TS31 coll";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s16b0_vdet_102_time",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 260 : momentum at VD6
//-----------------------------------------------------------------------------
  else if (Figure == 260) {
    plot_data_t          p(2);
    
    const char* dsid   = "su2020.bmum0s26b0";
    const char* dsid2  = "su2020.bmum0s28b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_106/mom");
    p.hd[0].fNewName       = "bmum0s26b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_106/mom");
    p.hd[1].fNewName       = "bmum0s28b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "P_{e}, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons in the end of Stage 2";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s26b0_vdet_106_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 261 : time at VD6
//-----------------------------------------------------------------------------
  else if (Figure == 261) {
    plot_data_t          p(2);
    
    const char* dsid   = "su2020.bmum0s26b0";
    const char* dsid2  = "su2020.bmum0s28b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_106/time");
    p.hd[0].fNewName       = "bmum0s26b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_106/time");
    p.hd[1].fNewName       = "bmum0s28b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "Time, ns";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons in the end of Stage 2";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s26b0_vdet_106_time",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 360 : momentum at VD9
//-----------------------------------------------------------------------------
  else if (Figure == 360) {
    plot_data_t          p(3);
    
    const char* dsid   = "su2020.bmum0s36b0";
    const char* dsid2  = "su2020.bmum0s38b0";
    const char* dsid3  = "su2020.bmum0s39b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_109/mom");
    p.hd[0].fNewName       = "bmum0s36b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_109/mom");
    p.hd[1].fNewName       = "bmum0s38b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid3,"spmc_ana.0000","murat_SpmcAna","vdet_109/mom");
    p.hd[2].fNewName       = "bmum0s39b0";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "e^{-} produced at Stage3";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kGreen+2;
    p.hd[2].fLineColor     = kGreen+2;
    p.hd[2].fFillStyle     = 3004;
    p.hd[2].fFillColor     = kGreen+1;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at VD9";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s36b0_vdet_109_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 361 : time at VD9
//-----------------------------------------------------------------------------
  else if (Figure == 361) {
    plot_data_t          p(3);
    
    const char* dsid   = "su2020.bmum0s36b0";
    const char* dsid2  = "su2020.bmum0s38b0";
    const char* dsid3  = "su2020.bmum0s39b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_109/time");
    p.hd[0].fNewName       = "bmum0s36b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_109/time");
    p.hd[1].fNewName       = "bmum0s38b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid3,"spmc_ana.0000","murat_SpmcAna","vdet_109/time");
    p.hd[2].fNewName       = "bmum0s39b0";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "e^{-} produced at Stage3";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kGreen+2;
    p.hd[2].fLineColor     = kGreen+2;
    p.hd[2].fFillStyle     = 3004;
    p.hd[2].fFillColor     = kGreen+1;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "Time, ns";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at VD9";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s36b0_vdet_109_time",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 362 : tan_th at VD9
//-----------------------------------------------------------------------------
  else if (Figure == 362) {
    plot_data_t          p(3);
    
    const char* dsid   = "su2020.bmum0s36b0";
    const char* dsid2  = "su2020.bmum0s38b0";
    const char* dsid3  = "su2020.bmum0s39b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_109/tan_th");
    p.hd[0].fNewName       = "bmum0s36b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_109/tan_th");
    p.hd[1].fNewName       = "bmum0s38b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3005;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid3,"spmc_ana.0000","murat_SpmcAna","vdet_109/tan_th");
    p.hd[2].fNewName       = "bmum0s39b0";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "e^{-} produced at Stage3";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kGreen+2;
    p.hd[2].fLineColor     = kGreen+2;
    p.hd[2].fFillStyle     = 3004;
    p.hd[2].fFillColor     = kGreen+1;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          =  1.;
    p.fXAxisTitle    = "#tan #Theta";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at VD9";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s36b0_vdet_109_tan_th",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 560 : cos_th_vs_mom_1 at the detector envelope for bmum0s56b0
//-----------------------------------------------------------------------------
  else if (Figure == 560) {
    plot_data_t          p(1);
    
    const char* dsid   = "su2020.bmum0s56b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    p.hd[0].fNewName       = "bmum0s56b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    // p.hd[0].fMarkerColor   = kRed+1;
    // p.hd[0].fLineColor     = kRed+1;
    // p.hd[0].fFillStyle     = 3005;
    // p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.8;

    p.fYLogScale     =  0;
    p.fXMin          =  00.;
    p.fXMax          =  200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at the detector envelope";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasSizeX   = 850;
    p.fCanvasSizeY   = 800;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s56b0_spmc_1_cth_vs_mom_1",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 580 : cos_th_vs_mom_1 at the detector envelope for bmum0s58b0
//-----------------------------------------------------------------------------
  else if (Figure == 580) {
    plot_data_t          p(1);
    
    const char* dsid   = "su2020.bmum0s58b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    p.hd[0].fNewName       = "bmum0s58b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage2";
    p.hd[0].fLabelFontSize = 0.04;
    // p.hd[0].fMarkerColor   = kRed+1;
    // p.hd[0].fLineColor     = kRed+1;
    // p.hd[0].fFillStyle     = 3005;
    // p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.8;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          =  200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at the detector envelope";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasSizeX   = 850;
    p.fCanvasSizeY   = 800;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s58b0_spmc_1_cth_vs_mom_1",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 590 : cos_th_vs_mom_1 at the detector envelope for bmum0s59b0
//-----------------------------------------------------------------------------
  else if (Figure == 590) {
    plot_data_t          p(1);
    
    const char* dsid   = "su2020.bmum0s59b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    p.hd[0].fNewName       = "bmum0s59b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage3";
    p.hd[0].fLabelFontSize = 0.04;
    // p.hd[0].fMarkerColor   = kRed+1;
    // p.hd[0].fLineColor     = kRed+1;
    // p.hd[0].fFillStyle     = 3005;
    // p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.8;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          =  200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at the detector envelope";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasSizeX   = 850;
    p.fCanvasSizeY   = 800;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s59b0_spmc_1_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 1561 : mom at the detector envelope  , three sources
//-----------------------------------------------------------------------------
  else if (Figure == 1561) {
    plot_data_t          p(3);
    TH2F*                h2;
    
    const char* dsid   = "su2020.bmum0s56b0";
    const char* dsid2  = "su2020.bmum0s58b0";
    const char* dsid3  = "su2020.bmum0s59b0";

    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[0].fHist;
    p.hd[0].fHist          = h2->ProjectionX("h_px_56",51,86);
    p.hd[0].fNewName       = "bmum0s56b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 3001;
    p.hd[0].fFillColor     = kBlue+2;
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.8;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[1].fHist;
    p.hd[1].fHist          = h2->ProjectionX("h_px_58",51,86);
    p.hd[1].fNewName       = "bmum0s58b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fLineColor     = kRed+1;
    p.hd[1].fFillStyle     = 3004;
    p.hd[1].fFillColor     = kRed+1;
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.8;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid3,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[2].fHist;
    p.hd[2].fHist          = h2->ProjectionX("h_px_59",51,86);
    
    p.hd[2].fNewName       = "bmum0s59b0";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "e^{-} produced at Stage3";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fLineColor     = kBlue+1;
    p.hd[2].fFillStyle     = 3005;
    p.hd[2].fFillColor     = kBlue+1;
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.8;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          =  200.;
    p.fYMax          =  50.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at the detector envelope";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasSizeX   = 850;
    p.fCanvasSizeY   = 800;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s59b0_spmc_1_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 1562 : mom at the detector envelope  , three sources 70 < P < 120)
//-----------------------------------------------------------------------------
  else if (Figure == 1562) {
    plot_data_t          p(3);
    TH2F*                h2;
    
    const char* dsid   = "su2020.bmum0s56b0";
    const char* dsid2  = "su2020.bmum0s58b0";
    const char* dsid3  = "su2020.bmum0s59b0";

    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[0].fHist;
    p.hd[0].fHist          = h2->ProjectionX("h_px_56",51,86);
    p.hd[0].fNewName       = "bmum0s56b0";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} produced at Stage1";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 3001;
    p.hd[0].fFillColor     = kBlue+2;
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.8;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[1].fHist;
    p.hd[1].fHist          = h2->ProjectionX("h_px_58",51,86);
    p.hd[1].fNewName       = "bmum0s58b0";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "e^{-} produced at Stage2";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fLineColor     = kRed+1;
    p.hd[1].fFillStyle     = 3004;
    p.hd[1].fFillColor     = kRed+1;
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.8;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid3,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    h2                     = (TH2F*) p.hd[2].fHist;
    p.hd[2].fHist          = h2->ProjectionX("h_px_59",51,86);
    
    p.hd[2].fNewName       = "bmum0s59b0";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "e^{-} produced at Stage3";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fLineColor     = kBlue+1;
    p.hd[2].fFillStyle     = 3005;
    p.hd[2].fFillColor     = kBlue+1;
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.8;

    p.fYLogScale     =  0;
    p.fXMin          =  70.;
    p.fXMax          =  120.;
    p.fYMax          =  50.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "P>100 MeV/c electrons at the detector envelope";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.6; p.fLegendYMax = 0.7;
    p.fCanvasSizeX   = 850;
    p.fCanvasSizeY   = 800;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s59b0_spmc_1_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
  else if ((Figure >= 3100) and (Figure < 3200)) {
    plot_stopped_particles(Figure,Print,Format);
  }
  else if ((Figure >= 3200) and (Figure < 3300)) {
    plot_oot_particles(Figure,Print,Format);
  }
  else if ((Figure >= 3700) and (Figure < 3800)) {
    plot_muon_beam_at_vd9(Figure,Print,Format);
  }
  else if ((Figure >= 4000) and (Figure < 4100)) {
    plot_decays_in_flight(Figure,Print,Format);
  }
  else if ((Figure >= 4100) and (Figure < 4200)) {
    plot_muon_scattering(Figure,Print,Format);
  }
  else {
    printf (" ERROR unknown Figure: %6i\n",Figure);
    return;
  }
}
