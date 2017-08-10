#include "TMath.h"

Double_t gaussian(Double_t *x, Double_t *par){
    
    //par[0] = gain
    //par[1] = mean
    //par[2] = sigma
    Double_t xx = x[0];
    
    Double_t gaussi1 = par[0]/(sqrt(2*TMath::Pi())*par[2])*TMath::Exp(-((xx-par[1])*(xx-par[1]))/(2*par[2]*par[2]));
    
    Double_t gaussi2 = par[0]/(sqrt(2*TMath::Pi())*par[2])*TMath::Exp(-((xx-(par[1]+2))*(xx-(par[1]+2)))/(2*par[2]*par[2]));
    
    Double_t gaussi = gaussi1 + gaussi2;
    
    return gaussi;
    
}

int defining_func(){

    TF1 *func = new TF1("gaussi",gaussian,-2,4,3);
    
    func->SetParameter(0,1);
    func->SetParameter(1,0);
    func->SetParameter(2,1);

    func->Draw();
    
    return 0;


}