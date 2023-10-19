#ifndef __plot_hist_1D__
#define __plot_hist_1D__

#include "TH1.h"
#include "TH2.h"

#include "plot_utilities.hh"
//-----------------------------------------------------------------------------
// compare two histograms with different ModuleName/HistName's from two different files
// HistName like "spmc_1/mom"
//-----------------------------------------------------------------------------
void plot_hist_1D(hist_data_t* Hist1,  hist_data_t*  Hist2, int Print = 0) {

  printf("WARNING: plot_hist_1D(hist_data_t*,...) is OBSOLETE, use plot_hist_1D(plot_data_t*, ...)\n");
  
  char figure_name[200];
//-----------------------------------------------------------------------------
// figure out clone histogram names
//-----------------------------------------------------------------------------
  if ((Hist1->fHist == nullptr) or (Hist2->fHist == nullptr)) {
    printf("plot_hist_1D ERROR: one of the two histograms is a NULL pointer\n");
    return;
  }
  
  TString h1name(Hist1->fName), h2name(Hist2->fName);

  if (Hist1->fNewName == "") h1name.ReplaceAll("/","_");
  else                       h1name = Hist1->fNewName;

  if (Hist2->fNewName == "") h2name.ReplaceAll("/","_");
  else                       h2name = Hist2->fNewName;

  hist_file_t* hf1 = Hist1->fFile;
  hist_file_t* hf2 = Hist2->fFile;
  
  TH1F* hpx1 = (TH1F*) Hist1->fHist->Clone(h1name);

  if (Hist1->fRebin > 0) hpx1->Rebin(Hist1->fRebin);  // rebin, if requested

  if (Hist2->fScale == 3) { //normalize to unity
    double scale = 1./hpx1->Integral();
    hpx1->Scale(scale);
  } else if (Hist1->fScale > 0) hpx1->Scale(Hist1->fScale);  // scale, if requested

  TH1F* hpx2 = (TH1F*) Hist2->fHist->Clone(h2name);

  if (Hist2->fRebin > 0) hpx2->Rebin(Hist2->fRebin);  // rebin, if requested

  //////////////////////////////////////
  stn_dataset_t* ds1(nullptr);
  stn_dataset_t* ds2(nullptr);

  if (hf1) {
    ds1 = hf1->fDataset;
    ds2 = hf2->fDataset;

    if (Hist2->fScale == 1) {
    
      double scale = (ds1->fNGenEvents+0.)/(ds2->fNGenEvents+0.);
      printf("ds1->fNGenEvents, ds2->fNGenEvents, scale: %li %li %f\n",ds1->fNGenEvents, ds2->fNGenEvents, scale);

      hpx2->Scale(scale);
    }
  }
  
  if (Hist2->fScale == 2) {
    double scale = hpx1->Integral()/hpx2->Integral();
    hpx2->Scale(scale);
  }

  if (Hist2->fScale == 3) { //normalize to unity
    double scale = 1./hpx2->Integral();
    hpx2->Scale(scale);
  }
//-----------------------------------------------------------------------------
// create a canvas
//-----------------------------------------------------------------------------
  TString canvas_name;

  if(hf1) {
    canvas_name += ds1->GetName();
    canvas_name += "_";
  }
  canvas_name += Hist1->fModule;
  canvas_name += "_";
  canvas_name += h1name;
  canvas_name += "_vs_";
  canvas_name += Hist2->fModule;
  canvas_name += "_";
  canvas_name += h2name;
  
  if (Hist1->fCanvasName != "") canvas_name = Hist1->fCanvasName;

  int cx = (Hist1->fCanvasSizeX < 0) ? 1200 : Hist1->fCanvasSizeX;
  int cy = (Hist1->fCanvasSizeY < 0) ?  800 : Hist1->fCanvasSizeY;

  TCanvas* c = new TCanvas(canvas_name.Data(),canvas_name.Data(),cx,cy);
  c->SetLogy(Hist1->fYLogScale);
//-----------------------------------------------------------------------------
// the two histograms correspond to slightly different NPOT
//-----------------------------------------------------------------------------
  int col = kRed-3;
  if(Hist1->fLineColor > 0) col =  Hist1->fLineColor;

  hpx1->SetLineColor(col);
  if (Hist1->fLineWidth != 1) hpx1->SetLineWidth(Hist1->fLineWidth);
  hpx1->SetTitle("");

  if (Hist1->fFillStyle >= 0) hpx1->SetFillStyle(Hist1->fFillStyle);
  if (Hist1->fFillColor >= 0) hpx1->SetFillColor(Hist1->fFillColor);

  if (Hist1->fMarkerStyle >=0) hpx1->SetMarkerStyle(Hist1->fMarkerStyle);
  if (Hist1->fMarkerColor >=0) hpx1->SetMarkerColor(Hist1->fMarkerColor);
  if (Hist1->fMarkerSize  >=0) hpx1->SetMarkerSize (Hist1->fMarkerSize );

  if (Hist1->fXMin < Hist1->fXMax) hpx1->GetXaxis()->SetRangeUser(Hist1->fXMin,Hist1->fXMax);
  if (Hist1->fXAxisTitle != ""   ) hpx1->GetXaxis()->SetTitle(Hist1->fXAxisTitle.Data());
  if (Hist1->fAxisFontSize >= 0. ) {
    hpx1->GetXaxis()->SetTitleSize(Hist1->fAxisFontSize);
    hpx1->GetXaxis()->SetLabelSize(Hist1->fAxisFontSize);
    hpx1->GetYaxis()->SetTitleSize(Hist1->fAxisFontSize);
    hpx1->GetYaxis()->SetLabelSize(Hist1->fAxisFontSize);
  }

  if (Hist1->fYMin < Hist1->fYMax) hpx1->GetYaxis()->SetRangeUser(Hist1->fYMin,Hist1->fYMax);
  if (Hist1->fYAxisTitle != ""   ) hpx1->GetYaxis()->SetTitle(Hist1->fYAxisTitle.Data());
  if (Hist1->fStats == 0) hpx1->SetStats(0);

  if (Hist1->fDrawOpt == "") hpx1->Draw("ep");
  else                       hpx1->Draw(Hist1->fDrawOpt.Data());

  hpx2->SetLineWidth(1);

  if (Hist2->fLineColor >= 0) hpx2->SetLineColor(Hist2->fLineColor);
  if (Hist2->fLineWidth != 1) hpx2->SetLineWidth(Hist2->fLineWidth);

  if (Hist2->fFillStyle >= 0) hpx2->SetFillStyle(Hist2->fFillStyle);
  if (Hist2->fFillColor >= 0) hpx2->SetFillColor(Hist2->fFillColor);

  if (Hist2->fMarkerStyle >=0) hpx2->SetMarkerStyle(Hist2->fMarkerStyle);
  if (Hist2->fMarkerColor >=0) hpx2->SetMarkerColor(Hist2->fMarkerColor);
  if (Hist2->fMarkerSize  >=0) hpx2->SetMarkerSize (Hist2->fMarkerSize );

  if (Hist2->fStats == 0) hpx2->SetStats(0);

  if (Hist2->fDrawOpt == "") hpx2->Draw("ep,sames");
  else {
    TString opt = Hist2->fDrawOpt;
    opt += ",sames";
    hpx2->Draw(opt.Data());
  }
//-----------------------------------------------------------------------------
// position statboxes - need to update the canvas first
//-----------------------------------------------------------------------------
  c->Modified();
  c->Update();

  if (Hist1->fStats != 0) {
    plot_stat_box(hpx1,Hist1->fOptStat,Hist1->fStatBoxXMin,Hist1->fStatBoxYMin,Hist1->fStatBoxXMax,Hist1->fStatBoxYMax);
    plot_stat_box(hpx2,Hist2->fOptStat,Hist2->fStatBoxXMin,Hist2->fStatBoxYMin,Hist2->fStatBoxXMax,Hist2->fStatBoxYMax);
  }
//-----------------------------------------------------------------------------
// add legend, normalized coordinates
//-----------------------------------------------------------------------------
  if (Hist1->fLabel != "") {
    TLegend* leg = new TLegend(Hist1->fLegendXMin,Hist1->fLegendYMin,Hist1->fLegendXMax,Hist1->fLegendYMax);
    leg->AddEntry(hpx1,Hist1->fLabel.Data(),"pl");  // "pl"
    leg->AddEntry(hpx2,Hist2->fLabel.Data(),"pl");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();
  }
//-----------------------------------------------------------------------------
// write DS names inside the plot
//-----------------------------------------------------------------------------
  TString label;

  if (Hist1->fPlotLabel != "") {
    label = Hist1->fPlotLabel;
  }
  else {
    label = Hist1->fName;
    if (Hist1->fName != Hist2->fName) {
      label += " vs ";
      label += Hist2->fName;
    }
  }

  // lower left corner
  draw_label_ndc(label.Data(),Hist1->fLabelXMin,Hist1->fLabelYMin,Hist1->fLabelFontSize,Hist1->fLabelFont); 

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// do we need to add something else? Print = -1 serves that purpose
//-----------------------------------------------------------------------------
  if (Hist1->fPlotName == "") {
    TString hn1(Hist1->fName), hn2(Hist2->fName);

    TString fol1 = hn1(0,hn1.Index('/'));
    TString nam1 = hn1(hn1.Index('/')+1,hn1.Length());

    TString fol2 = hn2(0,hn2.Index('/'));
    TString nam2 = hn2(hn2.Index('/')+1,hn2.Length());

    if (Hist1->fYLogScale == 1) {
      if (hf1) Hist1->fPlotName = Form("%s_%s_vs_%s_%s_log",ds1->GetName(),fol1.Data(),fol2.Data(),nam1.Data());
      else     Hist1->fPlotName = Form("%s_vs_%s_%s_log",fol1.Data(),fol2.Data(),nam1.Data());
    }
    else {
      if (hf1) Hist1->fPlotName = Form("%s_%s_vs_%s_%s_lin",ds1->GetName(),fol1.Data(),fol2.Data(),nam1.Data());
      else     Hist1->fPlotName = Form("%s_vs_%s_%s_lin",fol1.Data(),fol2.Data(),nam1.Data());
    }
  }
  
  Hist1->fOutputFn = Form("%s/eps/%s.eps",gEnv->GetValue("FiguresDir","./"),Hist1->fPlotName.Data());
  if (Print == 1) {
    c->Print(Form("%s",Hist1->fOutputFn.Data())) ;
  }
  
  Hist1->fCanvas = c;
  return;
}

