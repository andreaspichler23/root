//            sddtest.C
//
//     written by C. Berucci et al.
//
//


#include "TH1.h"
#include  "TSpectrum.h"



Double_t fitfunc(Double_t *x, Double_t *par){
    
    Double_t xx = x[0];
    
    //par[0] = ti ka1 gain
    //par[1] = ti ka1 mean
    //par[2] = ti ka1 sigma
    
    Double_t ti_ka1 = par[0]/(sqrt(2*TMath::Pi())*par[2])*TMath::Exp(-((xx-par[1])*(xx-par[1]))/(2*par[2]*par[2]));
    
    //ti_ka2 same sigma as ti_ka1, mean is fixed to 5.98 eV below ka1, gain is fixed to half the ti ka1 gain
    
    Double_t ti_ka2_gain = par[0]/2;
    Double_t ti_ka2_mean = par[1] - 5.98;
    
    Double_t ti_ka2 = ti_ka2_gain/(sqrt(2*TMath::Pi())*par[2])*TMath::Exp(-((xx-ti_ka2_mean)*(xx-ti_ka2_mean))/(2*par[2]*par[2]));
    
    //par[3] = ti kb gain
    //par[4] = ti kb mean
    //par[5] = ti kb sigma
    
    Double_t ti_kb = par[3]/(sqrt(2*TMath::Pi())*par[5])*TMath::Exp(-((xx-par[4])*(xx-par[4]))/(2*par[5]*par[5]));
    
    // ------------- same with mn peaks
    
    
    //par[6] = mn ka1 gain
    //par[7] = mn ka1 mean
    //par[8] = mn ka1 sigma
    
    Double_t mn_ka1 = par[6]/(sqrt(2*TMath::Pi())*par[8])*TMath::Exp(-((xx-par[7])*(xx-par[7]))/(2*par[8]*par[8]));
    
    //mn_ka2 same sigma as mn_ka1, mean is fixed to 11.1 eV below ka1, gain is fixed to half the mn ka1 gain
    
    Double_t mn_ka2_gain = par[6]/2;
    Double_t mn_ka2_mean = par[7] - 11.1;
    
    Double_t mn_ka2 = mn_ka2_gain/(sqrt(2*TMath::Pi())*par[2])*TMath::Exp(-((xx-mn_ka2_mean)*(xx-mn_ka2_mean))/(2*par[2]*par[2]));
    
    //par[9] = mn kb gain
    //par[10] = mn kb mean
    //par[11] = mn kb sigma
    
    Double_t mn_kb = par[9]/(sqrt(2*TMath::Pi())*par[11])*TMath::Exp(-((xx-par[10])*(xx-par[10]))/(2*par[11]*par[11]));
    
    Double_t func_value = ti_ka1 + ti_ka2 + ti_kb + mn_ka1 + mn_ka2 + mn_kb;
    
    return func_value;
    
}


