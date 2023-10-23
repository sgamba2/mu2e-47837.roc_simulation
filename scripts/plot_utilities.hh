#ifndef __roc_simulation__
#define __roc_simulation__

#include "TPaveStats.h"
#include "TLatex.h"

#include "Stntuple/val/hist_data.hh"
#include "Stntuple/val/hist_file.hh"
#include "Stntuple/val/plot_data.hh"
// #include "Stntuple/val/plot_utilities.hh"
#include "Stntuple/val/stn_book.hh"
#include "Stntuple/val/stn_catalog.hh"
#include "Stntuple/val/stn_dataset.hh"
#include "Stntuple/val/stntuple_val_functions.hh"
#include "TBadFolder.hh"
#include "TGoodFolder.hh"
#include "THistComp.hh"
//-----------------------------------------------------------------------------
void set_draw_options(TH1* Hist, hist_data_t* Hd) {
  if (Hd->fLineColor   > 0) Hist->SetLineColor(Hd->fLineColor);
  if (Hd->fMarkerSize  > 0) Hist->SetMarkerSize (Hd->fMarkerSize);
  if (Hd->fMarkerColor > 0) Hist->SetMarkerColor(Hd->fMarkerColor);
  if (Hd->fMarkerStyle > 0) Hist->SetMarkerStyle(Hd->fMarkerStyle);

  if (Hd->fXMin < Hd->fXMax) Hist->GetXaxis()->SetRangeUser(Hd->fXMin,Hd->fXMax);
  if (Hd->fYMin < Hd->fYMax) Hist->GetYaxis()->SetRangeUser(Hd->fYMin,Hd->fYMax);
}

//-----------------------------------------------------------------------------
// redraw the stat box, with the color of the histogram itself
//-----------------------------------------------------------------------------
void plot_stat_box(TH1* Hist, int OptStat, double X1, double Y1, double X2, double Y2) {
  TPaveStats* s = (TPaveStats*) Hist->GetListOfFunctions()->FindObject("stats");
  if (s != NULL) {
    if (OptStat >= 0) s->SetOptStat(OptStat);
    s->SetLineColor(Hist->GetLineColor());
    s->SetTextColor(Hist->GetLineColor());
    s->SetX1NDC(X1); s->SetY1NDC(Y1); s->SetX2NDC(X2); s->SetY2NDC(Y2);
    s->SetFillStyle(0);
    s->Draw();
  }
  else {
    printf("ERROR: stat box is not defined for %s\n",Hist->GetName());
  }
}

//-----------------------------------------------------------------------------
// draw label in normalized coordinates (x and y range from 0 to 1
//-----------------------------------------------------------------------------
void draw_label_ndc(const char* Text, double X1, double Y1, double FontSize, int Font = 52) {

  TLatex* label = new TLatex(X1,Y1,Text);
  label->SetNDC(kTRUE);
  label->SetTextSize(FontSize);
  label->SetTextFont(Font);
  label->Draw();
}

//-----------------------------------------------------------------------------
// draw a label in absolute coordinates
//-----------------------------------------------------------------------------
void draw_label_abs(const char* Text, double X1, double Y1, double FontSize, int Font = 52) {

  TLatex* label = new TLatex(X1,Y1,Text);
  label->SetNDC(kFALSE);
  label->SetTextSize(FontSize);
  label->SetTextFont(Font);
  label->Draw();
}

//-----------------------------------------------------------------------------
void make_empty_plot(const char* figure_name, int Print = 0) {

  TCanvas* c = new TCanvas("c_empty","EmptyPlot",1500,800);

  draw_label_ndc("EMPTY PLOT :  - don't forget to make !",0.25,0.4,0.06,52);

  // TArrow* arr = new TArrow(0.9,40.e3,0.9,10.e3,0.015);

  // arr->SetLineWidth(2);
  // arr->Draw();

  if (Print == 1) c->Print(figure_name);
}


#endif