//-----------------------------------------------------------------------------
// overlay N histograms , the first one is assumed to be always present, the
// other ones - not necessarily
// may have the problem with namng the output file
//-----------------------------------------------------------------------------
int plot_hist_1d(hist_data_t* Hist, int NHist, int Print = 0) {
  
  printf("WARNING: plot_hist_1D(hist_data_t*,...) is OBSOLETE, use plot_hist_1D(plot_data_t*, ...)\n");

  char figure_name[200];
//-----------------------------------------------------------------------------
// figure out clone histogram names
//-----------------------------------------------------------------------------
  hist_data_t* Hist1 = &Hist[0];

  if (Hist1->fHist == nullptr) {
    printf("plot_hist_1d error: Hist1->fHist == NULL, BAIL OUT\n");
    return -1; 
  }
  
  TString h1name(Hist1->fName);

  if (Hist1->fNewName == "") h1name.ReplaceAll("/","_");
  else                       h1name = Hist1->fNewName;

  hist_file_t* hf1 = Hist1->fFile;
  
  TH1F* hpx1 = (TH1F*) Hist1->fHist->Clone(h1name);

  //  printf("1:%s  2:%s    3:%s\n",hf1->fName.Data(),Hist1->fModule.Data(),Hist1->fName.Data());
  
  if (Hist1->fRebin > 0) hpx1->Rebin(Hist1->fRebin);
//-----------------------------------------------------------------------------
// scale, if requested
// fLumiSF : implement luminosity-based scaling
//-----------------------------------------------------------------------------
  if (Hist1->fScale  == 3) hpx1->Scale(1./hpx1->Integral());
  else if (Hist1->fScale  > 0) hpx1->Scale(Hist1->fScale);
  if (Hist1->fLumiSF > 0) hpx1->Scale(Hist1->fLumiSF);
  
  stn_dataset_t* ds1(nullptr);

  if (hf1) ds1 = hf1->fDataset;
//-----------------------------------------------------------------------------
// create a canvas
//-----------------------------------------------------------------------------
  TString canvas_name("c_plot_hist_1D");

  if (Hist1->fCanvasName != "") {
    canvas_name = Hist1->fCanvasName;
  }
  else {
    if (ds1) {
      canvas_name += ds1->GetName();
      canvas_name += "_";
    }
    canvas_name += Hist1->fModule;
    canvas_name += "_";
    canvas_name += h1name;
  }
  
  int cx = (Hist1->fCanvasSizeX < 0) ? 1200 : Hist1->fCanvasSizeX;
  int cy = (Hist1->fCanvasSizeY < 0) ?  800 : Hist1->fCanvasSizeY;
//-----------------------------------------------------------------------------
// initially, create canvas with an empty name
//-----------------------------------------------------------------------------
  TCanvas* c = new TCanvas(canvas_name,canvas_name,cx,cy);
  c->SetLogy(Hist1->fYLogScale);
  if(Hist1->fCanvasLeftMargin   >= 0.) c->SetLeftMargin  (Hist1->fCanvasLeftMargin);
  if(Hist1->fCanvasRightMargin  >= 0.) c->SetRightMargin (Hist1->fCanvasRightMargin);
  if(Hist1->fCanvasBottomMargin >= 0.) c->SetBottomMargin(Hist1->fCanvasBottomMargin);
  if(Hist1->fCanvasTopMargin    >= 0.) c->SetTopMargin   (Hist1->fCanvasTopMargin);

//-----------------------------------------------------------------------------
// the two histograms may correspond to slightly different NPOT
//-----------------------------------------------------------------------------
  int col = kRed-3;
  if (Hist1->fLineColor > 0) col =  Hist1->fLineColor;
  hpx1->SetLineColor(col);

  if (Hist1->fLineWidth != 1) hpx1->SetLineWidth(Hist1->fLineWidth);
  
  if (Hist1->fFillStyle >= 0) hpx1->SetFillStyle(Hist1->fFillStyle);
  if (Hist1->fFillColor >= 0) hpx1->SetFillColor(Hist1->fFillColor);

  hpx1->SetTitle("");

  if (Hist1->fMarkerStyle >=0) hpx1->SetMarkerStyle(Hist1->fMarkerStyle);
  if (Hist1->fMarkerColor >=0) hpx1->SetMarkerColor(Hist1->fMarkerColor);
  if (Hist1->fMarkerSize  >=0) hpx1->SetMarkerSize (Hist1->fMarkerSize );

  if (Hist1->fXMin < Hist1->fXMax) hpx1->GetXaxis()->SetRangeUser(Hist1->fXMin,Hist1->fXMax);
  if (Hist1->fXAxisTitle != ""   ) hpx1->GetXaxis()->SetTitle(Hist1->fXAxisTitle.Data());
  if (Hist1->fAxisFontSize >= 0. ) {
    hpx1->GetXaxis()->SetTitleSize(Hist1->fAxisFontSize);
    hpx1->GetXaxis()->SetLabelSize(Hist1->fAxisFontSize);
    hpx1->GetYaxis()->SetTitleSize(Hist1->fAxisFontSize);
    hpx1->GetYaxis()->SetLabelSize(Hist1->fAxisFontSize);
  }

  if (Hist1->fYMin < Hist1->fYMax) hpx1->GetYaxis()->SetRangeUser(Hist1->fYMin,Hist1->fYMax);

//-----------------------------------------------------------------------------
// Y axis title:  by default, assume constant bin size. Sometimes want to disable
//-----------------------------------------------------------------------------
  // if (Hist1->fYTitFormat != "") {
  //float bin      = hpx1->GetXaxis()->GetBinWidth(1);
  //TString ytitle = Form(Hist1->fYTitFormat);//,bin
  hpx1->GetYaxis()->SetTitle(Hist1->fYAxisTitle);//ytitle
    //}
   
  if (Hist1->fStats == 0) hpx1->SetStats(0);

  if (Hist1->fDrawOpt == "") hpx1->Draw("ep");
  else                       hpx1->Draw(Hist1->fDrawOpt.Data());

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// handle stat boxes
//-----------------------------------------------------------------------------
  float sb_ymax = Hist1->fStatBoxYMax;
  float sb_dy   = Hist1->fStatBoxYMax-Hist1->fStatBoxYMin;
  
  if (Hist1->fStats != 0) {
    plot_stat_box(hpx1,Hist1->fOptStat,Hist1->fStatBoxXMin,Hist1->fStatBoxYMin,Hist1->fStatBoxXMax,Hist1->fStatBoxYMax);
  }
//-----------------------------------------------------------------------------
// start forming legend
//-----------------------------------------------------------------------------
  TLegend*  leg(nullptr);

  if (Hist1->fLabel != "") {
    leg = new TLegend(Hist1->fLegendXMin,Hist1->fLegendYMin,Hist1->fLegendXMax,Hist1->fLegendYMax);
    leg->AddEntry(hpx1,Hist1->fLabel.Data(),"pl");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
  }
//-----------------------------------------------------------------------------
// at this point deal with the rest histograms if they are present
//-----------------------------------------------------------------------------
  for (int ihist=1; ihist<NHist; ihist++) {
    hist_data_t* Hist2 = &Hist[ihist];

    if (Hist2->fHist == nullptr) {
      printf("plot_hist_1d ERROR: ihist = %i Hist2->fHist == NULL, BAIL OUT\n",ihist);
      return -1;
    }

    TString h2name(Hist2->fName);
    if (Hist2->fNewName == "") h2name.ReplaceAll("/","_");
    else                       h2name = Hist2->fNewName;

    hist_file_t* hf2 = Hist2->fFile;
    
    TH1F* hpx2 = (TH1F*) Hist2->fHist->Clone(h2name);
//-----------------------------------------------------------------------------
//  by default, use the same rebinning as for Hist1
//-----------------------------------------------------------------------------
    int rebin = Hist2->fRebin;
    if (rebin == -1) rebin = Hist1->fRebin;
    if (rebin  >  0) hpx2->Rebin(rebin);
//-----------------------------------------------------------------------------
// in case there are 2 histograms, add the name of the second one to the canvas name
//-----------------------------------------------------------------------------
    if ((Hist1->fCanvasName == "") && (NHist == 2)) {
      canvas_name += "_vs_";
      canvas_name += Hist2->fModule;
      canvas_name += "_";
      canvas_name += h2name;
    }
      
    stn_dataset_t* ds2(nullptr);
    if (hf2) ds2     = hf2->fDataset;

    if (Hist2->fScale == 1) {
//-----------------------------------------------------------------------------
// normalize to the first histogram by dataset
//-----------------------------------------------------------------------------
      if (ds1 && ds2) {
	double scale = (ds1->fNGenEvents+0.)/(ds2->fNGenEvents+0.);
	printf("ds1->fNGenEvents, ds2->fNGenEvents, scale: %li %li %f\n",ds1->fNGenEvents, ds2->fNGenEvents, scale);
	hpx2->Scale(scale);
      }
    }
    else if (Hist2->fScale == 2) {
//-----------------------------------------------------------------------------
// normalize to the integral of the first histogram
//-----------------------------------------------------------------------------
      double scale = hpx1->Integral()/hpx2->Integral();
      hpx2->Scale(scale);
    }

//-----------------------------------------------------------------------------
// normalize to unity
//-----------------------------------------------------------------------------
  if (Hist2->fScale == 3) {
    double scale = 1./hpx2->Integral();
    hpx2->Scale(scale);
  }

  if (Hist2->fLumiSF > 0) hpx2->Scale(Hist2->fLumiSF);
  
    hpx2->SetLineWidth(1);

    if (Hist2->fLineColor >= 0) hpx2->SetLineColor(Hist2->fLineColor);
    if (Hist2->fLineWidth != 1) hpx2->SetLineWidth(Hist2->fLineWidth);

    if (Hist2->fFillStyle >= 0) hpx2->SetFillStyle(Hist2->fFillStyle);
    if (Hist2->fFillColor >= 0) hpx2->SetFillColor(Hist2->fFillColor);
    
    if (Hist2->fMarkerStyle >=0) hpx2->SetMarkerStyle(Hist2->fMarkerStyle);
    if (Hist2->fMarkerColor >=0) hpx2->SetMarkerColor(Hist2->fMarkerColor);
    if (Hist2->fMarkerSize  >=0) hpx2->SetMarkerSize (Hist2->fMarkerSize );

    // set the same limits as Hist1
    if (Hist1->fXMin < Hist1->fXMax) hpx2->GetXaxis()->SetRangeUser(Hist1->fXMin,Hist1->fXMax);

    if (Hist2->fStats == 0) hpx2->SetStats(0);

    if (Hist2->fDrawOpt == "") hpx2->Draw("ep,sames");
    else {
      TString opt = Hist2->fDrawOpt;
      opt += ",sames";
      hpx2->Draw(opt.Data());
    }

    c->Modified(); c->Update();
    
    if (Hist1->fStats != 0) {
//-----------------------------------------------------------------------------
// plot statbox for Hist2. If Hist2->fOptStat is not specified assume the same as for Hist1
//-----------------------------------------------------------------------------
      double sb2_ymax = sb_ymax-ihist*sb_dy;
      double sb2_ymin = sb2_ymax-sb_dy;

      int opt_stat = Hist2->fOptStat;
      if (opt_stat == -1) opt_stat = Hist1->fOptStat;
      
      plot_stat_box(hpx2,opt_stat,Hist2->fStatBoxXMin,sb2_ymin,Hist2->fStatBoxXMax,sb2_ymax);
    }

    if (leg) leg->AddEntry(hpx2,Hist2->fLabel.Data(),"pl");
  }
 
//-----------------------------------------------------------------------------
// position statboxes - need to update the canvas first
//-----------------------------------------------------------------------------
  c->Modified(); c->Update();

  if (leg) {
    leg->SetTextSize(Hist1->fLabelFontSize);
    leg->Draw();
  }
//-----------------------------------------------------------------------------
// write DS names inside the plot
//-----------------------------------------------------------------------------
  TString label;

  if (Hist1->fPlotLabel != "") {
    label = Hist1->fPlotLabel;
  }
  else {
    label = Hist1->fName;
    if (NHist == 2) {
      hist_data_t* Hist2 = &Hist[1];
      if (Hist1->fName != Hist2->fName) {
	label += " vs ";
	label += Hist2->fName;
      }
    }
  }

  // lower left corner
  draw_label_ndc(label.Data(),Hist1->fLabelXMin,Hist1->fLabelYMin,Hist1->fLabelFontSize,Hist1->fLabelFont); 

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// do we need to add something else? Print = -1 serves that purpose
// how to name the output file in case f multiple histograms ?
//-----------------------------------------------------------------------------
  if (Hist1->fPlotName == "") {
    TString hn1(Hist1->fName) ; // , hn2(Hist2->fName);

    TString fol1 = hn1(0,hn1.Index('/'));
    TString nam1 = hn1(hn1.Index('/')+1,hn1.Length());

    // TString fol2 = hn2(0,hn2.Index('/'));
    // TString nam2 = hn2(hn2.Index('/')+1,hn2.Length());

    if (Hist1->fYLogScale == 1) {
      if (hf1) Hist1->fPlotName = Form("%s_%s_vs_%s_%s_log",ds1->GetName(),fol1.Data(),"fol2_data",nam1.Data()); // fol2.Data(),);
      else     Hist1->fPlotName = Form("%s_vs_%s_%s_log",fol1.Data(),"fol2_data",nam1.Data()); // fol2.Data()
    }
    else {
      if (hf1) Hist1->fPlotName = Form("%s_%s_vs_%s_%s_lin",ds1->GetName(),fol1.Data(),"fol2_data",nam1.Data()); // fol2.Data(),nam1.Data());
      else     Hist1->fPlotName = Form("%s_vs_%s_%s_lin",fol1.Data(),"fol2_data",nam1.Data()); // fol2.Data(),
    }
  }
  
  Hist1->fOutputFn = Form("%s/eps/%s.eps",gEnv->GetValue("FiguresDir","."),Hist1->fPlotName.Data());
  if (Print == 1) {
    c->Print(Form("%s",Hist1->fOutputFn.Data())) ;
  }
  Hist1->fCanvas   = c;

  return 0;
}

