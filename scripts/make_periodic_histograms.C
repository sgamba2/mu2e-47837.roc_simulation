///////////////////////////////////////////////////////////////////////////////
// draw N pulses
///////////////////////////////////////////////////////////////////////////////
#ifndef __plot_muon_decay_time_C__
#define __plot_muon_decay_time_C__

#include <stdio.h>
#include "TObject.h"
#include "TSystem.h"
#include "TNtuple.h"
#include "TInterpreter.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"

#include "Stntuple/scripts/stn_catalog.hh"
#include "Stntuple/scripts/plot_utilities.hh"

// TH1F* h_t0, *h_decay;
//-----------------------------------------------------------------------------
// 

//-----------------------------------------------------------------------------
int make_beam_flash_hist(TH1F*& Hist, int FirstPulse = 0, int LastPulse = 1, double Scale = 1.) {
  double x[10000], y[10000];
  float  var[100];
  char   fn[500];

  int npulses = LastPulse-FirstPulse+1;
  
  if (Hist == nullptr) {
    float tmin = -200+1695*FirstPulse;
    float tmax =  200+1695*(LastPulse+1);
    int   nb   = (tmax-tmin)/10;
    Hist       = new TH1F("h_beam_flash_time","",nb,tmin,tmax);
  }

  Hist->Reset();

  sprintf(fn,"%s/su2020.flsh0s36b0.spmc_ana.0000.hist",su2020_HistDir);

  TH1F* hbf = gh1(fn,"murat_SpmcAna","vdet_9/time");

  int nbx = hbf->GetNbinsX();
  
  for (int pulse=FirstPulse; pulse<LastPulse+1; pulse++) {

    for (int ibx=1; ibx<=nbx; ibx++) {
      
      double x = hbf->GetBinCenter(ibx)+1695*pulse;
      double y = hbf->GetBinContent(ibx);

      int ib = Hist->FindBin(x);
      
      Hist->SetBinContent(ib,y);
      Hist->SetBinError  (ib,0);
    }
  }

  return 0;
};



//-----------------------------------------------------------------------------
int make_muon_vd9_hist(TH1F*& Hist, int FirstPulse = 0, int LastPulse = 0) {
  double x[10000], y[10000];
  int nb;
  float tmin, tmax; 
  
  if (Hist == nullptr) {
    tmin = (-200+1695*FirstPulse)/10*10;
    tmax =  (200+1695*(LastPulse+1))/10*10;
    nb   = (tmax-tmin)/10;
    Hist = new TH1F("h_mu_vd9_time","muon time at VD9",nb,tmin,tmax);
  }

  Hist->Reset();
//-----------------------------------------------------------------------------
// make one-pulse histogram for pulse=0
//-----------------------------------------------------------------------------
  // muon stop time

  char fn[500];
  sprintf(fn,"%s/su2020.bmum0s3cb0.spmc_ana.0000.hist",su2020_HistDir);

  TH1F* h_time = gh1(fn,"murat_SpmcAna","vdet_309/time");
  int nbt = h_time->GetNbinsX();

  for (int i=1; i<=nbt; i++) {
    double x   = h_time->GetBinCenter(i);
    double wt  = h_time->GetBinContent(i);
    int ibx=Hist->FindBin(x);
    Hist->Fill(x,wt);
    Hist->SetBinError(ibx,0);
  }
//-----------------------------------------------------------------------------
// fill the rest of the histogram
//-----------------------------------------------------------------------------
  for (int pulse=FirstPulse; pulse<LastPulse+1; pulse++) {
    if (pulse == 0) continue;
    
    for (int ib=1; ib<=nb; ib++) {
      
      double x = Hist->GetBinCenter(ib);
      Hist->SetBinError  (ib,0);
      if ((x < 0) or (x > 1695))  continue;
      
      x += 1695*pulse;
      
      double y = Hist->GetBinContent(ib);

      int ibx = Hist->FindBin(x);
      
      Hist->SetBinContent(ibx,y);
      Hist->SetBinError(ibx,0);
    }
  }

  return 0;
};

