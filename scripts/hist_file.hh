//-----------------------------------------------------------------------------
// a 'dataset' here is a histogram file plus data fields for plotting attributes
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_hist_file_hh__
#define __Stntuple_val_hist_file_hh__

#include "TNamed.h"
#include "TString.h"

class stn_dataset_t; // #include "stn_dataset.hh"

class hist_file_t : public TNamed {
public:
  stn_dataset_t*  fDataset;			// pointer to the STN dataset
  TString         fAnalysisJob;			// job name
  TString         fProductionJob;		// job name

  hist_file_t(const char* FileName = "", stn_dataset_t* Dataset = nullptr, const char* ProductionJob = "", const char* AnalysisJob = "") :
    TNamed(FileName,FileName) {
    fDataset       = Dataset;
    fAnalysisJob   = AnalysisJob;
    fProductionJob = ProductionJob;
  }
  
};

#endif