void sddtest(){
    
  gROOT->Reset();

 //Double_t cobalt = 14412.95;
 //Double_t iron = 6403.84;
    
 //Double_t cobalt = 5898.75; //k_alpha mangan
 Double_t mn_ka1 = 5898.75; 
 Double_t mn_ka2 = 5887.65;
 Double_t mn_kb  = 6490.45;
 
 //Double_t iron = 4510.84; //k_alpha titan
 Double_t ti_ka1 = 4510.84; 
 Double_t ti_ka2 = 4504.86; 
 Double_t ti_kb  = 4931.81;

    
 gROOT->Reset();

  double x1,x2,x3,x4,x5,x6,x7,x8;

  TFile *f=new TFile("sdd.root","recreate");
  TString h1name[]={"ch1_19.3"};
  TString h2name[]={"ch/_19.3"};
  TString h3name[]={"ch2_19.3"};
  TString h4name[]={"ch3_19.3"};
  TString h5name[]={"ch4_19.3"};
  TString h6name[]={"ch/_19.3"};
  TString h7name[]={"ch7_19.3"};
  TString h8name[]={"ch8_19.3"};


  int n=0;


  TH1F* h1;
  TH1F* h2;
  TH1F* h3;
  TH1F* h4;
  TH1F* h5;
  TH1F* h6;
  TH1F* h7;
  TH1F* h8;


  h1=new TH1F(h1name[0],h1name[0],1760,440,2200); // creating the histograms for the root file
  h2=new TH1F(h2name[0],h2name[0],1760,440,2200);
  h3=new TH1F(h3name[0],h3name[0],1760,440,2200);
  h4=new TH1F(h4name[0],h4name[0],1760,440,2200);
  h5=new TH1F(h5name[0],h5name[0],1760,440,2200);
  h6=new TH1F(h6name[0],h6name[0],1760,440,2200);
  h7=new TH1F(h7name[0],h7name[0],1760,440,2200);
  h8=new TH1F(h8name[0],h8name[0],1760,440,2200);

// --------------------- filling the histograms

  ifstream ifs("all.txt");
  //ifstream ifs("2016Nov23-16.07-F.EVE");
  while(ifs>>x1>>x2>>x3>>x4>>x5>>x6>>x7>>x8){
    n++;

    h1->Fill(x1);  // filling h1, h2, h3 and h4 with adc channel data
    h2->Fill(x2);
    h3->Fill(x3);
    h4->Fill(x4);
    h5->Fill(x5);
    h6->Fill(x6);
    h7->Fill(x7);
    h8->Fill(x8);
      
    
  }



//------------------------- end filling start finding scale

//  std::cout<<"start drawing"<<std::endl;
 // TCanvas *c1;
 // c1=new TCanvas();
  //gStyle->SetOptFit(kTRUE);

    //gStyle->SetOptStat(0);
    
    TSpectrum *t = new TSpectrum();// this function finds peaks in a spectrum
    t->Search(h1, 3.7, "", 0.01 );                    // 1 sigma, 0.01 threshold
    
    Int_t peakN = t->GetNPeaks();
    Double_t *pX = t->GetPositionX();
    Double_t *pY = t->GetPositionY();
    

    cout << pX[0] << " " << pX[1] << " " << pX[2] << endl; // print out the adc channel postition of the peaks tspecturm found (largest peak = px[0])
    
    if (pX[2]<pX[1]){
        pX[1]=pX[2];
    }
    
    cout << pX[0] << " " << pX[1] << endl;
    
   Double_t slope = (mn_ka1 - ti_ka1)/(pX[0] - pX[1]);// get the energy/adc channel slope in eV/ch by using the mn k-alpha and ti k-alpha
   Double_t offset = ti_ka1 - slope * pX[1]; // in eV

   //h1->Draw();
    
 

  //cout << slope << " " << offset << endl;


// ------------ refilling one histogram with energy bins
 
   Double_t dummie;
   dummie = 440 * slope + offset;
   Int_t lbin_ev = (Int_t)dummie;

   dummie = 2200 * slope + offset;
   Int_t ubin_ev = (Int_t)dummie;

   TH1F *h_en = new TH1F("Energy Histogram","Energy Histogram",1760,lbin_ev,ubin_ev); // creating a histogram with energy as x-axis, 1760 adc channels rebinned into 1760 eV channels 
   //(one eV channel does then not correspond to 1 eV)
   Double_t bin_ev;
   ifs.clear();                 // clear fail and eof bits
   ifs.seekg(0, std::ios::beg); // back to the start!

  while(ifs>>x1>>x2>>x3>>x4>>x5>>x6>>x7>>x8){
    n++;
    bin_ev = x1 * slope + offset; // filling this histogram with energy values by multiplying the adc channel values with slope
    h_en->Fill(bin_ev);
  
  }



    
// ------------------ fitting the energy histogram

 
  //TF1 *func   = new TF1 ("func","gaus(0) + gaus(3)",4000,8000); // fitting 2 gaussians to gaus(0), gaus(3) ... start numbering of the parameters for this function at 0 or 3
    
    TF1 *func   = new TF1 ("func",fitfunc,4000,8000,12);
    
    func -> SetParName(0, "Gain K_alpha(Ti)");
    func -> SetParName(3, "Gain K_beta(Ti)");
    func -> SetParName(6, "Gain K_alpha(Mn)");
    func -> SetParName(9, "Gain K_beta(Mn)");
    
    func -> SetParName(1, "Mean K_alpha1(Ti)");
    func -> SetParName(4, "Mean K_beta(Ti)");
    func -> SetParName(7, "Mean K_alpha1(Mn)");
    func -> SetParName(10,"Mean K_beta(Mn)");
    
    func -> SetParName(2, "Sigma K_alpha1(Ti)");
    func -> SetParName(5, "Sigma K_beta(Ti)");
    func -> SetParName(8, "Sigma K_alpha1(Mn)");
    func -> SetParName(11, "Sigma K_beta(Mn)");


  //func -> SetParameter(1,6400); // start for mean
  //func -> SetParameter(4,7058);

//  func -> SetParameter(1,4400); // start for mean
//  func -> SetParameter(4,5000);
//
//  func -> SetParameter(0,100); // start for gain
//  func -> SetParameter(3,30);
//
//  func -> SetParameter(2, 90); // start for sigma
//  func -> SetParameter(5, 90);
    
    func->SetParameter(0,pY[1]*100); // start for gain
    func->SetParameter(3,pY[1]*20);
    func->SetParameter(6,pY[0]*100);
    func->SetParameter(9,pY[0]*20);
    
    func->SetParameter(1,ti_ka1); // start for mean
    func->SetParameter(4,ti_kb);
    func->SetParameter(7,mn_ka1);
    func->SetParameter(10,mn_kb);
    
    Double_t sigma_start = 100;  // in eV
    
    func->SetParameter(2,sigma_start); // start for sigma in eV
    func->SetParameter(5,sigma_start);
    func->SetParameter(8,sigma_start);
    func->SetParameter(11,sigma_start);
    
  h_en -> Fit(func,"RIE");  // thats were the actual fit is done
  gStyle->SetOptFit(0);



  Double_t sig = func->GetParameter(8); // getting the fit parameter sigma for calculation of FWHM
  Double_t sigerr = func->GetParError(8);  //error on second parameter
    
  Double_t fwhm = sig * 2.355;
  Double_t fwhmerr = sigerr * 2.355;
    

  TCanvas *c2 = new TCanvas();
  gStyle->SetOptStat(0);


// ---------------- drawing the energy histogram
    

  h_en->GetXaxis()->SetTitle("Energy [eV]");
  h_en->GetYaxis()->SetTitle("Counts/7 eV"); // no idea were i got the 7 eV from, but I think its close to true
  //gStyle->SetOptStat(0);
  h_en -> Draw();
  //func->Draw("same");


  cout << "The energy resolution at 6.4 keV is approximately: (" << fwhm << "±" << fwhmerr << ") eV (FWHM)\n";
   
  
   
/*
    g1 = new TF1("m1","gaus",790,890);
    h1[0]->Fit(g1,"R");
    //h1[0]->Draw();

    //g2 = new TF1("m1","gaus",620,720);
    //h2[0]->Fit(g2,"R");
    //h2[0]->Draw();

    g3 = new TF1("m1","gaus",850,970);
    h3[0]->Fit(g3,"R");
    //h3[0]->Draw();

    g4 = new TF1("m1","gaus",850,970);
    h4[0]->Fit(g4,"R");
    //h4[0]->Draw();
*/


/*
  c1->Divide(3,2);

  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h3->Draw();
  c1->cd(3);
  h4->Draw();
  c1->cd(4);
  h5->Draw();
  c1->cd(5);
  h7->Draw();
  c1->cd(6);
  h8->Draw();   
*/

  
    //h1 is the total histogram; h1 is the signal and h2 is the background
//   double par[6];
//  TF1 *G1 = new TF1 ("G1","gaus",700,900);
//  TF1 *G2 = new TF1 ("G2","gaus",900,1000);

   //G1->FixParameter(1,0.0);
  // h1->G2(Fit,"R");
 //  h3->Fit(G2,"R");
  /*    
   G1->GetParameters(&par[0]);
    G2->GetParameters(&par[3]);

   TF1 *func   = new TF1 ("f","gaus(0)+gaus(3)",-3.0,3.0);
   func->SetParameters(par);
   h1->Fit(func,"R");
   func->SetLineColor(2);

        // 6 parameters of the fit: (p0 to p5)
   double Ncons  = func->GetParameter(0);
   double Gmean= func->GetParameter(1);
   double Gwdth = func->GetParameter(2);
*/

  //h1->Draw();
  //c1->Print(pdfname);
  //c1->Print(pdfname+"]");
  //f->Write();
  //f->Close();

}
