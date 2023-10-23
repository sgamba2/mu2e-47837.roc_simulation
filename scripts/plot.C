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

const char* NoteRepo         = "mu2e-xxxxx.roc_simulation";
char vst_HistDir [500]    = "/projects/tracker/vst" ;

//char mdc2020_HistDir[500]    = "/projects/mu2e/hist";

#include <stdio.h>
#include <string.h>

#include "plot_hist_1D.C"


stn_catalog*   catalog;


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

  const char* hist_dir  = gEnv->GetValue("mu2e.TrkVstDataDir" ,".");
  sprintf(vst_HistDir,"%s/hist",hist_dir);
//-----------------------------------------------------------------------------
// initialize books and datasets
//-----------------------------------------------------------------------------
  // book = new stn_book("su2020",su2020_HistDir);
  // init_su2020_datasets(book);
  // catalog->AddBook(book);
  
  printf(" after init_local\n");

  printf(" after init_channels\n");
}

//-----------------------------------------------------------------------------
void plot(int Figure, int Print = 1, const char* Format = "pdf") {
  init();
//-----------------------------------------------------------------------------
// Figure 2 : 
//-----------------------------------------------------------------------------
  if (Figure == 2) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/nh_vs_adc_1");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN105023-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.105023.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/nh_vs_adc");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN105023-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 100.;
    p.fXAxisTitle    = "channel";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Occupancy: nhits vs channel number - new order";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_nhitsvschannel_roc_simulation_2",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 1 : 
//-----------------------------------------------------------------------------
  else if (Figure == 1) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/frag_0/ch_00/ch_00_time0");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN105023-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     /*TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.105023.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/ch_00/time_00");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN105023-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;*/
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 30.;
    p.fXAxisTitle    = "Time [ns]";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Time distribution: data and MC for channel 0 - 1st FPGA";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_timedistr_roc_simulation_1",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
  else if (Figure == 3) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.000281.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/frag_0/ch_02/ch_02_time0");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN281-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     /*TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.105023.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/ch_00/time_00");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN105023-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;*/
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 70.;
    p.fYMin          = 1.e2;
    p.fYMax          = 2.e4;
    p.fXAxisTitle    = "Time [ns]";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Time distribution: data and MC for channel 2 - 2nd FPGA";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_timedistr_roc_simulation_ch2",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
  else if (Figure == 4) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.000281.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/nh_vs_adc_1");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN281-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.000281.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/nh_vs_adc");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN281-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 100.;
    p.fXAxisTitle    = "channel";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Occupancy: nhits vs channel number - new order";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_nhitsvschannel_roc_simulation_2",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//--
  else if (Figure == 5) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.000281.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/nhits");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN281-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.000281.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/nrh_tot");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN281-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          =300.;
    p.fXAxisTitle    = "nhits";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Number of hits";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_nhits_5",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
  else if (Figure == 6) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.000281.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/nbtot");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN281-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     /* TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.000281.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/nh_vs_adc");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN281-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;*/
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 9000.;
    p.fXAxisTitle    = "Bytes [Bytes]";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Number of total bytes for the events";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_nbytes_6",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
 else if (Figure == 7) {
    plot_data_t          p(2);
    
    // const char* dsid   = "su2020.bmum0s16b0";
    // const char* dsid2  = "su2020.bmum0s26b0";
    
    TFile* f1 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.000281.hist");
    TH1F* h1 = (TH1F *)f1->Get("TrkFragmentAna/trk/frag_0/ch_00/ch_00_time0");

    p.hd[0]                = hist_data_t(h1,"job1","gamba_roc_data");

    p.hd[0].fNewName       = "RUN281-data";
    // p.hd[0].fRebin         =  1;
    // p.hd[0].fLabel         = "end of Stage1"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
     p.hd[0].fMarkerColor   = kRed+1;
     p.hd[0].fLineColor     = kRed+1;
     p.hd[0].fFillStyle     = 3005;
     p.hd[0].fFillColor     = kRed+1;
     p.hd[0].fDrawOpt       = "hist";
     p.hd[0].fMarkerStyle   = 20;
     p.hd[0].fMarkerSize    = 0.3;

     /*TFile* f2 = TFile::Open("/srv/mu2e/data/projects/tracker/vst/hist/rocsim/rocsim.105023.hist");//"/srv/mu2e/data/projects/tracker/vst/hist/trkvst.annex.trk_fragment_ana.105023.hist"
     TH1F* h2 = (TH1F *)f2->Get("rocsim/Hist/ch_00/time_00");

    p.hd[1]                = hist_data_t(h2,"job2","gamba_roc_simulation");
    p.hd[1].fNewName       = "RUN105023-MC";
    // p.hd[1].fRebin         =  1;
    // p.hd[1].fLabel         = "end of Stage2"; // "mom";
     p.hd[1].fLabelFontSize = 0.04;
     p.hd[1].fMarkerColor   = kBlue+2;
     p.hd[1].fLineColor     = kBlue+2;
     p.hd[1].fFillStyle     = 3004;
     p.hd[1].fFillColor     = kBlue+1;
     p.hd[1].fDrawOpt       = "hist";
     p.hd[1].fMarkerStyle   = 20;
     p.hd[1].fMarkerSize    = 0.3;
     p.hd[1].fScale         = 2;*/
    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 70.;
    p.fYMin          = 1.e2;
    p.fYMax          = 2.e4;
    p.fXAxisTitle    = "Time [ns]";
    p.fYAxisTitle    = "counts";
    p.fYTitFormat    = "";
    p.fLabel         = "Time distribution: data and MC for channel 0 - 1st FPGA";
    p.fLabelXMin     = 0.15;
    p.fLabelYMin     = 0.87;
    p.fLegendXMin    = 0.15; p.fLegendXMax = 0.30; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_timedistr_roc_simulation_ch0",Figure);

    plot_hist_1d(&p,1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }

  else {
    printf (" ERROR unknown Figure: %6i\n",Figure);
    return;
  }
}
