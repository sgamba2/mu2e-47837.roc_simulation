///////////////////////////////////////////////////////////////////////////////
// muon beam at VD9 : bmum0s37b0
//
// only to be included by plot.C
//
// Figure 4000 : beam particle momentum at VD10
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
void plot_decays_in_flight(int Figure, int Print, const char* Format) {
//-----------------------------------------------------------------------------
// Figure 4000 : beam particle momentum at VD10
//-----------------------------------------------------------------------------
  if (Figure == 4000) {
    plot_data_t          p(1);
    
    const char* dsid   = "su2020.bmum0s5bb0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    p.hd[0].fNewName       = "ele";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} entering the detector envelope"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = 1; // kRed+1;
    p.hd[0].fMarkerStyle   = 2; // kRed+1;
    p.hd[0].fLineColor     = 1; // kRed+1;
    p.hd[0].fFillStyle     = 0; // 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.6;

    p.fYLogScale           =  0;
    p.fXMin                =  0.;
    p.fXMax                = 200.;
    p.fXAxisTitle          = "P, MeV/c";
    p.fYTitFormat          = "cos #theta";
    p.fLabel               = "#mu^{-} decays in flight";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.55; p.fLegendYMin = 0.4; p.fLegendYMax = 0.45;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fName                = Form("figure_%05i_bmum0s5bb0_spmc_1_cth_vs_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    TPave* pave = new TPave(100,0,200,0.707);
    pave->SetBorderSize(1);
    pave->SetFillColor(kRed+2);
    pave->SetFillStyle(3005);
    pave->Draw();
    
    if (Print > 0) p.print();
  }
//-----------------------------------------------------------------------------
// Figure 4001 : beam particle momentum at VD10
//-----------------------------------------------------------------------------
  else if (Figure == 4001) {
    plot_data_t          p(1);
    
    const char* dsid   = "su2020.bmum0s5bb0";

    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","spmc_1/cth_vs_mom_1");
    TH2F* h2               = (TH2F*) p.hd[0].fHist;
    p.hd[0]                = h2->ProjectionX("h_4001_px",51,85);
    p.hd[0].fNewName       = "ele";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "e^{-} entering the detector envelope"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = 1; // kRed+1;
    p.hd[0].fMarkerStyle   = 2; // kRed+1;
    p.hd[0].fLineColor     = 1; // kRed+1;
    p.hd[0].fFillStyle     = 0; // 3005;
    p.hd[0].fFillColor     = 1; // kRed+1;
    p.hd[0].fDrawOpt       = "hist,pe";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.6;

    p.fYLogScale           =  1;
    p.fXMin                =  60.;
    p.fXMax                = 110.;
    p.fXAxisTitle          = "P, MeV/c";
    p.fYTitFormat          = "cos #theta";
    p.fLabel               = "#mu^{-} decays in flight";
    p.fLabelXMin           = 0.15;
    p.fLegendXMin          = 0.15; p.fLegendXMax = 0.55; p.fLegendYMin = 0.7; p.fLegendYMax = 0.75;
    p.fCanvasName          = Form("Figure_%04i",Figure);
    p.fName                = Form("figure_%05i_bmum0s5bb0_spmc_1_cth_vs_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    
    p.hd[0].fHist->Fit("expo","c","pe",90,100);
    p.hd[0].fHist->GetXaxis()->SetRangeUser(60,110);

    p.fCanvas->Modified();
    p.fCanvas->Update();

    if (Print > 0) p.print();
  }
}
