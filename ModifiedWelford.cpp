#include "filter/ModifiedWelford.h"
#include <cmath>

ModifiedWelford::ModifiedWelford(unsigned int window_size)
        : window_(new double[window_size]),
          window_size_(window_size),
          count_(0),
          mean_(0),
          m2_(0),
          sum_(0),
          sum_squares_(0),
          oldest_value_(0),
          window_index_(0) {
}

ModifiedWelford::~ModifiedWelford() {
    delete[] window_;
}

void ModifiedWelford::AddSample(double new_value) {
    if (count_ < window_size_) {
        count_++;
    } else {
        oldest_value_ = window_[window_index_];
        sum_ -= oldest_value_;
        sum_squares_ -= oldest_value_ * oldest_value_;
    }

    window_[window_index_] = new_value;
    window_index_ = (window_index_ + 1) % window_size_;

    sum_ += new_value;
    sum_squares_ += new_value * new_value;
    mean_ = sum_ / count_;
    m2_ = sum_squares_ - (sum_ * sum_ / count_);  // Welford Algorithm
    if (m2_ < 0) {
        m2_ = 0;
    }
}

double ModifiedWelford::GetMean() {
    return mean_;
}

double ModifiedWelford::GetVariance() {
    if (count_ < window_size_) {
        return 0.0;
    }
    return m2_ / (count_ - 1);
}

double ModifiedWelford::GetDeviation() {
    return std::sqrt(GetVariance());
}

void ModifiedWelford::Clear() {
    count_ = 0;
    mean_ = 0;
    m2_ = 0;
    sum_ = 0;
    sum_squares_ = 0;
    window_index_ = 0;
    oldest_value_ = 0;
    for (unsigned int i = 0; i < window_size_; ++i) {
        window_[i] = 0;
    }
}