//-----------------------------------------------------------------------------
// overlay N histograms , the first one is assumed to be always present, the
// other ones - not necessarily
// may have the problem with namng the output file
//-----------------------------------------------------------------------------
int plot_hist_1d(plot_data_t* Plot, int Print = 0, const char* Format = "eps") {
  
  char figure_name[200];
//-----------------------------------------------------------------------------
// figure out clone histogram names
//-----------------------------------------------------------------------------
  hist_data_t* Hist1 = &Plot->hd[0];
  
  if (Hist1->fHist == nullptr) {
    printf("plot_hist_1d error: Hist1->fHist == NULL, BAIL OUT\n");
    return -1;
  }
  
  TString h1name(Hist1->fName);

  if (Hist1->fNewName == "") h1name.ReplaceAll("/","_");
  else                       h1name = Hist1->fNewName;

  hist_file_t* hf1 = Hist1->fFile;
  
  TH1F* hpx1 = (TH1F*) Hist1->fHist->Clone(h1name);
//-----------------------------------------------------------------------------
// rebinning: first check the histogram, then - default for the plot
//-----------------------------------------------------------------------------
  int rebin = Hist1->fRebin;
  if (rebin <= 0) rebin = Plot->fRebin;
  if (rebin >  1) hpx1->Rebin(rebin);
//-----------------------------------------------------------------------------
// scale, if requested
// fLumiSF : implement luminosity-based scaling
//-----------------------------------------------------------------------------
  if (Hist1->fScale  > 0) hpx1->Scale(Hist1->fScale);
  if (Hist1->fLumiSF > 0) hpx1->Scale(Hist1->fLumiSF);
  
  stn_dataset_t* ds1(nullptr);

  if (hf1) ds1 = hf1->fDataset;
//-----------------------------------------------------------------------------
// create a canvas
//-----------------------------------------------------------------------------
  TString canvas_name("c_plot_hist_1D");

  if (Plot->fCanvasName != "") canvas_name = Plot->fCanvasName;
  else if (Plot->fName  != "") canvas_name = "c_"+Plot->fName;
  else {
    if (ds1) {
      canvas_name += ds1->GetName();
      canvas_name += "_";
    }
    canvas_name += Hist1->fModule;
    canvas_name += "_";
    canvas_name += h1name;
  }
  
  int cx = Plot->fCanvasSizeX;
  int cy = Plot->fCanvasSizeY;
//-----------------------------------------------------------------------------
// initially, create canvas with an empty name, set scales
//-----------------------------------------------------------------------------
  TCanvas* c = new TCanvas(canvas_name,canvas_name,cx,cy);
  c->SetLogx(Plot->fXLogScale);
  c->SetLogy(Plot->fYLogScale);
//-----------------------------------------------------------------------------
// the two histograms may correspond to slightly different NPOT
//-----------------------------------------------------------------------------
  int col = kRed-3;
  if (Hist1->fLineColor > 0) col =  Hist1->fLineColor;
  hpx1->SetLineColor(col);

  if (Hist1->fLineWidth != 1) hpx1->SetLineWidth(Hist1->fLineWidth);
  
  if (Hist1->fFillStyle >= 0) hpx1->SetFillStyle(Hist1->fFillStyle);
  if (Hist1->fFillColor >= 0) hpx1->SetFillColor(Hist1->fFillColor);

  hpx1->SetTitle("");
  
  if (Hist1->fMarkerStyle >=0) hpx1->SetMarkerStyle(Hist1->fMarkerStyle);
  if (Hist1->fMarkerColor >=0) hpx1->SetMarkerColor(Hist1->fMarkerColor);
  if (Hist1->fMarkerSize  >=0) hpx1->SetMarkerSize (Hist1->fMarkerSize );

  if (Plot->fXMin < Plot->fXMax) hpx1->GetXaxis()->SetRangeUser(Plot->fXMin,Plot->fXMax);
  if (Hist1->fXMin < Hist1->fXMax) hpx1->GetXaxis()->SetRangeUser(Hist1->fXMin,Hist1->fXMax);
  
  if (Plot->fXAxisTitle != ""  ) hpx1->GetXaxis()->SetTitle(Plot->fXAxisTitle.Data());

  if (Plot->fYMin < Plot->fYMax) hpx1->GetYaxis()->SetRangeUser(Plot->fYMin,Plot->fYMax);
//-----------------------------------------------------------------------------
// Y axis title:  by default, assume constant bin size. Sometimes want to disable
//-----------------------------------------------------------------------------
  if (Plot->fYAxisTitle != "") {
    hpx1->GetYaxis()->SetTitle(Plot->fYAxisTitle.Data());
  }
  else if (Plot->fYTitFormat != "") {
    float bin      = hpx1->GetXaxis()->GetBinWidth(1);
    TString ytitle = Form(Plot->fYTitFormat,bin);
    hpx1->GetYaxis()->SetTitle(ytitle);
  }

  if (Hist1->fStats == 0) hpx1->SetStats(0);

  if (Hist1->fDrawOpt == "") hpx1->Draw("ep");
  else                       hpx1->Draw(Hist1->fDrawOpt.Data());

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// handle stat boxes
//-----------------------------------------------------------------------------
  float sb_ymax = Plot->fStatBoxYMax;
  float sb_ymin = Plot->fStatBoxYMin;
  float sb_dy   = Plot->fStatBoxYMax-Plot->fStatBoxYMin;
  
  if (Hist1->fStats != 0) {
    int opt_stat = Hist1->fOptStat;
    if (opt_stat <= 0) opt_stat = Plot->fOptStat;
    plot_stat_box(hpx1,opt_stat,Hist1->fStatBoxXMin,sb_ymin,Hist1->fStatBoxXMax,sb_ymax);
  }
//-----------------------------------------------------------------------------
// start forming legend
//-----------------------------------------------------------------------------
  TLegend*  leg(nullptr);

  if (Hist1->fLabel != "") {
    leg = new TLegend(Plot->fLegendXMin,Plot->fLegendYMin,Plot->fLegendXMax,Plot->fLegendYMax);
    // decide in the representation
    TString lopt("pl");
    if (Hist1->fFillStyle > 0) lopt = "f";
    leg->AddEntry(hpx1,Hist1->fLabel.Data(),lopt.Data());
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    if (Plot->fLegendTextSize > 0) leg->SetTextSize(Plot->fLegendTextSize);
  }
//-----------------------------------------------------------------------------
// at this point deal with the rest histograms if they are present
//-----------------------------------------------------------------------------
  for (int ihist=1; ihist<Plot->nhist; ihist++) {
    hist_data_t* Hist2 = &Plot->hd[ihist];

    if (Hist2->fHist == nullptr) {
      printf("plot_hist_1d ERROR: ihist = %i Hist2->fHist == NULL, BAIL OUT\n",ihist);
      return -1;
    }
    
    TString h2name(Hist2->fName);
    if (Hist2->fNewName == "") h2name.ReplaceAll("/","_");
    else                       h2name = Hist2->fNewName;

    hist_file_t* hf2 = Hist2->fFile;
    
    TH1F* hpx2 = (TH1F*) Hist2->fHist->Clone(h2name);
//-----------------------------------------------------------------------------
//  by default, use the same rebinning as for Hist1
//-----------------------------------------------------------------------------
    int rebin = Hist2->fRebin;
    if (rebin == -1) rebin = Plot->fRebin;
    if (rebin  >  0) hpx2->Rebin(rebin);
//-----------------------------------------------------------------------------
// in case there are 2 histograms, add the name of the second one to the canvas name
//-----------------------------------------------------------------------------
    if ((Plot->fCanvasName == "") && (Plot->nhist == 2)) {
      canvas_name += "_vs_";
      canvas_name += Hist2->fModule;
      canvas_name += "_";
      canvas_name += h2name;
    }

    stn_dataset_t* ds2(nullptr);
    if (hf2) ds2     = hf2->fDataset;

    if (Hist2->fScale == 1) {
//-----------------------------------------------------------------------------
// normalize to the first histogram by dataset
//-----------------------------------------------------------------------------
      if (ds1 && ds2) {
	double scale = (ds1->fNGenEvents+0.)/(ds2->fNGenEvents+0.);
	printf("ds1->fNGenEvents, ds2->fNGenEvents, scale: %li %li %f\n",ds1->fNGenEvents, ds2->fNGenEvents, scale);
	hpx2->Scale(scale);
      }
    }
    else if (Hist2->fScale == 2) {
//-----------------------------------------------------------------------------
// normalize to the integral of the first histogram
//-----------------------------------------------------------------------------
      double scale = hpx1->Integral()/hpx2->Integral();
      hpx2->Scale(scale);
    }

    if (Hist2->fLumiSF > 0) hpx2->Scale(Hist2->fLumiSF);
  
    hpx2->SetLineWidth(1);

    if (Hist2->fLineColor >= 0) hpx2->SetLineColor(Hist2->fLineColor);
    if (Hist2->fLineWidth != 1) hpx2->SetLineWidth(Hist2->fLineWidth);

    if (Hist2->fFillStyle >= 0) hpx2->SetFillStyle(Hist2->fFillStyle);
    if (Hist2->fFillColor >= 0) hpx2->SetFillColor(Hist2->fFillColor);
    
    if (Hist2->fMarkerStyle >=0) hpx2->SetMarkerStyle(Hist2->fMarkerStyle);
    if (Hist2->fMarkerColor >=0) hpx2->SetMarkerColor(Hist2->fMarkerColor);
    if (Hist2->fMarkerSize  >=0) hpx2->SetMarkerSize (Hist2->fMarkerSize );

    // set the same limits as Hist1
    if (Plot->fXMin < Plot->fXMax) hpx2->GetXaxis()->SetRangeUser(Plot->fXMin,Plot->fXMax);
    if (Hist1->fXMin < Hist1->fXMax) hpx2->GetXaxis()->SetRangeUser(Hist1->fXMin,Hist1->fXMax);
   
    hpx1->GetXaxis()->SetLimits(Plot->fXMin,Plot->fXMax);
    hpx2->GetXaxis()->SetLimits(Plot->fXMin,Plot->fXMax);
    if (Hist2->fStats == 0) hpx2->SetStats(0);

    if (Hist2->fDrawOpt == "") hpx2->Draw("ep,sames");
    else {
      TString opt = Hist2->fDrawOpt;
      opt += ",sames";
      hpx2->Draw(opt.Data());
    }

    c->Modified(); c->Update();
    
    if ((Hist1->fStats != 0) and (Hist2->fStats != 0)) {
//-----------------------------------------------------------------------------
// plot statbox for Hist2. If Hist2->fOptStat is not specified assume the same as for Hist1
//-----------------------------------------------------------------------------
      double sb2_ymax = sb_ymax-ihist*sb_dy;
      double sb2_ymin = sb2_ymax-sb_dy;

      int opt_stat = Hist2->fOptStat;
      if (opt_stat == -1) opt_stat = Plot->fOptStat;
      
      plot_stat_box(hpx2,opt_stat,Hist2->fStatBoxXMin,sb2_ymin,Hist2->fStatBoxXMax,sb2_ymax);
    }

    if (leg) {
      TString lopt("pl");
      if (Hist2->fFillStyle > 0) lopt = "f";
      leg->AddEntry(hpx2,Hist2->fLabel.Data(),lopt.Data());
    }
  }
//-----------------------------------------------------------------------------
// position statboxes - need to update the canvas first
//-----------------------------------------------------------------------------
  c->Modified(); c->Update();

  if (leg) leg->Draw();
//-----------------------------------------------------------------------------
// write DS names inside the plot
//-----------------------------------------------------------------------------
  TString label;

  if (Plot->fLabel != "") {
    label = Plot->fLabel;
  }
  else {
    label = Hist1->fName;
    if (Plot->nhist == 2) {
      hist_data_t* Hist2 = &Plot->hd[1];
      if (Hist1->fName != Hist2->fName) {
	label += " vs ";
	label += Hist2->fName;
      }
    }
  }

  // lower left corner
  draw_label_ndc(label.Data(),Plot->fLabelXMin,Plot->fLabelYMin,Plot->fLabelFontSize,Plot->fLabelFont); 

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// do we need to add something else? Print = -1 serves that purpose
// how to name the output file in case f multiple histograms ?
//-----------------------------------------------------------------------------
  // printf (" debug 001\n");
  if (Plot->fName == "") {
    TString hn1(Plot->fName) ; 

    TString fol1 = hn1(0,hn1.Index('/'));
    TString nam1 = hn1(hn1.Index('/')+1,hn1.Length());

    if (Plot->fYLogScale == 1) {
      if (hf1) Plot->fName = Form("%s_%s_vs_%s_%s_log",ds1->id(),fol1.Data(),"fol2_data",nam1.Data());
      else     Plot->fName = Form("%s_vs_%s_%s_log",fol1.Data(),"fol2_data",nam1.Data());
    }
    else {
      if (hf1) Plot->fName = Form("%s_%s_vs_%s_%s_lin",ds1->id(),fol1.Data(),"fol2_data",nam1.Data());
      else     Plot->fName = Form("%s_vs_%s_%s_lin",fol1.Data(),"fol2_data",nam1.Data());
    }
  }
//-----------------------------------------------------------------------------
// determine the output file name. Extension defines the file format (default: ".eps")
//-----------------------------------------------------------------------------
  TString ext(Format);
  ext.ToLower();
  Plot->fOutputFn = Form("%s/%s/%s.%s",gEnv->GetValue("FiguresDir","./"),ext.Data(),Plot->fName.Data(),ext.Data());
  if (Print == 1) {
    c->Print(Form("%s",Plot->fOutputFn.Data())) ;
  }
  Plot->fCanvas   = c;

  return 0;
}


