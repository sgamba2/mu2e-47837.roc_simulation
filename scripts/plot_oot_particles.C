///////////////////////////////////////////////////////////////////////////////
// muon beam at VD9 : bmum0s37b0
//
// only to be included by plot.C
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
void plot_oot_particles(int Figure, int Print, const char* Format) {
//-----------------------------------------------------------------------------
// Figure 3200 : beam particle momentum at VD10
//-----------------------------------------------------------------------------
  if (Figure == 3200) {
    plot_data_t          p(3);
    
    const char* dsid   = "su2020.bmum0s32b0";
    const char* dsid31 = "su2020.bmum0s31b0";
    
    p.hd[0]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_309/mom");
    p.hd[0].fNewName       = "oot_vd9";
    p.hd[0].fRebin         =  1;
    p.hd[0].fLabel         = "OOT mu- at VD9"; // "mom";
    p.hd[0].fLabelFontSize = 0.04;
    p.hd[0].fMarkerColor   = kRed+1;
    p.hd[0].fLineColor     = kRed+1;
    p.hd[0].fFillStyle     = 0; // 3005;
    p.hd[0].fFillColor     = kRed+1;
    p.hd[0].fDrawOpt       = "hist";
    p.hd[0].fMarkerStyle   = 20;
    p.hd[0].fMarkerSize    = 0.3;

    p.hd[1]                = hist_data_t(catalog,"su2020",dsid,"spmc_ana.0000","murat_SpmcAna","vdet_310/mom");
    p.hd[1].fNewName       = "oot_vd10";
    p.hd[1].fRebin         =  1;
    p.hd[1].fLabel         = "OOT mu- at VD10"; // "mom";
    p.hd[1].fLabelFontSize = 0.04;
    p.hd[1].fMarkerColor   = kBlue+2;
    p.hd[1].fLineColor     = kBlue+2;
    p.hd[1].fFillStyle     = 0;
    p.hd[1].fFillColor     = kBlue+2;
    p.hd[1].fDrawOpt       = "hist";
    p.hd[1].fMarkerStyle   = 20;
    p.hd[1].fMarkerSize    = 0.3;

    p.hd[2]                = hist_data_t(catalog,"su2020",dsid31,"spmc_ana.0000","murat_SpmcAna","vdet_309/mom");
    p.hd[2].fNewName       = "tgt_vd9";
    p.hd[2].fRebin         =  1;
    p.hd[2].fLabel         = "TGT mu- at VD9"; // "mom";
    p.hd[2].fLabelFontSize = 0.04;
    p.hd[2].fMarkerColor   = kRed+2;
    p.hd[2].fLineColor     = kRed+2;
    p.hd[2].fFillStyle     = 3004;
    p.hd[2].fFillColor     = kRed+2;
    p.hd[2].fDrawOpt       = "hist";
    p.hd[2].fMarkerStyle   = 20;
    p.hd[2].fMarkerSize    = 0.3;

    p.fYLogScale     =  0;
    p.fXMin          =  0.;
    p.fXMax          = 200.;
    p.fXAxisTitle    = "P, MeV/c";
    p.fYTitFormat    = "";
    p.fLabel         = "beam mu- reaching VD10";
    p.fLabelXMin     = 0.15;
    p.fLegendXMin    = 0.40; p.fLegendXMax = 0.55; p.fLegendYMin = 0.6; p.fLegendYMax = 0.75;
    p.fCanvasName    = Form("Figure_%04i",Figure);
    p.fName          = Form("figure_%05i_bmum0s32b0_vdet_0310_mom",Figure);

    plot_hist_1d(&p,-1,Format);
    // add whatever else you want
    if (Print > 0) p.print();
  }
}
