#include "../Classes/Particle.hpp"
#include "../Classes/ParticleType.hpp"
#include "../Classes/ResonanceType.hpp"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TRandom.h"

int macro() {
    Particle::addParticleType("Pione", 0.13957, 1);
    Particle::addParticleType("Kaone", 0.49367, 1);
    Particle::addParticleType("Protone", 0.93827, 1);
    Particle::addParticleType("AntiPione", 0.13957, -1);
    Particle::addParticleType("AntiKaone", 0.49367, -1);
    Particle::addParticleType("AntiProtone", 0.93827, -1);
    Particle::addParticleType("K*", 0.89166, 0, 0.050);
    gRandom->SetSeed();
    std::array<Particle, 120> eventParticles{};
    int numDecays = 0;

    TH1I *HTypes =
        new TH1I("HTypes", "Types of particles distribution", 8, 0, 8);
    TH2D *HAngles = new TH2D("HAngles", "Angles distribution", 1000, 0, 2 * 3.5,
                             1000, 0, 3.5);
    TH1D *HP = new TH1D("HP", "Momentum distribution", 200, 0, 10);
    TH1D *HTransverseImpulse = new TH1D(
        "HTransverseImpulse", "Transverse Momentum distribution", 200, 0, 10);
    TH1D *HEnergy = new TH1D("HEnergy", " Energy", 200, 0, 10);
    TH1D *HInvariantMass =
        new TH1D("HInvariantMass", " Invariant Mass distribution", 900, 0, 5);
    HInvariantMass->Sumw2();
    TH1D *HMassDiscorde =
        new TH1D("HMassDiscorde",
                 "Invariant Mass for opposite charged particles distribution",
                  1000, 0.5, 1.3);
    HMassDiscorde->Sumw2();
    TH1D *HMassConcorde =
        new TH1D("HMassConcorde",
                 "Invariant Mass for concordant charged particles distribution",
                  1000, 0.5, 1.3);
    HMassConcorde->Sumw2();
    TH1D *HMassPioneKaoneDiscorde = new TH1D(
        "HMassPioneKaoneDiscorde",
        "Invariant Mass for opposite charged Pion and Kaon distribution",  1000, 0.5, 1.3);
    HMassPioneKaoneDiscorde->Sumw2();
    TH1D *HMassPioneKaoneConcorde = new TH1D(
        "HMassPioneKaoneConcorde",
        "Invariant Mass for concordant charged Pion and Kaon distribution",
         1000, 0.5, 1.3);
    HMassPioneKaoneConcorde->Sumw2();
    TH1D *HMassKDecay =
        new TH1D("HMassKDecay",
                 "Invariant Mass for the children of each decay distribution",
                 1000, 0.5, 1.3);
    HMassKDecay->Sumw2();

    for (int i = 0; i < 1E3
    ; i++) {
        numDecays = 0;
        for (int j = 0; j <= 100; j++) {
            double phi = gRandom->Uniform(0, 2 * TMath::Pi());
            double theta = gRandom->Uniform(0, TMath::Pi());
            HAngles->Fill(phi, theta);
            double probability{};
            probability = gRandom->Rndm();
            if (probability <= 0.01) {
                eventParticles[j].setIndex(6);
            } else if (probability < 0.10) {

                double chargeProbability = gRandom->Rndm();
                if (chargeProbability <= 0.5) {
                    eventParticles[j].setIndex(2);
                } else {
                    eventParticles[j].setIndex(5);
                }
            } else if (probability < 0.20) {

                double chargeProbability = gRandom->Rndm();
                if (chargeProbability <= 0.5) {
                    eventParticles[j].setIndex(1);
                } else {
                    eventParticles[j].setIndex(4);
                }
            } else if (probability < 1) {

                double chargeProbability = gRandom->Rndm();
                if (chargeProbability <= 0.5) {
                    eventParticles[j].setIndex(0);
                } else {
                    eventParticles[j].setIndex(3);
                }
            }
            double p = gRandom->Exp(1);
            HP->Fill(p);
            double px = p * TMath::Sin(theta) * TMath::Sin(phi);
            double py = p * TMath::Sin(theta) * TMath::Cos(phi);
            double pz = p * TMath::Cos(theta);
            eventParticles[j].setImpulse(px, py, pz);
            HTransverseImpulse->Fill(eventParticles[j].getTransverseImpulse());
            HTypes->Fill(eventParticles[j].getIndex());

            if (eventParticles[j].getIndex() == 6) {
                double decayProbability = gRandom->Rndm();
                numDecays += 1;
                if (decayProbability <= 0.5) {
                    
                    Particle kaone("Kaone");
                    Particle antiPione("AntiPione");
                    eventParticles[j].Decay2body(kaone, antiPione);
                    eventParticles[100 + numDecays] = kaone;
                    eventParticles[j] = antiPione;
                    HMassKDecay->Fill(kaone.getInvariantMass(antiPione));
                    
                } else {
                    Particle antiKaone("AntiKaone");
                    Particle pione("Pione");
                    eventParticles[j].Decay2body(antiKaone, pione);
                    eventParticles[100 + numDecays] = antiKaone;
                    eventParticles[j] = pione;
                    HMassKDecay->Fill(antiKaone.getInvariantMass(pione));
                    
                }
            }

            HEnergy->Fill(eventParticles[j].getEnergy());
        }

        for (int k = 0; k < 100+numDecays; k++) {
            for (int j = k + 1; j <= 100+numDecays; j++) {
                HInvariantMass->Fill(
                    eventParticles[k].getInvariantMass(eventParticles[j]));
                if (Particle::m_particle_type[eventParticles[k].getIndex()]
                        ->getCharge() !=
                    Particle::m_particle_type[eventParticles[j].getIndex()]
                        ->getCharge()) {
                    HMassDiscorde->Fill(
                        eventParticles[j].getInvariantMass(eventParticles[k]));
                }
                if (Particle::m_particle_type[eventParticles[k].getIndex()]
                        ->getCharge() ==
                    Particle::m_particle_type[eventParticles[j].getIndex()]
                        ->getCharge()) {
                    HMassConcorde->Fill(
                        eventParticles[k].getInvariantMass(eventParticles[j]));
                }
                if ((eventParticles[k].getIndex() == 0 &&
                     eventParticles[j].getIndex() == 4) ||
                    (eventParticles[k].getIndex() == 4 &&
                     eventParticles[j].getIndex() == 0) ||
                    (eventParticles[k].getIndex() == 3 &&
                     eventParticles[j].getIndex() == 1) ||
                    (eventParticles[k].getIndex() == 1 &&
                     eventParticles[j].getIndex() == 3)) {
                    HMassPioneKaoneDiscorde->Fill(
                        eventParticles[j].getInvariantMass(eventParticles[k]));
                }
                if ((eventParticles[k].getIndex() == 0 &&
                     eventParticles[j].getIndex() == 1) ||
                    (eventParticles[k].getIndex() == 1 &&
                     eventParticles[j].getIndex() == 0) ||
                    (eventParticles[k].getIndex() == 3 &&
                     eventParticles[j].getIndex() == 4) ||
                    (eventParticles[k].getIndex() == 4 &&
                     eventParticles[j].getIndex() == 3)) {
                    HMassPioneKaoneConcorde->Fill(
                        eventParticles[j].getInvariantMass(eventParticles[k]));
                }
            }
        }
    }


    TFile *file = new TFile("Analysis.root", "recreate");
    file->Write();
    file->cd();

    TCanvas *canvas1 = new TCanvas("TypesCanvas", "canvas1", 1000, 1000);
 canvas1->Divide(2,2);
 canvas1->cd(1);
    HTypes->Draw();
    HTypes->Write();

 canvas1->cd(2);
    HAngles->Draw();
    HAngles->Write();

 canvas1->cd(3);
    HP->Draw();
    HP->Write();

canvas1->cd(4);
    HTransverseImpulse->Draw();
    HTransverseImpulse->Write();

    TCanvas *canvas2 = new TCanvas("InvariantMassCanvas", "canvas2", 1000, 1000);
 canvas2->Divide(3,2);
canvas2->cd(1);
    HInvariantMass->Draw();
    HInvariantMass->Write();

canvas2->cd(2);
    HMassDiscorde->Draw();
    HMassDiscorde->Write();

canvas2->cd(3);
    HMassConcorde->Draw();
    HMassConcorde->Write();

canvas2->cd(4);
    HMassPioneKaoneDiscorde->Draw();
    HMassPioneKaoneDiscorde->Write();

canvas2->cd(5);
    HMassPioneKaoneConcorde->Draw();
    HMassPioneKaoneConcorde->Write();

canvas2->cd(6);
    HMassKDecay->Draw();
    HMassKDecay->Write();

  TCanvas *canvas3 = new TCanvas("EnergyCanvas", "canvas3", 1000, 1000);

    HEnergy->Draw();
    HEnergy->Write();

    file->Close();
    file->ReadAll();
    file->Cp("../Root_Files", kTRUE, 300398);

 
    return 0;
}