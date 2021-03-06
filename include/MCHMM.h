#include <iostream>
#include <vector>
#include <tuple>
#include "Sample.h"
#include "Observation.h"
#include "DETree.h"
using namespace std;

#ifndef MCHMM_H
#define MCHMM_H

class MCHMM{

private:

    // Model parameters
    vector<Sample> *pi;     // Initial State Distribution
    vector<Sample> *m;      // Transition Model
    vector<Sample> *v;      // Observation Model

    DETree *pi_tree;        // Density Tree used for PI distribution
    DETree *v_tree;         // Density Tree used for V distribution
    DETree *m_tree;         // Density Tree used for M distribution

    vector<double> *pi_low_limit = NULL;
    vector<double> *pi_high_limit = NULL;

    vector<double> *m_low_limit = NULL;
    vector<double> *m_high_limit = NULL;

    vector<double> *v_low_limit = NULL;
    vector<double> *v_high_limit = NULL;

    bool initialized = false;

    double rho = 1.0;
    double rho_bar = 0.5;
    double eta = 1.2;

    size_t max_sample_size = 100;


public:
    MCHMM();

    void init_hmm_randomly(int sample_size_pi, int sample_size_m, int sample_size_v);
    void set_limits(vector<double> *pi_low_limit, vector<double> *pi_high_limit,
                    vector<double> *m_low_limit, vector<double> *m_high_limit,
                    vector<double> *v_low_limit, vector<double> *v_high_limit
                    );
    void set_distributions(vector<Sample> * pi, vector<Sample> * m, vector<Sample> * v, double rho);
    void learn_hmm(vector<Observation> *observations, size_t max_iteration, int N);
    void learn_hmm_KL(vector<Observation> *observations, double threshold, size_t max_iteration, int N);
    DETree * forward(vector<Observation> *observations, size_t N);
    DETree * forward_one_step(vector<Observation> *observations, size_t N, DETree * old_alpha); // Not implemented
    vector<DETree *> gamma(vector<Observation> *observations, size_t N);
    double KLD_compute(vector<double> P, vector<double> Q);
    vector<Sample> get_uniform_samples_from_pi(size_t N);

    double _rho();
    bool initialized_();
    DETree* pi_tree_();
};

#endif
