#include "frame_counter.h"

#include <iostream>

FrameCounter::FrameCounter(
    const std::string& name,
    double print_frequency_seconds,
    unsigned print_moving_average_length)
  : name_(name),
    print_frequency_seconds_(print_frequency_seconds),
    print_moving_average_length_(print_moving_average_length),
    last_print_message_(0),
    total_seconds_(0),
    frame_counts_() {}

void FrameCounter::report_frame(double seconds_passed) {
  if (frame_counts_.size() == 0 ||
      int(total_seconds_ + seconds_passed) - int(total_seconds_) >= 1) {
    frame_counts_.push_back(0);
  }
  total_seconds_ += seconds_passed;
  frame_counts_.back() += 1;

  if (total_seconds_ > last_print_message_ + print_frequency_seconds_ &&
      frame_counts_.size() > 1) {
    while (frame_counts_.size() > print_moving_average_length_ + 1) {
      frame_counts_.erase(frame_counts_. begin());
    }
    int total_frames = 0;
    for (int i = 0; i < frame_counts_.size() - 1; ++i) {
      total_frames += frame_counts_[i];
    }
    average_frames_ = double(total_frames) / (frame_counts_.size() - 1);
    last_print_message_ = total_seconds_;
  }
}

double FrameCounter::get_average_frames() const {
  return average_frames_;
}
