//==============================================================
// Copyright © 2021 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <algorithm>
#include <CL/sycl.hpp>

  // NEW include FOR THIS EXERCISE - so we can use Intel FPGA as a target
#include <CL/sycl/INTEL/fpga_extensions.hpp>

using namespace cv;
using namespace std;
using namespace sycl;

int main(){
  string image_path = "NermalWithBook540.jpg";

  // NEW (2 lines) FOR THIS EXERCISE (was just "queue q;" before) - now we use the FPGA emulator
  INTEL::fpga_emulator_selector my_selector;
  queue q( my_selector );

  // for this exercise, we did not control what type of device we are offloading to,
  // so this output will tell us what we were assigned
  std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;

  Mat img = imread(image_path, IMREAD_COLOR);
  if(img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return 1;
  }

  {
    CV_Assert(img.isContinuous());
    CV_CheckTypeEQ(img.type(), CV_8UC3, "");
    buffer<uint8_t, 3> frame_buffer(img.data, range<3>(img.rows, img.cols, 3));

    q.submit([&](handler& cgh) {
      auto pixels = frame_buffer.get_access<access::mode::read_write>(cgh);
      cgh.parallel_for(range<3>(img.rows, img.cols, 3), [=](item<3> item) {
        uint8_t p = pixels[item];
        pixels[item] = sycl::clamp(p+50,0,255);
      });
    });
    q.wait_and_throw();
  }

  imwrite("EnlightenedNermalWithBook.png", img);

  return 0;
}
