#include"../Classes/ParticleType.hpp"
#include"../Classes/ResonanceType.hpp"
#include"../Classes/Particle.hpp"
#include<cmath>
int macro(){
Particle::addParticleType("Pione", 0.13957,1);
Particle::addParticleType("Kaone", 0.49367 ,1);
Particle::addParticleType("Protone", 0.93827,1);
Particle::addParticleType("AntiPione", 0.13957,-1);
Particle::addParticleType("AntiKaone", 0.49367 ,-1);
Particle::addParticleType("AntiProtone", 0.93827,-1);
Particle::addParticleType("K*", 0.89166, 0, 0.050);
gRandom->SetSeed();
std::array<Particle, 120> eventParticles{};
int numDecays=0;

TH1I* HTypes= new TH1I("HTypes", "Types of particles", 8, 0,8);
TH2D* HAngles= new TH2D("HAngles", "Angles", 1000, 0,2*3.5, 1000, 0,3.5);//???
TH1D* HP= new TH1D("HP", "Impulse",200, 0, 10 );
TH1D* HTransverseImpulse= new TH1D("HTransverseImpulse","Transverse Impulse", 200, 0, 10 );
TH1D* HEnergy= new TH1D("HEnergy"," Energy", 200, 0,10 );
TH1D* HInvariantMass= new TH1D("HInvariantMass"," Invariant Mass", 1000, 0,5 );
HInvariantMass->Sumw2();
TH1D* HMassDiscorde = new TH1D("HMassDiscorde", "", 1000, 0,5);
HMassDiscorde->Sumw2();
TH1D* HMassConcorde = new TH1D("HMassConcorde", "", 1000, 0,5);
HMassConcorde->Sumw2();
TH1D* HMassPioneKaoneDiscorde = new TH1D("HMassPioneKaoneDiscorde", "", 1000, 0,5);
HMassPioneKaoneDiscorde->Sumw2();
TH1D* HMassPioneKaoneConcorde = new TH1D("HMassPioneKaoneConcorde", "", 1000, 0,5);
HMassPioneKaoneConcorde->Sumw2();
TH1D* HMassKDecay = new TH1D("HMassKDecay", "Benchmark", 1000, 0,5);
HMassKDecay->Sumw2();


for(int i=0;i<1E3;i++ ){
numDecays=0;
for(int j=0; j<=100;j++){
    double phi= gRandom->Uniform(0,2*3.14);
    double theta= gRandom->Uniform(0,3.14);
    HAngles->Fill(phi,theta);
double probability{};
probability=gRandom->Rndm();
if(probability<=0.01){
eventParticles[j].setIndex(6);
}
else if(probability<0.10){

double chargeProbability=gRandom->Rndm();
if(chargeProbability<=0.5){
eventParticles[j].setIndex(2);
}
else {
   eventParticles[j].setIndex(5); 
}
}
else if(probability<0.20){
    
double chargeProbability=gRandom->Rndm();
if(chargeProbability<=0.5){
eventParticles[j].setIndex(1);
}
else {
   eventParticles[j].setIndex(4); 
}
}
else if(probability<1){
    
double chargeProbability=gRandom->Rndm();
if(chargeProbability<=0.5){
eventParticles[j].setIndex(0);
}
else {
   eventParticles[j].setIndex(3); 
}
}
double p=gRandom->Exp(1);
HP->Fill(p);
double px= p*TMath::Sin(theta)*TMath::Sin(phi);
double py= p*TMath::Sin(theta)*TMath::Cos(phi);
double pz= p*TMath::Cos(theta);
eventParticles[j].setImpulse(px,py,pz);
HTransverseImpulse->Fill(eventParticles[j].getTransverseImpulse());
HTypes->Fill(eventParticles[j].getIndex());

if(eventParticles[j].getIndex()==6){
double decayProbability=gRandom->Rndm();
if(decayProbability<=0.5){
    Particle kaone("Kaone");
    Particle antiPione("AntiPione");
    eventParticles[j].Decay2body(kaone,antiPione);
    eventParticles[100+numDecays]=kaone;
   eventParticles[j]=antiPione;
   HMassKDecay->Fill(kaone.getInvariantMass(antiPione));
   numDecays+=1;
}
else{
    Particle antiKaone("AntiKaone");
    Particle pione("Pione");
    eventParticles[j].Decay2body(antiKaone, pione);
    eventParticles[100+numDecays]=antiKaone;
    eventParticles[j]=pione;
    HMassKDecay->Fill(antiKaone.getInvariantMass(pione));
    numDecays+=1;
}

}

HEnergy->Fill(eventParticles[j].getEnergy());
}
for(int k=0; k<eventParticles.size()-1; k++){
for(int j=k+1; j<eventParticles.size(); j++){
 HInvariantMass->Fill(eventParticles[k].getInvariantMass(eventParticles[j]));
if(Particle::m_particle_type[eventParticles[k].getIndex()]->getCharge()!=Particle::m_particle_type[eventParticles[j].getIndex()]->getCharge()){
HMassDiscorde->Fill(eventParticles[k].getInvariantMass(eventParticles[j]));
}
if(Particle::m_particle_type[eventParticles[k].getIndex()]->getCharge()==Particle::m_particle_type[eventParticles[j].getIndex()]->getCharge()){
HMassConcorde->Fill(eventParticles[k].getInvariantMass(eventParticles[j]));
}
if((eventParticles[k].getIndex()==0 && eventParticles[j].getIndex()==4) || (eventParticles[k].getIndex()==4 && eventParticles[j].getIndex()==0) ||(eventParticles[k].getIndex()==3 && eventParticles[j].getIndex()==1)||(eventParticles[k].getIndex()==1 && eventParticles[j].getIndex()==3 )){
HMassPioneKaoneDiscorde->Fill(eventParticles[k].getInvariantMass(eventParticles[j]));
}
if((eventParticles[k].getIndex()==0 && eventParticles[j].getIndex()==1) || (eventParticles[k].getIndex()==1 && eventParticles[j].getIndex()==0) ||(eventParticles[k].getIndex()==3 && eventParticles[j].getIndex()==4)||(eventParticles[k].getIndex()==4 && eventParticles[j].getIndex()==3) ){
HMassPioneKaoneConcorde->Fill(eventParticles[k].getInvariantMass(eventParticles[j]));
}
}

}


}

TCanvas* canvas= new TCanvas("canvas","canvas1", 1000,1000);
canvas->Divide(4,3);

TFile* file = new TFile("example.root","recreate");
file->Write();

canvas->cd(1);
HTypes->Draw();
HTypes->Write();

canvas->cd(2);
HAngles->Draw();
HAngles->Write();

canvas->cd(3);
HP->Draw();
HP->Write();

canvas->cd(4);
HTransverseImpulse->Draw();
HTransverseImpulse->Write();

canvas->cd(5);
HEnergy->Draw();
HEnergy->Write();

canvas->cd(6);
 HInvariantMass->Draw();
 HInvariantMass->Write();

 canvas->cd(7);
 HMassDiscorde ->Draw();
 HMassDiscorde->Write();

 canvas->cd(8);
 HMassConcorde->Draw();
 HMassConcorde->Write();

 canvas->cd(9);
HMassPioneKaoneDiscorde ->Draw();
HMassPioneKaoneDiscorde->Write();

canvas->cd(10);
HMassPioneKaoneConcorde ->Draw();
HMassPioneKaoneConcorde->Write();

canvas->cd(11);
HMassKDecay->Draw();
HMassKDecay->Write();
file->Close();

return 0;
}