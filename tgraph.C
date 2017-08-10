Double_t peakLine(Double_t *x, Double_t *par){
    Double_t calib_line = par[0] + par[1] * x[0];
    return calib_line;
}

Int_t tgraph(){

Double_t pX_line[2] = {0.,1.};
Double_t pY_line[2] = {0.,2.};

Double_t pX[4] = {0.,1.,2.,5.};
Double_t pY[4] = {0.,1.,2.,3.};
Double_t pXEr[4] = {0.};
Double_t pYEr[4] = {0.1,0.1,0.1,0.1};

TGraphErrors *gre2cerr = new TGraphErrors(4, pX, pY, pXEr, pYEr );
TGraph *gre2c = new TGraph(2,pX_line,pY_line); // graph eV 2 channel

TF1 *fe2c = new TF1("fe2c",peakLine,-1,5,2);

    gre2cerr->SetMarkerStyle(20);
    gre2cerr->SetMarkerColor(4);
    gre2cerr->Draw("AP");
    
    gre2c->SetMarkerStyle(20);
    gre2c->SetMarkerColor(4);
    gre2c->Fit("fe2c", "R");
    gre2c->Draw("same");

return 0;
}
