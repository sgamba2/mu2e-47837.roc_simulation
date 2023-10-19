//-----------------------------------------------------------------------------
// struct to hold a plot data with multiple histograms
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_plot_data_hh__
#define __Stntuple_val_plot_data_hh__

#include "Stntuple/val/hist_data.hh"

#include "TString.h"
#include "TCanvas.h"

class plot_data_t {
public:
  int           nhist;
  hist_data_t   hd[100];                // difficult to think of having more than that

  TString       fName;
  TString       fLabel  ;		// global label to appear on a plot
  float         fLabelXMin;
  float         fLabelYMin;
  float         fLabelFontSize;
  float         fLabelFont;
					// --- limits, scales, rebinning
  float         fXMin;
  float         fXMax;
  int           fXLogScale;
  float         fYMin;
  float         fYMax;
  int           fYLogScale;
  int           fRebin;
					// --- statistics 
  int           fStats;
  int           fOptStat;		// default for all histograms on the plot
  float         fStatBoxXMin;
  float         fStatBoxYMin;
  float         fStatBoxXMax;
  float         fStatBoxYMax;
					// --- titles
  TString       fXAxisTitle;
  TString       fYAxisTitle;
  TString       fYTitFormat;		// if "", Y axis title is not printed

  float         fLegendXMin;
  float         fLegendYMin;
  float         fLegendXMax;
  float         fLegendYMax;
  float         fLegendTextSize;

  TString       fCanvasName;
  int           fCanvasSizeX;
  int           fCanvasSizeY;
  TCanvas*      fCanvas;

  TString       fOutputFn;

  static TString fgFiguresDir;       

  plot_data_t(int NHist = -1) {
    nhist = NHist;
    init();
  }
  
  void  init() {
    fName          = "";
    fCanvasName    = "";
    fCanvasSizeX   = 1200.;
    fCanvasSizeY   =  800.;
    
    fLabel         = "";
    fLabelXMin     = 0.15;
    fLabelYMin     = 0.86;
    fLabelFontSize = 0.03;
    fLabelFont     = 52; // lower left corner

    fXMin          =  0;
    fXMax          = -1;
    fYMin          =  0;
    fYMax          = -1;

    fStats         =  1;
    fOptStat       = -1;
    fStatBoxXMin   = 0.70;
    fStatBoxXMax   = 0.90;
    fStatBoxYMin   = 0.72;
    fStatBoxYMax   = 0.90;

    fRebin         = -1;
    fXLogScale     =  0;
    fYLogScale     =  0;

    fXAxisTitle    = "";
    fYAxisTitle    = "";
    fYTitFormat    = "N / %10.3f";
    
    fLegendXMin    = 0.65;
    fLegendYMin    = 0.15;
    fLegendXMax    = 0.90;
    fLegendYMax    = 0.40;
    fLegendTextSize = -1;

    fOutputFn      = "";
  }
//-----------------------------------------------------------------------------
// what ROOT does is defined by the file extention
//-----------------------------------------------------------------------------
  int  print(const char* Fn = "") {
    TString fn = Fn;
    if (fn == "") fn = fOutputFn;

    if (fn == "") {
      printf("plot_data::print ERROR: output filename is not defined. BAIL OUT\n");
      return -1;
    }
    
    if (fCanvas == nullptr) {
      printf("plot_data::print ERROR: canvas is not defined. BAIL OUT\n");
      return -1;
    }
    
    fCanvas->Modified();
    fCanvas->Update();
    
    fCanvas->Print(fn.Data());
    return 0;
  }
};

#endif
