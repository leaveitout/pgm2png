#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>


constexpr auto NUM_ARGS = 2UL;


auto printHelp () noexcept -> void {
  std::cout << "Tool to convert 16 Bit PGM file representing a depth image to a png." << std::endl;
  std::cout << "The output will be in the same scale as the input (i.e. mm -> mm)." << std::endl;
  std::cout << "Usage: " << std::endl;
  std::cout << "pgm2png input.pgm output.png" << std::endl;
}


auto read16BitPGM (std::string const & image_path) -> cv::Mat {
  cv::Mat destination;
  std::ifstream in {image_path.c_str (), std::ios::binary};
  if (!in.is_open ()) {
    auto ss = std::stringstream {};
    ss << "Unable to open image file: " << image_path;
    throw std::invalid_argument (ss.str ().c_str ());
  }

  // Read metadata
  auto magic = std::string {};
  unsigned height, width, max_value;
  in >> magic;
  in >> height;
  in >> width;
  in >> max_value;
  in.ignore (64, '\n');
  auto const num_bytes = 2UL * height * width;
  in.read ((char *) destination.data, num_bytes);
  in.close ();
  return destination;
}


auto savePng (cv::Mat const & depth_image, std::string const & output_path) -> void {
  if (!cv::imwrite (output_path, depth_image)) {
    auto ss = std::stringstream {};
    ss << "Unable to save image file: " << output_path;
    throw std::invalid_argument (ss.str ());
  }
}


auto main (int argc, char ** argv) -> int {
  try {
    if (argc < NUM_ARGS + 1) {
      auto ss = std::stringstream {};
      ss << "Not enough arguments.";
      throw std::invalid_argument (ss.str ());
    }
    savePng (read16BitPGM (argv[1]), argv[2]);
  } catch (std::exception const & exception) {
    std::cerr << exception.what () << std::endl;
    printHelp ();
    return -1;
  }

  return 0;
}