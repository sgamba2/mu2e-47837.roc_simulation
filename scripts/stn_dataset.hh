//-----------------------------------------------------------------------------
// a 'dataset' here is a histogram file plus data fields for plotting attributes
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_stn_dataset_hh__
#define __Stntuple_val_stn_dataset_hh__

#include "TNamed.h"
#include "TObjArray.h"

#include "Stntuple/val/hist_file.hh"

class stn_book;

class stn_dataset_t : public TNamed {
public:
  stn_book*  fBook           ; // dataset book (not ready to use yet)
  TObjArray* fListOfHistFiles;
  TString    fName           ; // full name of the ntupled dataset
  long int   fNEvents        ; // number of events in all files
  long int   fNGenEvents     ; // N generated events (if MC, corresponding to the files, for normalization)
  float      fEMin           ; // sometimes, the signal particle energy range is constrained
  float      fEMax           ;
  int        fMinRun         ; // minimal run number
  int        fMaxRun         ; // maximal run number
  float      fLumiSF         ; // scale factor toget the right luminosity scaling

  stn_dataset_t (const char* DsID = "");
  ~stn_dataset_t();
                                        // dataset ID (short name)
  
  const char* id  () { return GetName (); }
  const char* name() { return GetTitle(); }

  hist_file_t* NewHistFile(const char* Dir, const char* ProductionJob, const char* AnalysisJob);
  
  hist_file_t* HistFile(int I) { return (hist_file_t*) fListOfHistFiles->At(I); }

  hist_file_t* FindHistFile(const char* ProductionJob, const char* AnalysisJob) const ;
};

#endif
