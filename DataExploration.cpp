#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;                                // Use the standard namespace

vector<double> rm;                                  // Declare vectors
vector<double> medv;

// Declare functions
double sum(vector<double> v) {  
    double s = 0;   
    for (int i = 0; i < v.size(); i++) {
        s += v[i];
    }
    return s;
}

double mean(vector<double> v) {
    return sum(v) / v.size();
}

double median(vector<double> v) {
    sort(v.begin(), v.end());
    int n = v.size();
    if (n % 2 == 0) {
        return (v[n / 2 - 1] + v[n / 2]) / 2;
    } else {
        return v[n / 2];
    }
}

double range(vector<double> v) {
    return *max_element(v.begin(), v.end()) - *min_element(v.begin(), v.end());
}
// Covariance and correlation by pg.74
double covariance(vector<double> x, vector<double> y) {
    int n = x.size();
    double mean_x = mean(x);
    double mean_y = mean(y);
    double cov = 0;
    for (int i = 0; i < n; i++) {
        cov += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return cov / (n - 1);
}

double variance(vector<double> x, vector<double> y) {
    return covariance(x, y);
}

double correlation(vector<double> x, vector<double> y) {
    return covariance(x, y) / sqrt(variance(x, x) * variance(y, y));
}

// Main function
int main() {
    // Read data from file
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_SIZE = 1000;
    vector<double> rm(MAX_SIZE);
    vector<double> medv(MAX_SIZE);

    cout << "*** Opening file Boston.csv ***" << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "!!! Could not open file Boston.csv !!!" << endl;
        return 1;                                                       // 1 indicates error
    }

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    cout << "Heading: " << line << endl;                                

    int numObservations = 0;
    while (inFS.good()){
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm[numObservations] = stod(rm_in);                                          // Convert string to double                       
        medv[numObservations] = stod(medv_in);
        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "new length: " << rm.size() << endl;

    cout << "*** Closing file Boston.csv ***" << endl;
    inFS.close();
    
    cout << "\nNumber of records: " << numObservations << endl;



    // Call functions for rm vector
    cout << "\nResults for rm:" << endl;
    cout << "Sum: " << sum(rm) << endl;
    cout << "Mean: " << mean(rm) << endl;
    cout << "Median: " << median(rm) << endl;
    cout << "Range: " << range(rm) << endl;

    // Call functions for medv vector
    cout << "\nResults for medv:" << endl;
    cout << "Sum: " << sum(medv) << endl;
    cout << "Mean: " << mean(medv) << endl;
    cout << "Median: " << median(medv) << endl;
    cout << "Range: " << range(medv) << endl;

    // Call functions for covariance and correlation
    cout << "\nCovariance: " << covariance(rm, medv) << endl;
    cout << "Correlation: " << correlation(rm, medv) << endl;

    return 0;

}