//-----------------------------------------------------------------------------
// perform a fairly common task - fit histogram with a gaussian
// HistName like "spmc_1/mom"
//-----------------------------------------------------------------------------
void fit_gaus_hist_1D(hist_data_t* Hist, const char* FOpt, const char* GOpt, double XMin, double XMax, int Print = 0) {

  char figure_name[200];

  TString hname(Hist->fName);

  if (Hist->fNewName == "") hname.ReplaceAll("/","_");
  else                      hname = Hist->fNewName;

  hist_file_t*   hf = Hist->fFile;
  stn_dataset_t* ds = hf->fDataset;
  
  TH1F* hpx1 = (TH1F*) gh1(hf->GetName(),Hist->fModule,Hist->fName)->Clone(hname);
  Hist->fHist = hpx1;

  if (Hist->fRebin > 0) hpx1->Rebin(Hist->fRebin);
//-----------------------------------------------------------------------------
// create a canvas
//-----------------------------------------------------------------------------
  TString canvas_name(Hist->fModule);
  canvas_name += "_";
  canvas_name += hname;
  canvas_name += "_fit_gaus";
  canvas_name += "_";
  canvas_name += Hist->fName;
  
  if (Hist->fCanvasName != "") canvas_name = Hist->fCanvasName;
  TCanvas* c = new TCanvas(canvas_name.Data(),canvas_name.Data(),Hist->fCanvasSizeX,Hist->fCanvasSizeY);
  c->SetLogy(Hist->fYLogScale);
//-----------------------------------------------------------------------------
// fit histogram
//-----------------------------------------------------------------------------
  if (Hist->fLineColor > 0) hpx1->SetLineColor(Hist->fLineColor);
  hpx1->SetLineWidth(1);
  hpx1->SetTitle("");
  if (Hist->fXMin < Hist->fXMax) hpx1->GetXaxis()->SetRangeUser(Hist->fXMin,Hist->fXMax);
  if (Hist->fXAxisTitle != ""  ) hpx1->GetXaxis()->SetTitle(Hist->fXAxisTitle.Data());
  hpx1->Fit("gaus",FOpt,GOpt,XMin,XMax);
//-----------------------------------------------------------------------------
// position statbox - need to update the canvas first
//-----------------------------------------------------------------------------
  c->Modified();
  c->Update();

  if (Hist->fStats != 0) {
    plot_stat_box(hpx1,Hist->fOptStat,0.6,0.5,0.9,0.9);
  }
//-----------------------------------------------------------------------------
// add legend
//-----------------------------------------------------------------------------
  TLegend* leg = new TLegend(Hist->fLegendXMin,Hist->fLegendYMin,Hist->fLegendXMax,Hist->fLegendYMax);
  leg->AddEntry(hpx1,Hist->fLabel.Data(),"pl");  // "pl"
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();
//-----------------------------------------------------------------------------
// label the plot
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// write dataset names inside the plot
//-----------------------------------------------------------------------------
  TString label(ds->id());

  if (Hist->fPlotLabel != "") label = Hist->fPlotLabel;
					// lower left corner
  draw_label_ndc(label.Data(),Hist->fLabelXMin,Hist->fLabelYMin,Hist->fLabelFontSize,Hist->fLabelFont); 

  c->Modified(); c->Update();
//-----------------------------------------------------------------------------
// .png files are written into /png/ subdirectory
//-----------------------------------------------------------------------------
  if (Print == 1) {
    if (Hist->fPlotName == "") {
      Hist->fPlotName = Form("%s_fit_gaus",Hist->fName.Data());
    }
    c->Print(Form("%s/eps/%s.eps",gEnv->GetValue("FiguresDir","./"),Hist->fPlotName.Data())) ;
  }

  Hist->fCanvas   = c;
}

//-----------------------------------------------------------------------------
// new interface, try to provide a smooth transition
// so far, defined are only cases of NHist=1 and NHist=2
//-----------------------------------------------------------------------------
void plot_hist(hist_data_t* Hist, int NHist, int Print = 0) {
  plot_hist_1d(Hist,NHist,Print);
}

#endif
