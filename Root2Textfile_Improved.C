{

    gROOT->Reset();
    
TFile *f = new TFile("fin.root");
TTree *tree = (TTree*)f->Get("tr");
TH1F *htmp = (TH1F*)f->Get("hEnergySDD20;1");

htmp->Draw();

ofstream txt_file;
txt_file.open("hEnergySDD20.txt");

Int_t binN = htmp->GetSize();
cout << binN << endl;

//Int_t ent = tr->GetEntries();
Int_t x,y;

for(Int_t i = 0; i < 252; i++){

 y = htmp->GetBinContent(i);
 x = htmp->GetBinCenter(i);

 txt_file << x << " " << y << endl;

}

txt_file.close();

}
