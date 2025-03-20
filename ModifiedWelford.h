#ifndef FILTER_MODIFIEDWELFORD_H_
#define FILTER_MODIFIEDWELFORD_H_

class ModifiedWelford {
 public:
    explicit ModifiedWelford(unsigned int window_size = 5);
    ModifiedWelford &operator=(const ModifiedWelford &) = delete;
    ModifiedWelford(ModifiedWelford const &) = delete;
    ~ModifiedWelford();

    void AddSample(double new_value);
    void Clear();
    double GetMean();
    double GetVariance();
    double GetDeviation();

 protected:
    double *window_;

 private:
    unsigned int window_size_;
    unsigned int count_;
    double mean_;
    double m2_;  // aggregates the squared distance from the mean
    double sum_;
    double sum_squares_;
    double oldest_value_;
    unsigned int window_index_;
};

#endif  // FILTER_MODIFIEDWELFORD_H_
