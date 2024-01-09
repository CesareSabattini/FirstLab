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
    TH1I *HistoTypes = (TH1I *)file->Get("Species counts data");
    TH2D *HistoAngles = (TH2D *)file->Get("HAngles");
    TH1D *HistoImpulse = (TH1D *)file->Get("Momentum module data");
    TH1D *HistoTransverseImpulse =
        (TH1D *)file->Get("Transverse momentum module data");
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
    TH1D *HistoMassDecay = (TH1D *)file->Get("Decay IM data");

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

    std::array<double, 7> entries{};
    for (int i = 1; i <= 7; i++) {
        entries[i - 1] = HistoTypes->GetBinContent(i);
    }

    std::cout << std::endl;
    std::cout << "Species Entries:" << std::endl;
    std::cout << "Pion:" << entries[0] << std::endl;
    std::cout << "Kaon:" << entries[1] << std::endl;
    std::cout << "Proton:" << entries[2] << std::endl;
    std::cout << "AntiPion:" << entries[3] << std::endl;
    std::cout << "AntiKaon:" << entries[4] << std::endl;
    std::cout << "AntiProton:" << entries[5] << std::endl;
    std::cout << "K*:" << entries[6] << std::endl;

    TCanvas *firstCanvas =
        new TCanvas("firstCanvas", "first canvas", 1000, 1000);
    firstCanvas->Divide(2, 2);

    firstCanvas->cd(1);
    TH1D *histoTheta = new TH1D(*HistoAngles->ProjectionX());
    histoTheta->SetName("Theta data");
    histoTheta->SetTitle("#bf{Polar angle distribution (Theta)}");
    histoTheta->GetXaxis()->CenterTitle(true);
    histoTheta->GetXaxis()->SetTitleSize(.04);
    histoTheta->GetXaxis()->SetTitle("Theta");
    histoTheta->GetYaxis()->SetTitleSize(.04);
    histoTheta->GetYaxis()->CenterTitle(true);
    histoTheta->GetYaxis()->SetTitle("Counts");
    TF1 *thetaFit = new TF1("thetaFit", "[0]", 0, 3.5);
    thetaFit->SetParameter(0, 1e7 / 1000);
    histoTheta->Fit(thetaFit);

    histoTheta->Draw();

    firstCanvas->cd(2);
    TH1D *histoPhi = new TH1D(*HistoAngles->ProjectionY());
    histoPhi->SetName("Phi data");
    histoPhi->SetTitle("#bf{Azimutal angle distribution (Phi)}");
    histoPhi->GetXaxis()->CenterTitle(true);
    histoPhi->GetXaxis()->SetTitleSize(.04);
    histoPhi->GetXaxis()->SetTitle("Phi");
    histoPhi->GetYaxis()->CenterTitle(true);
    histoPhi->GetYaxis()->SetTitleSize(.04);
    histoPhi->GetYaxis()->SetTitle("Counts");
    TF1 *phiFit = new TF1("phiFit", "[0]", 0, 7);
    phiFit->SetParameter(0, 1e7 / 1000);
    histoPhi->Fit(phiFit);
    histoPhi->Draw();

    std::cout << "Theta p0=" << thetaFit->GetParameter(0) << "+/-"
              << thetaFit->GetParError(0);
    std::cout << std::endl;
    std::cout << "Phi p0=" << phiFit->GetParameter(0) << "+/-"
              << phiFit->GetParError(0);
    std::cout << std::endl;

    std::cout << "ThetaFit ChiSquare=" << thetaFit->GetChisquare();
    std::cout << std::endl;
    std::cout << "PhiFit ChiSquare=" << phiFit->GetChisquare();
    std::cout << std::endl;

    std::cout << "ThetaFit NDF=" << thetaFit->GetNDF();
    std::cout << std::endl;
    std::cout << "PhiFit NDF=" << phiFit->GetNDF();
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

    firstCanvas->cd(3);
    TF1 *impulseFit = new TF1("impulseFit", "exp([0]+[1]*x)", 0, 10);
    impulseFit->SetParameters(3, 1);
    HistoImpulse->GetXaxis()->CenterTitle(true);
    HistoImpulse->GetXaxis()->SetTitleSize(.04);
    HistoImpulse->GetXaxis()->SetTitle("Impulse Module (GeV/c^2*m/s)");
    HistoImpulse->GetYaxis()->CenterTitle(true);
    HistoImpulse->GetYaxis()->SetTitleSize(.04);
    HistoImpulse->GetYaxis()->SetTitle("Counts");
    HistoImpulse->Fit(impulseFit);
    std::cout << "ImpulseFit par1=" << impulseFit->GetParameter(0) << "+/-"
              << impulseFit->GetParError(0);
    std::cout << std::endl;
    std::cout << "ImpulseFit par2=" << impulseFit->GetParameter(1) << "+/-"
              << impulseFit->GetParError(1);
    std::cout << std::endl;
    std::cout << "ImpulseFit ChiSquare=" << impulseFit->GetChisquare();
    std::cout << std::endl;

    std::cout << "ImpulseFit NDF=" << impulseFit->GetNDF();
    std::cout << std::endl;

    std::cout << "ImpulseFit Reduced ChiSquare="
              << impulseFit->GetChisquare() / impulseFit->GetNDF();
    std::cout << std::endl;

    std::cout << "ImpulseFit Probability=" << impulseFit->GetProb();
    std::cout << std::endl;

    HistoImpulse->Draw();

    firstCanvas->cd(4);
    HistoTypes->GetXaxis()->CenterTitle(true);
    HistoTypes->GetXaxis()->SetTitleSize(.04);
    HistoTypes->GetXaxis()->SetTitle("Particle Species");
    HistoTypes->GetYaxis()->CenterTitle(true);
    HistoTypes->GetYaxis()->SetTitleSize(.04);
    HistoTypes->GetYaxis()->SetTitle("Counts");

    HistoTypes->Draw();

    TCanvas *secondCanvas = new TCanvas(
        "secondCanvas", "Invariant Mass Histos subtractions", 1000, 1000);
    secondCanvas->Divide(2, 2);
    secondCanvas->cd(1);
    TF1 *gaussFit3 = new TF1("gaussFit3", fitFunction, 0.7, 1.1, 3);
    gaussFit3->SetParameters(1.78, 0.89, 0.05);
    HistoMassDecay->Draw();
    HistoMassDecay->Fit(gaussFit3);

    std::cout << "VALORI DELLA MASSA INVARIANTE DELLE K* VERE" << std::endl;
    std::cout << "par1=" << gaussFit3->GetParameter(0) << "+/-"
              << gaussFit3->GetParError(0);
    std::cout << std::endl;
    std::cout << "par2=" << gaussFit3->GetParameter(1) << "+/-"
              << gaussFit3->GetParError(1);
    std::cout << std::endl;

    std::cout << "sigma=" << HistoMassDecay->GetRMS() << "+/-"
              << HistoMassDecay->GetRMSError();
    std::cout << std::endl;

    std::cout << "Reduced ChiSquare="
              << gaussFit3->GetChisquare() / gaussFit3->GetNDF();
    std::cout << std::endl;
    std::cout << "Fit Probability=" << gaussFit3->GetProb();
    std::cout << std::endl;

    secondCanvas->cd(2);

    TF1 *gaussFit1 = new TF1("gaussFit1", fitFunction, 0.7, 1.1, 3);
    gaussFit1->SetParameters(1.78, 0.89, 0.05);
    TH1D *DifferenzaGenerale =
        new TH1D("All particles subtraction IM data",
                 "#bf{All particles subtraction IM data}", 40, 0.7, 1.1);

    DifferenzaGenerale->Sumw2();
    DifferenzaGenerale->Add(HistoInvariantMassDiscordant, 1);
    DifferenzaGenerale->Add(HistoInvariantMassConcordant, -1);
    DifferenzaGenerale->GetXaxis()->CenterTitle(true);
    DifferenzaGenerale->GetXaxis()->SetTitleSize(.04);
    DifferenzaGenerale->GetXaxis()->SetTitle("Invariant Mass(GeV/c^2)");
    DifferenzaGenerale->GetYaxis()->CenterTitle(true);
    DifferenzaGenerale->GetYaxis()->SetTitleSize(.04);
    DifferenzaGenerale->GetYaxis()->SetTitle("Counts");
    DifferenzaGenerale->Fit(gaussFit1);

    std::cout << "VALORI DELLA MASSA INVARIANTE DISCORDE-CONCORDE" << std::endl;
    std::cout << "par1=" << gaussFit1->GetParameter(0) << "+/-"
              << gaussFit1->GetParError(0);
    std::cout << std::endl;
    std::cout << "par2=" << gaussFit1->GetParameter(1) << "+/-"
              << gaussFit1->GetParError(1);
    std::cout << std::endl;

    std::cout << "sigma=" << DifferenzaGenerale->GetRMS() << "+/-"
              << DifferenzaGenerale->GetRMSError();
    std::cout << std::endl;

    std::cout << "Reduced ChiSquare="
              << gaussFit1->GetChisquare() / gaussFit1->GetNDF();
    std::cout << std::endl;
    std::cout << "Fit Probability=" << gaussFit1->GetProb();
    std::cout << std::endl;
    DifferenzaGenerale->Draw();
    secondCanvas->cd(3);

    TF1 *gaussFit2 = new TF1("gaussFit2", fitFunction, 0.7, 1.1, 3);
    gaussFit2->SetParameters(1.78, 0.89, 0.05);
    TH1D *DifferenzaPioneKaone = new TH1D(
        "PK subtraction IM data", "#bf{PK subtraction IM data}", 40, 0.7, 1.1);
    DifferenzaPioneKaone->Sumw2();
    DifferenzaPioneKaone->Add(HistoMassPioneKaoneDiscorde, 1);
    DifferenzaPioneKaone->Add(HistoMassPioneKaoneConcorde, -1);
    DifferenzaPioneKaone->GetXaxis()->CenterTitle(true);
    DifferenzaPioneKaone->GetXaxis()->SetTitleSize(.04);
    DifferenzaPioneKaone->GetXaxis()->SetTitle("Invariant Mass(GeV/c^2)");
    DifferenzaPioneKaone->GetYaxis()->CenterTitle(true);
    DifferenzaPioneKaone->GetYaxis()->SetTitleSize(.04);
    DifferenzaPioneKaone->GetYaxis()->SetTitle("Counts");
    DifferenzaPioneKaone->Fit(gaussFit2);

    std::cout << "VALORI DELLA MASSA INVARIANTE PK DISCRDE-CONCORDE"
              << std::endl;

    std::cout << "par1=" << gaussFit2->GetParameter(0) << "+/-"
              << gaussFit2->GetParError(0);
    std::cout << std::endl;
    std::cout << "par2=" << gaussFit2->GetParameter(1) << "+/-"
              << gaussFit2->GetParError(1);
    std::cout << std::endl;

    std::cout << "sigma=" << DifferenzaPioneKaone->GetRMS() << "+/-"
              << DifferenzaPioneKaone->GetRMSError();
    std::cout << std::endl;

    std::cout << "Reduced ChiSquare="
              << gaussFit2->GetChisquare() / gaussFit2->GetNDF();
    std::cout << std::endl;
    std::cout << "Fit Probability=" << gaussFit2->GetProb();
    std::cout << std::endl;
    DifferenzaPioneKaone->Draw();

    return 0;
}