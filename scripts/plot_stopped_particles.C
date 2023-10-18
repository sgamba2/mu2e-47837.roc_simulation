///////////////////////////////////////////////////////////////////////////////
// muon beam at VD9 : bmum0s37b0
//
// only to be included by plot.C
//
// Figure 3100 : beam particle momentum at VD9 for different particle species
// Figure 3101 : stopped and total particle momentum at VD7
// Figure 3103 : X:Y at at VD9 for stopped mu-
// Figure 3104 : X:Y at at VD9 for stopped mu+
// Figure 3105 : X:Y at a stop point for stopped mu-
// Figure 3106 : X:Y at a stop point for stopped mu+
// Figure 3150 : time distribution (combined)
// Figure 3160 : combined timing distribution
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
void plot_stopped_particles(int Figure, int Print, const char* Format) {
//-----------------------------------------------------------------------------
// Figure 3100 : beam particle momentum at VD9
//-----------------------------------------------------------------------------
  if (Figure == 3100) {
    plot_data_t          p(3);
    
    const char* dsid   = "su2020.bmum0s31b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_309/mom");
    p.hd[0].fNewName       = "mu-";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "mu-"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 0; // 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_409/mom");
    p.hd[1].fNewName       = "mu+";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "mu+"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 0;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_1009/mom");
    p.hd[2].fNewName       = "pi-";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "pi-"; // "mom";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kBlue+2;
    p.hd[2].fLineColor     = kBlue+2;
    p.hd[2].fFillStyle     = 3003;
    p.hd[2].fFillColor     = kBlue+1;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;

    p.fYLogScale     =  1;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "stopped beam particles in front of the ST (at VD9)";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.20; p.fLegendXMax = 0.35; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s31b0_vdet_xx09_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3101 : stopped and total particle momentum at VD7
//-----------------------------------------------------------------------------
  if (Figure == 3101) {
    plot_data_t          p(3);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    const char* dsid2   = "su2020.bmum0s32b0";   // stopped outside the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_307/mom");
    p.hd[0].fNewName       = "oot_vd7";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "OOT mu- at VD7"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_309/mom");
    p.hd[1].fNewName       = "oot_vd9";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "OOT mu- at VD9"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 3004;
    p.hd[1].fFillColor     = kBlue+1;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_309/mom");
    p.hd[2].fNewName       = "tgt_vd9";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "TGT mu- at VD9"; // "mom";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kRed+1;
    p.hd[2].fLineColor     = kRed+1;
    p.hd[2].fFillStyle     = 3005; // 3005;
    p.hd[2].fFillColor     = kRed+1;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;


    p.fYLogScale           =  0;
    p.fXMin                =  0.;
    p.fXMax                = 200.;
    p.fXAxisTitle          = "P, MeV/c";
    p.fYTitFormat          = "";
    p.fLabel               = "beam mu- in front of the ST (at VD9)";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.50; p.fLegendXMax = 0.70; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fName                = Form("figure_%05i_bmum0s31b0_vdet_x309_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3103 : X:Y at at VD9 for stopped mu-
//-----------------------------------------------------------------------------
  if (Figure == 3103) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_309/y_vs_x");
    p.hd[0].fNewName       = "tgt_mum";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "TGT mu- at VD9"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "col";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.fYLogScale           =  0;
    // p.fXMin                =  0.;
    // p.fXMax                = 200.;
    p.fXAxisTitle          = "X, mm";
    p.fYTitFormat          = "";
    p.fLabel               = "beam mu- in front of the ST (at VD9)";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         =  900;
    p.fCanvasSizeY         =  950;
    p.fName                = Form("figure_%05i_bmum0s31b0_vdet_309_y_vs_x",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3104 : X:Y at at VD9 for stopped mu-
//-----------------------------------------------------------------------------
  if (Figure == 3104) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_409/y_vs_x");
    p.hd[0].fNewName       = "tgt_mup";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "TGT mu+ at VD9"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "col";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.fYLogScale           =  0;
    // p.fXMin                =  0.;
    // p.fXMax                = 200.;
    p.fXAxisTitle          = "X, mm";
    p.fYTitFormat          = "";
    p.fLabel               = "beam mu+ in front of the ST (at VD9)";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         =  900;
    p.fCanvasSizeY         =  950;
    p.fName                = Form("figure_%05i_bmum0s31b0_vdet_409_y_vs_x",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3105 : X:Y stop points stopped mu-
//-----------------------------------------------------------------------------
  if (Figure == 3105) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","simp_603/y_vs_x");
    p.hd[0].fNewName       = "tgt_mum";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "TGT mu- stops"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "col";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.fYLogScale           =  0;
    // p.fXMin                =  0.;
    // p.fXMax                = 200.;
    p.fXAxisTitle          = "X, mm";
    p.fYTitFormat          = "";
    p.fLabel               = "mu- stop coordinates";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         =  900;
    p.fCanvasSizeY         =  930;
    p.fName                = Form("figure_%05i_bmum0s31b0_simp_603_y_vs_x",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3106 : X:Y stop points stopped mu+
//-----------------------------------------------------------------------------
  if (Figure == 3106) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","simp_604/y_vs_x");
    p.hd[0].fNewName       = "tgt_muplus";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "TGT mu+ stops"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "col";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.fYLogScale           =  0;
    // p.fXMin                =  0.;
    // p.fXMax                = 200.;
    p.fXAxisTitle          = "X, mm";
    p.fYTitFormat          = "";
    p.fLabel               = "mu+ stop coordinates";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         =  900;
    p.fCanvasSizeY         =  930;
    p.fName                = Form("figure_%05i_bmum0s31b0_simp_604_y_vs_x",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3106 : X:Y stop points stopped mu+
//-----------------------------------------------------------------------------
  if (Figure == 3106) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.bmum0s31b0";   // stopped in the ST
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","simp_604/y_vs_x");
    p.hd[0].fNewName       = "tgt_muplus";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "TGT mu+ stops"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kBlue+2;
    p.hd[0].fLineColor     = kBlue+2;
    p.hd[0].fFillStyle     = 0;
    p.hd[0].fFillColor     = kBlue+1;
    p.hd[0].fDrawOpt       = "col";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.fYLogScale           = 0;
    p.fStats               = 0;
    // p.fXMin                =  0.;
    // p.fXMax                = 200.;
    p.fXAxisTitle          = "X, mm";
    p.fYTitFormat          = "";
    p.fLabel               = "mu+ stop coordinates";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         =  900;
    p.fCanvasSizeY         =  930;
    p.fName                = Form("figure_%05i_bmum0s31b0_simp_604_y_vs_x",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3150 : proton pulse timing
//-----------------------------------------------------------------------------
  if (Figure == 3150) {
    plot_data_t          p(1);
    
    const char* dsid    = "su2020.flsh0s36b0";   // beam flash, 2.5e6, at VD9 with the smeared timing
    const char* dsid2   = "su2020.bmum0s3cb0";   // muon beam,  1e9  , at VD9 with the smeared timing

    int npulses = 2;
    TH1F* h_ppt(nullptr);
  
    make_proton_pulse_hist(h_ppt,2);
    p.hd[0]                = hist_data_t(h_ppt);
    p.hd[0].fNewName       = "";
    p.hd[0].fLineColor     = kRed+2;
    p.hd[0].fFillStyle     = 3003;
    p.hd[0].fFillColor     = kRed+2;
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;
    p.hd[0].fMarkerColor   = kRed+2;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fOptStat       = 0;
    p.hd[0].fStats         = 0;
    p.hd[0].fLumiSF        = 1.6e7;   // integral over pulse was set to 1.

    p.fYLogScale           =  0;
    p.fXMin                =  -300.;
    p.fXMax                = 2000.;
    p.fYMax                = 6.e5;
    p.fXAxisTitle          = "time, ns";
    p.fYTitFormat          = "";
    p.fLabel               = "time at VD9";
    p.fStats               = 0;
    p.fOptStat             = 0;
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.45; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fName                = Form("figure_%05i_proton_pulse_ime",Figure);

    plot_hist_1d(&p,-1,Format);

    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 3160 : combined timing distribution
//-----------------------------------------------------------------------------
  if (Figure == 3160) {
    plot_data_t          p(5);
    
    const char* dsid    = "su2020.flsh0s36b0";   // beam flash, 2.5e6, at VD9 with the smeared timing
    const char* dsid2   = "su2020.bmum0s3cb0";   // muon beam,  1e9  , at VD9 with the smeared timing
//-----------------------------------------------------------------------------
// proton pulse
//-----------------------------------------------------------------------------
    int npulses = 2;
    TH1F* h_ppt(nullptr);
    make_proton_pulse_hist(h_ppt,2,1.6e7);
    h_ppt->Rebin(5);
    p.hd[0]                = hist_data_t(h_ppt);
    p.hd[0].fNewName       = "";
    p.hd[0].fLabel         = "proton pulse arrival at the production target";
    p.hd[0].fLineColor     = kGray+2;
    p.hd[0].fLineWidth     = 2;
    p.hd[0].fFillStyle     = 3013;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fFillColor     = kGray+2;
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;
    p.hd[0].fMarkerColor   = kGray+2;
    p.hd[0].fOptStat       = 0;
    p.hd[0].fStats         = 0;
    p.hd[0].fHist->GetXaxis()->SetLabelSize(0.05);
    p.hd[0].fHist->GetXaxis()->SetTitleSize(0.05);
    p.hd[0].fHist->GetYaxis()->SetLabelSize(0.05);
    p.hd[0].fHist->GetYaxis()->SetTitleSize(0.05);
    p.hd[0].fHist->GetYaxis()->SetTitleOffset(0.6);
//-----------------------------------------------------------------------------
// beam flash
//-----------------------------------------------------------------------------
    float sf_flash = 4;
    
    TH1F* h_bf(nullptr);
    make_beam_flash_hist(h_bf,-1,1);
    p.hd[1]                = hist_data_t(h_bf);
    p.hd[1].fNewName       = "flash";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = Form("beam flash arrival at the stopping target (#times%i)",(int) sf_flash);
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue-9;
    p.hd[1].fLineColor     = kBlue-9;
    p.hd[1].fLineWidth     = 2;
    p.hd[1].fFillStyle     = 3013;
    p.hd[1].fFillColor     = kBlue-9;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;
//-----------------------------------------------------------------------------
// flsh0 simulation used 2.5e6 POT, renormalize to the low lumi mode pulse
// scale up by x5 for presentation purposes
//-----------------------------------------------------------------------------
    p.hd[1].fLumiSF        = (1.6e7/2.5e6)*sf_flash;
    p.hd[1].fStats         = 0;

//-----------------------------------------------------------------------------
// pions at VD9
//-----------------------------------------------------------------------------
    float sf_pions_vd9 = 7e4;
    TH1F* h_pi(nullptr);
    make_pion_vd9_hist(h_pi,-1,1);
    p.hd[2]                = hist_data_t(h_pi);
    // p.hd[2]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_1009/time");
    p.hd[2].fNewName       = "pi-";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = Form("#pi^{-} arrival at the stopping target (#times%i,000)",(int)(sf_pions_vd9/1000));
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kBlue+2;
    p.hd[2].fLineColor     = kBlue+2;
    p.hd[2].fLineWidth     = 2;
    p.hd[2].fFillStyle     = 0;
    p.hd[2].fFillColor     = kBlue+2;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;
    p.hd[2].fOptStat       = 0;
    p.hd[2].fStats         = 0;
//-----------------------------------------------------------------------------
// pion distribution is normalized to 1.6e7 and additionally scaled up by a factor 100,000 
//-----------------------------------------------------------------------------
    p.hd[2].fLumiSF        = (1./62.5)*sf_pions_vd9;
//-----------------------------------------------------------------------------
// muons at VD9
//-----------------------------------------------------------------------------
    float sf_muons_vd9     = 300.;
    TH1F* h_mu(nullptr);
    make_muon_vd9_hist(h_mu,-1,1);
    p.hd[3]                = hist_data_t(h_mu);
    // p.hd[3]                = hist_data_t(catalog,"su2020",dsid2,"spmc_ana.0000","murat_SpmcAna","vdet_309/time");
    p.hd[3].fNewName       = "mu-";
    p.hd[3].fRebin         =  1;
    p.hd[3].fLabel         = Form("#mu^{-} arrival at stopping target (#times%i)",(int)sf_muons_vd9);
    p.hd[3].fLabelFontSize = 0.05;
    p.hd[3].fMarkerColor   = kRed+2;
    p.hd[3].fLineColor     = kRed+2;
    p.hd[3].fLineWidth     = 2;
    p.hd[3].fFillStyle     = 0;
    p.hd[3].fFillColor     = kRed+2;
    p.hd[3].fDrawOpt       = "hist";
    p.hd[3].fMarkerStyle   = 20;
    p.hd[3].fMarkerSize    = 0.3;
    p.hd[3].fOptStat       = 0;
    p.hd[3].fStats         = 0;
//-----------------------------------------------------------------------------
// bmum0 generation used 1e9 POT ; 1e9/1.6e7 = 62.5
// so to normalize a bmum0 histogram to 1.6e7 POT, need to scale it by 1/62.5
// for presentation purposes, scale muon histogram by x400
//-----------------------------------------------------------------------------
    p.hd[3].fLumiSF        = (sf_muons_vd9/62.5);
//-----------------------------------------------------------------------------
// stopped muons
//-----------------------------------------------------------------------------
    float sf_stopped_muons = 1000;
    TH1F* h_bmdt(nullptr);
    make_bound_muon_decay_hist(h_bmdt,1000000,-1,1);
    p.hd[4]                = hist_data_t(h_bmdt);
    p.hd[4].fLabel         = Form("#mu^{-} decays/captures in the stopping target (#times%4.0f)",sf_stopped_muons);
    p.hd[4].fDrawOpt       = "hist";
    p.hd[4].fLineColor     = kRed+2;
    p.hd[4].fFillStyle     = 3013;
    p.hd[4].fFillColor     = kRed+2;
    p.hd[4].fOptStat       = 0;
    p.hd[4].fNewName       = "";
    p.hd[4].fStats         = 0;
//-----------------------------------------------------------------------------
// h_bmdt is normalized to an integral of one
// normalization to the proton pulse: 1.6e7*1.59e-3 (plus scale up by 'lumi_sf' for presentation)
//-----------------------------------------------------------------------------
    p.hd[4].fLumiSF        = 2.54e4*sf_stopped_muons;
    
    p.fYLogScale           =  0;
    p.fXMin                =  -300.;
    p.fXMax                = 2000.;
    p.fYMin                = 1.e-2;
    p.fYMax                = 3.e6;
    p.fXAxisTitle          = "Time (ns)";
    p.fYTitFormat          = "N / 10 ns";
    p.fLabel               = "Mu2e simulation, 1.6 #times 10^{7} protons / pulse";
    p.fLabelFontSize       = 0.045;
    p.fStats               = 0;
    p.fOptStat             = 0;
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.35; p.fLegendXMax = 0.65; p.fLegendYMin = 0.5; p.fLegendYMax = 0.80;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fCanvasSizeX         = 1700;
    p.fCanvasSizeY         = 550;
    p.fName                = Form("figure_%05i_flsh0s36b0_vdet_9_time",Figure);

    plot_hist_1d(&p,-1,Format);

    TPaveLabel* pave = new TPaveLabel(640.,1e3,1650,700e3,"delayed live-time window");
    pave->SetBorderSize(1);
    pave->SetLineColor(1); //kYellow-3);
    pave->SetFillColor(kYellow-3);
    pave->SetTextFont(42);
    pave->SetTextSize(0.35);
    pave->SetFillStyle(3005);
    pave->Draw();

    p.fCanvas->Modified();
    p.fCanvas->Update();
    
    if (Print > 0) p.print();
  }
}
