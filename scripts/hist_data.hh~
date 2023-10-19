//-----------------------------------------------------------------------------
// a 'dataset' here is a histogram file plus data fields for plotting attributes
// hist_data_t::fHist is supposed to be defined on exit
// need libStntuple_val.so
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_hist_data_hh__
#define __Stntuple_val_hist_data_hh__

#include "TH1.h"
#include "TString.h"
#include "TCanvas.h"

#include "Stntuple/val/stntuple_val_functions.hh"

class stn_book;
class stn_catalog;
class hist_file_t;

class hist_data_t {
public:
  TH1*          fHist;                  // if non-null, fFile is not needed
  hist_file_t*  fFile;                  // it contains a pointer to the dataset
  stn_book*     fBook;

  TString       fLabel  ;		// label to appear on a plot
  float         fLabelXMin;
  float         fLabelYMin;
  float         fLabelFontSize;
  float         fLabelFont;

  TString       fModule;	        // module name
  TString       fName;	                // histogram name, as saved in a file
  TString       fNewName;	        // redefines histogram name at plotting time
  int           fLineColor;             // these are utility fields to be used as needed
  int           fLineWidth;
  int           fFillColor;             // these are utility fields to be used as needed
  int           fFillStyle;             // these are utility fields to be used as needed
  int           fMarkerStyle;
  float         fMarkerSize;
  int           fMarkerColor;
  float         fXMin;
  float         fXMax;
  float         fYMin;
  float         fYMax;
  int           fStats;
  int           fOptStat;
  float         fStatBoxXMin;
  float         fStatBoxYMin;
  float         fStatBoxXMax;
  float         fStatBoxYMax;
  int           fRebin;
  int           fYLogScale;
  TString       fDrawOpt;
  float         fScale;			// 1:normalize to NGenEvents, 2:normalize to integral
  float         fLumiSF;                // alternative to scale: just scale by this number
  TString       fPlotName;
  TString       fPlotLabel;
  TString       fXAxisTitle;
  TString       fYAxisTitle;
  float         fAxisFontSize;
  TString       fYTitFormat;		// if "", Y axis title is not printed
  float         fLegendXMin;
  float         fLegendYMin;
  float         fLegendXMax;
  float         fLegendYMax;
  float         fLegendFontSize;
  TString       fCanvasName;
  int           fCanvasSizeX;
  int           fCanvasSizeY;
  float         fCanvasLeftMargin;
  float         fCanvasRightMargin;
  float         fCanvasBottomMargin;
  float         fCanvasTopMargin;
  TCanvas*      fCanvas;
  TString       fOutputFn;
                                        // stnana histogram file, JobName is the stnana (analysis) job name
  hist_data_t(const char* DsID = "", const char* JobName = "", const char* Module = "", const char* HistName = "");
                                        // stnana histogram file
  hist_data_t(stn_book* Book, const char* DsID, const char* JobName, const char* Module, const char* HistName);

                                        // art histogram file - FullHistName is a full path, the rest parameters
                                        // define the file name
  hist_data_t(stn_book* Book, const char* DsID, const char* JobName, const char* FullHistName);
  
  hist_data_t(stn_catalog* Catalog, const char* BookName, const char* DsID,
	      const char* JobName,   const char* Module, const char* HistName);

  hist_data_t(TH1* Hist, const char* JobName = "", const char* Module = "");

  void  init();

//-----------------------------------------------------------------------------
// get histogram file for a given dataset ID
//-----------------------------------------------------------------------------
  hist_file_t*  get_hist_file(const char* DsID, const char* JobName) ;
  int  print(const char* Fn = "") ;

};

#endif
