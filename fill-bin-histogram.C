{
    gROOT->Reset();
    
    
    TH1F *hist = new TH1F("hist","hist",100,-2,2);
    
    for(Int_t i = 0; i < 1000; i++){
        
        hist->Fill(0);
    
    }
    
    hist->Fit("gaus");
    
    hist->Draw();
    
    
}