//-----------------------------------------------------------------------------
int make_pion_vd9_hist(TH1F*& Hist, int FirstPulse = 0, int LastPulse = 0) {
  double x[10000], y[10000];
  int nb;
  float tmin, tmax; 
  
  if (Hist == nullptr) {
    tmin = (-200+1695*FirstPulse)/10*10;
    tmax =  (200+1695*(LastPulse+1))/10*10;
    nb   = (tmax-tmin)/10;
    Hist = new TH1F("h_pi_vd9_time","pi- time at VD9",nb,tmin,tmax);
  }

  Hist->Reset();
//-----------------------------------------------------------------------------
// make one-pulse histogram for pulse=0
//-----------------------------------------------------------------------------
  // muon stop time
  char fn[500];
  sprintf(fn,"%s/su2020.bmum0s3cb0.spmc_ana.0000.hist",su2020_HistDir);
  TH1F* h_time = gh1(fn,"murat_SpmcAna","vdet_1009/time");

  int nbt = h_time->GetNbinsX();

  for (int i=1; i<=nbt; i++) {
    double x   = h_time->GetBinCenter(i);
    double wt  = h_time->GetBinContent(i);
    int ibx=Hist->FindBin(x);
    Hist->Fill(x,wt);
    Hist->SetBinError(ibx,0);
  }
//-----------------------------------------------------------------------------
// fill the rest of the histogram
//-----------------------------------------------------------------------------
  for (int pulse=FirstPulse; pulse<LastPulse+1; pulse++) {
    if (pulse == 0) continue;
    
    for (int ib=1; ib<=nb; ib++) {
      
      double x = Hist->GetBinCenter(ib);
      Hist->SetBinError  (ib,0);
      if ((x < 0) or (x > 1695))  continue;
      
      x += 1695*pulse;
      
      double y = Hist->GetBinContent(ib);

      int ibx = Hist->FindBin(x);
      
      Hist->SetBinContent(ibx,y);
      Hist->SetBinError(ibx,0);
    }
  }

  return 0;
};

//-----------------------------------------------------------------------------
int make_bound_muon_decay_hist(TH1F*& Hist, int NEvents = 1000000, int FirstPulse = 0, int LastPulse = 0) {
  double x[10000], y[10000];
  int nb;
  float tmin, tmax; 
  
  if (Hist == nullptr) {
    tmin = -200+1695*FirstPulse;
    tmax =  200+1695*(LastPulse+1);
    nb   = (tmax-tmin)/10;
    Hist = new TH1F("h_bound_mu_decay_time","Bound muon decay time",nb,tmin,tmax);
  }

  Hist->Reset();
//-----------------------------------------------------------------------------
// make one-pulse histogram for pulse=0
//-----------------------------------------------------------------------------
  // muon stop time
  char fn[500];
  sprintf(fn,"%s/su2020.bmum0s31b0.spmc_ana.0000.hist",su2020_HistDir);
  TH1F* h_muon_stop_time = gh1(fn,"murat_SpmcAna","simp_603/time");
  
  TRandom3 rn3;
  double   t0, t1;
  
  double tau(864.);

  double tdecay = rn3.Exp(tau);

  double wt = 1./NEvents;
  
  for (int i=0; i<NEvents; i++) {
    t0     = h_muon_stop_time->GetRandom();
    tdecay = rn3.Exp(tau);
    t1     = t0+tdecay;
    while (t1 >= 1695) t1 -=1695;
    Hist->Fill(t1,wt);
  }
//-----------------------------------------------------------------------------
// fill the rest of the histogram
//-----------------------------------------------------------------------------
  for (int pulse=FirstPulse; pulse<LastPulse+1; pulse++) {
    if (pulse == 0) continue;
    
    for (int ib=1; ib<=nb; ib++) {
      
      double x = Hist->GetBinCenter(ib);
      Hist->SetBinError  (ib,0);
      if ((x < 0) or (x > 1695))  continue;
      
      x += 1695*pulse;
      
      double y = Hist->GetBinContent(ib);

      int ibx = Hist->FindBin(x);
      
      Hist->SetBinContent(ibx,y);
    }
  }

  return 0;
};

//-----------------------------------------------------------------------------
void plot_bound_muon_decay_time(int NPulses = 1, int DrawArrivals = 0, int Print = 0) {

  TCanvas* c;
  TH1F* hist(0);
  
  make_bound_muon_decay_hist(hist);

  c = new TCanvas("c_pulse","pulse",1500,400);

  hist->Draw();
}


#endif

