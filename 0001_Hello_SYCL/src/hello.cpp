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

using namespace cv;
using namespace std;
using namespace sycl;

int main(){
  string image_path = "NermalWithBook540.jpg";
    
  //# define queue which has default device associated for offload
  queue q;
  // for this exercise, we did not control what type of device we are offloading to,
  // so this output will tell us what we were assigned
  std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;

  Mat img = imread(image_path, IMREAD_COLOR);
  if(img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return 1;
  }

#if 0
  // the SYCL kernel, after the endif, will do the same as this C++ code would do
  for( int y = 0; y < img.rows; y++ ) {
    for( int x = 0; x < img.cols; x++ ) {
      for( int c = 0; c < img.channels(); c++ ) {
        img.at<Vec3b>(y,x)[c] =
          clamp( img.at<Vec3b>(y,x)[c] + 50, 0, 255 );
      }
    }
  }
#endif
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
