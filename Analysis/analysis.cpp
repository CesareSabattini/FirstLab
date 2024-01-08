#include <iostream>

#include "../Classes/Particle.hpp"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"

Double_t fitFunction(Double_t *x, Double_t *par) {
  Double_t xx = x[0];
  Double_t val = par[0] * TMath::Exp(-(xx - par[1]) * (xx - par[1]) / 2. /
                                     par[2] / par[2]);
                                      return val;
}

int main() {
  TFile *file = new TFile("../Classes/Analysis.root", "read");
  TH1I *HistoTypes = (TH1I *)file->Get("HTypes");
  TH2D *HistoAngles = (TH2D *)file->Get("HAngles");
  TH1D *HistoImpulse = (TH1D *)file->Get("HP");
  TH1D *HistoTransverseImpulse = (TH1D *)file->Get("HTransverseImpulse");
  TH1D *HistoEnergy = (TH1D *)file->Get("HEnergy");
  TH1D *HistoInvariantMass = (TH1D *)file->Get("HInvariantMass");
  TH1D *HistoInvariantMassDiscordant = (TH1D *)file->Get("HMassDiscorde");
  HistoInvariantMassDiscordant->Sumw2();
  TH1D *HistoInvariantMassConcordant = (TH1D *)file->Get("HMassConcorde");
  HistoInvariantMassConcordant->Sumw2();
  TH1D *HistoMassPioneKaoneDiscorde =
      (TH1D *)file->Get("HMassPioneKaoneDiscorde");
  HistoMassPioneKaoneDiscorde->Sumw2();
  TH1D *HistoMassPioneKaoneConcorde =
      (TH1D *)file->Get("HMassPioneKaoneConcorde");
  HistoMassPioneKaoneConcorde->Sumw2();
  TH1D *HistoMassDecay = (TH1D *)file->Get("HMassKDecay");

  int totalElems = HistoTypes->GetEntries();

  std::cout << "Entries:" << std::endl;
  std::cout << "Types entries:" << totalElems << std::endl;
  std::cout << "Angles entries:" << HistoAngles->GetEntries() << std::endl;
  std::cout << "Momentum entries:" << HistoImpulse->GetEntries() << std::endl;
  std::cout << "Transverse Momentum entries:"
            << HistoTransverseImpulse->GetEntries() << std::endl;
  std::cout << "Energy entries:" << HistoEnergy->GetEntries() << std::endl;
  std::cout << "Invariant Mass entries:" << HistoInvariantMass->GetEntries()
            << std::endl;
  std::cout << "Discordant Invariant Mass entries:"
            << HistoInvariantMassDiscordant->GetEntries() << std::endl;
  std::cout << "Concordant Invariant Mass entries:"
            << HistoInvariantMassConcordant->GetEntries() << std::endl;
  std::cout << "Discordant Pion and Kaon entries:"
            << HistoMassPioneKaoneDiscorde->GetEntries() << std::endl;
  std::cout << "Concordant Pion and Kaon entries:"
            << HistoMassPioneKaoneConcorde->GetEntries() << std::endl;
  std::cout << "Decay entries:" << HistoMassDecay->GetEntries() << std::endl;

  std::array<double, 7> proportions{};
  for (int i = 1; i <= 7; i++) {
    proportions[i - 1] = HistoTypes->GetBinContent(i) / totalElems;
  }

  std::cout << std::endl;
  std::cout << "Proportions:" << std::endl;
  std::cout << "Pion fraction:" << proportions[0] << std::endl;
  std::cout << "Kaon fraction:" << proportions[1] << std::endl;
  std::cout << "Proton fraction:" << proportions[2] << std::endl;
  std::cout << "AntiPion fraction:" << proportions[3] << std::endl;
  std::cout << "AntiKaon fraction:" << proportions[4] << std::endl;
  std::cout << "AntiProton fraction:" << proportions[5] << std::endl;
  std::cout << "K* fraction:" << proportions[6] << std::endl;

  TCanvas *firstCanvas = new TCanvas("firstCanvas", "first canvas", 1000, 1000);
  firstCanvas->Divide(2, 2);

  firstCanvas->cd(1);
  TF1 *thetaFit = new TF1("thetaFit", "[0]", 0, 3.5);
  thetaFit->SetParameter(0, 1e7 / 1000);
  HistoAngles->ProjectionX()->Fit(thetaFit);
  HistoAngles->ProjectionX()->Draw();

  firstCanvas->cd(2);
  TF1 *phiFit = new TF1("phiFit", "[0]", 0, 7);
  phiFit->SetParameter(0, 1e7 / 1000);
  HistoAngles->ProjectionY()->Fit(phiFit);
  HistoAngles->ProjectionY()->Draw();

  std::cout << "ThetaEntries=" << thetaFit->GetParameter(0);
  std::cout << std::endl;
  std::cout << "PhiEntries=" << phiFit->GetParameter(0);
  std::cout << std::endl;
  std::cout << "ThetaFit Reduced ChiSquare="
            << thetaFit->GetChisquare() / thetaFit->GetNDF();
  std::cout << std::endl;
  std::cout << "PhiFit Reduced ChiSquare="
            << phiFit->GetChisquare() / phiFit->GetNDF();
  std::cout << std::endl;
  std::cout << "ThetaFit Probability=" << thetaFit->GetProb();
  std::cout << std::endl;
  std::cout << "PhiFit Probability=" << phiFit->GetProb();
  std::cout << std::endl;

  TF1 *impulseFit = new TF1("impulseFit", "exp([0]+[1]*x)", 0, 10);
  impulseFit->SetParameters(3, 1);
  HistoImpulse->Fit(impulseFit);
  std::cout << "ImpulseFit par1=" << impulseFit->GetParameter(0);
  std::cout << std::endl;
  std::cout << "ImpulseFit par2=" << impulseFit->GetParameter(1);
  std::cout << std::endl;
  std::cout << "ImpulseFit Reduced ChiSquare="
            << impulseFit->GetChisquare() / impulseFit->GetNDF();
  std::cout << std::endl;
  std::cout << "ImpulseFit Probability=" << impulseFit->GetProb();
  std::cout << std::endl;
  firstCanvas->cd(3);
  HistoImpulse->Draw();

  firstCanvas->cd(4);
  HistoTypes->Draw();

  TCanvas *secondCanvas = new TCanvas(
      "secondCanvas", "Invariant Mass Histos subtractions", 1000, 1000);
  secondCanvas->Divide(2, 2);
  secondCanvas->cd(1);
  HistoInvariantMass->Draw();
  secondCanvas->cd(2);
  TF1 *gaussFit1 = new TF1("gaussFit1", fitFunction, 0.7, 1.1, 3); 
  gaussFit1->SetParameters(1.78, 0.89, 0.05);
  TH1D *DifferenzaGenerale =
      new TH1D("DifferenzaGenerale", "DifferenzaGenerale", 1000, 0.7, 1.1);
  DifferenzaGenerale->Sumw2();
  DifferenzaGenerale->Add(HistoInvariantMassDiscordant, 1);
  DifferenzaGenerale->Add(HistoInvariantMassConcordant, -1);
  DifferenzaGenerale->Fit(gaussFit1);
  std::cout << "GaussFit1 par1=" << gaussFit1->GetParameter(0);
  std::cout << std::endl;
  std::cout << "GaussFit1 par2=" << gaussFit1->GetParameter(1);
  std::cout << std::endl;
  std::cout << "GaussFit1 Reduced ChiSquare="
            << gaussFit1->GetChisquare() / gaussFit1->GetNDF();
  std::cout << std::endl;
  std::cout << "GaussFit1 Probability=" << gaussFit1->GetProb();
  std::cout << std::endl;
  DifferenzaGenerale->Draw();
  secondCanvas->cd(3);
  TF1 *gaussFit2 = new TF1("gaussFit2", fitFunction, 0.7, 1.1, 3); 
  gaussFit2->SetParameters(1.78, 0.89, 0.05);
  TH1D *DifferenzaPioneKaone =
      new TH1D("DifferenzaPioneKaone", "DifferenzaPioneKaone", 1000, 0.7, 1.1);
  DifferenzaPioneKaone->Sumw2();
  DifferenzaPioneKaone->Add(HistoMassPioneKaoneDiscorde, 1);
  DifferenzaPioneKaone->Add(HistoMassPioneKaoneConcorde, -1);
  DifferenzaPioneKaone->Fit(gaussFit2);
    std::cout << "GaussFit2 par1=" << gaussFit2->GetParameter(0);
  std::cout << std::endl;
  std::cout << "GaussFit2 par2=" << gaussFit2->GetParameter(1);
  std::cout << std::endl;
  std::cout << "GaussFit2 Reduced ChiSquare="
            << gaussFit2->GetChisquare() / gaussFit2->GetNDF();
  std::cout << std::endl;
  std::cout << "GaussFit2 Probability=" << gaussFit2->GetProb();
  std::cout << std::endl;
  DifferenzaPioneKaone->Draw();

  return 0;
}