#include "Particle.hpp"
#include <cmath>

std::vector<ParticleType *> Particle::m_particle_type;
int Particle::m_nParticleType = 0;

Particle::Particle(const std::string name, double impulseX, double impulseY,
                   double impulseZ) {
    m_index = findParticle(name);
    m_nParticleType = m_particle_type.size();
}

int Particle::findParticle(const std::string name) {
    for (int i{}; i <= static_cast<int>(m_particle_type.size()); i++) {
        if (m_particle_type[i]->getName() == name) {
            return i;
        }
    }
}

int Particle::getIndex() const { return m_index; }

void Particle::addParticleType(std::string name, double mass, int charge,
                               double width) {
    if (m_nParticleType < m_maxNumParticleType) {
        ResonanceType *newType = new ResonanceType(name, mass, charge, width);
        if (width == 0) {
            dynamic_cast<ParticleType *>(newType);
        }
        m_particle_type.push_back(newType);
        m_nParticleType = m_particle_type.size();
    }
}

const void Particle::addParticleType(ParticleType *particleType) {
    if (m_nParticleType < m_maxNumParticleType) {
        m_particle_type.push_back(particleType);
        m_nParticleType = m_particle_type.size();
    }
};

// unsigned int, const print
void Particle::setIndex(int index) {
    if (index <= m_nParticleType) {
        m_index = index;
    }
}

void Particle::setIndex(std::string name) {
    if (findParticle(name) != -1) {
        m_index = findParticle(name);
    }
}

void Particle::printArray() {
    for (int i{}; i < m_nParticleType; i++) {
        std::cout << "Index:" << i << std::endl;
        m_particle_type[i]->print();
        std::cout << std::endl;
    }
}
std::array<double, 3> Particle::getImpulse() const { return m_impulseVector; }

void Particle::print() {
    std::cout << "Index:" << m_index << std::endl;
    std::cout << "Name:" << m_particle_type[m_index]->getName() << std::endl;
    std::cout << "Impulse: (" << m_impulseVector[0] << "," << m_impulseVector[1]
              << "," << m_impulseVector[2] << ")" << std::endl;
}

double Particle::getMass() const { return m_particle_type[m_index]->getMass(); }

double Particle::getEnergy() const {
    double energy{sqrt(pow(m_particle_type[m_index]->getMass(), 2) +
                       pow(m_impulseVector[0], 2) + pow(m_impulseVector[1], 2) +
                       pow(m_impulseVector[2], 2))};
    return energy;
}

double Particle::getInvariantMass(Particle other) const {
    double invariantMass{
        sqrt(pow(getEnergy() + other.getEnergy(), 2) -
             pow(m_impulseVector[0] + other.getImpulse()[0], 2) -
             pow(m_impulseVector[1] + other.getImpulse()[1], 2) -
             pow(m_impulseVector[2] + other.getImpulse()[2], 2))};
    return invariantMass;
}

void Particle::setImpulse(double impulseX, double impulseY, double impulseZ) {

    m_impulseVector[0] = impulseX;
    m_impulseVector[1] = impulseY;
    m_impulseVector[2] = impulseZ;
};

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
    if (getMass() == 0.0) {
        printf("Decayment cannot be preformed if mass is zero\n");
        return 1;
    }

    double massMot = getMass();
    double massDau1 = dau1.getMass();
    double massDau2 = dau2.getMass();

    if (m_index > -1) { // add width effect ???

        // gaussian random numbers

        float x1, x2, w, y1;

        double invnum = 1. / RAND_MAX;
        do {
            x1 = 2.0 * rand() * invnum - 1.0;
            x2 = 2.0 * rand() * invnum - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;

        massMot += m_particle_type[m_index]->getWidth() * y1;
    }

    if (massMot < massDau1 + massDau2) {
        printf("Decayment cannot be preformed because mass is too low in this "
               "channel\n");
        return 2;
    }

    double pout = sqrt((massMot * massMot -
                        (massDau1 + massDau2) * (massDau1 + massDau2)) *
                       (massMot * massMot -
                        (massDau1 - massDau2) * (massDau1 - massDau2))) /
                  massMot * 0.5;

    double norm = 2 * M_PI / RAND_MAX;

    double phi = rand() * norm;
    double theta = rand() * norm * 0.5 - M_PI / 2.;
    dau1.setImpulse(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
                    pout * cos(theta));
    dau2.setImpulse(-pout * sin(theta) * cos(phi),
                    -pout * sin(theta) * sin(phi), -pout * cos(theta));

    double energy = sqrt(getImpulse()[0] * getImpulse()[0] +
                         getImpulse()[1] * getImpulse()[1] +
                         getImpulse()[2] * getImpulse()[2] + massMot * massMot);

    double bx = getImpulse()[0] / energy;
    double by = getImpulse()[1] / energy;
    double bz = getImpulse()[2] / energy;

    dau1.Boost(bx, by, bz);
    dau2.Boost(bx, by, bz);

    return 0;
}

void Particle::Boost(double bx, double by, double bz) {

    double energy = getEnergy();

    // Boost this Lorentz vector
    double b2 = bx * bx + by * by + bz * bz;
    double gamma = 1.0 / sqrt(1.0 - b2);
    double bp =
        bx * getImpulse()[0] + by * getImpulse()[1] + bz * getImpulse()[2];
    double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

    getImpulse()[0] += gamma2 * bp * bx + gamma * bx * energy;
    getImpulse()[1] += gamma2 * bp * by + gamma * by * energy;
    getImpulse()[2] += gamma2 * bp * bz + gamma * bz * energy;
}

double Particle::getTransverseImpulse() {
    double module = sqrt(pow(getImpulse()[0], 2) + pow(getImpulse()[1], 2));
    return module;
}